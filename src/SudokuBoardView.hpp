#ifndef SUDOKUBOARDVIEW_HPP
#define SUDOKUBOARDVIEW_HPP

#include "SudokuBoard.hpp"

#include <QWidget>

class SudokuBoardView : public QWidget
{
    Q_OBJECT

public:
    SudokuBoardView(QWidget * parent = nullptr);

    void paintEvent(QPaintEvent * event) override;

protected:
    virtual void keyPressEvent(QKeyEvent * event) override;
    virtual void mousePressEvent(QMouseEvent * event) override;

private:
    QPoint getBoardStartingPoint(const QRect & area);
    bool handleArrowKey(int key);
    bool handleNumberKey(int key);
    unsigned short getNumKeyValue(int key);

private:
    constexpr static short bigRectFrame = 2;
    constexpr static short smallRectFrame = 1;

    SudokuBoard sudokuBoard;
    short selectedRow = -1;
    short selectedColumn = -1;

    int fieldWidth;
    QPoint startingPoint;
};

#endif // SUDOKUBOARDVIEW_HPP
