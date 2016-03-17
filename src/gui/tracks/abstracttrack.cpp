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
#include <QGraphicsDropShadowEffect>

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


    mShadowEffect = new QGraphicsDropShadowEffect();
    mShadowEffect->setBlurRadius(50);
    setGraphicsEffect(mShadowEffect);
    mShadowEffect->setEnabled(false);


    setAcceptHoverEvents(true);

    // Debug Height
    setHeight(30+qrand()%270);
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
    emit resized();
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

void AbstractTrack::updateSlotTop(int slotTop)
{
    if (isSelected())
    {
        return;
    }

    mSlotGhostTop = slotTop;
    mSlotTop = slotTop;

    // Todo @IDK : force the redraw of the track...
    setPos(0,slotTop);
    update();
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
                QString("%1 0x%2 - %3 [%4-%5]\nSlot n°%6")
                .arg(mSlotIndex)
                .arg((quintptr)this, QT_POINTER_SIZE * 2, 16, QChar('0'))
                .arg(chromosom)
                .arg(start)
                .arg(end)
                .arg(mSlotIndex)
                );


    painter->drawText(boundingRect().left()+100, boundingRect().center().y(), QString::number(start));
    painter->drawText(boundingRect().right()-100, boundingRect().center().y(), QString::number(end));
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
    //painter->setRenderHint(QPainter::Antialiasing);


    // -------------------------
    // Draw Track Global Background
    // -------------------------
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


    // -------------------------
    // Draw Track Handle
    // -------------------------

    // Background
    QRect toolbarRect =  boundingRect().toRect();
    toolbarRect.setWidth(30);
    QStyleOption op;
    op.rect = toolbarRect;

    // Forground
    QColor base = qApp->style()->standardPalette().dark().color();
    QColor activeColor = base.darker(250);
    QColor inactiveColor = base.darker(120);// inactiveColor.setAlpha(200);

    painter->setBrush(base);
    painter->drawRect(toolbarRect);
    qApp->style()->drawPrimitive(QStyle::PE_PanelMenu, &op,painter);


    // Rubber
    QVariantMap handleIcon;
    QPoint handleIconPos = QPoint(toolbarRect.left() + 5, toolbarRect.top() + toolbarRect.height() / 2 - 10);
    handleIcon.insert( "color" , isUnderMouse() ? activeColor : inactiveColor);
    painter->drawPixmap(handleIconPos, App::awesome()->icon(fa::bars, handleIcon).pixmap(20,20));


    // Icon "Track Options"
    QVariantMap settingIcon;
    QColor settingIconColor = isSelected() ? inactiveColor : base;
    settingIcon.insert( "color" , settingIconColor);
    QPoint settingIconPos = QPoint(toolbarRect.left() + 5, toolbarRect.top() + 5);
    painter->drawPixmap(settingIconPos, App::awesome()->icon(fa::wrench, settingIcon).pixmap(20,20));


    // -------------------------
    // Draw Track Content
    // -------------------------

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
            mShadowEffect->setEnabled(true);
        }
        else
        {
            setZValue(0);
            mShadowEffect->setEnabled(false);
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
