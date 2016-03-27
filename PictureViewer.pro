#-------------------------------------------------
#
# Project created by QtCreator 2016-03-16T22:26:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PictureViewer
TEMPLATE = app


SOURCES += main.cpp\
        PVMainWindow.cpp \
    PVImageViewer.cpp \
    PVImageListViewer.cpp \
    PVIconModel.cpp \
    PVImageFileSeacher.cpp

HEADERS  += PVMainWindow.h \
    PVImageViewer.h \
    PVImageListViewer.h \
    PVIconModel.h \
    PVImageFileSearcher.h \
    PVCommon.h \
    PVObserver.h

FORMS    += pvmainwindow.ui
