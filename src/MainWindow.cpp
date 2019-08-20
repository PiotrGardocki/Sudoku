#include "MainWindow.hpp"
#include "SudokuWidget.hpp"
#include "ButtonWithCounter.hpp"
#include "NewGameDialog.hpp"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QFile>

MainWindow::MainWindow(QWidget * parent)
    : QMainWindow(parent)
{
//    QFile stylesheetFile("style.css");
//    stylesheetFile.open(QFile::OpenModeFlag::ReadOnly);
//    setStyleSheet(QString::fromLatin1(stylesheetFile.readAll()));

    QWidget * widget = new QWidget;
    setCentralWidget(widget);

    QVBoxLayout * lay = new QVBoxLayout;
    widget->setLayout(lay);

    QHBoxLayout * buttons = new QHBoxLayout;
    lay->addLayout(buttons);

    SudokuWidget * sudoku = new SudokuWidget;
    lay->addWidget(sudoku);

    sudokuController = &sudoku->getController();

    QPushButton * newGameButton = createButton<QPushButton>(*buttons, "New Game");
    connect(newGameButton, &QPushButton::clicked, this, &MainWindow::startNewGame);

    QHBoxLayout * bottomButtons = new QHBoxLayout;
    lay->addLayout(bottomButtons);

    QPushButton * undoButton = createButton<QPushButton>(*bottomButtons, "Undo");
    connect(undoButton, &QPushButton::clicked, [this](){ sudokuController->undoState(); });

    QPushButton * clearButton = createButton<QPushButton>(*bottomButtons, "Clear");
    connect(clearButton, &QPushButton::clicked, [this](){ sudokuController->clearCurrentField(); });

    QPushButton * penButton = createButton<QPushButton>(*bottomButtons, "Pen");
    connect(penButton, &QPushButton::clicked, [this](){ sudokuController->flipNotingMode(); });

    clueButton = createButton<ButtonWithCounter>(*bottomButtons, "Clue");
    clueButton->connectFunction([this](){ return sudokuController->revealCurrentField(); });

    connect(sudoku, &SudokuWidget::sudokuSolved, this, &MainWindow::startNewGame);

    dialog = new NewGameDialog(this);
}

void MainWindow::startNewGame()
{
    dialog->exec();
    auto percent = dialog->getLevel();

    sudokuController->generateNewBoard(percent);
    clueButton->setMaxTimesToClick(3);
}
