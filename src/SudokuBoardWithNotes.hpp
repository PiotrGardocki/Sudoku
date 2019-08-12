#ifndef SUDOKUBOARDWITHNOTES_HPP
#define SUDOKUBOARDWITHNOTES_HPP

#include "SudokuBoard.hpp"

#include <bitset>

class SudokuBoardWithNotes : public SudokuBoard
{
public:
    SudokuBoardWithNotes() = default;

    explicit SudokuBoardWithNotes(const SudokuBoard & board);
    explicit SudokuBoardWithNotes(SudokuBoard && board);

    SudokuBoardWithNotes& operator=(const SudokuBoard & board);
    SudokuBoardWithNotes& operator=(SudokuBoard && board);

    void noteNumber(SudokuIndex index, unsigned short number);
    void applyBitset(SudokuIndex index, std::bitset<9> numbersToNote);
    void clearNote(SudokuIndex index, unsigned short number);
    std::bitset<9> getNotedNumbers(SudokuIndex index) const;

    void setNumber(SudokuIndex index, unsigned short number);
    void clearField(SudokuIndex index);
    bool isFieldEmpty(SudokuIndex index) const;

    bool isFieldInNotedMode(SudokuIndex index) const;

private:
    std::size_t getStartInternalIndex(const SudokuIndex & index) const;
    bool isFieldNoted(const SudokuIndex & index) const;

private:
    std::bitset<81*9> notedNumbers;
};

#endif // SUDOKUBOARDWITHNOTES_HPP
