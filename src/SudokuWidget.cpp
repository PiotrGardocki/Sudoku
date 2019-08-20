#include "SudokuWidget.hpp"

SudokuWidget::SudokuWidget(QWidget *parent)
    : QWidget(parent)
    , view(model, *this)
    , controller(model, view)
{
    setMinimumSize(400, 400);
    setFocusPolicy(Qt::StrongFocus);
}

void SudokuWidget::resizeEvent(QResizeEvent *event)
{
    view.resizeEvent(event);
}

void SudokuWidget::paintEvent(QPaintEvent *event)
{
    view.paintEvent(event);
}

void SudokuWidget::mousePressEvent(QMouseEvent *event)
{
    controller.mousePressEvent(event);
}

void SudokuWidget::keyPressEvent(QKeyEvent *event)
{
    controller.keyPressEvent(event);

    auto gameState = controller.getCurrentState();
    switch (gameState)
    {
    case SudokuBoardController::GameState::win:
        emit boardFilled(true);
        break;
    case SudokuBoardController::GameState::lose:
        emit boardFilled(false);
        break;
    default:;
    }
}

SudokuBoardController &SudokuWidget::getController()
{
    return controller;
}
