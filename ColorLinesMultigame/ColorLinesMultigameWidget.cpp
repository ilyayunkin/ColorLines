/** @file
  * @author Yunkin Ilya.
  */
#include "ColorLinesMultigameWidget.h"

#include <assert.h>

#include <QHBoxLayout>
#include <QIcon>

#include "Lines/ColorLinesBuilder.h"
#include "Snake/SnakeGameBuilder.h"
#include "Tetris/TetrisGameBuilder.h"

ColorLinesMultigameWidget::ColorLinesMultigameWidget(QWidget *parent)
    : QWidget(parent),
      gameWidget(NULL)
{
    QHBoxLayout *lay = new QHBoxLayout;
    setLayout(lay);

    menuWidget = new MenuWidget;
    lay->addWidget(menuWidget);

    addBuilder(new ColorLinesBuilder);
    addBuilder(new SnakeGameBuilder);
    addBuilder(new TetrisGameBuilder);

    layout()->setMargin(0);
    setWindowIcon(QIcon(":/icons/icons/field.png"));
}

ColorLinesMultigameWidget::~ColorLinesMultigameWidget()
{
}

void ColorLinesMultigameWidget::addBuilder(AbstractGameBuilder *builder)
{
    QPushButton *button = new QPushButton(builder->getIcon(),
                                          builder->getName());

    connect(button, SIGNAL(clicked()), SLOT(runGameClicked()));
    buttonToBuilderMap.insert(button,
                              QSharedPointer<AbstractGameBuilder>(builder));
    menuWidget->addButton(button);
}

void ColorLinesMultigameWidget::runGameClicked()
{
    ButtonToBuilderMap::iterator it = buttonToBuilderMap.find(sender());
    if(it != buttonToBuilderMap.end()){
        runGame((*it).data());
    }
}

void ColorLinesMultigameWidget::runGame(AbstractGameBuilder *builder)
{
    assert(gameWidget == NULL);

    menuWidget->hide();

    {
        AbstractColorLinesGame *game;
        builder->createGame(game, gameWidget);
        this->game = QSharedPointer<AbstractColorLinesGame>(game);
        connect(game, SIGNAL(quitToMenu()), SLOT(quitToMenu()));
    }

    gameWidget->setFocus();
    layout()->addWidget(gameWidget);
}

void ColorLinesMultigameWidget::keyPressEvent(QKeyEvent *e)
{
    e->ignore();
}

void ColorLinesMultigameWidget::keyReleaseEvent(QKeyEvent *e)
{
    e->ignore();
}

void ColorLinesMultigameWidget::quitToMenu()
{
    menuWidget->show();

    {
        layout()->removeWidget(gameWidget);
        delete gameWidget;
        gameWidget = NULL;
    }
    game.clear();
}
