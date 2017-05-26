#-------------------------------------------------
#
# Project created by QtCreator 2016-05-20T16:35:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Tetris
TEMPLATE = app

INCLUDEPATH += ../

SOURCES += main.cpp\
    ../COMMON/INTERFACES/AbstractColorLinesGame.cpp \
    ../COMMON/MAP/ColorLinesTile.cpp \
    ../COMMON/MAP/ColorLinesTileMap.cpp \
    ../COMMON/GUI/ColorLinesWidget.cpp \
    TetrisGame.cpp \
    ../COMMON/GUI/ChampionsTable.cpp \
    Block.cpp

HEADERS  += ../COMMON/INTERFACES/AbstractColorLinesGame.h \
    ../COMMON/MAP/ColorLinesTile.h \
    ../COMMON/MAP/ColorLinesTileMap.h \
    ../COMMON/GUI/ColorLinesWidget.h \
    TetrisGame.h \
    ../COMMON/GUI/ChampionsTable.h \
    Block.h \
    TetrisCommon.h
