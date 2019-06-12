#ifndef SUDOKUBOARD_HPP
#define SUDOKUBOARD_HPP

#include "SudokuIndex.hpp"

#include <vector>
#include <string>

class SudokuBoard
{
public:
    SudokuBoard();

    unsigned short getNumber(SudokuIndex index);
    std::string getFieldAsString(SudokuIndex index);
    bool setNumber(SudokuIndex index, unsigned short number);
    void setFieldAsEmpty(SudokuIndex index);
    bool isFieldEmpty(SudokuIndex index);

private:
    std::vector<std::vector<unsigned short>> numbers;
};

#endif // SUDOKUBOARD_HPP
