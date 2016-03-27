#ifndef PVICONMODEL_H
#define PVICONMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QStringList>
#include <QIcon>
#include <QMap>
#include <QVariant>

#include "PVCommon.h"

class PVIconModel : public QAbstractListModel
{
    Q_OBJECT
public:
    PVIconModel(QObject *parent = 0);
    ~PVIconModel();
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    void setIconData(QStringList &data);

private:
    //QMap<QString, QIcon> iconData;
    QStringList iconData;
};

#endif // PVICONMODEL_H
