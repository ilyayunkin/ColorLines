#-------------------------------------------------
#
# Project created by QtCreator 2016-05-27T09:44:51
#
#-------------------------------------------------

QT       += core gui
CONFIG += c++11
QMAKE_CXXFLAGS+= -Wall -Werror -Wextra

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ClickLines
TEMPLATE = app

INCLUDEPATH += ../

SOURCES += main.cpp\
    ../COMMON/INTERFACES/AbstractColorLinesGame.cpp \
    ../COMMON/MAP/ColorLinesTile.cpp \
    ../COMMON/MAP/ColorLinesTileMap.cpp \
    ../COMMON/GUI/ColorLinesWidget.cpp \
    ../COMMON/GUI/ChampionsTable.cpp \
    ClickLinesGame.cpp \
    ClickLinesGameBuilder.cpp \
    ../COMMON/INTERFACES/AbstractGameBuilder.cpp \
    ../COMMON/GUI/StatusBar.cpp

HEADERS  += ../COMMON/INTERFACES/AbstractColorLinesGame.h \
    ../COMMON/MAP/ColorLinesTile.h \
    ../COMMON/MAP/ColorLinesTileMap.h \
    ../COMMON/GUI/ColorLinesWidget.h \
    ../COMMON/GUI/ChampionsTable.h \
    ClickLinesGame.h \
    ClickLinesGameBuilder.h \
    ../COMMON/INTERFACES/AbstractGameBuilder.h \
    ../COMMON/GUI/StatusBar.h
