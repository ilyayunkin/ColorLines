/** @file
  * @author Yunkin Ilya.
  */
#ifndef JALWIDGET_H
#define JALWIDGET_H

#include <QWidget>

#include "AbstractColorLinesGame.h"

/// Виджет, представляющий окно игры "Цветные линии"
class ColorLinesWidget : public QWidget
{
    Q_OBJECT

public:
    typedef enum
    {
        CIRCLE,
        RECTANGLE
    }elementType_t;

private:
    AbstractColorLinesGame *game;

    int side;
    float plotToWidgetScale;
    float widgetToPlotScale;

    int horizontalBorder;
    int verticalBorder;

    const int plotWidth;
    int cellWidth;

    elementType_t elementType;
    float elementWidth;

    void drawElement(QPainter &p, ColorLinesTile *tile, int x, int y);
    void drawPath(QPainter &p);

    void paintEvent(QPaintEvent *e);
    void resizeEvent(QResizeEvent * event);
    void mouseReleaseEvent(QMouseEvent *e);
    void keyPressEvent(QKeyEvent *e);
    void keyReleaseEvent(QKeyEvent *e);
public:
    ColorLinesWidget(AbstractColorLinesGame *game, QWidget *parent = 0);
    void setElementType(elementType_t elementType);
    void setElementWidth(float elementWidth);
    ~ColorLinesWidget();
};

#endif // JALWIDGET_H
