#include "SudokuBoardController.hpp"

#include <QMouseEvent>
#include <QKeyEvent>

SudokuBoardController::SudokuBoardController(SudokuGameplay & sudokuData, SudokuBoardView & view)
    : sudokuGameplay(sudokuData)
    , view(view)
{
}

void SudokuBoardController::generateNewBoard()
{
    solvedBoard = SudokuBoard::generateBoard();
    sudokuGameplay.sudokuBoard = solvedBoard;
    hideFieldsInBoard(20.f);
    sudokuGameplay.selectedRow = -1;
    sudokuGameplay.selectedColumn = -1;
    view.repaintBoard();
}

void SudokuBoardController::clearCurrentField()
{
    if (sudokuGameplay.selectedRow != -1 && sudokuGameplay.selectedColumn != -1 && isCurrentFieldModifiable())
    {
        sudokuGameplay.sudokuBoard.clearField({static_cast<unsigned short>(sudokuGameplay.selectedRow),
                                static_cast<unsigned short>(sudokuGameplay.selectedColumn)});
        view.repaintBoard();
    }
}

void SudokuBoardController::flipNotingMode()
{
    sudokuGameplay.notingMode = !sudokuGameplay.notingMode;
    view.repaintBoard();
}

void SudokuBoardController::revealCurrentField()
{
    if (sudokuGameplay.selectedRow != -1 && sudokuGameplay.selectedColumn != -1)
    {
        SudokuIndex index(static_cast<unsigned short>(sudokuGameplay.selectedRow), static_cast<unsigned short>(sudokuGameplay.selectedColumn));
        sudokuGameplay.sudokuBoard.setNumber(index, solvedBoard.getNumber(index));
        view.repaintBoard();
    }
}

void SudokuBoardController::mousePressEvent(QMouseEvent * event)
{
    auto mousePosition = event->pos();
    auto viewData = view.getViewData();

    for (short row = 0; row < 9; ++row)
    {
        for (short column = 0; column < 9; ++column)
        {
            QPoint shiftBorders(viewData.bigRectFrame*(column/3+1) + viewData.smallRectFrame*(column-column/3), viewData.bigRectFrame*(row/3+1) + viewData.smallRectFrame*(row-row/3));
            QPoint shiftFields(viewData.fieldWidth*column, viewData.fieldWidth*row);
            QRect fieldRect(viewData.startingPoint + shiftBorders + shiftFields, QSize(viewData.fieldWidth, viewData.fieldWidth));

            if (fieldRect.contains(mousePosition))
            {
                sudokuGameplay.selectedRow = row;
                sudokuGameplay.selectedColumn = column;
                view.repaintBoard();
                return;
            }
        }
    }

    sudokuGameplay.selectedRow = -1;
    sudokuGameplay.selectedColumn = -1;
    view.repaintBoard();
}

void SudokuBoardController::keyPressEvent(QKeyEvent * event)
{
    if (event->key() == Qt::Key::Key_Shift)
        flipNotingMode();

    if (sudokuGameplay.selectedRow == -1 || sudokuGameplay.selectedColumn == -1)
        return;

    if (event->isAutoRepeat())
        return;

    auto key = event->key();

    if (!handleArrowKey(key))
        handleNumberKey(key);
}

bool SudokuBoardController::isCurrentFieldModifiable() const
{
    return !sudokuGameplay.blockedFields.test(static_cast<size_t>(sudokuGameplay.selectedRow * 9 + sudokuGameplay.selectedColumn));
}

void SudokuBoardController::hideFieldsInBoard(float percentage)
{
    sudokuGameplay.sudokuBoard.hideFields(percentage);
    sudokuGameplay.blockedFields.reset();

    for (unsigned short row = 0; row < 9; ++row)
        for (unsigned short column = 0; column < 9; ++column)
            if (sudokuGameplay.sudokuBoard.getNumber({row, column}) != 0)
                sudokuGameplay.blockedFields.set(row * 9 + column);
}

void SudokuBoardController::flipNumberInField(const SudokuIndex & index, unsigned short number)
{
    if (sudokuGameplay.notingMode)
    {
        if (sudokuGameplay.sudokuBoard.getNotedNumbers(index).test(number - 1))
            sudokuGameplay.sudokuBoard.clearNote(index, number);
        else
            sudokuGameplay.sudokuBoard.noteNumber(index, number);
    }
    else
    {
        if (sudokuGameplay.sudokuBoard.getNumber(index) == number)
            sudokuGameplay.sudokuBoard.clearField(index);
        else
            sudokuGameplay.sudokuBoard.setNumber(index, number);
    }
}

bool SudokuBoardController::handleArrowKey(int key)
{
    switch (key)
    {
    case Qt::Key_Up:
        if (sudokuGameplay.selectedRow > 0)
            --sudokuGameplay.selectedRow;
        break;
    case Qt::Key_Down:
        if (sudokuGameplay.selectedRow < 8)
            ++sudokuGameplay.selectedRow;
        break;
    case Qt::Key_Left:
        if (sudokuGameplay.selectedColumn > 0)
            --sudokuGameplay.selectedColumn;
        break;
    case Qt::Key_Right:
        if (sudokuGameplay.selectedColumn < 8)
            ++sudokuGameplay.selectedColumn;
        break;
    default:
        return false;
    }

    view.repaintBoard();
    return true;
}

bool SudokuBoardController::handleNumberKey(int key)
{
    if (!isCurrentFieldModifiable())
        return false;

    auto keyValue = getNumKeyValue(key);

    if (keyValue != 0)
    {
        SudokuIndex index(static_cast<unsigned short>(sudokuGameplay.selectedRow), static_cast<unsigned short>(sudokuGameplay.selectedColumn));
        flipNumberInField(index, keyValue);
        view.repaintBoard();
        return true;
    }
    return false;
}

unsigned short SudokuBoardController::getNumKeyValue(int key)
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
