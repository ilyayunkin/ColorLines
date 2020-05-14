#-------------------------------------------------
#
# Project created by QtCreator 2017-05-26T20:30:02
#
#-------------------------------------------------

QT       += core gui
CONFIG += c++14
QMAKE_CXXFLAGS+= -Wall -Werror -Wextra

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

INCLUDEPATH += ../

TARGET = ColorLinesMultigame
TEMPLATE = app


SOURCES += main.cpp\
        ColorLinesMultigameWidget.cpp \
    ../COMMON/INTERFACES/AbstractColorLinesGame.cpp \
    ../COMMON/INTERFACES/AbstractGameBuilder.cpp \
    ../COMMON/GUI/ChampionsTable.cpp \
    ../COMMON/GUI/ColorLinesWidget.cpp \
    ../COMMON/MAP/ColorLinesTile.cpp \
    ../COMMON/MAP/ColorLinesTileMap.cpp \
    ../Lines/ColorLinesBuilder.cpp \
    ../Lines/GameData.cpp \
    ../Lines/JustAnotherLines.cpp \
    ../Lines/MainWidget.cpp \
    ../Snake/SnakeGame.cpp \
    ../Snake/SnakeGameBuilder.cpp \
    ../COMMON/PathSearchToWidth.cpp \
    ../Tetris/Block.cpp \
    ../Tetris/TetrisGame.cpp \
    ../Tetris/TetrisGameBuilder.cpp \
    MenuWidget.cpp \
    ../COMMON/GUI/StatusBar.cpp \
    ../ClickLines/ClickLinesGame.cpp \
    ../ClickLines/ClickLinesGameBuilder.cpp

HEADERS  += ColorLinesMultigameWidget.h \
    ../COMMON/INTERFACES/AbstractColorLinesGame.h \
    ../COMMON/INTERFACES/AbstractGameBuilder.h \
    ../COMMON/GUI/ChampionsTable.h \
    ../COMMON/GUI/ColorLinesWidget.h \
    ../COMMON/MAP/ColorLinesTile.h \
    ../COMMON/MAP/ColorLinesTileMap.h \
    ../COMMON/MISC/sign.h \
    ../Lines/ColorLinesBuilder.h \
    ../Lines/GameData.h \
    ../Lines/JustAnotherLines.h \
    ../Lines/MainWidget.h \
    ../Snake/SnakeGame.h \
    ../Snake/SnakeGameBuilder.h \
    ../COMMON/PathSearchToWidth.h \
    ../Tetris/Block.h \
    ../Tetris/TetrisCommon.h \
    ../Tetris/TetrisGame.h \
    ../Tetris/TetrisGameBuilder.h \
    MenuWidget.h \
    ../COMMON/GUI/StatusBar.h \
    ../ClickLines/ClickLinesGame.h \
    ../ClickLines/ClickLinesGameBuilder.h

RESOURCES += \
    icons.qrc

DESTDIR= ../bin

win32{
RC_ICONS = icons\icon.ico
}
