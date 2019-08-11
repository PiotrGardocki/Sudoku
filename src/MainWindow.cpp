#include "MainWindow.hpp"
#include "SudokuWidget.hpp"
#include "ButtonWithCounter.hpp"

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

    QPushButton * newGameButton = createButton<QPushButton>(*buttons, "New Game");
    connect(newGameButton, &QPushButton::clicked, [&sudokuController](){ sudokuController.generateNewBoard(); });

    QHBoxLayout * bottomButtons = new QHBoxLayout;
    lay->addLayout(bottomButtons);

    /*QPushButton * undoButton = */createButton<QPushButton>(*bottomButtons, "Undo");

    QPushButton * clearButton = createButton<QPushButton>(*bottomButtons, "Clear");
    connect(clearButton, &QPushButton::clicked, [&sudokuController](){ sudokuController.clearCurrentField(); });

    QPushButton * penButton = createButton<QPushButton>(*bottomButtons, "Pen");
    connect(penButton, &QPushButton::clicked, [&sudokuController](){ sudokuController.flipNotingMode(); });

    ButtonWithCounter * clueButton = createButton<ButtonWithCounter>(*bottomButtons, "Clue");
    clueButton->setMaxTimesToClick(3);
    connect(clueButton, &ButtonWithCounter::clicked, [&sudokuController](){ sudokuController.revealCurrentField(); });
}
