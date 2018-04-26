#include "mainwindow.h"
#include <QDebug>
#include <QtGui>
#include <QFileDialog>
#include <QLabel>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include "chipmarkwidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    chipMarkWidget = new ChipMarkWidget;
    chipMarkWidget->mainwindow = this;
    chipMarkWidget->Init();
    setCentralWidget(chipMarkWidget);
    //setWindowState(Qt::WindowMaximized);
    resize(QSize(1800,900));
    setWindowTitle("ChipMark");
    createActions();
    createMenus();
    createContextMenu();
    createToolBars();
    createStatusBar();
}

MainWindow::~MainWindow()
{

}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (okToContinue()) {
        event->accept();
    } else {
        event->ignore();
    }
}

void MainWindow::createActions()
{
    openAction = new QAction(tr("&Open..."), this);
    openAction->setIcon(QIcon(":/images/open.png"));
    openAction->setShortcut(QKeySequence::Open);
    openAction->setStatusTip(tr("Open images by a folder"));
    connect(openAction, SIGNAL(triggered()), this, SLOT(open()));

    saveAction = new QAction(tr("&Save"), this);
    saveAction->setIcon(QIcon(":/images/save.png"));
    saveAction->setShortcut(QKeySequence::Save);
    saveAction->setStatusTip(tr("Save the Model and Image to disk"));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));

    saveAsAction = new QAction(tr("Save &As..."), this);
    saveAsAction->setStatusTip(tr("Save the Model and Image under a new ""name"));
    connect(saveAsAction, SIGNAL(triggered()), this, SLOT(saveAs()));

    //Chip Model actions
    openmodelAction = new QAction(tr("&Open Model..."), this);
    openmodelAction->setIcon(QIcon(":/images/open.png"));
    openmodelAction->setShortcut(QKeySequence::Open);
    openmodelAction->setStatusTip(tr("Open Models by a folder"));
    connect(openmodelAction, SIGNAL(triggered()), this, SLOT(openmodel()));

    savemodelAction = new QAction(tr("&Save Model"), this);
    savemodelAction->setIcon(QIcon(":/images/save.png"));
    savemodelAction->setShortcut(QKeySequence::Save);
    savemodelAction->setStatusTip(tr("Save the Model to disk"));
    connect(savemodelAction, SIGNAL(triggered()), this, SLOT(savemodel()));

    savemodelAsAction = new QAction(tr("Save Model &As..."), this);
    savemodelAsAction->setStatusTip(tr("Save the Model under a new ""name"));
    connect(savemodelAsAction, SIGNAL(triggered()), this, SLOT(savemodelAs()));

    //Chip Model actions
    openImageAction = new QAction(tr("&Open Image..."), this);
    openImageAction->setIcon(QIcon(":/images/open.png"));
    openImageAction->setShortcut(QKeySequence::Open);
    openImageAction->setStatusTip(tr("Open Images by a folder"));
    connect(openImageAction, SIGNAL(triggered()), this, SLOT(openImage()));

    saveImageAction = new QAction(tr("&Save Image"), this);
    saveImageAction->setIcon(QIcon(":/images/save.png"));
    saveImageAction->setShortcut(QKeySequence::Save);
    saveImageAction->setStatusTip(tr("Save the image to disk"));
    connect(saveImageAction, SIGNAL(triggered()), this, SLOT(saveImage()));

    saveImageAsAction = new QAction(tr("Save Image &As..."), this);
    saveImageAsAction->setStatusTip(tr("Save the image under a new ""name"));
    connect(saveImageAsAction, SIGNAL(triggered()), this, SLOT(saveImageAs()));
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveAsAction);
    fileMenu->addSeparator();
    menuBar()->addSeparator();

    modelMenu = menuBar()->addMenu(tr("&Model"));
    modelMenu->addAction(openmodelAction);
    modelMenu->addAction(savemodelAction);
    modelMenu->addAction(savemodelAsAction);
    modelMenu->addSeparator();
    menuBar()->addSeparator();

    ImageMenu = menuBar()->addMenu(tr("&Image"));
    ImageMenu->addAction(openImageAction);
    ImageMenu->addAction(saveImageAction);
    ImageMenu->addAction(saveImageAsAction);
    ImageMenu->addSeparator();
    menuBar()->addSeparator();
}

void MainWindow::createContextMenu()
{

}

void MainWindow::createToolBars()
{
    fileToolBar = addToolBar(tr("&File"));
    fileToolBar->addAction(openAction);
    fileToolBar->addAction(saveAction);
    editToolBar = addToolBar(tr("&Edit"));
}

void MainWindow::createStatusBar()
{
    location = new QLabel(" W999 ");
    location1 = new QLabel(" W999 ");

    location->setAlignment(Qt::AlignHCenter);
    location->setMinimumSize(location->sizeHint());

    statusBar()->addWidget(location);
    statusBar()->addWidget(location1, 1);

}

bool MainWindow::save()
{
    if (CurSaveFloder == NULL) {
        return saveAs();
    } else {
        return chipMarkWidget->writeModelAndImage(CurSaveFloder);
    }
}

bool MainWindow::saveAs()
{
    CurSaveFloder = QFileDialog::getExistingDirectory(this,"Please select the file Save path",DefaultSaveFolder);
    QDir dir(CurSaveFloder);
    if (!dir.exists())
    {
        dir.mkpath(CurSaveFloder);
        statusBar()->showMessage("Create the Save path!");
    }

    return chipMarkWidget->writeModelAndImage(CurSaveFloder);
}

void MainWindow::open()
{
    if (okToContinue())
    {
        //获取文件夹路径名
        ImageFolder = QFileDialog::getExistingDirectory(this,"Please select the file path",DefaultOpenFolder);
        if (!ImageFolder.isEmpty())
        {       
            if (!chipMarkWidget->readImages(ImageFolder))
            {
                statusBar()->showMessage(tr("Loading canceled"), 2000);
            }
            statusBar()->showMessage(tr("File loaded"), 2000);
        }
    }
}

//Model functions
bool MainWindow::savemodel()
{
    if (CurModelPath.isEmpty()) {
        return savemodelAs();
    } else {
        return chipMarkWidget->writeModel(CurModelPath);
    }
}

bool MainWindow::savemodelAs()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                               tr("Save Json Model"), ".",
                               tr("json model(*.json)"));
    if (fileName.isEmpty())
        return false;
    CurModelPath = fileName;
    return chipMarkWidget->writeModel(CurLabelImgPath);
}

void MainWindow::openmodel()
{
    if (okToContinue())
    {
        //获取文件夹路径名
        QString fileName = QFileDialog::getOpenFileName(this,tr("Mark Modle"), ".",tr("Json files(*.json)"));
        if (!fileName.isEmpty())
        {
            if (!chipMarkWidget->readModel(fileName))
            {
                statusBar()->showMessage(tr("Loading canceled"), 2000);
            }
            statusBar()->showMessage(tr("File loaded"), 2000);
        }
    }
}

//Image functions
bool MainWindow::saveImage()
{
    if (CurLabelImgPath.isEmpty()) {
        return saveImageAs();
    } else {
        return chipMarkWidget->writeLabelImage(CurLabelImgPath);
    }
}

bool MainWindow::saveImageAs()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                               tr("Save Lanel Image"), ".",
                               tr("Label Image(*.bmp)"));
    if (fileName.isEmpty())
        return false;
    CurLabelImgPath = fileName;
    return chipMarkWidget->writeLabelImage(CurLabelImgPath);
}

void MainWindow::openImage()
{
    if (okToContinue())
    {
        //获取文件夹路径名
        QString fileName = QFileDialog::getOpenFileName(this,tr("Mark Modle"), ".",tr("Label Image(*.bmp)"));
        if (!fileName.isEmpty())
        {
            if (!chipMarkWidget->readLabelImage(fileName))
            {
                statusBar()->showMessage(tr("Loading canceled"), 2000);
            }
            statusBar()->showMessage(tr("File loaded"), 2000);
        }
    }
}

bool MainWindow::okToContinue()
{
    if(chipMarkWidget->vecAllChip.length() == 0)
    {
        return true;
    }else
    {
        for(int i = 0;i< chipMarkWidget->vecAllChip.length();i++)
        {
            if(chipMarkWidget->vecAllChip.at(i)->NeedToSave)
            {
                int r = QMessageBox::warning(this, tr("Mark Model"),
                                tr("The Image Model has been modified.\n"
                                   "Do you want to save your changes?"),
                                QMessageBox::Yes | QMessageBox::No
                                | QMessageBox::Cancel);
                if (r == QMessageBox::Yes)
                {
                    return save();
                } else if (r == QMessageBox::Cancel)
                {
                    return false;
                }else if(r == QMessageBox::No)
                {
                    return true;
                }
            }
        }
        return true;
    }

}
