#include "PVImageFileSearcher.h"

PVImageFileSearcher::PVImageFileSearcher(QString &path)
{
    filePaths.clear();
    curPath = path;
}

void PVImageFileSearcher::run()
{
    getDir();
    findImageFiles();
}

QStringList PVImageFileSearcher::getFilePaths()
{
    return filePaths;
}

QString PVImageFileSearcher::getCurDir()
{
    return curPath;
}


void PVImageFileSearcher::findImageFiles()
{
    QDir path(curPath);
    if(!path.exists())
        return;

    QStringList filters;
    filters<<QString("*.jpeg")<<QString("*.jpg") \
           <<QString("*.png")<<QString("*.bmp");

    QDirIterator dirIterator(curPath,
                             filters,
                             QDir::Files | QDir::NoSymLinks,
                             QDirIterator::Subdirectories);

    while(dirIterator.hasNext())
    {
        dirIterator.next();
        QFileInfo fileInfo = dirIterator.fileInfo();
        QString relPath = fileInfo.absoluteFilePath();
        filePaths.append(relPath);
    }
}

void PVImageFileSearcher::getDir()
{
    QString s_NeedToDel = "";
    QStringList s_Strings = curPath.split("/");
    for(int i = 0; i < s_Strings.count(); i++)
    {
        QString tmp = s_Strings.at(i);
        if(tmp.contains("."))
        {
            s_NeedToDel = tmp;
            break;
        }
    }
    int delCnt = s_NeedToDel.count();
    curPath.chop(delCnt);
}
