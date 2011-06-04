#-------------------------------------------------
#
# Project created by QtCreator 2011-05-27T12:40:46
#
#-------------------------------------------------

QT       += core gui

TARGET = earth_viewer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp\
        Exif.cpp\
        region.cpp\
        location.cpp\
        ladybug.cpp\
        quadtree.cpp\
        mapview.cpp \
        imageview.cpp

HEADERS  += mainwindow.h\
        Exif.hpp\
        quadtree.hpp\
        region.hpp\
        location.hpp\
        ladybug.hpp\
        mapview.h \
        imageview.h

FORMS    += mainwindow.ui
