#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H

#include <QGraphicsView>
#include "chipsot.h"
#include <QMouseEvent>
#include <QDebug>
class QObject;
class MainWindow;

class ImageView : public QGraphicsView
{
Q_OBJECT
public:
    ImageView(MainWindow *m,QGraphicsView *q) : QGraphicsView(q), mainwindow(m) { }
    ImageView(MainWindow *m) : QGraphicsView(), mainwindow(m) { }
    ImageView();
    virtual ~ImageView()  {}
protected:
    void wheelEvent(QWheelEvent *) override;

public slots:
    void zoomIn(int level = 1);
    void zoomOut(int level = 1);
protected:
    //void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
public:
    MainWindow *mainwindow;
};

#endif // IMAGEVIEW_H
