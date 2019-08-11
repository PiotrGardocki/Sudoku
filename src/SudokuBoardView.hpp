#ifndef SUDOKUBOARDVIEW_HPP
#define SUDOKUBOARDVIEW_HPP

#include "SudokuBoardModel.hpp"

#include <QWidget>

struct SudokuViewData
{
    constexpr static short bigRectFrame = 2;
    constexpr static short smallRectFrame = 1;

    int fieldWidth;
    QPoint startingPoint;
};

class SudokuBoardView
{
public:
    SudokuBoardView(const SudokuBoardModel & model, QWidget & widgetToPaintOn);

    void repaintBoard();

    const SudokuViewData& getViewData() const;

    void resizeEvent(QResizeEvent * event);
    void paintEvent(QPaintEvent * event);

private:
    void drawBigSquares(QPainter & painter, const QPoint & startPoint, int width) const;
    void drawBackgroundInSmallSquare(QPainter & painter, QRect rect, const SudokuIndex & index) const;
    void drawTextInSmallSquare(QPainter & painter, const SudokuIndex & index, const QRect & rect, const QPoint & rectStartPoint, const QSize & miniRectSize,
                               const QFont & normalFont, const QFont & miniFont) const;

    void calculateFieldsSize(const QSize & newSize);
    void calculateBoardStartingPoint();

private:
    SudokuViewData viewData;
    const SudokuBoardModel & model;
    QWidget & widgetToPaintOn;
};

#endif // SUDOKUBOARDVIEW_HPP
