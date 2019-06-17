#include "catch.hpp"

#include "SudokuBoardModel.hpp"

TEST_CASE("SudokuBoardModel - correct size of board", "[sudoku][model][qt]")
{
    SudokuBoardModel model;

    CHECK(model.rowCount() == 9);
    CHECK(model.columnCount() == 9);
}

TEST_CASE("SudokuBoardModel - empty board", "[sudoku][model][qt]")
{
    SudokuBoardModel model;
    QModelIndex index = model.index(5, 6);

    CHECK(model.data(index, Qt::DisplayRole).toString() == "");

    model.setData(index, "", Qt::EditRole);
    CHECK(model.data(index, Qt::DisplayRole).toString() == "");
}

TEST_CASE("SudokuBoardModel - setting value", "[sudoku][model][qt]")
{
    SudokuBoardModel model;
    QModelIndex index = model.index(5, 6);
    unsigned short value = 3;
    model.setData(index, value, Qt::EditRole);

    SECTION("Setting empty field again")
    {
        model.setData(index, "", Qt::EditRole);
        CHECK(model.data(index, Qt::DisplayRole).toString() == "");
    }
    SECTION("Checking normal value")
    {
        CHECK(model.data(index, Qt::DisplayRole).toString() == "3");
    }
}
