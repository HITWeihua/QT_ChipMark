#ifndef CHIP_H
#define CHIP_H
#include <QGraphicsItemGroup>
#include "item.h"
#include "itemrect.h"
#include <QDebug>
#include <QStandardPaths>
class ChipData
{
public:
    ChipData();
    ~ChipData();
public:
    int up = 8;
    int down = 8;
    int totalpin = up + down + 2;
    bool NeedToSave = false;
    QString  DefaultChipFloder = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    QString  DefaultChipPath = NULL;
    qreal ChipRotation = 0;
    QString ChipChildType = "SOT23";
    QString ChipType = "SOT";
    QVector <QVector<qreal>> par;
public:
    virtual bool readDataFromJson(QString ModelPath) = 0;
    virtual bool writeDataToJson(QString filename) = 0;
    void setData(ChipData* data);
};

class Chip:public QGraphicsItemGroup
{
public:
    Chip();
    ~Chip();
public:
    ChipData * CurData;
    QString  DefaultChipFloder = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    QString  DefaultChipPath = NULL;
    qreal ChipRotation;
public:
    QVector <Item*> vecItem;
    bool removeAllItem();
    virtual bool InitFromData( );
    virtual bool UpdateToData( );
    virtual bool InitDefault( );
    virtual void setCurData(ChipData* data) = 0;
};



class BGA:public Chip
{
    virtual bool InitFromData( ) override
    {

    }
    virtual bool UpdateToData( ) override
    {

    }
    virtual bool InitDefault( ) override
    {

    }
    virtual void setCurData(ChipData* data) override
    {

    }
};

#endif // CHIP_H
