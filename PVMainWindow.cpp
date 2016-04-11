#include "PVMainWindow.h"
#include "ui_pvmainwindow.h"

PVMainWindow::PVMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PVMainWindow)
{
    ui->setupUi(this);
    initUI();
    connectSlots2Signals();
}

PVMainWindow::~PVMainWindow()
{
    delete ui;
}

/*--------------------------------------------------
*Summary: init UI
*Parameters:
*           None
*Return :
*           None
--------------------------------------------------*/
void PVMainWindow::initUI()
{
    initMainForm();

}

/*--------------------------------------------------
*Summary: init MainForm
*Parameters:
*           None
*Return :
*           None
--------------------------------------------------*/
void PVMainWindow::initMainForm()
{
    this->setWindowTitle("PictureViewer");
    this->setBaseSize(960, 640);
    initMenuBar();
    initToolBar();
    initCenterWidget();
}

/*--------------------------------------------------
*Summary: init menubar
*Parameters:
*           None
*Return :
*           None
--------------------------------------------------*/
void PVMainWindow::initMenuBar()
{
    QMenu *p_menu = menuBar()->addMenu(tr("&File"));
    openAction = new QAction(tr("Open"), p_menu);
    openAction->setIcon(QPixmap(":/image/resource/Add folder.png"));
    p_menu->addAction(openAction);

    closeAction = new QAction(tr("Close"), p_menu);
    closeAction->setIcon(QPixmap(":/image/resource/Close folder.png"));
    p_menu->addAction(closeAction);

    exitAction = new QAction(tr("Exit"), p_menu);
    exitAction->setIcon(QPixmap(":/image/resource/Close.png"));
    p_menu->addAction(exitAction);

    p_menu = menuBar()->addMenu(tr("&Edit"));
    lastOne = new QAction(tr("Last"), p_menu);
    lastOne->setIcon(QPixmap(":/image/resource/Left.png"));
    p_menu->addAction(lastOne);

    nextOne = new QAction(tr("Next"), p_menu);
    nextOne->setIcon(QPixmap(":/image/resource/Right.png"));
    p_menu->addAction(nextOne);
}

/*--------------------------------------------------
*Summary: init toolbar
*Parameters:
*           None
*Return :
*           None
--------------------------------------------------*/
void PVMainWindow::initToolBar()
{
    QToolBar *toolBar = addToolBar(tr("File"));
    toolBar->addAction(openAction);
    toolBar->addAction(closeAction);
    toolBar = addToolBar(tr("Change Picture"));
    toolBar->addAction(lastOne);
    toolBar->addAction(nextOne);
}

/*--------------------------------------------------
*Summary: init center widget
*Parameters:
*           None
*Return :
*           None
--------------------------------------------------*/
void PVMainWindow::initCenterWidget()
{
    QWidget *centerWidget = this->centralWidget();
    QHBoxLayout *mainLayout = new QHBoxLayout;
    centerWidget->setLayout(mainLayout);

    iconsViewer = new PVImageListViewer;
    mainLayout->addWidget(iconsViewer);

    imageViewer = new PVImageViewer;
    mainLayout->addWidget(imageViewer);
    imageViewer->show();

    iconsViewer->registerObserver(dynamic_cast<PVObserver*>(imageViewer));

}

/*--------------------------------------------------
*Summary: connect slot to signal
*Parameters:
*           None
*Return :
*           None
--------------------------------------------------*/
void PVMainWindow::connectSlots2Signals()
{
    connect(openAction, SIGNAL(triggered()), this, SLOT(openFile()));
    connect(closeAction, SIGNAL(triggered()), this, SLOT(closeAllFiles()));
    connect(nextOne, SIGNAL(triggered()), this, SLOT(changeNextPicture()));
    connect(lastOne, SIGNAL(triggered()), this, SLOT(changeLastPicture()));

}

/*--------------------------------------------------
*Summary: slot function of open file
*Parameters:
*           None
*Return :
*           None
--------------------------------------------------*/
void PVMainWindow::openFile()
{
    QString path = QFileDialog::getOpenFileName(this,
                                                tr("Open picture"),
                                                "/home",
                                                tr("Images (*.png *.jpeg *.jpg)"));
    if(!path.isEmpty())
    {
        imageViewer->setFilePath(path);
        imageViewer->updateViewer();
        imageFinder = new PVImageFileSearcher(path);
        connect(imageFinder, SIGNAL(finished()), this, SLOT(searcherImageFinished()));
        imageFinder->start();
    }
    else
    {
        QMessageBox::warning(this, tr("Path"),
                             tr("You did not select any file."));
    }
}

/*--------------------------------------------------
*Summary: slot function of seacher image finished
*Parameters:
*           None
*Return :
*           None
--------------------------------------------------*/
void PVMainWindow::searcherImageFinished()
{
    QString dir = imageFinder->getCurDir();
    QStringList imagePaths = imageFinder->getFilePaths();
    iconsViewer->setImagePathData(dir, imagePaths);
}

/*--------------------------------------------------
*Summary: slot function of close all files
*Parameters:
*           None
*Return :
*           None
--------------------------------------------------*/
void PVMainWindow::closeAllFiles()
{
    iconsViewer->closeViewer();
    imageViewer->closeViewer();
}

/*--------------------------------------------------
*Summary: slot function of change next picture
*Parameters:
*           None
*Return :
*           None
--------------------------------------------------*/
void PVMainWindow::changeNextPicture()
{
    iconsViewer->setSelectedChanged(QString("next"));
}

/*--------------------------------------------------
*Summary: slot function of change last picture
*Parameters:
*           None
*Return :
*           None
--------------------------------------------------*/
void PVMainWindow::changeLastPicture()
{
    iconsViewer->setSelectedChanged(QString("last"));
}
