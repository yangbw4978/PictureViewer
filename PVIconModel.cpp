#include "PVIconModel.h"


PVIconModel::PVIconModel(QObject *parent)
    :QAbstractListModel(parent)
{
    iconData.clear();
}

PVIconModel::~PVIconModel()
{
    if(!(iconData.isEmpty()))
        iconData.clear();
}

int PVIconModel::rowCount(const QModelIndex &parent) const
{
    return iconData.count();
}

QVariant PVIconModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    if (role == Qt::DecorationRole)
    {
        if(!iconData.isEmpty())
        {
            QString iconPath = iconData.at(index.row());
            QIcon data = QIcon(iconPath);
            return data;
        }
        else
        {
            return QVariant();
        }
    }
    if(role == IMAGEPATHROLE)
    {
        QString iconPath = iconData.at(index.row());
        return iconPath;
    }
    return QVariant();
}

void PVIconModel::setIconData(QStringList &data)
{
    iconData = data;
}


