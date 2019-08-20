#ifndef SUDOKUWIDGET_HPP
#define SUDOKUWIDGET_HPP

#include "SudokuBoardView.hpp"
#include "SudokuBoardController.hpp"

#include <QWidget>

class SudokuWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SudokuWidget(QWidget * parent = nullptr);

    void resizeEvent(QResizeEvent * event) override;
    void paintEvent(QPaintEvent * event) override;
    void mousePressEvent(QMouseEvent * event) override;
    void keyPressEvent(QKeyEvent * event) override;

    SudokuBoardController & getController();

signals:
    void sudokuSolved();
    void boardFilled(bool won);

private:
    SudokuBoardModel model;
    SudokuBoardView view;
    SudokuBoardController controller;
};

#endif // SUDOKUWIDGET_HPP
