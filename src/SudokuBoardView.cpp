#include "SudokuBoardView.hpp"

#include <QPaintEvent>
#include <QPainter>
#include <QPen>

#include <cmath>

SudokuBoardView::SudokuBoardView(const SudokuBoardModel & model, QWidget & widgetToPaintOn)
    : model(model)
    , widgetToPaintOn(widgetToPaintOn)
{
}

void SudokuBoardView::repaintBoard()
{
    widgetToPaintOn.repaint();
}

const SudokuViewData &SudokuBoardView::getViewData() const
{
    return viewData;
}

void SudokuBoardView::resizeEvent(QResizeEvent *event)
{
    calculateFieldsSize(event->size());
    calculateBoardStartingPoint();
}

void SudokuBoardView::paintEvent(QPaintEvent * /*event*/)
{
    QPainter painter(&widgetToPaintOn);

    const auto boardLeftMargin = viewData.bigRectFrame / 2;
    const auto boardTopMargin = viewData.bigRectFrame / 2;
    const auto bigRectStartingPoint = viewData.startingPoint + QPoint(boardLeftMargin, boardTopMargin);

    const auto bigRectWidth = viewData.bigRectFrame + 2 * viewData.smallRectFrame + 3 * viewData.fieldWidth;

    const auto smallRectWidth = viewData.fieldWidth + 1;
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
    bigRectPen.setWidth(viewData.bigRectFrame);
    bigRectPen.setColor(Qt::black);

    QPen smallRectPen;
    smallRectPen.setWidth(viewData.smallRectFrame);
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
            auto point = viewData.startingPoint + QPoint(viewData.bigRectFrame - 1, viewData.bigRectFrame - 1) + QPoint(x * bigRectWidth, y * bigRectWidth);
            if (viewData.bigRectFrame % 2)
            {
                point.rx() += viewData.bigRectFrame / 2;
                point.ry() += viewData.bigRectFrame / 2;
            }
            else
            {
                point.rx() += viewData.bigRectFrame / 2 - 1;
                point.ry() += viewData.bigRectFrame / 2 - 1;
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

void SudokuBoardView::drawBigSquares(QPainter & painter, const QPoint & startPoint, int width) const
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

void SudokuBoardView::drawBackgroundInSmallSquare(QPainter &painter, QRect rect, const SudokuIndex & index) const
{
    rect -= QMargins(1, 1, 0, 0);

    if (model.blockedFields.test(static_cast<size_t>(index.getRow() * 9 + index.getColumn())))
    {
        painter.fillRect(rect, QColor::fromRgb(220, 220, 220));
    }
    else if (index.getRow() == model.selectedRow && index.getColumn() == model.selectedColumn)
    {
        if (!model.notingMode)
            painter.fillRect(rect, QColor::fromRgb(161, 224, 227));
        else
            painter.fillRect(rect, Qt::blue);
    }
}

void SudokuBoardView::drawTextInSmallSquare(QPainter & painter, const SudokuIndex & index, const QRect & rect, const QPoint & rectStartPoint, const QSize & miniRectSize,
                                            const QFont & normalFont, const QFont & miniFont) const
{
    if (!model.sudokuBoard.isFieldInNotedMode(index))
    {
        auto text = model.sudokuBoard.getFieldAsString(index);
        painter.drawText(rect, Qt::AlignCenter, QString::fromStdString(text));
    }
    else
    {
        auto numbers = model.sudokuBoard.getNotedNumbers(index);

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
    viewData.fieldWidth = std::min(newSize.width(), newSize.height());
    viewData.fieldWidth -= (4*viewData.bigRectFrame + 6*viewData.smallRectFrame);
    viewData.fieldWidth /= 9;
}

void SudokuBoardView::calculateBoardStartingPoint()
{
    auto area = widgetToPaintOn.contentsRect();

    auto linesWidth = (4*viewData.bigRectFrame + 6*viewData.smallRectFrame);
    auto boardWidth = viewData.fieldWidth * 9 + linesWidth;

    auto leftMargin = (area.width() - boardWidth) / 2;
    auto topMargin = (area.height() - boardWidth) / 2;

    viewData.startingPoint = area.topLeft() + QPoint(leftMargin, topMargin);
}
