#include "SudokuBoardView.hpp"

#include <QPaintEvent>
#include <QPainter>
#include <QPen>

#include <cmath>

SudokuBoardView::SudokuBoardView(QWidget * parent)
    : QWidget(parent)
{
    setMinimumSize(400, 400);
    sudokuBoard = SudokuBoard::generateBoard();
    setFocusPolicy(Qt::StrongFocus);
}

void SudokuBoardView::resizeEvent(QResizeEvent *event)
{
    calculateFieldsSize(event->size());
    calculateBoardStartingPoint();
}

void SudokuBoardView::paintEvent(QPaintEvent * /*event*/)
{
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
    QBrush brush(Qt::white);
    painter.setBrush(brush);

    fieldWidth++;
    QSize smallSize(fieldWidth, fieldWidth);

    auto font = painter.font();
    font.setPixelSize(static_cast<int>(fieldWidth*0.8));
    painter.setFont(font);

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

                    auto row = j*3+g;
                    auto column = i*3+k;
                    SudokuIndex index(static_cast<unsigned short>(row), static_cast<unsigned short>(column));
                    auto text = sudokuBoard.getFieldAsString(index);

                    if (row == selectedRow && column == selectedColumn)
                    {
                        QRect fillRect = r;
                        fillRect -= QMargins(1, 1, 0, 0);
                        painter.fillRect(fillRect, Qt::blue);
                    }

                    painter.drawText(r, Qt::AlignCenter, QString::fromStdString(text));
                }
            }
        }
    }

    fieldWidth--;
}

void SudokuBoardView::keyPressEvent(QKeyEvent *event)
{
    if (selectedRow == -1 || selectedColumn == -1)
        return;

//    if (event->isAutoRepeat())
//        return;

    auto key = event->key();

    if (!handleArrowKey(key))
        handleNumberKey(key);
}

void SudokuBoardView::mousePressEvent(QMouseEvent *event)
{
    auto mousePosition = event->pos();

    for (short i = 0; i < 9; ++i)
    {
        for (short j = 0; j < 9; ++j)
        {
            QPoint shiftBorders(bigRectFrame*(j/3+1) + smallRectFrame*(j-j/3), bigRectFrame*(i/3+1) + smallRectFrame*(i-i/3));
            QPoint shiftFields(fieldWidth*j, fieldWidth*i);
            QRect fieldRect(startingPoint + shiftBorders + shiftFields - QPoint(1, 1), QSize(fieldWidth, fieldWidth));

            if (fieldRect.contains(mousePosition))
            {
                selectedRow = i;
                selectedColumn = j;
                repaint();
                return;
            }
        }
    }

    selectedRow = -1;
    selectedColumn = -1;
    repaint();
}

void SudokuBoardView::calculateFieldsSize(const QSize & newSize)
{
    fieldWidth = std::min(newSize.width(), newSize.height());
    fieldWidth -= (4*bigRectFrame + 6*smallRectFrame);
    fieldWidth /= 9;
}

void SudokuBoardView::calculateBoardStartingPoint()
{
    auto area = contentsRect();

    auto linesWidth = (4*bigRectFrame + 6*smallRectFrame);
    auto boardWidth = fieldWidth * 9 + linesWidth;

    auto leftMargin = (area.width() - boardWidth) / 2;
    auto topMargin = (area.height() - boardWidth) / 2;

    leftMargin += bigRectFrame / 2;
    topMargin += bigRectFrame / 2;
    startingPoint =  area.topLeft() + QPoint(leftMargin, topMargin);
}

bool SudokuBoardView::handleArrowKey(int key)
{
    switch (key)
    {
    case Qt::Key_Up:
        if (selectedRow > 0)
            --selectedRow;
        break;
    case Qt::Key_Down:
        if (selectedRow < 8)
            ++selectedRow;
        break;
    case Qt::Key_Left:
        if (selectedColumn > 0)
            --selectedColumn;
        break;
    case Qt::Key_Right:
        if (selectedColumn < 8)
            ++selectedColumn;
        break;
    default:
        return false;
    }

    repaint();
    return true;
}

bool SudokuBoardView::handleNumberKey(int key)
{
    auto keyValue = getNumKeyValue(key);

    if (keyValue != 0)
    {
        sudokuBoard.setNumber(SudokuIndex(static_cast<unsigned short>(selectedRow), static_cast<unsigned short>(selectedColumn)),
                              keyValue);
        repaint();
        return true;
    }
    return false;
}

unsigned short SudokuBoardView::getNumKeyValue(int key)
{
    switch (key)
    {
    case Qt::Key_1:
        return 1;
    case Qt::Key_2:
        return 2;
    case Qt::Key_3:
        return 3;
    case Qt::Key_4:
        return 4;
    case Qt::Key_5:
        return 5;
    case Qt::Key_6:
        return 6;
    case Qt::Key_7:
        return 7;
    case Qt::Key_8:
        return 8;
    case Qt::Key_9:
        return 9;
    default:
        return 0;
    }
}
