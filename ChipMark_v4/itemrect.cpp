#include "itemrect.h"
#include <QGraphicsItem>
#include <QCursor>
#include <QKeyEvent>

ItemRect::ItemRect()
{
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
}

ItemRect::ItemRect(qreal cenx, qreal ceny, qreal width, qreal height)
{
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    this->cenx = cenx;
    this->ceny = ceny;
    setPos(cenx,ceny);
    setData(0,width);
    setData(1,height);
    this->width = data(0).toInt();
    this->height = data(1).toInt();

}

void ItemRect::InitFromScenePos(qreal Scenecenx, qreal Sceneceny, qreal width, qreal height)
{
    QPointF point = this->mapToParent( this->mapFromScene( QPointF(Scenecenx,Sceneceny)));
    this->cenx = point.x();
    this->ceny = point.y();
    setPos(cenx,ceny);
    setData(0,width);
    setData(1,height);
    this->width = data(0).toInt();
    this->height = data(1).toInt();
}

QColor ItemRect::setBrushColor(QString colorName)
{
  brushcolor = QColor(colorName)  ;
  brushcolor.setAlpha(127);
  return brushcolor;
}

void ItemRect::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget)
{
    cenx = pos().x();
    ceny = pos().y();
    this->width = data(0).toInt();
    this->height = data(1).toInt();
    QRectF recf = QRectF(-width/2,-height/2,width,height);
    brushcolor = QColor(data(2).toString());
    brushcolor.setAlpha(127);
    painter->setBrush(brushcolor);
    painter->drawRect(recf);
}

void ItemRect::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    setFocus();
    QGraphicsItem::mousePressEvent(event);
    update();
}

void ItemRect::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug()<<" ItemRect:: "<<event->scenePos();
    QGraphicsItem::mouseMoveEvent(event);
    update();
}

void ItemRect::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    setSelected(true);
    setFocus();
    if(isSelected())
        qDebug()<< "ItemRect has been selected";
    else qDebug() << "ItemRect NO selected";
    QGraphicsItem::mouseDoubleClickEvent(event);
    update();
}

void ItemRect::keyPressEvent(QKeyEvent *event)
{

}

QRectF ItemRect::boundingRect() const
{
    return QRectF(-width/2,-height/2,width,height);
}
