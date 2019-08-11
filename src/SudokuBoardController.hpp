#ifndef SUDOKUBOARDCONTROLLER_HPP
#define SUDOKUBOARDCONTROLLER_HPP

#include "SudokuBoardView.hpp"
#include "SudokuBoardModel.hpp"

class QMouseEvent;
class QKeyEvent;

class SudokuBoardController
{
public:
    SudokuBoardController(SudokuBoardModel & sudokuModel, SudokuBoardView & view);

    void generateNewBoard();
    void clearCurrentField();
    void flipNotingMode();
    bool revealCurrentField();

    void mousePressEvent(QMouseEvent * event);
    void keyPressEvent(QKeyEvent * event);

private:
    bool isCurrentFieldModifiable() const;

    void hideFieldsInBoard(float percentage);
    void flipNumberInField(const SudokuIndex & index, unsigned short number);

    bool handleArrowKey(int key);
    bool handleNumberKey(int key);
    unsigned short getNumKeyValue(int key);

private:
    SudokuBoardModel & model;
    SudokuBoard solvedBoard;
    SudokuBoardView & view;
};

#endif // SUDOKUBOARDCONTROLLER_HPP
