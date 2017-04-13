#-------------------------------------------------
#
# Project created by QtCreator 2016-05-18T08:08:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ColorLines
TEMPLATE = app

INCLUDEPATH += ../

SOURCES += main.cpp\
    ../COMMON/GUI/ChampionsTable.cpp \
    ColorLinesTile.cpp \
    PathSearchToWidth.cpp \
    JustAnotherLines.cpp \
    AbstractColorLinesGame.cpp \
    ColorLinesWidget.cpp \
    ColorLinesTileMap.cpp \
    GameData.cpp \
    MainWidget.cpp

HEADERS  += \
    ../COMMON/GUI//trunk/ChampionsTable.h \
    ColorLinesTile.h \
    PathSearchToWidth.h \
    JustAnotherLines.h \
    AbstractColorLinesGame.h \
    ColorLinesWidget.h \
    ColorLinesTileMap.h \
    GameData.h \
    MainWidget.h
    COMMON/sign.h \
