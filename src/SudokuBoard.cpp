#include "SudokuBoard.hpp"

#include <stdexcept>

SudokuBoard::SudokuBoard()
    : numbers(9, std::vector<unsigned short>(9, 0))
{
}

unsigned short SudokuBoard::getNumber(SudokuIndex index)
{
    return numbers[index.getRow()][index.getColumn()];
}

std::string SudokuBoard::getFieldAsString(SudokuIndex index)
{
    auto number = getNumber(index);

    if (number == 0)
        return "";
    return std::to_string(number);
}

bool SudokuBoard::setNumber(SudokuIndex index, unsigned short number)
{
    if (number < 1 || number > 9)
        throw std::runtime_error(std::string("Field in sudoku board can have only value in range [1,9], given: ") + std::to_string(number));

    numbers[index.getRow()][index.getColumn()] = number;
}

void SudokuBoard::setFieldAsEmpty(SudokuIndex index)
{
    // empty field has value 0
    numbers[index.getRow()][index.getColumn()] = 0;
}

bool SudokuBoard::isFieldEmpty(SudokuIndex index)
{
    // empty field has value 0
    return getNumber(index) == 0;
}
