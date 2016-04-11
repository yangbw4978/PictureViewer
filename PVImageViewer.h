#ifndef PVIMAGEVIEWER_H
#define PVIMAGEVIEWER_H

#include <QObject>
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QEvent>
#include <QWheelEvent>
#include <QCursor>
#include <QLabel>
#include <QBrush>
#include <QImage>
#include <QToolButton>
#include <QAction>
#include <QGroupBox>
#include <QPixmap>
#include <math.h>
#include <PVObserver.h>

class PVImageViewer : public QWidget, public PVObserver
{
    Q_OBJECT
public:
    PVImageViewer();
    void setFilePath(QString &path);
    void updateViewer();
    void closeViewer();
    bool eventFilter(QObject *obj, QEvent *e);
    void updateData(QVariant &data);
public slots:
    void zoomIn();
    void zoomOut();
private:
    void initPVImageViewer();
    void initData();
    void initGUI();
    void connectSignal2Slot();
    void updatePosDisplay(const QString pos);
private:
    //widget
    QGraphicsView *m_graphicsView;
    QGraphicsScene m_noPictureScene;
    QGraphicsScene m_mainScene;
    QLabel *m_positionDisplay;

    QGroupBox *m_toolBox;
    QToolButton *m_zoomInBtn;
    QToolButton *m_zoomOutBtn;
    //data
    QString fileDir;
    QImage *curImage;
    bool isImageChanged;
    bool hasFile;
    QPointF curPos;
};

#endif // PVIMAGEVIEWER_H
