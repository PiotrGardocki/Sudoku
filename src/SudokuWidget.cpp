#include "SudokuWidget.hpp"

SudokuWidget::SudokuWidget(QWidget *parent)
    : QWidget(parent)
    , view(sudokuGameplay, *this)
    , controller(sudokuGameplay, view)
{
    setMinimumSize(400, 400);
    setFocusPolicy(Qt::StrongFocus);
    controller.generateNewBoard();
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
}
