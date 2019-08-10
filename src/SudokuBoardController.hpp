#ifndef SUDOKUBOARDCONTROLLER_HPP
#define SUDOKUBOARDCONTROLLER_HPP

#include "SudokuBoardView.hpp"
#include "SudokuGameplay.hpp"

class QMouseEvent;
class QKeyEvent;

class SudokuBoardController
{
public:
    SudokuBoardController(SudokuGameplay & sudokuData, SudokuBoardView & view);

    void generateNewBoard();
    void clearCurrentField();
    void flipNotingMode();
    void revealCurrentField();

    void mousePressEvent(QMouseEvent * event);
    void keyPressEvent(QKeyEvent * event);

    bool isCurrentFieldModifiable() const;

    void hideFieldsInBoard(float percentage);
    void flipNumberInField(const SudokuIndex & index, unsigned short number);

    bool handleArrowKey(int key);
    bool handleNumberKey(int key);
    unsigned short getNumKeyValue(int key);

private:
    SudokuGameplay & sudokuGameplay;
    SudokuBoard solvedBoard;
    SudokuBoardView & view;
};

#endif // SUDOKUBOARDCONTROLLER_HPP
