#include "SudokuBoardWithNotes.hpp"

SudokuBoardWithNotes::SudokuBoardWithNotes(const SudokuBoard & board)
    : SudokuBoard(board)
{
}

SudokuBoardWithNotes::SudokuBoardWithNotes(SudokuBoard && board)
    : SudokuBoard(board)
{
}

SudokuBoardWithNotes &SudokuBoardWithNotes::operator=(const SudokuBoard & board)
{
    SudokuBoard::operator=(board);
    notedNumbers.reset();
    return *this;
}

SudokuBoardWithNotes &SudokuBoardWithNotes::operator=(SudokuBoard && board)
{
    SudokuBoard::operator=(board);
    notedNumbers.reset();
    return *this;
}

void SudokuBoardWithNotes::noteNumber(SudokuIndex index, unsigned short number)
{
    SudokuBoard::clearField(index);
    std::size_t internalIndex = getStartInternalIndex(index) + number - 1;
    notedNumbers.set(internalIndex);
}

std::bitset<9> SudokuBoardWithNotes::getNotedNumbers(SudokuIndex index) const
{
    std::bitset<9> numbers;
    std::size_t internalIndex = getStartInternalIndex(index);

    for (std::size_t i = 0; i < 9; ++i)
    {
        if (notedNumbers.test(internalIndex))
            numbers.set(i);
        ++internalIndex;
    }

    return numbers;
}

void SudokuBoardWithNotes::setNumber(SudokuIndex index, unsigned short number)
{
    clearField(index);
    SudokuBoard::setNumber(index, number);
}

void SudokuBoardWithNotes::clearField(SudokuIndex index)
{
    SudokuBoard::clearField(index);
    std::size_t internalIndex = getStartInternalIndex(index);

    for (std::size_t i = 0; i < 9; ++i)
    {
        notedNumbers.reset(internalIndex);
        ++internalIndex;
    }
}

bool SudokuBoardWithNotes::isFieldEmpty(SudokuIndex index) const
{
    return SudokuBoard::isFieldEmpty(index) && !isFieldNoted(index);
}

bool SudokuBoardWithNotes::isFieldInNotedMode(SudokuIndex index)
{
    return !isFieldNoted(index);
}

std::size_t SudokuBoardWithNotes::getStartInternalIndex(const SudokuIndex &index) const
{
    return index.getRow() * 81 + index.getColumn() * 9;
}

bool SudokuBoardWithNotes::isFieldNoted(const SudokuIndex &index) const
{
    std::size_t internalIndex = getStartInternalIndex(index);

    for (std::size_t i = 0; i < 9; ++i)
    {
        if (notedNumbers.test(internalIndex))
            return false;
        ++internalIndex;
    }

    return true;
}
