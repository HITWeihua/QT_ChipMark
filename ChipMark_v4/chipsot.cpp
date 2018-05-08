#include "chipsot.h"
#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>
ChipSOT::ChipSOT( )
{
    QGraphicsItemGroup::setFlag(QGraphicsItem::ItemIsMovable);
    QGraphicsItemGroup::setFlag(QGraphicsItem::ItemIsFocusable,true);
    QGraphicsItem::setHandlesChildEvents(false);
    CurData = new ChipSOTData();
    InitDefault();
}

ChipSOT::~ChipSOT( )
{

}

bool ChipSOT::InitDefault()
{
   //Initilize the Class ChipSOT defaultly
    DefaultChipPath = QString(DefaultChipFloder +"/"+ CurData->ChipChildType);
    qDebug() << DefaultChipPath;
    if(QFile(DefaultChipPath +".json").exists())
    {
        CurData->readDataFromJson(DefaultChipPath +".json");
        InitFromData();
    }
}

bool ChipSOT::InitFromData()
{
   //Get the value of up,down;Initilize the Class ChipSOT
    if(CurData != NULL)
    {
        removeAllItem();
        int up = CurData->up;
        int down = CurData->down;
        for(int i = 0 ; i < CurData->totalpin;i++ )
        {
            vecItem.push_back( new ItemRect(0,0,50,50));
            vecItem.at(i)->setScale(scale());
            vecItem.at(i)->setData(0,50);
            vecItem.at(i)->setData(1,50);
            if(i < up + 1 && i>0)
            {
                vecItem.at(i)->setData(2,"Red");
            }
            else if(i >=  up + 1)
            {
                if(i == CurData->totalpin -1)
                vecItem.at(i)->setData(2,"Blue");
                else vecItem.at(i)->setData(2,"Green");
            }
            else if(i == 0)
            {
                vecItem.at(i)->setData(2,"Yellow");
            }
            addToGroup(vecItem.at(i));
        }
        for(int i = 0;i < CurData->par.length();i++)
        {
            qreal Scenecenx = CurData->par.at(i).at(0);
            qreal Sceneceny = CurData->par.at(i).at(1);
            qreal width = CurData->par.at(i).at(2);
            qreal height = CurData->par.at(i).at(3);
            qreal rotation = CurData->par.at(i).at(4);
            vecItem.at(i);
            vecItem.at(i)->setRotation(rotation);
            vecItem.at(i)->InitFromScenePos(Scenecenx,Sceneceny,width,height);
        }
    }
    else
    {
        return false;
    }
    return true;
}

bool ChipSOT::UpdateToData()
{
    CurData->ChipRotation = rotation();
    CurData->ChipType = "SOT";
    CurData->par.clear();
    qreal Totalrotation = 0;
    for(int i = 0;i<CurData->totalpin;i++)
    {
        QPointF posToScene =  this -> mapToScene(vecItem.at(i)->pos());
        QVector<qreal> Item;
        Item.push_back(posToScene.x());
        Item.push_back(posToScene.y());
        Item.push_back(vecItem.at(i)->data(0).toInt());
        Item.push_back(vecItem.at(i)->data(1).toInt());
        Item.push_back(vecItem.at(i)->rotation());
        CurData->par.push_back(Item);
        if(i>0)
        {
            Totalrotation = Totalrotation + vecItem.at(i)->rotation();
        }
    }
    CurData->ChipRotation = Totalrotation /(CurData->up+CurData->down);
}

void ChipSOT::setCurData(ChipData * data)
{
    CurData->up = data->up;
    CurData->down = data->down;
    CurData->totalpin =data->totalpin;
    CurData->par.clear();
    CurData->par = data->par;
    CurData->ChipChildType = data->ChipChildType;
    CurData->ChipRotation = data->ChipRotation;
    CurData->ChipType = data->ChipType;
}

void ChipSOT::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget)
{
    painter->setPen(QPen(QColor(255,0,0,100)));
}

void ChipSOT::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
   QGraphicsItem::mousePressEvent(event);
    update();
}

void ChipSOT::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug()<<" ChipSOT.Position:: "<<event->pos();
    QGraphicsItem::mouseMoveEvent(event);
    update();
}

QRectF ChipSOT::boundingRect() const
{
     return QRectF(0, 0, 400, 400);
}

bool ChipSOTData::readDataFromJson(QString ModelPath)
{
    QFile file(ModelPath);
    QString val;
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();
    QJsonDocument document= QJsonDocument::fromJson(val.toUtf8());
    if (!document.isNull())
    {  // 解析未发生错误
        if (document.isObject())
        {  // JSON 文档为对象
            QJsonObject object = document.object();  // 转化为对象
            if (object.contains("ChipChildType"))
            {
                QJsonValue value = object.value("ChipChildType");
                if (value.isString())
                {
                    ChipChildType = value.toString();
                }
            }
            if (object.contains("ChipType"))
            {
                QJsonValue value = object.value("ChipType");
                if (value.isString())
                {
                    ChipType= value.toString();
                }
            }
            if (object.contains("ChipRotation"))
            {
                QJsonValue value = object.value("ChipRotation");
                ChipRotation = value.toVariant().toDouble();
            }
            if (object.contains("Num_Up"))
            {
                QJsonValue value = object.value("Num_Up");
                up = value.toVariant().toInt();
            }
            if (object.contains("Num_Down"))
            {
                QJsonValue value = object.value("Num_Down");
                down = value.toVariant().toInt();
            }
            if (object.contains("Parameter"))
            {
                par.clear();
                QJsonValue value = object.value("Parameter");
                if (value.isObject())
                {  // Version 的 value 是数组
                    QJsonObject parameter = value.toObject();
                    int nSize = parameter.size();
                    for (int i = 0; i < nSize; ++i)
                    {
                        QString PinName;
                        if(i <= up  && i>0)
                        {
                            PinName += "Up";
                        }
                        else if(i > up )
                        {
                            if(i == totalpin -1)
                                PinName += "Outline";
                            else PinName += "Down";
                        }
                        else PinName += "Body";
                        PinName += QString::number(i);
                        if(parameter.contains(PinName))
                        {
                            QJsonValue pinValue = parameter.value(PinName);
                            QVector<qreal> ItemPar;
                            if (pinValue .isArray())
                            {
                                QJsonArray body = pinValue.toArray();
                                for(int j = 0;j< body.size();++j)
                                {
                                    ItemPar.push_back(body.at(j).toDouble());
                                }
                            }
                            par.push_back(ItemPar);
                        }else{
                            qDebug() << "ModelFile No "<< PinName;
                          return false;
                        }
                    }
                }
            }
        }
    }
    return true;
}

bool ChipSOTData::writeDataToJson(QString filename)
{
    QJsonObject json;
    QJsonObject parameter;
    for(int i = 0;i<totalpin;i++)
    {
        QJsonArray body;
        body.append(qRound (par.at(i).at(0)));
        body.append(qRound (par.at(i).at(1)));
        body.append(par.at(i).at(2));
        body.append(par.at(i).at(3));
        body.append(par.at(i).at(4));
        QString PinName;
        if(i <= up  && i>0)
        {
            PinName += "Up";
        }
        else if(i > up )
        {
            if(i == totalpin -1)
                PinName += "Outline";
            else PinName += "Down";
        }
        else PinName += "Body";
        PinName += QString::number(i);
        parameter.insert(PinName,body);
    }
    json.insert("ChipType","SOT");
    json.insert("ChipChildType","SOT"+QString::number(up*10 + down));
    json.insert("Num_Up",up);
    json.insert("Num_Down",down);
    json.insert("ChipRotation",ChipRotation);
    json.insert("Parameter",parameter);

    QJsonDocument document;
    document.setObject(json);
    QByteArray byteArray = document.toJson(QJsonDocument::Indented);
    QFile saveFile(filename + ".json");
    if (!saveFile.open(QIODevice::WriteOnly))
    {
        qWarning("Couldn't open save file.");
        return false;
    }
    if(saveFile.write(byteArray))
    NeedToSave = false;
    else NeedToSave =true;
    return !NeedToSave;
}

