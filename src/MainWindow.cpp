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

    QPushButton * newGameButton = createButton(*buttons, "New Game");
    connect(newGameButton, &QPushButton::clicked, [&sudokuController](){ sudokuController.generateNewBoard(); });

    QHBoxLayout * bottomButtons = new QHBoxLayout;
    lay->addLayout(bottomButtons);

    /*QPushButton * undoButton = */createButton(*bottomButtons, "Undo");

    QPushButton * clearButton = createButton(*bottomButtons, "Clear");
    connect(clearButton, &QPushButton::clicked, [&sudokuController](){ sudokuController.clearCurrentField(); });

    QPushButton * penButton = createButton(*bottomButtons, "Pen");
    connect(penButton, &QPushButton::clicked, [&sudokuController](){ sudokuController.flipNotingMode(); });

    QPushButton * clueButton = createButton(*bottomButtons, "Clue");
    connect(clueButton, &QPushButton::clicked, [&sudokuController](){ sudokuController.revealCurrentField(); });
}

QPushButton * MainWindow::createButton(QLayout & layout, const std::string & text)
{
    QPushButton * button = new QPushButton(QString::fromStdString(text));
    layout.addWidget(button);
    return button;
}
