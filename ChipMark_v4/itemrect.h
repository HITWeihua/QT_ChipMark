#ifndef ITEMRECT_H
#define ITEMRECT_H

#include <QGraphicsItem>
#include <QPoint>
#include <QPainter>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include "item.h"

class ItemRect : public Item
{
public:
    qreal cenx;
    qreal ceny;
    qreal width;
    qreal height;
    QColor brushcolor = QColor(255,0,255,100);
public:
    ItemRect();
    //(cenx,ceny): Rect center position relative to Chip(ItemGroup)
    //Item
    ItemRect(qreal cenx, qreal ceny, qreal width, qreal height);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget);
    QColor setBrushColor(QString colorName);
    virtual void InitFromScenePos(qreal Scenecenx, qreal Sceneceny, qreal width, qreal height) override;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
};


#endif // ITEMRECT_H
