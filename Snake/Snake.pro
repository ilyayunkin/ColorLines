#-------------------------------------------------
#
# Project created by QtCreator 2016-05-19T13:58:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

INCLUDEPATH += ../

TARGET = Snake
TEMPLATE = app


SOURCES += main.cpp \
    SnakeGame.cpp \
    ../Lines/AbstractColorLinesGame.cpp \
    ../Lines/ColorLinesTile.cpp \
    ../Lines/ColorLinesTileMap.cpp \
    ../Lines/ColorLinesWidget.cpp \
    ../COMMON/GUI/ChampionsTable.cpp

HEADERS  += \
    SnakeGame.h \
    ../Lines/AbstractColorLinesGame.h \
    ../Lines/ColorLinesTile.h \
    ../Lines/ColorLinesTileMap.h \
    ../Lines/ColorLinesWidget.h \
    ../COMMON/GUI/ChampionsTable.h
