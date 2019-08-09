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

    QHBoxLayout * bottomButtons = new QHBoxLayout;
    lay->addLayout(bottomButtons);

    QPushButton * undoButton = new QPushButton;
    bottomButtons->addWidget(undoButton);
    undoButton->setText("Undo");

    QPushButton * clearButton = new QPushButton;
    bottomButtons->addWidget(clearButton);
    clearButton->setText("Clear");
    connect(clearButton, &QPushButton::clicked, view, &SudokuBoardView::clearCurrentField);

    QPushButton * penButton = new QPushButton;
    bottomButtons->addWidget(penButton);
    penButton->setText("Pen");
    connect(penButton, &QPushButton::clicked, view, &SudokuBoardView::flipNotingMode);

    QPushButton * clueButton = new QPushButton;
    bottomButtons->addWidget(clueButton);
    clueButton->setText("Clue");
    connect(clueButton, &QPushButton::clicked, view, &SudokuBoardView::revealCurrentField);
}
