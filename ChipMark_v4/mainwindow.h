#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "predef.h"
#include <QMainWindow>
#include <QtWidgets>
//#include "chipmarkwidget.h"

class ChipMarkWidget;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
public:
    QLabel *location;
    QLabel *location1;

    QStringList ImageFullPathList;
    QStringList ImageNamesList;
    QString ImageFolder;
    QString CurModelPath = NULL;
    QString CurLabelImgPath = NULL;
    QString CurSaveFloder = NULL;
    QString DefaultOpenFolder= "../ChipMark_v4/images/";
    QString DefaultSaveFolder= "..";

    ChipMarkWidget *chipMarkWidget;

public:
    QMenu *fileMenu;
    QAction *openAction;
    QAction *saveAction;
    QAction *saveAsAction;

    QMenu *modelMenu;
    QAction *openmodelAction;
    QAction *savemodelAction;
    QAction *savemodelAsAction;

    QMenu *ImageMenu;
    QAction *openImageAction;
    QAction *saveImageAction;
    QAction *saveImageAsAction;

    QToolBar *fileToolBar;
    QToolBar *editToolBar;

public slots:

    void open();
    bool save();
    bool saveAs();

    void openmodel();
    bool savemodel();
    bool savemodelAs();

    void openImage();
    bool saveImage();
    bool saveImageAs();
public:
    void closeEvent(QCloseEvent *event);
    bool okToContinue();
private:
    void createActions();
    void createMenus();
    void createContextMenu();
    void createToolBars();
    void createStatusBar();

};

#endif // MAINWINDOW_H
