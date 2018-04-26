#ifndef ITEM_H
#define ITEM_H
#include <QGraphicsItem>
#include <QCursor>
#include <QKeyEvent>
#include <QVariant>
class Item: public QGraphicsItem
{
public:
    Item();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget);
public:
    virtual void InitFromScenePos(qreal Scenecenx, qreal Sceneceny, qreal width, qreal height);
};

#endif // ITEM_H
