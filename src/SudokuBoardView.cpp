#include "SudokuBoardView.hpp"
#include "SudokuBoardModel.hpp"
#include "SudokuFieldDelegate.hpp"

#include <QPaintEvent>
#include <QPainter>
#include <QResizeEvent>
#include <QPen>

#include <cmath>

SudokuBoardView::SudokuBoardView(QWidget * parent)
    : QWidget(parent)
{
    setMinimumSize(400, 400);
}

void SudokuBoardView::paintEvent(QPaintEvent *event)
{
    auto rect = event->rect();
    auto fieldWidth = std::min(rect.width(), rect.height());
    fieldWidth -= (4*bigRectFrame + 6*smallRectFrame);
    fieldWidth /= 9;

    auto startingPoint = getBoardStartingPoint(rect);

    auto bigRectSize = bigRectFrame + 3*fieldWidth + 2*smallRectFrame;
    QRect bigRect(startingPoint, QSize(bigRectSize, bigRectSize));

    QPainter painter(this);

    QPen pen;
    pen.setWidth(bigRectFrame);
    pen.setColor(Qt::black);
    painter.setPen(pen);

    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            auto innerRect = bigRect;
            innerRect.setX(innerRect.x() + i*bigRectSize);
            innerRect.setY(innerRect.y() + j*bigRectSize);
            painter.drawRect(innerRect);
        }
    }

    pen.setWidth(smallRectFrame);
    painter.setPen(pen);

    fieldWidth++;
    QSize smallSize(fieldWidth, fieldWidth);

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            auto point = startingPoint + QPoint(i*bigRectSize, j*bigRectSize);
            if (bigRectFrame % 2)
            {
                point.rx() += bigRectFrame/2;
                point.ry() += bigRectFrame/2;
            }
            else
            {
                point.rx() += bigRectFrame/2 - 1;
                point.ry() += bigRectFrame/2 - 1;
            }

            for (int k = 0; k < 3; ++k)
            {
                for (int g = 0; g < 3; ++g)
                {
                    auto newPoint = point + QPoint(k*fieldWidth, g*fieldWidth);
                    QRect r(newPoint, smallSize);
                    painter.drawRect(r);
                }
            }
        }
    }
}

QPoint SudokuBoardView::getBoardStartingPoint(const QRect &area)
{
    auto fieldWidth = std::min(area.width(), area.height());
    auto linesWidth = (4*bigRectFrame + 6*smallRectFrame);
    fieldWidth -= linesWidth;
    fieldWidth /= 9;

    auto boardWidth = fieldWidth * 9 + linesWidth;

    auto leftMargin = (area.width() - boardWidth) / 2;
    auto topMargin = (area.height() - boardWidth) / 2;

    leftMargin += bigRectFrame / 2;
    topMargin += smallRectFrame / 2;

    return area.topLeft() + QPoint(leftMargin, topMargin);
}
