#include "chip.h"

ChipData::ChipData()
{

}

ChipData::~ChipData()
{

}

bool ChipData::readDataFromJson(QString ModelPath)
{

}

bool ChipData::writeDataToJson(QString ModelPath)
{

}

void ChipData::setData(ChipData *data)
{
    this->up = data->up;
    this->down = data->down;
    this->totalpin = data->totalpin;
    this->par.clear();
    this->par = data->par;
    this->ChipChildType = data->ChipChildType;
    this->ChipType =data->ChipType;
    this->ChipRotation = data->ChipRotation;
    this->NeedToSave = data->NeedToSave;
    DefaultChipPath = QString(DefaultChipFloder +"/"+ChipChildType);
}

Chip::Chip()
{

}

Chip::~Chip()
{

}

bool Chip::InitFromData()
{
    qDebug() << " Chip ::InitFromData";
}

bool Chip::UpdateToData()
{

}

bool Chip::InitDefault()
{

}

bool Chip::removeAllItem()
{
    for(int i =0;i<vecItem.length();i++)
    {
        this->removeFromGroup(vecItem[i]);
    }
}
