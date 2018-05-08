#ifndef CHIPSOT_H
#define CHIPSOT_H
#include <QGraphicsItem>
#include <QPoint>
#include "chip.h"
#include "itemrect.h"
#include <QVector>
#include <QGraphicsSceneMouseEvent>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QColor>

class ChipSOTData :public ChipData
{
public:
    ChipSOTData()
    {
        Initpar();
    }
    ChipSOTData(int up,int down)
    {
        this->up = up;
        this->down = down;
        Initpar();
    }
public:
    bool Initpar()
    {        
        ChipType = "SOT";
        ChipChildType = "SOT" + QString::number(up*10 +down);
        DefaultChipPath = QString(DefaultChipFloder +"/"+ ChipChildType);
        if(QFile(DefaultChipPath +".json").exists())
        {
            readDataFromJson(DefaultChipPath +".json");
        }else{
            totalpin = up+down+2;
            NeedToSave = false;
            for(int i =0; i< totalpin;i++)
            {
                QVector<qreal> Item;
                Item.push_back(0);
                Item.push_back(0);
                Item.push_back(50);
                Item.push_back(50);
                Item.push_back(0);
                par.push_back(Item);
            }
        }
    }
public:
    virtual bool readDataFromJson(QString ModelPath) override;
    virtual bool writeDataToJson(QString filename) override;
};

class ChipSOT : public Chip
{
public:
    ChipSOT();
    ~ChipSOT();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget);
public:
    //---UP(1)---1.9---UP(2)---
    //-----------Body(0)---------
    //---DOWN1(3)--DOWN(4)-DOWN(5)---
public:
    void setCurData(ChipData *data);
    virtual bool InitFromData() override;
    virtual bool UpdateToData() override;
    virtual bool InitDefault() override;
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
};

#endif // CHIPSOT_H
