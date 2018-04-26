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
    int up = 2;
    int down = 3;
    int totalpin = (up+down)*2 + 1;
    qreal ChipRotation = 0;
    QString ChipChildType = "SOT23";
    QString ChipType = "SOT";
    QVector <QVector<qreal>> par;
public:
    virtual bool readDataFromJson(QString ModelPath) = 0;
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
    bool NeedToSave = false;
public:
    QVector <Item*> vecItem;
    bool removeAllItem();
    virtual bool InitFromData( );
    virtual bool UpdateToData( );
    virtual bool InitDefault( );
    virtual bool writeLabelModel(QString filename);
    virtual void setCurData(ChipData* data) = 0;
};



#endif // CHIP_H
