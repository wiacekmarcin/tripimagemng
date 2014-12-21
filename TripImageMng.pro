#-------------------------------------------------
#
# Project created by QtCreator 2014-11-09T09:14:53
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TripImageMng
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    adddirdlg.cpp \
    authors.cpp \
    worker.cpp \
    authorinfo.cpp

HEADERS  += mainwindow.h \
    adddirdlg.h \
    authors.h \
    worker.h \
    authorinfo.h

FORMS    += mainwindow.ui \
    adddirdlg.ui \
    workers.ui \
    authorinfo.ui \
    workerthread.ui
