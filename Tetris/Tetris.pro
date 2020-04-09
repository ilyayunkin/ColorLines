#-------------------------------------------------
#
# Project created by QtCreator 2016-05-20T16:35:12
#
#-------------------------------------------------

QT       += core gui
CONFIG += c++14
QMAKE_CXXFLAGS+= -Wall -Werror -Wextra

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
    Block.cpp \
    TetrisGameBuilder.cpp \
    ../COMMON/INTERFACES/AbstractGameBuilder.cpp \
    ../COMMON/GUI/StatusBar.cpp

HEADERS  += ../COMMON/INTERFACES/AbstractColorLinesGame.h \
    ../COMMON/MAP/ColorLinesTile.h \
    ../COMMON/MAP/ColorLinesTileMap.h \
    ../COMMON/GUI/ColorLinesWidget.h \
    TetrisGame.h \
    ../COMMON/GUI/ChampionsTable.h \
    Block.h \
    TetrisCommon.h \
    TetrisGameBuilder.h \
    ../COMMON/INTERFACES/AbstractGameBuilder.h \
    ../COMMON/GUI/StatusBar.h
