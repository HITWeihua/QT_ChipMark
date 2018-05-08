#include "chipmarkwidget.h"
#include <QMap>
#define NO_CURCHIP_HINT "WARNING!NO CurChip"

ChipMarkWidget::ChipMarkWidget(QWidget *parent) : QWidget(parent)
{  
    //Add Chip Child type to this Map
    //1 step:Add SOT** to this map
    //2 step:Add ChipSOTData(up,down) to vecChipData;
    //3 step:Add SOT** updateCurLabelModelKinds
    //4 step:Add foot and root to updateCurLabelModel;
    chipstyleMap["SOT23"] = 0;
    chipstyleMap["SOT32"] = 1;
    chipstyleMap["SOT12"] = 2;
    chipstyleMap["SOT88"] = 3;
    chipstyleMap[""] = 999;

    mapChipType["SOT"] = 0;
    mapChipType["BGA"] = 1;

    vecChipType.push_back(new ChipSOT);
    vecChipType.push_back(new BGA);

    vecChildChipData.push_back(new ChipSOTData(2,3));
    vecChildChipData.push_back(new ChipSOTData(3,2));
    vecChildChipData.push_back(new ChipSOTData(1,2));
    vecChildChipData.push_back(new ChipSOTData(8,8));

    imageview = new ImageView();
    imagescene = new ImageScene();
    imageview->setScene(imagescene);
    placeItem();
}

void ChipMarkWidget::placeItem()
{
    tableWidget = new QTableWidget(this);
    tableWidget->setTabletTracking(false);
    tableWidget->setDragEnabled(false);
    tableWidget->setRowCount(400);
    tableWidget->setColumnCount(1);
    tableWidget->setColumnWidth(0,200);

    viewmodelcheckBox = new QCheckBox(this);
    viewmodelcheckBox->setText("Not View Model");

    generatemodelButton = new QPushButton(this);
    generatemodelButton->setText("Generate Model");

    setCurChipDataButton = new QPushButton(this);
    setCurChipDataButton->setText("Set this model as default");

    zoomSlider = new QSlider(this);
    zoomSlider->setMinimum(0);
    zoomSlider->setMaximum(2000);
    zoomSlider->setValue(250);

    chipstyleBox = new QComboBox(this);

    //ChipStyle combBox
    QStringList ChipStyle;
    ChipStyle << "SOT" << "BGA";
    chipstyleBox->addItems(ChipStyle);

    chipstyle2Box = new QComboBox(this);
    chippinBox = new QComboBox(this);

    itemzoomlabel = new QLabel();
    itemzoomlabel->setText("Zoom");
    itemupdownlabel= new QLabel();
    itemupdownlabel->setText("Up/Down");
    itemlrlabel= new QLabel();
    itemlrlabel->setText("Left/Right");
    itemrotatelabel= new QLabel();
    itemrotatelabel->setText("Rotate");
    itemzoomXlabel = new QLabel();
    itemzoomXlabel->setText("X Lenth");
    itemzoomYlabel = new QLabel();
    itemzoomYlabel->setText("Y Lenth");

    itemzoomSlider  = new QSlider();
    itemzoomSlider->setOrientation(Qt::Horizontal);
    itemzoomSlider->setMinimum(1);
    itemzoomSlider->setMaximum(100);
    itemzoomSlider->setValue(50);

    itemupdownSlider  = new QSlider();
    itemupdownSlider->setOrientation(Qt::Horizontal);
    itemupdownSlider->setMinimum(0);
    itemupdownSlider->setMaximum(500);
    itemupdownSlider->setValue(0);

    itemlrSlider  = new QSlider();
    itemlrSlider->setOrientation(Qt::Horizontal);
    itemlrSlider->setMinimum(0);
    itemlrSlider->setMaximum(500);
    itemlrSlider->setValue(0);

    itemrotateSlider  = new QSlider();
    itemrotateSlider->setOrientation(Qt::Horizontal);
    itemrotateSlider->setMinimum(-30);
    itemrotateSlider->setMaximum(30);
    itemrotateSlider->setValue(0);

    itemzoomXSlider = new QSlider();
    itemzoomXSlider->setOrientation(Qt::Horizontal);
    itemzoomXSlider->setMinimum(1);
    itemzoomXSlider->setMaximum(1000);
    itemzoomXSlider->setValue(50);

    itemzoomYSlider = new QSlider();
    itemzoomYSlider->setOrientation(Qt::Horizontal);
    itemzoomYSlider->setMinimum(1);
    itemzoomYSlider->setMaximum(1000);
    itemzoomYSlider->setValue(50);

    itemzoomSpin  = new QSpinBox();
    itemzoomSpin->setMinimum(-360);
    itemzoomSpin->setMaximum(360);
    itemzoomSpin->setValue(0);

    itemupdownSpin  = new QSpinBox();
    itemupdownSpin->setMinimum(0);
    itemupdownSpin->setMaximum(500);
    itemupdownSpin->setValue(0);

    itemlrSpin  = new QSpinBox();
    itemlrSpin->setMinimum(0);
    itemlrSpin->setMaximum(500);
    itemlrSpin->setValue(0);

    itemrotateSpin  = new QDoubleSpinBox();
    itemrotateSpin->setMinimum(-30);
    itemrotateSpin->setMaximum(30);
    itemrotateSpin->setValue(0);
    itemrotateSpin->setSingleStep(0.05);

    itemzoomYSpin  = new QSpinBox();
    itemzoomYSpin->setMinimum(1);
    itemzoomYSpin->setMaximum(1000);
    itemzoomYSpin->setValue(50);

    itemzoomXSpin  = new QSpinBox();
    itemzoomXSpin->setMinimum(1);
    itemzoomXSpin->setMaximum(1000);
    itemzoomXSpin->setValue(50);

    QHBoxLayout *zoomLayout = new QHBoxLayout;
    zoomLayout->addWidget(itemzoomlabel);
    zoomLayout->addWidget(itemzoomSlider);
    zoomLayout->addWidget(itemzoomSpin);

    QHBoxLayout *rotateLayout = new QHBoxLayout;
    rotateLayout->addWidget(itemrotatelabel);
    rotateLayout->addWidget(itemrotateSlider);
    rotateLayout->addWidget(itemrotateSpin);

    QHBoxLayout *updownLayout = new QHBoxLayout;
    updownLayout->addWidget(itemupdownlabel);
    updownLayout->addWidget(itemupdownSlider);
    updownLayout->addWidget(itemupdownSpin);

    QHBoxLayout *lrLayout = new QHBoxLayout;
    lrLayout->addWidget(itemlrlabel);
    lrLayout->addWidget(itemlrSlider);
    lrLayout->addWidget(itemlrSpin);

    QHBoxLayout *zoomXLayout = new QHBoxLayout;
    zoomXLayout->addWidget(itemzoomXlabel);
    zoomXLayout->addWidget(itemzoomXSlider);
    zoomXLayout->addWidget(itemzoomXSpin);

    QHBoxLayout *zoomYLayout = new QHBoxLayout;
    zoomYLayout->addWidget(itemzoomYlabel);
    zoomYLayout->addWidget(itemzoomYSlider);
    zoomYLayout->addWidget(itemzoomYSpin);

    QHBoxLayout *imageLayout = new QHBoxLayout;
    imageLayout->addWidget(imageview);
    imageLayout->addWidget(zoomSlider);

    QHBoxLayout *tableLayout = new QHBoxLayout;
    tableLayout->addWidget(tableWidget);

    QGridLayout *OptionsLayout = new QGridLayout;
    OptionsLayout->addWidget(chipstyleBox,0,0,1,1);
    OptionsLayout->addWidget(chipstyle2Box,0,1,1,1);
    OptionsLayout->addWidget(chippinBox,0,2,1,2);
    OptionsLayout->addLayout(zoomLayout,1,0,1,4);
    OptionsLayout->addLayout(updownLayout,2,0,1,4);
    OptionsLayout->addLayout(lrLayout,3,0,1,4);
    OptionsLayout->addLayout(rotateLayout,4,0,1,4);
    OptionsLayout->addLayout(zoomXLayout,5,0,1,4);
    OptionsLayout->addLayout(zoomYLayout,6,0,1,4);
    OptionsLayout->addWidget(viewmodelcheckBox,7,0,1,4);
    OptionsLayout->addWidget(generatemodelButton,8,0,1,4);
    OptionsLayout->addWidget(setCurChipDataButton,9,0,1,4);

    QGridLayout *topLayout = new QGridLayout;
    topLayout->addLayout(tableLayout,0,0,1,1);
    topLayout->addLayout(imageLayout,0,1,1,2,Qt::AlignVCenter);
    topLayout->addLayout(OptionsLayout,0,3,1,1);
    topLayout->setColumnStretch(0,1);
    topLayout->setColumnStretch(1,3);

    setLayout(topLayout);
}

void ChipMarkWidget::Init()
{
    connect(viewmodelcheckBox,SIGNAL(stateChanged(int)),this,SLOT(modelcheckState(int)));
    connect(generatemodelButton,SIGNAL(clicked()),this,SLOT(generateCurLabelModel()));
    connect(setCurChipDataButton,SIGNAL(clicked()),this,SLOT(setCurChipData()));

    connect(chipstyleBox,SIGNAL(currentIndexChanged(QString)),this,SLOT(updateCurLabelModelKinds()));
    connect(chipstyle2Box,SIGNAL(currentIndexChanged(QString)),this,SLOT(updateCurLabelModel()));
    connect(chippinBox,SIGNAL(currentIndexChanged(QString)),this,SLOT(updateCurItem()));

    connect(zoomSlider, SIGNAL(valueChanged(int)), this, SLOT(setupMatrix()));
    connect(itemzoomSlider,SIGNAL(valueChanged(int)),this,SLOT(updateParzoom()));
    connect(itemzoomSlider,SIGNAL(valueChanged(int)),itemzoomSpin,SLOT(setValue(int)));
    connect(itemzoomSpin,SIGNAL(valueChanged(int)),itemzoomSlider,SLOT(setValue(int)));

    connect(itemupdownSlider,SIGNAL(valueChanged(int)),this,SLOT(updateParupdown()));
    connect(itemupdownSlider,SIGNAL(valueChanged(int)),itemupdownSpin,SLOT(setValue(int)));
    connect(itemupdownSpin,SIGNAL(valueChanged(int)),itemupdownSlider,SLOT(setValue(int)));

    connect(itemlrSlider,SIGNAL(valueChanged(int)),this,SLOT(updateParlr()));
    connect(itemlrSlider,SIGNAL(valueChanged(int)),itemlrSpin,SLOT(setValue(int)));
    connect(itemlrSpin,SIGNAL(valueChanged(int)),itemlrSlider,SLOT(setValue(int)));

    connect(itemrotateSpin,SIGNAL(valueChanged(double)),this,SLOT(updateParrotate()));
    connect(itemrotateSlider,SIGNAL(valueChanged(int)),this,SLOT(setDoubleSpin()));
    connect(itemrotateSpin,SIGNAL(valueChanged(double)),this,SLOT(setSlider()));

    connect(itemzoomXSlider,SIGNAL(valueChanged(int)),this,SLOT(updateParzoomX()));
    connect(itemzoomXSlider,SIGNAL(valueChanged(int)),itemzoomXSpin,SLOT(setValue(int)));
    connect(itemzoomXSpin,SIGNAL(valueChanged(int)),itemzoomXSlider,SLOT(setValue(int)));
    connect(itemzoomYSlider,SIGNAL(valueChanged(int)),this,SLOT(updateParzoomY()));
    connect(itemzoomYSlider,SIGNAL(valueChanged(int)),itemzoomYSpin,SLOT(setValue(int)));
    connect(itemzoomYSpin,SIGNAL(valueChanged(int)),itemzoomYSlider,SLOT(setValue(int)));
    connect(tableWidget,SIGNAL(itemDoubleClicked(QTableWidgetItem*)),this,SLOT(on_tableWidget_itemDoubleClicked(QTableWidgetItem *)));
    connect(imagescene,SIGNAL(ItemMove()),this,SLOT(setCurMouseMovePar()));
    connect(imagescene,SIGNAL(ItemPress(QGraphicsItem*)),this,SLOT(setCurLabelPin(QGraphicsItem*)));
    //Read Settings to get the default Model path
    CurLabelModelPath = DefaultLabelModelPath;
    updateCurLabelModelKinds();
    updateCurLabelModel();
    setCurChipData();
}

void ChipMarkWidget::setCurLabelPin(QGraphicsItem* q)
{
    if(CurChip != NULL)
    {
        for(int i =0; i< CurChip->vecItem.length();i++)
        {
            if(q == CurChip->vecItem.at(i))
            {
                chippinBox->setCurrentIndex(i);
                break;
            }
        }
    }else{
        mainwindow->statusBar()->showMessage("No Model:Please Generate Model");
    }
}

void ChipMarkWidget::setDoubleSpin()
{
    itemrotateSpin->setValue((double)itemrotateSlider->value());
}

void ChipMarkWidget::setSlider()
{
    itemrotateSlider->setValue((int)(itemrotateSpin->value()));
}

void ChipMarkWidget::modelcheckState(int state)
{
    if(CurChip != NULL)
    {
        if(state == Qt::Checked)
        {
            CurChip->setVisible(false);
        }else
        {
            CurChip->setVisible(true);
        }
    }else
    {
        mainwindow->statusBar()->showMessage(NO_CURCHIP_HINT);
    }
}

void ChipMarkWidget::on_tableWidget_itemDoubleClicked(QTableWidgetItem *item)
{
    if(okToContinue())
    {
        imagescene->removeItem(CurImgPixmap);
        imagescene->removeItem(CurChip);
        QString aa = item -> text();
        NoImage = item->row();
        vecLabeledImgNum.push_back(NoImage);
        //读取图片
        QString CurImgPath = ImageFolder +"/"+ aa;
        CurImg = QImage(CurImgPath);
        //显示图片
        imagescene->setSceneRect(CurImg.rect());
        itemupdownSlider->setMaximum(CurImg.rect().height());
        itemupdownSlider->update();
        itemupdownSpin->setMaximum(itemupdownSlider->maximum());
        itemupdownSpin->update();
        itemlrSlider->setMaximum(CurImg.rect().width());
        itemlrSlider->update();
        itemlrSpin->setMaximum(itemlrSlider->maximum());
        itemlrSpin->update();
        CurImgPixmap = imagescene -> addPixmap(QPixmap::fromImage(CurImg));
        CurImgPixmap->setPos(0,0);
        imageview->setScene(imagescene);
        imageview ->setMouseTracking(true) ;
        imageview ->show();
        LoadImgFlag = true;
    }
}

void ChipMarkWidget::updateParupdown()
{
    if(CurChip == NULL)
    {
        mainwindow->statusBar()->showMessage("No Model:Please Generate Model");
    }
    else
    {
        QPointF point = CurOperateItem->mapFromScene(QPointF(itemlrSlider->value(),itemupdownSlider->value()));
        QPointF curpos = CurOperateItem->mapToParent(point);
        CurOperateItem->setY(curpos.y());
        CurChip->UpdateToData();
        imagescene->update();
        imageview->update();
        update();
        CurChip->CurData->NeedToSave = true;
        vecAllImgChipData.at(NoImage)->setData(CurChip->CurData);
    }

}

void ChipMarkWidget::updateParlr()
{
    if(CurChip == NULL)
    {
        mainwindow->statusBar()->showMessage("No Model:Please Generate Model");
    }
    else
    {
        QPointF point = CurOperateItem->mapFromScene(QPointF(itemlrSlider->value(),itemupdownSlider->value()));
        QPointF curpos = CurOperateItem->mapToParent(point);
        CurOperateItem->setX(curpos.x());
        CurChip->UpdateToData();
        imagescene->update();
        imageview->update();
        update();
        CurChip->CurData->NeedToSave =true;
        vecAllImgChipData.at(NoImage)->setData(CurChip->CurData);
    }
}

void ChipMarkWidget::updateParzoom()
{
    if(CurChip == NULL)
    {
        mainwindow->statusBar()->showMessage("No Model:Please Generate Model");
    }
    else
    {

    }
}

void ChipMarkWidget::updateParzoomX()
{
    if(CurChip == NULL)
    {
        mainwindow->statusBar()->showMessage("No Model:Please Generate Model");
    }
    else
    {
        CurOperateItem->setData(0,itemzoomXSlider->value());
        CurChip->UpdateToData();
        imagescene->update();
        imageview->update();
        update();
        CurChip->CurData->NeedToSave =true;
        vecAllImgChipData.at(NoImage)->setData(CurChip->CurData);
    }
}

void ChipMarkWidget::updateParzoomY()
{
    if(CurChip == NULL)
    {
        mainwindow->statusBar()->showMessage("No Model:Please Generate Model");
    }
    else
    {
        CurOperateItem->setData(1,itemzoomYSlider->value());
        CurChip->UpdateToData();
        imagescene->update();
        imageview->update();
        update();
        CurChip->CurData->NeedToSave = true;
        vecAllImgChipData.at(NoImage)->setData(CurChip->CurData);
    }
}

void ChipMarkWidget::updateParrotate()
{
    if(CurChip == NULL)
    {
        mainwindow->statusBar()->showMessage("No Model:Please Generate Model");
    }
    else
    {
        if(chippinBox->currentText().right(3).toInt()  < CurChip->vecItem.length() - 1)
        {
            CurOperateItem->setRotation(itemrotateSpin->value());
        }
        CurChip->UpdateToData();
        imagescene->update();
        imageview->update();
        update();
        CurChip->CurData->NeedToSave =true;
        vecAllImgChipData.at(NoImage)->setData(CurChip->CurData);
    }
}

void ChipMarkWidget::updateCurItem()
{
    if(CurChip == NULL)
    {
        mainwindow->statusBar()->showMessage("No Model:Please Generate Model");
    }
    else
    {
        CurOperateItem  = CurChip->vecItem[chippinBox->currentText().right(3).toInt()];
        setCurPar();
        setCurMouseMovePar();
    }
}

void ChipMarkWidget::updateCurLabelModel()
{
    chippinBox->clear();
    QString str = chipstyle2Box->currentText();
    switch(chipstyleMap[str])
    {
        case 0://SOT23
        {
            QStringList ChipPin;
            ChipPin << "Body000" << "Up001" <<"Up002"
                    <<"Down003"<<"Down004" <<"Down005"
                    <<"Outline006";
            chippinBox->addItems(ChipPin);
            break;
        }
        case 1://SOT32
        {
            QStringList ChipPin;
            ChipPin << "Body000" << "Up001" <<"Up002"<<"Up003"
                    <<"Down004" <<"Down005"
                    <<"Outline006";
            chippinBox->addItems(ChipPin);
            break;
        }
        case 2://SOT12
        {
            QStringList ChipPin;
            ChipPin << "Body000"
                    << "Up001"
                    <<"Down002"<<"Down003"
                    <<"Outline004";
            chippinBox->addItems(ChipPin);
            break;
        }
        case 3://SOT88
        {
            QStringList ChipPin;
            ChipPin << "Body000"
                    << "Up001" <<"Up002"<< "Up003" <<"Up004"<< "Up005" <<"Up006"<< "Up007" <<"Up008"
                    << "Down009"<<"Down010"<<"Down011" <<"Down012"<< "Down013"<<"Down014"<<"Down015" <<"Down016"
                    <<"Outline017";
            chippinBox->addItems(ChipPin);
            break;
        }
         default:
        {
            QStringList ChipPin ;
            chippinBox->addItems(ChipPin);
            break;
        }
    }
    setCurChipData();
}

void ChipMarkWidget::updateCurLabelModelKinds()
{
    //Update the child chip item options
   int ChipIndex= chipstyleBox->currentIndex();
   switch(ChipIndex)
    {
        case 0://SOT
        {
            QStringList ChipStyle2;
            ChipStyle2<<"SOT88" << "SOT23" <<"SOT32" << "SOT12";
            chipstyle2Box->clear();
            chipstyle2Box->addItems(ChipStyle2);
            break;
        }
       case 1://BGA
       {
           QStringList ChipStyle2;
           chipstyle2Box->clear();
           chipstyle2Box->addItems(ChipStyle2);
           break;
       }
        default:
            break;
   }
   updateCurLabelModel();
}

bool ChipMarkWidget::generateCurLabelModel()
{
    //Get the Model from the CurLabelModel path,Depending on the path
    //Update the label model,actually label the image by the chipstyple
    if (chipstyle2Box->currentText() != "")
    {
        if(LoadImgFlag)
        {
            if(CurSaveFolder != "")
            {
                if(CurChip !=NULL)
                {
                    imagescene->removeItem(CurChip);
                }
                int i = chipstyleMap[chipstyle2Box->currentText()];                
                QString str = ImageNamesList[NoImage];
                //If there exists the file with the same name as the CurImg,it will load it
                //else it will load the default model in my document
                QString modelstr =  QString(CurSaveFolder+"/"+str.split('.').at(0)+".json");
                if(QFile(modelstr).exists())
                {
                    vecAllImgChipData.at(NoImage)->readDataFromJson(modelstr);
                }else{
                    vecAllImgChipData.at(NoImage)->setData(vecChildChipData.at(i));
                }
                CurChip =  vecChipType.at(mapChipType[vecAllImgChipData.at(NoImage)->ChipType]);
                CurChip->setCurData(vecAllImgChipData.at(NoImage));
                CurChip->setHandlesChildEvents(false);
                CurChip->InitFromData();
                imagescene->addItem(CurChip);
                imagescene->update();
                imageview->show();
                imageview->update();
                updateCurItem();
                setCurPar();
                mainwindow->statusBar()->showMessage("Generate Finished");
                return true;
            }else{
                mainwindow->save();
                return false;
            }
        }else{
            mainwindow->statusBar()->showMessage("Please load Image");
        }
    }else
    {
        mainwindow->statusBar()->showMessage("Generate failed! NO choose proper Chip style!");
        return false;
    }
}

void ChipMarkWidget::setCurPar()
{
    if(CurChip == NULL || CurOperateItem == NULL)
    {
        mainwindow->statusBar()->showMessage("No Model:Please Generate Model");
    }else{
        QPointF point = CurChip->mapToScene(CurOperateItem->pos());
        itemupdownSlider->setValue(point.y());
        itemlrSlider->setValue(point.x());
        itemzoomXSlider->setValue(CurOperateItem->data(0).toInt());
        itemzoomYSlider->setValue(CurOperateItem->data(1).toInt());
        itemrotateSpin->setValue(CurOperateItem->rotation());
        itemzoomSlider->setValue(CurOperateItem->scale()*50);
        update();
    }
}

//The default model saved in My document
//"Set as the Default model" actually changes files in My document
//vecChip save all kinds of chips in chipStyleMap;
void ChipMarkWidget::setCurChipData()
{
    if(CurChip != NULL)
    {
       CurChip->UpdateToData();
       int i = chipstyleMap[CurChip->CurData->ChipChildType];
       vecChildChipData.at(i)->setData(CurChip->CurData);
       vecChildChipData.at(i)->writeDataToJson(vecChildChipData.at(i)->DefaultChipPath);
    }
}

void ChipMarkWidget::setCurMouseMovePar()
{
    disconnect(itemupdownSlider,SIGNAL(valueChanged(int)),this,SLOT(updateParupdown()));
    disconnect(itemlrSlider,SIGNAL(valueChanged(int)),this,SLOT(updateParlr()));
    QPointF point = CurChip->mapToScene(CurOperateItem->pos());
    itemupdownSlider->setValue(point.y());
    itemlrSlider->setValue(point.x());
    qDebug() << "Item Pos" << point;
    connect(itemupdownSlider,SIGNAL(valueChanged(int)),this,SLOT(updateParupdown()));
    connect(itemlrSlider,SIGNAL(valueChanged(int)),this,SLOT(updateParlr()));
    CurChip->CurData->NeedToSave = true;
}

void ChipMarkWidget::mouseMoveEvent(QMouseEvent *e)
{
    if(CurChip == NULL)
    {
        mainwindow->statusBar()->showMessage("No Model:Please Generate Model");
    }
    else
    {
        QWidget::mouseMoveEvent(e);
    }

}

void ChipMarkWidget::mousePressEvent(QMouseEvent *e)
{
    QWidget::mousePressEvent(e);
}

bool ChipMarkWidget::readImages(QString ImageFolder_)
{
    vecLabeledImgNum.clear();
    QStringList nameFilters;
    ImageFolder = ImageFolder_;
    nameFilters << "*.jpg" << "*.png" << "*.bmp";
    if (!ImageFolder.isEmpty())
    {
        QDir IF(ImageFolder);
        ImageFullPathList = IF.entryList(nameFilters);
        //对文件名字列表进行排序
        ImageFullPathList.sort();
        //获取图片文件名字
        ImageNamesList = ImageFullPathList.replaceInStrings(ImageFolder + "/","");
        for(int i = 0;i<ImageNamesList.length();i++)
        {
            QString temName = ImageNamesList.at(i);
            ImageNamesNoPostList.push_back(temName.split(".").at(0));
        }
        //将ImageFullPathList中文件名字显示到窗口
        int len = ImageFullPathList.length();
        tableWidget->setRowCount(len);
        vecAllImgChipData.clear();
        if(chipstyle2Box->currentText() != "")
        {
            int i = chipstyleMap[chipstyle2Box->currentText()];
            for(int row = 0; row < len;row++)
            {
                switch (i) {
                case 0:
                    vecAllImgChipData.push_back(new ChipSOTData(2,3));
                    break;
                case 1:
                    vecAllImgChipData.push_back(new ChipSOTData(3,2));
                    break;
                case 2:
                    vecAllImgChipData.push_back(new ChipSOTData(1,2));
                    break;
                case 3:
                    vecAllImgChipData.push_back(new ChipSOTData(8,8));
                    break;
                default:
                    vecAllImgChipData.push_back(new ChipSOTData(2,3));
                    break;
                }
                tableWidget->setItem(row,0,new QTableWidgetItem(ImageNamesList.at(row)));
            }
            return true;
        }else
        {
            return false;
        }
    }
    else
        return false;
}

bool ChipMarkWidget::writeAllModels(const QString &fileName )
{
    CurSaveFolder = fileName;
    QDir IF(CurSaveFolder);
    QStringList SavePathList = IF.entryList(QStringList("*.json"));
    //获取图片文件名字
    QStringList SavedName;
    SavedName= SavePathList.replaceInStrings(CurSaveFolder + "/","");
    //将ImageFullPathList中文件名字显示到窗口
    if(vecAllImgChipData.length() >0 )
    {
        for(int m = 0; m <ImageNamesNoPostList.length();m++ )
        {
            QString str =ImageNamesNoPostList.at(m);
            QString st(str+".json");
            if(!SavedName.contains(st))
            {
                QBrush Q(QColor(Qt::white));
                tableWidget->item(m,0)->setBackground(Q);
            }
        }
        for(int i =0;i< vecLabeledImgNum.length();i++)
        {
            int j = vecLabeledImgNum.at(i);
            QString str = ImageNamesList[j];
            if(vecAllImgChipData.at(j)->NeedToSave)
            {
                vecAllImgChipData.at(j)->writeDataToJson(QString(CurSaveFolder + "/"+str.split('.').at(0)));
                QBrush Q(QColor(Qt::green));
                tableWidget->item(j,0)->setBackground(Q);
            }
        }
        //
        for(int k = 0; k<SavedName.length();k++ )
        {
            QString str =SavedName[k];
            QString ImageName =  str.split(".").at(0);
            if(ImageNamesNoPostList.contains(ImageName))
            {
                QBrush Q(QColor(Qt::green));
                int n =ImageNamesNoPostList.indexOf(ImageName);
                tableWidget->item(n,0)->setBackground(Q);
            }
        }
        if(CurChip != NULL)
        {
            CurChip->CurData->NeedToSave = false;
        }
        return true;
    }else{
        mainwindow->statusBar()->showMessage("No load Image");
        return false;
    }
}

//Read Single Model and set it as temp default
bool ChipMarkWidget::readModel(QString ModelPath)
{
   if(chipstyleBox->currentText() == "SOT")
   {
       ChipSOTData * data  = new ChipSOTData();
       data->readDataFromJson(ModelPath);
       chipstyleBox->setCurrentText(data->ChipType);
       chipstyle2Box->setCurrentText(data->ChipChildType);
       int i = chipstyleMap[chipstyle2Box->currentText()];
       vecChildChipData.at(i)->setData(data);
       mainwindow->statusBar()->showMessage("Read Model Successfully.");
       return true;
   }else{
       mainwindow->statusBar()->showMessage("No valid chip style,plese choose again.");
       return false;
   }
}

bool ChipMarkWidget::writeModel(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(this, tr("ChipMark"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(file.fileName())
                             .arg(file.errorString()));
        return false;
    }
    if(CurChip == NULL)
    {
        mainwindow->statusBar()->showMessage("WARNING!No Chip Model");
        return false;
    }else{
        CurChip->CurData->writeDataToJson(fileName);
        QBrush Q(QColor(Qt::green));
        tableWidget->item(NoImage,0)->setBackground(Q);
        return true;
    }
}

void ChipMarkWidget::wheelEvent(QWheelEvent *e)
{
    if (e->modifiers() & Qt::ControlModifier) {
        if (e->delta() > 0)
            zoomSlider->setValue(zoomSlider->value()+10);
        else
            zoomSlider->setValue(zoomSlider->value()-10);
        e->accept();
    } else {
        //QGraphicsView::wheelEvent(e);
    }
}

void ChipMarkWidget::setupMatrix()
{
    qreal scale = qPow(qreal(2), (zoomSlider->value() - 250) / qreal(50));
    QMatrix matrix;
    matrix.scale(scale, scale);
    imageview->setMatrix(matrix);
}

bool ChipMarkWidget::okToContinue()
{
    if(CurChip == NULL)
    {
        mainwindow->statusBar()->showMessage("No Model:Please Generate Model");
        return true;
    }else
    {
        vecAllImgChipData.at(NoImage)->setData(CurChip->CurData);
        if(vecAllImgChipData.length() !=0)
        {
            if (vecAllImgChipData.at(NoImage)->NeedToSave)
            {
                int r = QMessageBox::warning(this, tr("Mark Model"),
                                tr("The Image Model has been modified.\n"
                                   "Do you want to save your changes?"),
                                QMessageBox::Yes | QMessageBox::No
                                | QMessageBox::Cancel);
                if (r == QMessageBox::Yes)
                {
                    vecAllImgChipData.at(NoImage)->NeedToSave = ! mainwindow->save();
                    return !vecAllImgChipData.at(NoImage)->NeedToSave;
                } else if (r == QMessageBox::Cancel)
                {
                    return false;
                }else if(r == QMessageBox::No)
                {
                    QBrush Q(QColor(Qt::red));
                    tableWidget->item(NoImage,0)->setBackground(Q);
                }

            }
            return true;
        }else
        {
            return true;
        }
    }
}
