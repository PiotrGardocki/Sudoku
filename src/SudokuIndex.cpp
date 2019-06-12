#include "SudokuIndex.hpp"
#include "IndexError.hpp"

SudokuIndex::SudokuIndex(unsigned short row, unsigned short column)
    : row(row), column(column)
{
    validateIndex();
}

void SudokuIndex::setCoord(unsigned short row, unsigned short column)
{
    this->row = row;
    this->column = column;

    validateIndex();
}

void SudokuIndex::setRow(unsigned short row)
{
    this->row = row;
    validateIndex();
}

void SudokuIndex::setColumn(unsigned short column)
{
    this->column = column;
    validateIndex();
}

unsigned short SudokuIndex::getRow() const
{
    return row;
}

unsigned short SudokuIndex::getColumn() const
{
    return column;
}

void SudokuIndex::validateIndex() const
{
    if (row > 8 || column > 8)
        throw IndexError(row, column);
}
