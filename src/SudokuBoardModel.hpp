#ifndef SUDOKUGAMEPLAY_HPP
#define SUDOKUGAMEPLAY_HPP

#include "SudokuBoardWithNotes.hpp"

#include <bitset>

struct SudokuBoardModel
{
    SudokuBoardWithNotes sudokuBoard;

    std::bitset<81> blockedFields;

    short selectedRow = -1;
    short selectedColumn = -1;
    bool notingMode = false;
};

#endif // SUDOKUGAMEPLAY_HPP
