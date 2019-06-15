#include "catch.hpp"

#include "IndexError.hpp"

TEST_CASE("Index error shows correct message", "[core][sudoku]")
{
//    std::string("Given index (") + std::to_string(row) + ',' + std::to_string(column) + ") out of range [0,8]"
    REQUIRE_THROWS_WITH(throw IndexError(10, 9), "Given index (10,9) out of range [0,8]");
}
