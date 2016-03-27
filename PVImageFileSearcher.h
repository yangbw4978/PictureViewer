#ifndef PVIMAGEFILESEACHER_H
#define PVIMAGEFILESEACHER_H

#include <QThread>
#include <QDir>
#include <QDirIterator>
#include <QFileInfo>

class PVImageFileSearcher : public QThread
{
    Q_OBJECT
public:
    PVImageFileSearcher(QString &path);
    void run();
    QStringList getFilePaths();
    QString getCurDir();

private:
    void findImageFiles();
    void getDir();

private:
    QStringList filePaths;
    QString curPath;
};

#endif // PVIMAGEFILESEACHER_H
