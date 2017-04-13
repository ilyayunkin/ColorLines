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
    ../Lines/AbstractColorLinesGame.cpp \
    ../Lines/ColorLinesTile.cpp \
    ../Lines/ColorLinesTileMap.cpp \
    ../Lines/ColorLinesWidget.cpp \
    TetrisGame.cpp \
    ../COMMON/GUI/ChampionsTable.cpp

HEADERS  += ../Lines/AbstractColorLinesGame.h \
    ../Lines/ColorLinesTile.h \
    ../Lines/ColorLinesTileMap.h \
    ../Lines/ColorLinesWidget.h \
    TetrisGame.h \
    ../COMMON/GUI/ChampionsTable.h
