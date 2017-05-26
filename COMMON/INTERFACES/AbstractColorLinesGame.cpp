/** @file
  * @author Yunkin Ilya.
  */
#include "AbstractColorLinesGame.h"
#include <QApplication>

AbstractColorLinesGame::AbstractColorLinesGame(QObject *parent) : QObject(parent)
{

}

AbstractColorLinesGame::~AbstractColorLinesGame()
{

}

const QString &AbstractColorLinesGame::getStatistics() const
{
    return emptyString;
}

void AbstractColorLinesGame::tileClicked(int col, int row)
{
    Q_UNUSED(col);
    Q_UNUSED(row);
}
void AbstractColorLinesGame::keyPressed(int key, Qt::KeyboardModifiers modifiers)
{
    Q_UNUSED(key);
    Q_UNUSED(modifiers);
}
void AbstractColorLinesGame::keyReleased(int key)
{
    Q_UNUSED(key);
}
void AbstractColorLinesGame::pauseToggle()
{
}
void AbstractColorLinesGame::escape()
{
    QApplication::quit();
}
