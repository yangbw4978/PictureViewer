#ifndef PVIMAGEVIEWER_H
#define PVIMAGEVIEWER_H

#include <QObject>
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSplitter>
#include <QEvent>
#include <QWheelEvent>
#include <QCursor>
#include <QLabel>
#include <QBrush>
#include <QImage>
#include <math.h>
#include <PVObserver.h>

class PVImageViewerMainScene : public QGraphicsScene
{
    Q_OBJECT
public:
    PVImageViewerMainScene(QWidget *parent = 0);


protected:
    //void mousePressEvent(QGraphicsSceneMouseEvent *event);
    //void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    //void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

class PVImageViewer : public QWidget, public PVObserver
{
    Q_OBJECT
public:
    PVImageViewer();
    void setFilePath(QString &path);
    void updateViewer();
    bool eventFilter(QObject *obj, QEvent *e);
    void updateData(QVariant &data);

private:
    void initPVImageViewer();
    void initData();
    void initGUI();
    void updatePosDisplay(const QString pos);
private:
    //widget
    QGraphicsView *m_graphicsView;
    QGraphicsScene m_noPictureScene;
    QGraphicsScene m_mainScene;
    QLabel *m_positionDisplay;

    //data
    QString fileDir;
    QImage *curImage;
    bool isImageChanged;
    bool hasFile;
    QRectF initRectF;
    QPointF curPos;
};

#endif // PVIMAGEVIEWER_H
