#include "ClickLinesGameBuilder.h"

#include <QVBoxLayout>

#include "ClickLinesGame.h"
#include "COMMON/GUI/ColorLinesWidget.h"
#include "COMMON/GUI/StatusBar.h"

void ClickLinesGameBuilder::createGame(AbstractColorLinesGame *&game,
                                       QWidget *&widget)
{
    ClickLinesGame *gameNew = new ClickLinesGame;
    game = gameNew;

    QWidget *w = new QWidget;
    widget = w;

    QVBoxLayout *mainLayout = new QVBoxLayout(w);

    StatusBar *bar = new StatusBar(game);
    mainLayout->addWidget(bar);

    /// Виджет игрового поля
    {
        ColorLinesWidget *linesWidget = new ColorLinesWidget(game);

        linesWidget->setElementType(ColorLinesWidget::CIRCLE);
        linesWidget->setElementWidth(0.6);
        mainLayout->addWidget(linesWidget);
    }

    mainLayout->setMargin(0);
}

QString ClickLinesGameBuilder::getName() const
{
    return "Click Lines";
}

QIcon ClickLinesGameBuilder::getIcon() const
{
    return QIcon(":/icons/icons/clicklines_ico.png");
}
