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

private:
    constexpr static short bigRectFrame = 2;
    constexpr static short smallRectFrame = 1;

    QPoint getBoardStartingPoint(const QRect & area);

    SudokuBoard sudokuBoard;
    unsigned short selectedRow = 0;
    unsigned short selectedColumn = 0;
};

#endif // SUDOKUBOARDVIEW_HPP
