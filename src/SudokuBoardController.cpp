#include "SudokuBoardController.hpp"

#include <QMouseEvent>
#include <QKeyEvent>

SudokuBoardController::SudokuBoardController(SudokuBoardModel & sudokuModel, SudokuBoardView & view)
    : model(sudokuModel)
    , view(view)
{
}

void SudokuBoardController::generateNewBoard(float percentageOfDeletedFields)
{
    solvedBoard = SudokuBoard::generateBoard();
    model.sudokuBoard = solvedBoard;
    hideFieldsInBoard(percentageOfDeletedFields);
    model.selectedRow = -1;
    model.selectedColumn = -1;
    fieldStates.clear();
    view.repaintBoard();
}

void SudokuBoardController::clearCurrentField()
{
    if (model.selectedRow != -1 && model.selectedColumn != -1 && isCurrentFieldModifiable())
    {
        model.sudokuBoard.clearField({static_cast<unsigned short>(model.selectedRow),
                                static_cast<unsigned short>(model.selectedColumn)});
        view.repaintBoard();
    }
}

void SudokuBoardController::flipNotingMode()
{
    model.notingMode = !model.notingMode;
    view.repaintBoard();
}

bool SudokuBoardController::revealCurrentField()
{
    if (model.selectedRow == -1 || model.selectedColumn == -1 || !isCurrentFieldModifiable())
        return false;

    SudokuIndex index(static_cast<unsigned short>(model.selectedRow), static_cast<unsigned short>(model.selectedColumn));
    model.sudokuBoard.setNumber(index, solvedBoard.getNumber(index));
    model.blockedFields.set(static_cast<size_t>(model.selectedRow * 9 + model.selectedColumn), true);
    view.repaintBoard();
    return true;
}

void SudokuBoardController::resetGame()
{
    model.sudokuBoard = solvedBoard;

    for (unsigned short row = 0; row < 9; ++row)
        for (unsigned short column = 0; column < 9; ++column)
            if (!model.blockedFields.test(static_cast<size_t>(row * 9 + column)))
                model.sudokuBoard.clearField({row, column});
    view.repaintBoard();
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
                model.selectedRow = row;
                model.selectedColumn = column;
                view.repaintBoard();
                return;
            }
        }
    }

    model.selectedRow = -1;
    model.selectedColumn = -1;
    view.repaintBoard();
}

void SudokuBoardController::keyPressEvent(QKeyEvent * event)
{
    if (event->key() == Qt::Key::Key_Shift)
        flipNotingMode();

    if (model.selectedRow == -1 || model.selectedColumn == -1)
        return;

    if (event->isAutoRepeat())
        return;

    auto key = event->key();

    if (!handleArrowKey(key))
        handleNumberKey(key);
}

bool SudokuBoardController::isSudokuSolved() const
{
    return model.sudokuBoard.isSolved();
}

SudokuBoardController::GameState SudokuBoardController::getCurrentState() const
{
    if (!model.sudokuBoard.isFilled())
        return GameState::unsolved;
    if (model.sudokuBoard.isSolved())
        return GameState::win;
    return GameState::lose;
}

bool SudokuBoardController::isCurrentFieldModifiable() const
{
    return !model.blockedFields.test(static_cast<size_t>(model.selectedRow * 9 + model.selectedColumn));
}

void SudokuBoardController::hideFieldsInBoard(float percentage)
{
    model.sudokuBoard.hideFields(percentage);
    model.blockedFields.reset();

    for (unsigned short row = 0; row < 9; ++row)
        for (unsigned short column = 0; column < 9; ++column)
            if (model.sudokuBoard.getNumber({row, column}) != 0)
                model.blockedFields.set(row * 9 + column);
}

void SudokuBoardController::flipNumberInField(const SudokuIndex & index, unsigned short number)
{
    if (model.notingMode)
    {
        if (model.sudokuBoard.getNotedNumbers(index).test(number - 1))
            model.sudokuBoard.clearNote(index, number);
        else
            model.sudokuBoard.noteNumber(index, number);
    }
    else
    {
        if (model.sudokuBoard.getNumber(index) == number)
            model.sudokuBoard.clearField(index);
        else
            model.sudokuBoard.setNumber(index, number);
    }
}

bool SudokuBoardController::handleArrowKey(int key)
{
    switch (key)
    {
    case Qt::Key_Up:
        if (model.selectedRow > 0)
            --model.selectedRow;
        break;
    case Qt::Key_Down:
        if (model.selectedRow < 8)
            ++model.selectedRow;
        break;
    case Qt::Key_Left:
        if (model.selectedColumn > 0)
            --model.selectedColumn;
        break;
    case Qt::Key_Right:
        if (model.selectedColumn < 8)
            ++model.selectedColumn;
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
        SudokuIndex index(static_cast<unsigned short>(model.selectedRow), static_cast<unsigned short>(model.selectedColumn));
        saveFieldState(index);
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

void SudokuBoardController::saveFieldState(const SudokuIndex & index)
{
    FieldState state;
    state.index = index;

    if (model.sudokuBoard.isFieldInNotedMode(index))
    {
        state.noteMode = true;
        auto notedNumbers = model.sudokuBoard.getNotedNumbers(index);
        state.numberState = notedNumbers;
    }
    else
    {
        state.noteMode = false;
        auto number = model.sudokuBoard.getNumber(index);
        state.numberState = number;
    }

    fieldStates.push_back(state);
}

void SudokuBoardController::undoState()
{
    if (fieldStates.size() == 0)
        return;

    auto state = fieldStates.back();

    while (fieldStates.size() != 0 && model.blockedFields.test(static_cast<size_t>(state.index.getRow() * 9 + state.index.getColumn())))
    {
        fieldStates.pop_back();
        state = fieldStates.back();
    }
    if (fieldStates.size() == 0)
        return;

    model.notingMode = state.noteMode;
    if (state.noteMode)
    {
        auto notes = std::get<std::bitset<9>>(state.numberState);
        model.sudokuBoard.applyBitset(state.index, notes);
    }
    else
    {
        auto number = std::get<unsigned short>(state.numberState);
        if (number)
            flipNumberInField(state.index, number);
        else
            model.sudokuBoard.clearField(state.index);
    }

    fieldStates.pop_back();
    view.repaintBoard();
}
