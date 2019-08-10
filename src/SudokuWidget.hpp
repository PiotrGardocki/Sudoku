#ifndef SUDOKUWIDGET_HPP
#define SUDOKUWIDGET_HPP

#include "SudokuBoardView.hpp"
#include "SudokuBoardController.hpp"

#include <QWidget>

class SudokuWidget : public QWidget
{
public:
    explicit SudokuWidget(QWidget * parent = nullptr);

    void resizeEvent(QResizeEvent * event) override;
    void paintEvent(QPaintEvent * event) override;
    void mousePressEvent(QMouseEvent * event) override;
    void keyPressEvent(QKeyEvent * event) override;

    SudokuBoardController & getController();

private:
    SudokuGameplay sudokuGameplay;
    SudokuBoardView view;
    SudokuBoardController controller;
};

#endif // SUDOKUWIDGET_HPP
