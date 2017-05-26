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
    ../COMMON/MAP/ColorLinesTile.cpp \
    ../COMMON/PathSearchToWidth.cpp \
    JustAnotherLines.cpp \
    ../COMMON/INTERFACES/AbstractColorLinesGame.cpp \
    ../COMMON/GUI/ColorLinesWidget.cpp \
    ../COMMON/MAP/ColorLinesTileMap.cpp \
    GameData.cpp \
    MainWidget.cpp

HEADERS  += \
    ../COMMON/GUI/ChampionsTable.h \
    ../COMMON/MAP/ColorLinesTile.h \
    /COMMON/PathSearchToWidth.h \
    JustAnotherLines.h \
    ../COMMON/INTERFACES/AbstractColorLinesGame.h \
    ../COMMON/GUI/ColorLinesWidget.h \
    ../COMMON/MAP/ColorLinesTileMap.h \
    GameData.h \
    MainWidget.h
    COMMON/sign.h \
