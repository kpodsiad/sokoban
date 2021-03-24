#include <catch.hpp>

#include <sokobanlib.h>

TEST_CASE("IsSolved returns true for empty locations", "[sokobanlib]")
{
    auto board = Board();
    auto locations = std::vector<Point>();
    CHECK(isSolved(board, locations));
}
