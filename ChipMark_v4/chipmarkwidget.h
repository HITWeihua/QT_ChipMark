#ifndef CHIPMARKWIDGET_H
#define CHIPMARKWIDGET_H
#include "predef.h"
#include <QWidget>
#include <QtWidgets>
#include <QJsonObject>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QJsonDocument>
#include "mainwindow.h"

class ChipMarkWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ChipMarkWidget(QWidget *parent = nullptr);
public:
    int NoImage = 0;
    MainWindow* mainwindow = NULL;
    ImageScene* imagescene = NULL;
    ImageView * imageview = NULL;

    QGraphicsItem * CurOperateItem = NULL;
    QGraphicsPixmapItem *CurImgPixmap = NULL;

    QImage CurImg;
    QImage CurLabel;

    QStringList ImageFullPathList;
    QStringList ImageNamesList;
    QStringList ImageNamesNoPostList;
    QString ImageFolder;
    QString DefaultLabelModelPath;
    QString CurLabelModelPath;
    QString CurSaveFolder;

    QTableWidget *tableWidget;
    QCheckBox *viewmodelcheckBox;
    QPushButton *generatemodelButton;
    QPushButton *setCurChipDataButton;
    QLabel *itemzoomlabel;
    QLabel *itemupdownlabel;
    QLabel *itemlrlabel;
    QLabel *itemrotatelabel;
    QLabel *itemzoomXlabel;
    QLabel *itemzoomYlabel;

    QSlider *zoomSlider;
    QSlider *itemzoomSlider;
    QSlider *itemupdownSlider;
    QSlider *itemlrSlider;
    QSlider *itemrotateSlider;
    QSlider *itemzoomXSlider;
    QSlider *itemzoomYSlider;

    QSpinBox *itemzoomSpin;
    QSpinBox *itemupdownSpin;
    QSpinBox *itemlrSpin;
    QDoubleSpinBox *itemrotateSpin;
    QSpinBox *itemzoomXSpin;
    QSpinBox *itemzoomYSpin;


    QComboBox *chipstyleBox;
    QComboBox *chipstyle2Box;
    QComboBox *chippinBox;
    QMap<QString,int> chipstyleMap;
    QMap<QString,int> mapChipType;
    Chip * CurChip = NULL;
    QVector<Chip *> vecChipType;
    QVector<ChipData *> vecChildChipData;
    QVector<ChipData *> vecAllImgChipData;
    QVector<int > vecLabeledImgNum;
    bool LoadImgFlag = false;
public:
    bool readImages(QString ImageFolder_);
    bool writeAllModels(const QString &fileName );
    bool readModel(QString ModelPath);
    bool writeModel(const QString &fileName);
public slots:
    void modelcheckState(int state);
    void setupMatrix();
    void setCurPar();
    void setCurMouseMovePar();
    void setCurChipData();
    void updateParupdown();
    void updateParlr();
    void updateParrotate();
    void updateParzoom();
    void updateParzoomX();
    void updateParzoomY();
    void setDoubleSpin();
    void setSlider();
    void on_tableWidget_itemDoubleClicked(QTableWidgetItem *item);
    void updateCurLabelModelKinds();
    void updateCurLabelModel();
    void updateCurItem();
    bool generateCurLabelModel();
    void setCurLabelPin(QGraphicsItem*q);
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void wheelEvent(QWheelEvent *e);
public:
    void Init();
    void placeItem();
    bool okToContinue();
signals:

public slots:
};

#endif // CHIPMARKWIDGET_H
