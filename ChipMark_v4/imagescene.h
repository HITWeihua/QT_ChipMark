#ifndef IMAGESCENE_H
#define IMAGESCENE_H
#include <QGraphicsScene>
#include <QDebug>
#include <qgraphicssceneevent.h>
#include <QGraphicsItem>
class ImageScene : public QGraphicsScene
{
    Q_OBJECT
public:
    ImageScene();
protected:
   // void keyPressEvent(QKeyEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
signals:
    void ItemMove();
    void ItemPress(QGraphicsItem *q);
public slots:
};

#endif // IMAGESCENE_H
