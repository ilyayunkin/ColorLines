/** @file
  * @author Yunkin Ilya.
  */
#ifndef JUSTANOTHERLINES_H
#define JUSTANOTHERLINES_H

#include "AbstractColorLinesGame.h"

#include <QSharedPointer>

class JustAnotherLines;
class AdapterData;

/// Класс объекта-модели, подсказывающего следующий ход.
class Adapter : public AbstractColorLinesGame
{
    Q_OBJECT
    /// Приватная реализация
    QSharedPointer<AdapterData> data;
    /// Объект игры, для которой выполняется подсказка.
    JustAnotherLines *game;
private slots:
    void update();
public:
    Adapter(JustAnotherLines *game, QObject *parent = 0);
    ~Adapter();
    int getRowCount() const;
    int getColCount() const;
    ColorLinesTile *getRootTile() const;
    ColorLinesTile *getSelectedTile() const;
    QList<ColorLinesTile *> const&getPath() const;
};

class GameData;

enum
{
    /// Количество фишек, появляющихся за один раз.
    BALLS_IN_STEP = 3,
};

/// Набор цветов фишек, появляющихся за один ход
struct NextColors
{
    ColorLinesTile::Color color[BALLS_IN_STEP];
};

/// Реализация игры "Цветные линии"
class JustAnotherLines : public AbstractColorLinesGame
{
    Q_OBJECT
    friend class Adapter;
    /// Приватная реализация
    QSharedPointer<GameData> data;
    /// Возвращает цвета фишек, которые появятся на следующим ходе.
    NextColors getNextColors();
public:
    explicit JustAnotherLines(QObject *parent = 0);
    int getRowCount() const;
    int getColCount() const;
    int getCoins() const;
    int getCombo() const;
    const QString &getStatistics() const;
    ColorLinesTile *getRootTile() const;
    ColorLinesTile *getSelectedTile() const;
    QList<ColorLinesTile *> const&getPath() const;

    /// Обрабатывает случай поражения.
    void lose();
    /// Возвращает указатель на объект-модель,
    /// подсказывающий следующий ход.
    AbstractColorLinesGame *getAdapter();

private slots:
    void update();

public slots:
    void tileClicked(int col, int row);
};

#endif // JUSTANOTHERLINES_H
