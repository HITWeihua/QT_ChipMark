#include "imageview.h"
#include <QWheelEvent>
#include "itemrect.h"
#include "chipsot.h"
#include <QGraphicsScene>

ImageView::ImageView()
{

}

void ImageView::wheelEvent(QWheelEvent *e)
{
    QGraphicsView::wheelEvent(e);
    if (e->modifiers() & Qt::ControlModifier) {
        if (e->delta() > 0)
            zoomIn(6);
        else
            zoomOut(6);
        e->accept();
    } else {
        QGraphicsView::wheelEvent(e);
    }
}

void ImageView::zoomIn(int value)
{

}

void ImageView::zoomOut(int value)
{

}

void ImageView::mouseMoveEvent(QMouseEvent *e)
{
    qDebug()<<"ImageView::mouseMoveEvent"<<e->pos();
    QGraphicsView::mouseMoveEvent(e);
    update();
}
