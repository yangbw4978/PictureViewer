#ifndef PVMAINWINDOW_H
#define PVMAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QPixmap>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMenu>
#include <QAction>
#include <QToolBar>
#include <QFileDialog>
#include <QMessageBox>

#include "PVImageViewer.h"
#include "PVImageListViewer.h"
#include "PVIconModel.h"
#include "PVImageFileSearcher.h"

namespace Ui {
class PVMainWindow;
}

class PVMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PVMainWindow(QWidget *parent = 0);
    ~PVMainWindow();

public:
    void initUI();

public slots:
    void openFile();
    void closeAllFiles();
    void changeLastPicture();
    void changeNextPicture();
    void searcherImageFinished();

private:
    void initMainForm();
    void initMenuBar();
    void initToolBar();
    void initCenterWidget();
    void connectSlots2Signals();

private:
    Ui::PVMainWindow *ui;

    //menubar
    QAction *openAction;
    QAction *closeAction;
    QAction *exitAction;
    QAction *lastOne;
    QAction *nextOne;


    //center widget
    PVImageViewer *imageViewer;
    PVImageListViewer *iconsViewer;

    //data model
    PVIconModel *iconsModel;

    //image file seacher thread
    PVImageFileSearcher *imageFinder;
};


#endif // PVMAINWINDOW_H
