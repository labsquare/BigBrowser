#include "abstracttrack.h"
#include <QPainter>
#include <QDebug>
#include <QStyle>
#include <QApplication>
#include <QGraphicsScene>
#include <QVariantMap>
#include <QStyleOptionProgressBar>
#include <QStyleOptionFrame>
#include <QStyleOptionRubberBand>
#include "app.h"
#include "tracklistwidget.h"

namespace big {
namespace gui {



AbstractTrack::AbstractTrack(QGraphicsItem *parent)
    :QGraphicsObject(parent)
{
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    setFlag(QGraphicsItem::ItemIsSelectable);

    mAnimation = new QPropertyAnimation(this,"y");
    mSlotModeON = false;

    setHeight(30+qrand()%270);

    setAcceptHoverEvents(true);

}



void AbstractTrack::setTrackList(TrackListWidget *parent)
{
    mTrackList = parent;
}

TrackListWidget *AbstractTrack::trackList() const
{
    return mTrackList;
}

int AbstractTrack::height() const
{
    return mHeight;
}

void AbstractTrack::setHeight(int h)
{
    mHeight = h;
}




void AbstractTrack::setSlotMode(bool slotModeON)
{
    if (mSlotModeON != slotModeON)
    {
        mSlotModeON = slotModeON;
        if (!slotModeON && (mSlotTop != mSlotGhostTop || pos().y() != mSlotGhostTop))
        {
            mSlotTop = mSlotGhostTop;
            goToSlotPosition();
        }
        update();
    }
}

bool AbstractTrack::slotMode() const
{
    return mSlotModeON;
}

int AbstractTrack::setSlotIndex(int slotIdx)
{
    mSlotIndex = slotIdx;
}

int AbstractTrack::slotIndex() const
{
    return mSlotIndex;
}

int AbstractTrack::setSlotTop(int slotTop)
{
    mSlotTop = slotTop;
    mSlotGhostTop = slotTop;
}

int AbstractTrack::slotTop() const
{
    return mSlotTop;
}

void AbstractTrack::updateSlotPosition(int slotIndex, int slotGhostTop)
{
    if (mSlotModeON && mSlotIndex != slotIndex)
    {
        mSlotIndex = slotIndex;
        mSlotGhostTop = slotGhostTop;
        goToSlotPosition();
    }
}

int AbstractTrack::matchSlot(int yPosition)
{
    // Top Out of the slot
    if (yPosition < mSlotTop)
        return -1;
    // Top In the slot
    if (yPosition <= mSlotTop + mHeight/2)
        return 1;
    // Bottom In the slot
    if (yPosition <= mSlotTop + mHeight)
        return 2;
    // Bottom Out of the slot
    return -2;
}





const QString &AbstractTrack::chromosom() const
{

    return trackList()->chromosom();

}

quint64 AbstractTrack::start() const
{
    return trackList()->start();

}

quint64 AbstractTrack::end() const
{
    return trackList()->end();

}



QRectF AbstractTrack::boundingRect() const
{
    int w = scene()->views().first()->width();
    return QRect(0,0,w,height());
    //return QRect(0,0,scene()->width(),mHeight);
}

void AbstractTrack::paintRegion(QPainter *painter, const QString &chromosom, quint64 start, quint64 end)
{
    // Default implementation draw some usefull debug informations
    // This method must be overriden by children classes
    painter->drawText(
                boundingRect(),
                Qt::AlignCenter,
                QString("%1 0x%2 - %3 [%4-%5]")
                .arg(mSlotIndex)
                .arg((quintptr)this, QT_POINTER_SIZE * 2, 16, QChar('0'))
                .arg(chromosom)
                .arg(start)
                .arg(end)
                );
}





void AbstractTrack::goToSlotPosition()
{
    if (isSelected())
    {
        return;
    }
    if (mAnimation->state() == QAbstractAnimation::Running)
    {
        mAnimation->stop();
    }

    mAnimation->setStartValue(pos().y());
    mAnimation->setEndValue((mSlotModeON) ? mSlotGhostTop : mSlotTop);
    mAnimation->setDuration(200);
    mAnimation->setEasingCurve(QEasingCurve::InOutCubic);
    mAnimation->start();
}


void AbstractTrack::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setPen(Qt::black);
    painter->setRenderHint(QPainter::Antialiasing);

    if (isSelected())
    {
        QColor col  =qApp->style()->standardPalette().color(QPalette::Highlight);
        col.setAlpha(50);
        QBrush brush(col);
        painter->setBrush(brush);
    }
    else
    {
        painter->setBrush(qApp->style()->standardPalette().color(QPalette::Base));
    }
    painter->drawRect(boundingRect());



    // Draw Track Handle
    QRect toolbarRect =  boundingRect().toRect();
    toolbarRect.setWidth(40);

    QStyleOption op;
    op.rect = toolbarRect;



    painter->setBrush(qApp->palette("QWidget").button());
    qApp->style()->drawPrimitive(QStyle::PE_PanelButtonTool, &op,painter);

    op.rect = toolbarRect;

    qApp->style()->drawControl(QStyle::CE_Splitter, &op,painter);

    painter->setPen(QPen(Qt::black));

    painter->drawText(boundingRect().left()+100, boundingRect().center().y(), QString::number(start()));
    painter->drawText(boundingRect().right()-100, boundingRect().center().y(), QString::number(end()));


    QVariantMap options;
    options.insert( "color" , qApp->style()->standardPalette().color(QPalette::WindowText));
    QPoint iconPos = toolbarRect.topLeft();
    iconPos += QPoint(10,10);
    painter->drawPixmap(iconPos, App::awesome()->icon(fa::cogs, options).pixmap(20,20));

//    QRect bottomLine;
//    bottomLine.setWidth(boundingRect().width());
//    bottomLine.setHeight(10);
//    bottomLine.setTop(height()-5);
//    bottomLine.setBottom(height());

//    painter->setBrush(QBrush(Qt::red));
//    painter->drawRect(bottomLine);


    // draw rubber
    //    QStyleOptionRubberBand bandOption;
    //    bandOption.shape = QRubberBand::Rectangle;
    //    bandOption.rect.setWidth(boundingRect().toRect().width()-100);
    //    bandOption.rect.setHeight(10);


    //    qApp->style()->drawControl(QStyle::CE_RubberBand, &bandOption, painter);






    //    QStyleOptionFrame frameOption;
    //    frameOption.features = QStyleOptionFrame::Rounded;
    //    frameOption.rect = boundingRect().toRect();

    //    qApp->style()->drawPrimitive(QStyle::PE_Frame,&frameOption, painter );



    // Set the bounds of the painter for the Content region
    // TODO

    // Call the method to draw the content of the Track
    this->paintRegion(painter, chromosom(), start(), end());

}




QVariant AbstractTrack::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemPositionChange)
    {
        QPointF pos  = value.toPointF();
        pos.setX(0);

        if (mSlotModeON && isSelected())
        {
            trackList()->slotReordering(this);
        }
        return pos;

    }

    // This part manage selection. A native feature of QGraphicsItem
    if ( change == QGraphicsItem::ItemSelectedHasChanged)
    {
        // if selection == True, move the item on the top , to be not hiddable by other track
        if ( value.toBool())
        {
            setZValue(10);
        }
        else
        {
            setZValue(0);
        }
    }

    return QGraphicsObject::itemChange(change,value);
}






void AbstractTrack::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    // default
    QGraphicsObject::mouseDoubleClickEvent(event);
}

void AbstractTrack::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{

    if (cursor().shape() == Qt::SizeVerCursor)
    {
        QRectF oldRect = boundingRect();
        setHeight(event->pos().y());
        update(oldRect);
        emit resized();


    }


    //Default
    QGraphicsObject::mouseMoveEvent(event);
}

void AbstractTrack::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    // Set movable only if cursor select the toolbar
    QGraphicsObject::mousePressEvent(event);

    QRect toolbarRect = boundingRect().toRect();
    toolbarRect.setWidth(40);

    if (toolbarRect.contains( event->pos().toPoint()))
    {
        setFlag(QGraphicsItem::ItemIsMovable,true);
        trackList()->switchSlotMode(true);
    }
    else
    {
        setFlag(QGraphicsItem::ItemIsMovable,false);
        trackList()->switchSlotMode(false);
    }
}

void AbstractTrack::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    setSelected(false);
    trackList()->switchSlotMode(false);
    QGraphicsObject::mouseReleaseEvent(event);
}

void AbstractTrack::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{

    QGraphicsObject::hoverEnterEvent(event);
}

void AbstractTrack::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{

    QRect bottomLine;
    bottomLine.setWidth(boundingRect().width());
    bottomLine.setTop(height()-10);
    bottomLine.setBottom(height());

    if (bottomLine.contains(event->pos().toPoint()))
        setCursor(Qt::SizeVerCursor);
    else
        setCursor(Qt::ArrowCursor);




    QGraphicsObject::hoverMoveEvent(event);
}

void AbstractTrack::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{

    QGraphicsObject::hoverLeaveEvent(event);
}








}} // end namespace
