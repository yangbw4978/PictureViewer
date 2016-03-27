#ifndef PVIMAGELISTVIEWER_H
#define PVIMAGELISTVIEWER_H

#include <QObject>
#include <QWidget>
#include <QListView>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QPainter>
#include <QItemDelegate>
#include <QMouseEvent>
#include "PVIconModel.h"
#include "PVObserver.h"

class PVImageListViewer : public QWidget, public PVSubject
{
    Q_OBJECT
public:
    PVImageListViewer();
    ~PVImageListViewer();
    void setImagePathData(QString &curDir, QStringList &data);
    QString getSelectedItem();
    void notifyAllObservers();
public slots:
    void selectListViewItem(QModelIndex index);
private:
    void initPVImageListViewer();
    void initGUI();
    void initData();
    void connectSlot2Signal();

private:
    QListView *m_listView;
    PVIconModel* m_dataModel;
    QLabel *m_imagePathLabel;
    QString m_curDir;
    QString m_curPicturePath;
};

#endif // PVIMAGELISTVIEWER_H
