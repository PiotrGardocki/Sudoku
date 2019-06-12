#ifndef SUDOKUINDEX_HPP
#define SUDOKUINDEX_HPP

class SudokuIndex
{
public:
    SudokuIndex() = default;
    SudokuIndex(unsigned short row, unsigned short column);

    void setCoord(unsigned short row, unsigned short column);
    void setRow(unsigned short row);
    void setColumn(unsigned short column);

    unsigned short getRow() const;
    unsigned short getColumn() const;

private:
    void validateIndex() const;

private:
    unsigned short row = 0;
    unsigned short column = 0;
};

#endif // SUDOKUINDEX_HPP
