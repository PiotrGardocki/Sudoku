#include "SudokuBoard.hpp"

#include <stdexcept>

SudokuBoard::SudokuBoard()
    : numbers(81, 0)
{
}

unsigned short SudokuBoard::getNumber(SudokuIndex index)
{
    return numbers[toInternalIndex(index)];
}

std::string SudokuBoard::getFieldAsString(SudokuIndex index)
{
    auto number = getNumber(index);

    if (number == 0)
        return "";
    return std::to_string(number);
}

void SudokuBoard::setNumber(SudokuIndex index, unsigned short number)
{
    if (number < 1 || number > 9)
        throw std::runtime_error(std::string("Field in sudoku board can have only value in range [1,9], given: ") + std::to_string(number));

    numbers[toInternalIndex(index)] = number;
}

void SudokuBoard::setFieldAsEmpty(SudokuIndex index)
{
    // empty field has value 0
    numbers[toInternalIndex(index)] = 0;
}

bool SudokuBoard::isFieldEmpty(SudokuIndex index)
{
    // empty field has value 0
    return getNumber(index) == 0;
}

unsigned short SudokuBoard::toInternalIndex(const SudokuIndex & index)
{
    return index.getRow() * 9 + index.getColumn();
}
