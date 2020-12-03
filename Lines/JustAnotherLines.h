/** @file
  * @author Yunkin Ilya.
  */
#ifndef JUSTANOTHERLINES_H
#define JUSTANOTHERLINES_H

#include "../COMMON/INTERFACES/AbstractColorLinesGame.h"

#include <memory>
#include <vector>

class JustAnotherLines;
class AdapterData;

/// Класс объекта-модели, подсказывающего следующий ход.
class Adapter : public AbstractColorLinesGame
{
    Q_OBJECT
    /// Приватная реализация
    std::unique_ptr<AdapterData> data;
    /// Объект игры, для которой выполняется подсказка.
    JustAnotherLines *game;
    Adapter();
    Adapter(Adapter&);
private slots:
    void update();
public:
    Adapter(JustAnotherLines *game, QObject *parent = 0);
    ~Adapter();
    int getRowCount() const override;
    int getColCount() const override;
    ColorLinesTile *getRootTile() const override;
    ColorLinesTile *getSelectedTile() const override;
    std::vector<ColorLinesTile *> const&getPath() const override;
};

class ColorLinesGameData;

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
    std::unique_ptr<ColorLinesGameData> data;
    /// Возвращает цвета фишек, которые появятся на следующим ходе.
    NextColors getNextColors() const;
public:
    explicit JustAnotherLines(QObject *parent = 0);
    ~JustAnotherLines();
    int getRowCount() const override;
    int getColCount() const override;
    int getCoins() const;
    int getCombo() const;
    const QString &getStatistics() const override;
    ColorLinesTile *getRootTile() const override;
    ColorLinesTile *getSelectedTile() const override;
    std::vector<ColorLinesTile *> const&getPath() const override;

    /// Обрабатывает случай поражения.
    void lose();
    /// Возвращает указатель на объект-модель,
    /// подсказывающий следующий ход.
    AbstractColorLinesGame *getAdapter();

private slots:
    void update();

public slots:
    void tileClicked(int col, int row) override;
};

#endif // JUSTANOTHERLINES_H
