#include "MainWindow.hpp"
#include "SudokuBoardView.hpp"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>

MainWindow::MainWindow(QWidget * parent)
    : QMainWindow(parent)
{
    QWidget * widget = new QWidget;
    setCentralWidget(widget);

    QVBoxLayout * lay = new QVBoxLayout;
    widget->setLayout(lay);

    QHBoxLayout * buttons = new QHBoxLayout;
    lay->addLayout(buttons);

    SudokuBoardView * view = new SudokuBoardView;
    lay->addWidget(view);

    QPushButton * newGameButton = new QPushButton;
    buttons->addWidget(newGameButton);
    newGameButton->setText("New Game");
    connect(newGameButton, &QPushButton::clicked, view, &SudokuBoardView::generateNewBoard);
}
