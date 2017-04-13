/** @file
  * @author Yunkin Ilya.
  */
#ifndef PATHSEARCHTOWIDTH_H
#define PATHSEARCHTOWIDTH_H

#include <QQueue>
#include <QMap>

#include "ColorLinesTile.h"

/// Класс, реализующий алгоритм "Поиск в глубину".
class PathSearchToWidth
{
    /// Очередь тайлов на проверку
    QQueue<ColorLinesTile *> openQueue;
    /// Дерево, к котором ключ - тайл, значение - откуда на него пришли.
    QMap<ColorLinesTile *, ColorLinesTile*> tileParentMap;

    /**
     * @brief Ставит тайл в очередь на посещение, если он свободен
     * и не связан еще ни с одни "родителем".
     * @param child Тайл для постановки в очередь.
     * @param parent "Родитель" - тайл, с которого пришли на указанный тайл.
     */
    void enqueueChild(ColorLinesTile *child, ColorLinesTile *parent);
public:
    /**
     * @brief Выполняет поиск пути через незанятые клеточки.
     * @param from Начальная точка маршрута
     * @param to Желаемая конечная точка маршрута.
     * @param path Возвращаемый путь, если он имеется.
     * @return true если путь существует.
     */
    bool search(ColorLinesTile *from, ColorLinesTile *to,
                QList<ColorLinesTile *> &path);
};

#endif // PATHSEARCHTOWIDTH_H
