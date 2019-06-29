#include "MainWindow.hpp"
#include "SudokuBoardView.hpp"

#include <QVBoxLayout>

MainWindow::MainWindow(QWidget * parent)
    : QMainWindow(parent)
{
    QWidget * widget = new QWidget;
    setCentralWidget(widget);

    QVBoxLayout * lay = new QVBoxLayout;
    widget->setLayout(lay);

    SudokuBoardView * view = new SudokuBoardView;
    lay->addWidget(view);
}
