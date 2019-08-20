#ifndef SUDOKUBOARDCONTROLLER_HPP
#define SUDOKUBOARDCONTROLLER_HPP

#include "SudokuBoardView.hpp"
#include "SudokuBoardModel.hpp"

#include <variant>

class QMouseEvent;
class QKeyEvent;

struct FieldState
{
    SudokuIndex index;
    bool noteMode;
    std::variant<unsigned short, std::bitset<9>> numberState;
};

class SudokuBoardController
{
public:
    SudokuBoardController(SudokuBoardModel & sudokuModel, SudokuBoardView & view);

    void generateNewBoard(float percentageOfDeletedFields);
    void clearCurrentField();
    void flipNotingMode();
    bool revealCurrentField();

    void resetGame();

    void mousePressEvent(QMouseEvent * event);
    void keyPressEvent(QKeyEvent * event);

    bool isSudokuSolved() const;

private:
    bool isCurrentFieldModifiable() const;

    void hideFieldsInBoard(float percentage);
    void flipNumberInField(const SudokuIndex & index, unsigned short number);

    bool handleArrowKey(int key);
    bool handleNumberKey(int key);
    unsigned short getNumKeyValue(int key);

    void saveFieldState(const SudokuIndex & index);

public:
    void undoState();

private:
    SudokuBoardModel & model;
    SudokuBoard solvedBoard;
    SudokuBoardView & view;

    std::vector<FieldState> fieldStates;
};

#endif // SUDOKUBOARDCONTROLLER_HPP
