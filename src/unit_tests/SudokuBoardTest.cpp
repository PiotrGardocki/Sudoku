#include "catch.hpp"

#include "SudokuBoard.hpp"

#include <string>

// TODO add tests for all fields

TEST_CASE("SudokuBoard - setting and getting normal values", "[core][sudoku]")
{
    SudokuBoard board;
    const SudokuIndex index(4, 5);
    const unsigned short num = 1;
    board.setNumber(index, num);

    SECTION("Get value as number")
        CHECK(board.getNumber(index) == num);
    SECTION("Get value as string")
        CHECK(board.getFieldAsString(index) == std::to_string(num));
}

TEST_CASE("SudokuBoard - empty fields", "[core][sudoku]")
{
    SudokuBoard board;
    const SudokuIndex index(4, 5);

    SECTION("Check if initial fields are empty")
    {
        CHECK(board.getNumber(index) == 0);
        CHECK(board.getFieldAsString(index) == "");
        CHECK(board.isFieldEmpty(index));
    }

    const unsigned short num = 1;
    board.setNumber(index, num);

    CHECK(!board.isFieldEmpty(index));

    board.setFieldAsEmpty(index);

    SECTION("Check if fields after setting are empty")
    {
        CHECK(board.getNumber(index) == 0);
        CHECK(board.getFieldAsString(index) == "");
        CHECK(board.isFieldEmpty(index));
    }
}
