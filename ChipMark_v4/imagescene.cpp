#include "imagescene.h"

ImageScene::ImageScene()
{


}

void ImageScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug()<<"ImageScene::mouseMoveEvent: scenePos::"<<event->scenePos();
    QGraphicsScene::mouseMoveEvent(event);
    if(mouseGrabberItem() == NULL)
    {

    }
    else
    {
        emit ItemMove();
        qDebug()<<"Current Item Pos" << mouseGrabberItem()->pos();
    }
    update();
}

void ImageScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug()<< "ImageScene::Doubleclick";
    QGraphicsScene::mouseDoubleClickEvent(event);
    emit ItemPress(mouseGrabberItem());
}

void ImageScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mousePressEvent(event);
    emit ItemPress(mouseGrabberItem());
}
