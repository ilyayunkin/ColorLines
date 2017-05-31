#-------------------------------------------------
#
# Project created by QtCreator 2016-05-19T13:58:20
#
#-------------------------------------------------

QT       += core gui

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

INCLUDEPATH += ../

TARGET = Snake
TEMPLATE = app


SOURCES += main.cpp \
    SnakeGame.cpp \
    ../COMMON/INTERFACES/AbstractColorLinesGame.cpp \
    ../COMMON/MAP/ColorLinesTile.cpp \
    ../COMMON/MAP/ColorLinesTileMap.cpp \
    ../COMMON/GUI/ColorLinesWidget.cpp \
    ../COMMON/GUI/ChampionsTable.cpp \
    SnakeGameBuilder.cpp \
    ../COMMON/INTERFACES/AbstractGameBuilder.cpp \
    ../COMMON/GUI/StatusBar.cpp

HEADERS  += \
    SnakeGame.h \
    ../COMMON/INTERFACES/AbstractColorLinesGame.h \
    ../COMMON/MAP/ColorLinesTile.h \
    ../COMMON/MAP/ColorLinesTileMap.h \
    ../COMMON/GUI/ColorLinesWidget.h \
    ../COMMON/GUI/ChampionsTable.h \
    SnakeGameBuilder.h \
    ../COMMON/INTERFACES/AbstractGameBuilder.h \
    ../COMMON/GUI/StatusBar.h
