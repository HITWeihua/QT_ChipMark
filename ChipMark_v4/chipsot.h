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
        totalpin = (up+down)*2+1;
        for(int i =0; i< (up+down)*2+1;i++)
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
public:
    virtual bool readDataFromJson(QString ModelPath) override;
};

class ChipSOT : public Chip
{
public:
    ChipSOT();
    ChipSOT(int up,int down);
    ~ChipSOT();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget);
public:
    int up;
    int down;
    int totalpin = (up+down)*2 +1;
    bool hasBody;
    //ChipSOTData *CurData;
    void setCurData(ChipData *data);
    //---UF1(1)---1.9---UF2(3)---
    //---UR1(2)---------UR2(4)---
    //-----------Body(0)---------
    //---DR1(5)--DR2(7)-DR3(9)---
    //---DF1(6)--DF2(8)-DF3(10)--
public:
    virtual bool InitFromData() override;
    virtual bool UpdateToData() override;
    virtual bool InitDefault() override;
    virtual bool writeLabelModel(QString filename) override;
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
};

#endif // CHIPSOT_H
