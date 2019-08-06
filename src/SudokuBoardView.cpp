#include "SudokuBoardView.hpp"

#include <QPaintEvent>
#include <QPainter>
#include <QPen>

#include <cmath>

SudokuBoardView::SudokuBoardView(QWidget * parent)
    : QWidget(parent)
{
    setMinimumSize(400, 400);
    setFocusPolicy(Qt::StrongFocus);
    generateNewBoard();
}

void SudokuBoardView::generateNewBoard()
{
    sudokuBoard = SudokuBoard::generateBoard();
    hideFieldsInBoard(20.f);
    selectedRow = -1;
    selectedColumn = -1;
    repaint();
}

void SudokuBoardView::resizeEvent(QResizeEvent *event)
{
    calculateFieldsSize(event->size());
    calculateBoardStartingPoint();
}

void SudokuBoardView::paintEvent(QPaintEvent * /*event*/)
{
    QPainter painter(this);

    const auto boardLeftMargin = bigRectFrame / 2;
    const auto boardTopMargin = bigRectFrame / 2;
    const auto bigRectStartingPoint = startingPoint + QPoint(boardLeftMargin, boardTopMargin);

    const auto bigRectWidth = bigRectFrame + 2 * smallRectFrame + 3 * fieldWidth;

    const auto smallRectWidth = fieldWidth + 1;
    const QSize smallRectSize(smallRectWidth, smallRectWidth);
    const auto miniRectSize = smallRectSize / 3;

    auto font = painter.font();
    font.setPixelSize(static_cast<int>(smallRectWidth*0.8));
    painter.setFont(font);

    auto miniFont = font;
    miniFont.setPixelSize(static_cast<int>(smallRectWidth * 0.25));

    QBrush brush(Qt::white);
    painter.setBrush(brush);

    QPen bigRectPen;
    bigRectPen.setWidth(bigRectFrame);
    bigRectPen.setColor(Qt::black);

    QPen smallRectPen;
    smallRectPen.setWidth(smallRectFrame);
    smallRectPen.setColor(Qt::black);

    // -------------------------------------

    // big squares
    painter.setPen(bigRectPen);
    drawBigSquares(painter, bigRectStartingPoint, bigRectWidth);

    // small squares
    painter.setPen(smallRectPen);

    for (int x = 0; x < 3; ++x)
    {
        for (int y = 0; y < 3; ++y)
        {
            auto point = startingPoint + QPoint(bigRectFrame - 1, bigRectFrame - 1) + QPoint(x * bigRectWidth, y * bigRectWidth);
            if (bigRectFrame % 2)
            {
                point.rx() += bigRectFrame / 2;
                point.ry() += bigRectFrame / 2;
            }
            else
            {
                point.rx() += bigRectFrame / 2 - 1;
                point.ry() += bigRectFrame / 2 - 1;
            }

            for (int k = 0; k < 3; ++k)
            {
                for (int g = 0; g < 3; ++g)
                {
                    auto smallRectStartPoint = point + QPoint(k * smallRectWidth, g * smallRectWidth);
                    QRect rect(smallRectStartPoint, smallRectSize);
                    painter.drawRect(rect);

                    auto row = y * 3 + g;
                    auto column = x * 3 + k;
                    SudokuIndex index(static_cast<unsigned short>(row), static_cast<unsigned short>(column));

                    drawBackgroundInSmallSquare(painter, rect, index);
                    drawTextInSmallSquare(painter, index, rect, smallRectStartPoint, miniRectSize, font, miniFont);
                }
            }
        }
    }
}

void SudokuBoardView::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key::Key_Shift)
    {
        //sudokuBoard.hideFields(50.f);
        notingMode = !notingMode;
        repaint();
    }

    if (selectedRow == -1 || selectedColumn == -1)
        return;

    if (event->isAutoRepeat())
        return;

    auto key = event->key();

    if (!handleArrowKey(key))
        handleNumberKey(key);
}

void SudokuBoardView::mousePressEvent(QMouseEvent *event)
{
    auto mousePosition = event->pos();

    for (short row = 0; row < 9; ++row)
    {
        for (short column = 0; column < 9; ++column)
        {
            QPoint shiftBorders(bigRectFrame*(column/3+1) + smallRectFrame*(column-column/3), bigRectFrame*(row/3+1) + smallRectFrame*(row-row/3));
            QPoint shiftFields(fieldWidth*column, fieldWidth*row);
            QRect fieldRect(startingPoint + shiftBorders + shiftFields, QSize(fieldWidth, fieldWidth));

            if (fieldRect.contains(mousePosition))
            {
                selectedRow = row;
                selectedColumn = column;
                repaint();
                return;
            }
        }
    }

    selectedRow = -1;
    selectedColumn = -1;
    repaint();
}

void SudokuBoardView::drawBigSquares(QPainter & painter, const QPoint & startPoint, int width)
{
    for (int x = 0; x < 3; ++x)
    {
        for (int y = 0; y < 3; ++y)
        {
            QRect bigRect(startPoint + QPoint(x * width, y * width),
                          QSize(width, width));
            painter.drawRect(bigRect);
        }
    }
}

void SudokuBoardView::drawBackgroundInSmallSquare(QPainter &painter, QRect rect, const SudokuIndex & index)
{
    rect -= QMargins(1, 1, 0, 0);

    if (blockedFields.test(static_cast<size_t>(index.getRow() * 9 + index.getColumn())))
    {
        painter.fillRect(rect, QColor::fromRgb(220, 220, 220));
    }
    else if (index.getRow() == selectedRow && index.getColumn() == selectedColumn)
    {
        if (!notingMode)
            painter.fillRect(rect, QColor::fromRgb(161, 224, 227));
        else
            painter.fillRect(rect, Qt::blue);
    }
}

void SudokuBoardView::drawTextInSmallSquare(QPainter & painter, const SudokuIndex & index, const QRect & rect, const QPoint & rectStartPoint, const QSize & miniRectSize,
                                            const QFont & normalFont, const QFont & miniFont)
{
    if (!sudokuBoard.isFieldInNotedMode(index))
    {
        auto text = sudokuBoard.getFieldAsString(index);
        painter.drawText(rect, Qt::AlignCenter, QString::fromStdString(text));
    }
    else
    {
        auto numbers = sudokuBoard.getNotedNumbers(index);

        for (std::size_t i = 0; i < 9; ++i)
        {
            if (numbers.test(i))
            {
                QRect miniRect(rectStartPoint + QPoint(static_cast<int>(i % 3) * miniRectSize.width(), static_cast<int>(i / 3) * miniRectSize.width()), miniRectSize);

                painter.setFont(miniFont);
                painter.drawText(miniRect, Qt::AlignCenter, QString::number(i+1));
                painter.setFont(normalFont);
            }
        }
    }
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

    startingPoint = area.topLeft() + QPoint(leftMargin, topMargin);
}

void SudokuBoardView::hideFieldsInBoard(float percentage)
{
    sudokuBoard.hideFields(percentage);
    blockedFields.reset();

    for (unsigned short row = 0; row < 9; ++row)
        for (unsigned short column = 0; column < 9; ++column)
            if (sudokuBoard.getNumber({row, column}) != 0)
                blockedFields.set(row * 9 + column);
}

void SudokuBoardView::flipNumberInField(const SudokuIndex & index, unsigned short number)
{
    if (notingMode)
    {
        if (sudokuBoard.getNotedNumbers(index).test(number - 1))
            sudokuBoard.clearNote(index, number);
        else
            sudokuBoard.noteNumber(index, number);
    }
    else
    {
        if (sudokuBoard.getNumber(index) == number)
            sudokuBoard.clearField(index);
        else
            sudokuBoard.setNumber(index, number);
    }
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
    if (blockedFields.test(static_cast<size_t>(selectedRow * 9 + selectedColumn)))
        return false;

    auto keyValue = getNumKeyValue(key);

    if (keyValue != 0)
    {
        SudokuIndex index(static_cast<unsigned short>(selectedRow), static_cast<unsigned short>(selectedColumn));
        flipNumberInField(index, keyValue);
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
