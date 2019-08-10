#include "MainWindow.hpp"
#include "SudokuWidget.hpp"

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

    SudokuWidget * sudoku = new SudokuWidget;
    lay->addWidget(sudoku);

    auto& sudokuController = sudoku->getController();

    QPushButton * newGameButton = new QPushButton;
    buttons->addWidget(newGameButton);
    newGameButton->setText("New Game");
    connect(newGameButton, &QPushButton::clicked, [&sudokuController](){ sudokuController.generateNewBoard(); });

    QHBoxLayout * bottomButtons = new QHBoxLayout;
    lay->addLayout(bottomButtons);

    QPushButton * undoButton = new QPushButton;
    bottomButtons->addWidget(undoButton);
    undoButton->setText("Undo");

    QPushButton * clearButton = new QPushButton;
    bottomButtons->addWidget(clearButton);
    clearButton->setText("Clear");
    connect(clearButton, &QPushButton::clicked, [&sudokuController](){ sudokuController.clearCurrentField(); });

    QPushButton * penButton = new QPushButton;
    bottomButtons->addWidget(penButton);
    penButton->setText("Pen");
    connect(penButton, &QPushButton::clicked, [&sudokuController](){ sudokuController.flipNotingMode(); });

    QPushButton * clueButton = new QPushButton;
    bottomButtons->addWidget(clueButton);
    clueButton->setText("Clue");
    connect(clueButton, &QPushButton::clicked, [&sudokuController](){ sudokuController.revealCurrentField(); });
}
