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
    :QGraphicsObject(parent),
      mHeight(30+qrand()%270),
      mHeightMax(600),
      mHeightMin(10),
      mIsResizable(true),
      mIsSelected(false),
      mSlotModeON(false),
      mSlotIndex(0),
      mSlotTop(0),
      mSlotGhostTop(0),
      mCursorPosition(0)

{
    setFlag(QGraphicsItem::ItemIsMovable);
    //setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    //setFlag(QGraphicsItem::ItemIsSelectable);

    mAnimation    = new QPropertyAnimation(this,"pos");
    mShadowEffect = new QGraphicsDropShadowEffect();
    mShadowEffect->setBlurRadius(50);
    mShadowEffect->setEnabled(false);

    setGraphicsEffect(mShadowEffect);
    setAcceptHoverEvents(true);

}

AbstractTrack::~AbstractTrack()
{
    disconnect(this, 0, 0, 0);
    delete mAnimation;
    delete mShadowEffect;
}



void AbstractTrack::setTrackList(TrackListWidget *parent)
{
    // @IDK : If mTrackList != null, need to unconnect
    disconnect(this, 0, 0, 0);

    mTrackList = parent;

    connect(mTrackList,SIGNAL(cursorChanged(int, quint64, int, int)),
            this,SLOT(updateCursor(int, quint64, int, int)));
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

void AbstractTrack::updateSelection()
{
    // Need to clear cache to force redraw of all tracks
    mContentCache = QImage();
    update();
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

void AbstractTrack::setIndex(int slotIdx)
{
    mSlotIndex = slotIdx;
}

int AbstractTrack::index() const
{
    return mSlotIndex;
}

void AbstractTrack::setTop(int slotTop)
{
    mSlotTop = slotTop;
    mSlotGhostTop = slotTop;
}

int AbstractTrack::top() const
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
    if (isTrackSelected())
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
}
QRectF AbstractTrack::boundingRectContent() const
{
    QRectF b = boundingRect();
    b.setLeft(mTrackList->C_TRACK_HANDLE_PIXEL_WIDTH);
    b.setWidth(mTrackList->trackContentWidth());
    return b;
}

void AbstractTrack::paintRegion(QPainter *painter, const QString &chromosom, quint64 start, quint64 end)
{
    // Cache management : we redraw content only if needed
    if (!isUnderMouse() && mContentCache.rect() == boundingRect())
    {
        return;
    }

    // qDebug() << " - redraw content";

    // Init painter for drawing in cache image
    mContentCache = QImage(QSize(boundingRect().width(), boundingRect().height()), QImage::Format_ARGB32_Premultiplied);
    QPainter contentPainter;
    mContentCache.fill(0);
    contentPainter.begin(&mContentCache);


    // Default implementation draw some usefull debug informations
    // This method must be overriden by children classes
    contentPainter.drawText(
                boundingRectContent(),
                Qt::AlignCenter,
                QString("%1 0x%2 - %3 [%4-%5]\nSlot n°%6")
                .arg(mSlotIndex)
                .arg((quintptr)this, QT_POINTER_SIZE * 2, 16, QChar('0'))
                .arg(chromosom)
                .arg(start)
                .arg(end)
                .arg(mSlotIndex)
                );


    contentPainter.drawText(boundingRectContent().left()+100, boundingRectContent().center().y(), QString::number(start));
    contentPainter.drawText(boundingRectContent().right()-100, boundingRectContent().center().y(), QString::number(end));


    contentPainter.end();
}





void AbstractTrack::goToSlotPosition()
{
    if (isTrackSelected())
    {
        return;
    }
    if (mAnimation->state() == QAbstractAnimation::Running)
    {
        mAnimation->stop();
    }

    mAnimation->setStartValue(pos());
    mAnimation->setEndValue((mSlotModeON) ? QPointF(0,mSlotGhostTop) : QPointF(0,mSlotTop));
    mAnimation->setDuration(200);
    mAnimation->setEasingCurve(QEasingCurve::InOutCubic);
    mAnimation->start();
}


void AbstractTrack::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);


    //qDebug() << "paint track " << mSlotIndex;



    painter->setPen(Qt::black);


    // -------------------------
    // Draw Track Global Background
    // -------------------------
    if (isTrackSelected())
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
    // Draw Track Content
    // -------------------------
    // We let the track redraw its content only if needed (paintRegionMethod draw in cache : mContentCache)
    this->paintRegion(painter, chromosom(), start(), end());

    // Content is cached so redraw the cached image and draw cursor over it
    painter->drawImage(boundingRect(), mContentCache);
    paintCursorLayer(painter);



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
    painter->setPen(Qt::black);
    painter->drawRect(toolbarRect);
    qApp->style()->drawPrimitive(QStyle::PE_PanelMenu, &op,painter);


    // Rubber
    QVariantMap handleIcon;
    QPoint handleIconPos = QPoint(toolbarRect.left() + 5, toolbarRect.top() + toolbarRect.height() / 2 - 10);
    handleIcon.insert( "color" , isUnderMouse() ? activeColor : inactiveColor);
    painter->drawPixmap(handleIconPos, App::awesome()->icon(fa::bars, handleIcon).pixmap(20,20));


    // Icon "Track Options"
    QVariantMap settingIcon;
    QColor settingIconColor = isTrackSelected() ? inactiveColor : base;
    settingIcon.insert( "color" , settingIconColor);
    QPoint settingIconPos = QPoint(toolbarRect.left() + 5, toolbarRect.top() + 5);
    painter->drawPixmap(settingIconPos, App::awesome()->icon(fa::wrench, settingIcon).pixmap(20,20));


}


void AbstractTrack::updateCursor(int posX,quint64 posB, int baseX, int baseW)
{
    update();
}

void AbstractTrack::paintCursorLayer(QPainter * painter)
{
    QColor baseColor = qApp->style()->standardPalette().highlight().color();
    painter->setPen(baseColor);

    if (mTrackList->sharedCursorBaseW() > 2)
    {
        QColor bg = baseColor.lighter(150);
        bg.setAlpha(100);
        painter->setBrush(bg);
        painter->drawRect(mTrackList->sharedCursorBaseX(), 0, mTrackList->sharedCursorBaseW(), boundingRectContent().height());
    }
    else
    {
        painter->drawLine(mTrackList->sharedCursorPosX(), 0, mTrackList->sharedCursorPosX(), boundingRectContent().height());
    }
}




void AbstractTrack::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    // default
    QGraphicsObject::mouseDoubleClickEvent(event);
}

void AbstractTrack::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    // Manage track rearrangment
    if (isTrackSelected())
    {
        if (mSlotModeON && isTrackSelected())
        {
            trackList()->slotReordering(this);
        }

        // Default
        QGraphicsObject::mouseMoveEvent(event);
        return;
    }


    // Manage resize of the track
    if (isResizable() && cursor().shape() == Qt::SizeVerCursor)
    {
        QRectF oldRect = boundingRect();
        setHeight(event->pos().y());
        update(oldRect);
        trackList()->updateTracksHeight();
    }

    // Manage scrolling
    QPoint newCursorPos = QPoint(event->pos().x(), event->pos().y());
    int deltaX = mCursorPosition - newCursorPos.x();
    mTrackList->trackScroll(deltaX);
    mCursorPosition =  newCursorPos.x();

    // Manage and share the position of the cursor
    mTrackList->updateSharedCursor(newCursorPos);



}

void AbstractTrack::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    QRect trackHandle = boundingRect().toRect();
    trackHandle.setWidth(40);

    if (trackHandle.contains( event->pos().toPoint()))
    {
        setTrackSelected(true);
        setFlag(QGraphicsItem::ItemIsMovable,true);
        trackList()->switchSlotMode(true);
    }
    else
    {
        setFlag(QGraphicsItem::ItemIsMovable,false);
        trackList()->switchSlotMode(false);
        setTrackSelected(false);
        mCursorPosition =  event->pos().x();
    }

    // Set movable only if cursor select the toolbar
    //QGraphicsObject::mousePressEvent(event);
}

void AbstractTrack::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    setTrackSelected(false);
    trackList()->switchSlotMode(false);

    //QGraphicsObject::mouseReleaseEvent(event);
}

void AbstractTrack::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    // Manage and share the position of the cursor
    mTrackList->updateSharedCursor(QPoint(event->pos().x(), event->pos().y()));

    // Mange resing feedback of the track
    if (isResizable())
    {
        QRect bottomLine;
        bottomLine.setWidth(boundingRect().width());
        bottomLine.setTop(height()-10);
        bottomLine.setBottom(height());

        if (bottomLine.contains(event->pos().toPoint()))
            setCursor(Qt::SizeVerCursor);
        else
            setCursor(Qt::ArrowCursor);
    }



    QGraphicsObject::hoverMoveEvent(event);
}

void AbstractTrack::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    setFocus();
    QGraphicsObject::hoverEnterEvent(event);
}

void AbstractTrack::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    QGraphicsObject::hoverLeaveEvent(event);
}






bool AbstractTrack::isTrackSelected() const
{
    return mIsSelected;
}
void AbstractTrack::setTrackSelected(bool selected)
{
    mIsSelected = selected;
    setZValue((selected) ? 10 : 0);
    mShadowEffect->setEnabled(selected);
}

bool AbstractTrack::isResizable() const
{
    return mIsResizable;
}
void AbstractTrack::setResizable(bool isResizable)
{
    mIsResizable = isResizable;
}

}} // end namespace
