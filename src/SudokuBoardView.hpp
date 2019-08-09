#ifndef SUDOKUBOARDVIEW_HPP
#define SUDOKUBOARDVIEW_HPP

#include "SudokuBoardWithNotes.hpp"

#include <QWidget>

class SudokuBoardView : public QWidget
{
    Q_OBJECT

public:
    explicit SudokuBoardView(QWidget * parent = nullptr);

public slots:
    void generateNewBoard();
    void clearCurrentField();
    void flipNotingMode();
    void revealCurrentField();

protected:
    void resizeEvent(QResizeEvent * event) override;
    void paintEvent(QPaintEvent * event) override;
    virtual void keyPressEvent(QKeyEvent * event) override;
    virtual void mousePressEvent(QMouseEvent * event) override;

private:
    void drawBigSquares(QPainter & painter, const QPoint & startPoint, int width) const;
    void drawBackgroundInSmallSquare(QPainter & painter, QRect rect, const SudokuIndex & index) const;
    void drawTextInSmallSquare(QPainter & painter, const SudokuIndex & index, const QRect & rect, const QPoint & rectStartPoint, const QSize & miniRectSize,
                               const QFont & normalFont, const QFont & miniFont) const;

    void calculateFieldsSize(const QSize & newSize);
    void calculateBoardStartingPoint();

    bool isCurrentFieldModifiable() const;

    void hideFieldsInBoard(float percentage);
    void flipNumberInField(const SudokuIndex & index, unsigned short number);

    bool handleArrowKey(int key);
    bool handleNumberKey(int key);
    unsigned short getNumKeyValue(int key);

private:
    constexpr static short bigRectFrame = 2;
    constexpr static short smallRectFrame = 1;

    SudokuBoardWithNotes sudokuBoard;
    SudokuBoard solvedBoard;

    std::bitset<81> blockedFields;
    short selectedRow = -1;
    short selectedColumn = -1;

    int fieldWidth;
    QPoint startingPoint;

    bool notingMode = false;
};

#endif // SUDOKUBOARDVIEW_HPP
