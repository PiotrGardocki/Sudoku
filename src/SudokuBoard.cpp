#include "SudokuBoard.hpp"
#include "vendor/RandomNumbersLibrary/RandomIntegerGenerator.hpp"

#include <stdexcept>
#include <algorithm>

SudokuBoard::SudokuBoard()
    : numbers(81, 0)
{
}

unsigned short SudokuBoard::getNumber(SudokuIndex index) const
{
    return numbers[toInternalIndex(index)];
}

std::string SudokuBoard::getFieldAsString(SudokuIndex index) const
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

bool SudokuBoard::isFieldEmpty(SudokuIndex index) const
{
    // empty field has value 0
    return getNumber(index) == 0;
}

void SudokuBoard::hideFields(float percentage)
{
    if (percentage < 0.f || percentage > 100.f)
        throw std::runtime_error(std::string("Percentage has to be in range [0,100], given: ") + std::to_string(percentage));

    RandomIntegerGenerator<int> condition(0, 1);

    for (auto& number : numbers)
        if (condition())
            number = 0;
}

namespace
{
    struct BigSquare
    {
        unsigned short rowStart;
        unsigned short columnStart;
        unsigned short rowEnd;
        unsigned short columnEnd;
    };

    BigSquare getBigSquare(SudokuIndex index)
    {
        BigSquare square;

        const auto & row = index.getRow();
        const auto & col = index.getColumn();

        if (row < 3)
        {
            square.rowStart = 0;
            square.rowEnd = 2;
        }
        else if (row < 6)
        {
            square.rowStart = 3;
            square.rowEnd = 5;
        }
        else
        {
            square.rowStart = 6;
            square.rowEnd = 8;
        }

        if (col < 3)
        {
            square.columnStart = 0;
            square.columnEnd = 2;
        }
        else if (col < 6)
        {
            square.columnStart = 3;
            square.columnEnd = 5;
        }
        else
        {
            square.columnStart = 6;
            square.columnEnd = 8;
        }

        return square;
    }
}

bool SudokuBoard::doesFieldCollide(SudokuIndex index) const
{
    if (isFieldEmpty(index))
        return false;

    auto number = getNumber(index);

    // collision in row
    for (unsigned short column = 0; column < 9; ++column)
    {
        if (index.getColumn() == column)
            continue;
        if (getNumber(SudokuIndex(index.getRow(), column)) == number)
            return true;
    }

    // collision in column
    for (unsigned short row = 0; row < 9; ++row)
    {
        if (index.getRow() == row)
            continue;
        if (getNumber(SudokuIndex(row, index.getColumn())) == number)
            return true;
    }

    // collision in square (3x3)
    auto bigSquare = getBigSquare(index);

    for (auto row = bigSquare.rowStart; row <= bigSquare.rowEnd; ++row)
        for (auto col = bigSquare.columnStart; col <= bigSquare.columnEnd; ++col)
            if (row != index.getRow() && col != index.getColumn() && number == getNumber(SudokuIndex(row, col)))
                return true;

    return false;
}

namespace
{
    bool previousIndex(SudokuIndex & index)
    {
        auto row = index.getRow();
        auto col = index.getColumn();

        if (row == 0 && col == 0)
            return false;

        if (col > 0)
            --col;
        else
        {
            col = 8;
            --row;
        }

        index.setCoord(row, col);
        return true;
    }

    bool nextIndex(SudokuIndex & index)
    {
        auto row = index.getRow();
        auto col = index.getColumn();

        if (row == 8 && col == 8)
            return false;

        if (col < 8)
            ++col;
        else
        {
            col = 0;
            ++row;
        }

        index.setCoord(row, col);
        return true;
    }
}

SudokuBoard SudokuBoard::generateBoard()
{
    static const std::vector<unsigned short> allNumbers{1, 2, 3, 4, 5, 6, 7, 8, 9};

    // at the beginning in every field every number is possible; we will remove them later
    std::vector<std::vector<unsigned short>> possibleNumbers(81, allNumbers);

    SudokuBoard board;
    SudokuIndex index;

    while (true)
    {
        auto & currentField = possibleNumbers[toInternalIndex(index)];
        unsigned short fieldSize = static_cast<unsigned short>(currentField.size());

        if (fieldSize > 0)
        {
            RandomIntegerGenerator<unsigned short> random(0, fieldSize-1);
            unsigned short numIndex = random();
            unsigned short number = currentField[numIndex];

            currentField.erase(std::find(currentField.begin(), currentField.end(), number));
            board.setNumber(index, number);

            if (!board.doesFieldCollide(index))
            {
                if (!nextIndex(index))
                    break;
            }
            else
                continue;
        }
        else
        {
            board.setFieldAsEmpty(index);
            currentField = allNumbers;
            previousIndex(index);
        }
    }

    return board;
}

unsigned short SudokuBoard::toInternalIndex(const SudokuIndex & index)
{
    return index.getRow() * 9 + index.getColumn();
}
