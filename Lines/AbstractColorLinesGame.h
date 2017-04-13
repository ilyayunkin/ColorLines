/** @file
  * @author Yunkin Ilya.
  */
#ifndef ABSTRACTCOLORLINESGAME_H
#define ABSTRACTCOLORLINESGAME_H

#include <QObject>

#include "ColorLinesTile.h"

class AbstractColorLinesGame : public QObject
{
    Q_OBJECT
    const QString emptyString;
public:
    explicit AbstractColorLinesGame(QObject *parent = 0);
    virtual ~AbstractColorLinesGame() = 0;
    virtual int getRowCount() const = 0;
    virtual int getColCount() const = 0;
    virtual const QString &getStatistics() const;
    virtual ColorLinesTile *getRootTile() const = 0;
    virtual ColorLinesTile *getSelectedTile() const = 0;
    virtual QList<ColorLinesTile *> const&getPath() const = 0;
signals:

public slots:
    virtual void tileClicked(int col, int row);
    virtual void keyPressed(int key, Qt::KeyboardModifiers modifiers);
    virtual void keyReleased(int key);
    virtual void pauseToggle();
    virtual void escape();
};

#endif // ABSTRACTCOLORLINESGAME_H
