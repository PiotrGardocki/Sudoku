#include "catch.hpp"

#include "SudokuIndex.hpp"
#include "IndexError.hpp"

#include <vector>
#include <limits>

TEST_CASE("SudokuIndex - initial values are 0", "[core][sudoku]")
{
    SudokuIndex index;
    CHECK(index.getRow() == 0);
    REQUIRE(index.getColumn() == 0);
}

TEST_CASE("SudokuIndex - setting and getting values", "[core][sudoku]")
{
    unsigned short row = 1, col = 2;
    SudokuIndex index;

    SECTION("Values given in constructor")
        index = SudokuIndex(row, col);
    SECTION("Values given in setters")
    {
        index.setRow(row);
        index.setColumn(col);
    }
    SECTION("Values given in setCoord()")
        index.setCoord(row, col);

    CHECK(index.getRow() == row);
    REQUIRE(index.getColumn() == col);
}

TEST_CASE("SudokuIndex - incorrect values", "[core][sudoku]")
{
    std::vector<unsigned short> incorrectValues = {9, 10, 100, std::numeric_limits<unsigned short>::max()};
    SudokuIndex index;

    for (const auto & value : incorrectValues)
    {
        DYNAMIC_SECTION("Values given in constructor, current value: " << value)
            CHECK_THROWS_AS(index = SudokuIndex(value, value), IndexError);
        DYNAMIC_SECTION("Values given in setters, current value: " << value)
        {
            CHECK_THROWS_AS(index.setRow(value), IndexError);
            CHECK_THROWS_AS(index.setColumn(value), IndexError);
        }
        DYNAMIC_SECTION("Values given in setCoord(), current value: " << value)
            CHECK_THROWS_AS(index.setCoord(value, value), IndexError);
    }
}
