#ifndef SUDOKUBOARD_HPP
#define SUDOKUBOARD_HPP

#include "SudokuIndex.hpp"

#include <vector>
#include <string>

class SudokuBoard
{
public:
    SudokuBoard();

    unsigned short getNumber(SudokuIndex index) const;
    std::string getFieldAsString(SudokuIndex index) const;
    void setNumber(SudokuIndex index, unsigned short number);
    void clearField(SudokuIndex index);
    bool isFieldEmpty(SudokuIndex index) const;

    void hideFields(float percentage);

    bool doesFieldCollide(SudokuIndex index) const;
    bool isSolved() const;
    bool isFilled() const;

    static SudokuBoard generateBoard();

private:
    static unsigned short toInternalIndex(const SudokuIndex & index);

private:
    std::vector<unsigned short> numbers;
};

#endif // SUDOKUBOARD_HPP
