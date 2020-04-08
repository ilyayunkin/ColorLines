/** @file
  * @author Yunkin Ilya.
  */
#include "ColorLinesWidget.h"

#include <algorithm>

#include <QResizeEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QTimer>

ColorLinesWidget::ColorLinesWidget(AbstractColorLinesGame *game, QWidget *parent)
    : QWidget(parent),
      game(game),
      side(0),
      plotToWidgetScale(0),
      widgetToPlotScale(0),
      horizontalBorder(0),
      verticalBorder(0),
      plotWidth(10000),
      cellWidth(1),
      elementType(RECTANGLE),
      elementWidth(0.5)
{
    float k = float(std::max(game->getColCount(), game->getRowCount())) /
            std::min(game->getColCount(), game->getRowCount());

    int h;
    int w;

    if(game->getColCount() > game->getRowCount()){
        w = 500;
        h = 500 / k;
    }else{
        h = 500;
        w = 500 / k;
    }
    setMinimumSize(w, h);
    resize(w, h);

    QTimer *updateTimer= new QTimer(this);
    connect(updateTimer, SIGNAL(timeout()), SLOT(update()));
    updateTimer->start(10);

    setFocusPolicy(Qt::StrongFocus);
    setSizePolicy(QSizePolicy(QSizePolicy::Expanding,
                              QSizePolicy::Expanding));
}

ColorLinesWidget::~ColorLinesWidget()
{

}

void ColorLinesWidget::drawElement(QPainter &p,
                                   ColorLinesTile *tile,
                                   int x,
                                   int y)
{
    p.setBrush(tile->getQColor());

    float rectSide = cellWidth * elementWidth;
    float spanSize = cellWidth / 2 - rectSide / 2;
    QPointF upLeft(x + spanSize, y + spanSize);
    QPointF downRight(x + spanSize + rectSide, y + spanSize + rectSide);

    QRectF elementRect(upLeft,downRight);

    switch (elementType) {
    case RECTANGLE: p.drawRect(elementRect);
        break;

    case CIRCLE:
    default: p.drawEllipse(elementRect);
        break;
    }
}

void ColorLinesWidget::drawPath(QPainter &p)
{
    for(ColorLinesTile *t: game->getPath()){
        QPoint point = game->getRootTile()->getTileCoordinate(t);
        QPen pen(Qt::darkBlue);
        pen.setWidth(plotWidth / 100);
        p.setPen(pen);
        p.setBrush(QBrush());
        int x = cellWidth * point.x();
        int y = cellWidth * point.y();
        p.drawRect(x, y, cellWidth, cellWidth);
    }
}

void ColorLinesWidget::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QPainter p(this);
    p.scale(plotToWidgetScale, plotToWidgetScale);
    p.translate(horizontalBorder, verticalBorder);

    for(int row = 0; row < game->getRowCount(); row++){
        for(int col = 0; col < game->getColCount(); col++){
            ColorLinesTile *tile = game->getRootTile()->getTile(col, row);
            if(game->getSelectedTile() == tile){
                p.setBrush(Qt::cyan);
            }else{
                p.setBrush(QBrush());
            }
            int x = cellWidth * col;
            int y = cellWidth * row;
            QPen pen(Qt::black);
            pen.setWidth(plotWidth / 1000);
            p.setPen(pen);
            p.drawRect(x, y, cellWidth, cellWidth);
            if(tile->getColor() != ColorLinesTile::NONE){
                drawElement(p, tile, x, y);
            }
        }
    }
    QFont f;
    f.setPixelSize(plotWidth / 100 * 4);
    p.setPen(Qt::black);
    p.setFont(f);

    drawPath(p);
}

void ColorLinesWidget::resizeEvent(QResizeEvent * event)
{
    int h = event->size().height();
    int w = event->size().width();
    if((float(h) / w) < float(game->getRowCount()) / game->getColCount()){
        side = h;
        cellWidth = float(plotWidth) / game->getRowCount();
    }else{
        side = w;
        cellWidth = float(plotWidth) / game->getColCount();
    }
    widgetToPlotScale = float(plotWidth) / side;
    plotToWidgetScale = float(side) / plotWidth;
    horizontalBorder = (w / plotToWidgetScale -
                        cellWidth * game->getColCount())/ 2;
    verticalBorder = (h / plotToWidgetScale -
                      cellWidth * game->getRowCount())/ 2;
}

void ColorLinesWidget::mouseReleaseEvent(QMouseEvent *e)
{
    int xOnPlot = e->pos().x() * widgetToPlotScale - horizontalBorder;
    int yOnPlot = e->pos().y() * widgetToPlotScale - verticalBorder;

    int col = xOnPlot / cellWidth;
    int row = yOnPlot / cellWidth;

    if((col >= 0) && (col < game->getColCount()) &&
            (row >= 0) && (row < game->getRowCount())){
        game->tileClicked(col, row);
    }
}

void ColorLinesWidget::keyPressEvent(QKeyEvent *e)
{
    if(!e->isAutoRepeat()){
        switch(e->key()){
        case Qt::Key_Pause: game->pauseToggle();
            break;
        case Qt::Key_Escape: game->escape();
            break;
        default: game->keyPressed(e->key(), e->modifiers());
            break;
        }
    }
}

void ColorLinesWidget::keyReleaseEvent(QKeyEvent *e)
{
    if(!e->isAutoRepeat()){
        game->keyReleased(e->key());
    }
}

void ColorLinesWidget::setElementType(elementType_t elementType)
{
    this->elementType = elementType;
}

void ColorLinesWidget::setElementWidth(float elementWidth)
{
    this->elementWidth = elementWidth;
}
