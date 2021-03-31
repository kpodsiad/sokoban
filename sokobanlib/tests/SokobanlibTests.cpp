#include <catch.hpp>

#include <sokobanlib.h>
#include <sstream>

TEST_CASE("isSolved returns true for empty locations", "[sokobanlib]") {
	auto board = Board();
	auto locations = std::vector<Point>();
	CHECK(isSolved(board, locations));
}

TEST_CASE("isSolved returns true when boxes are at locations", "[sokobanlib]") {
	Board board = {
			{BOX,         EMPTY_SPACE, EMPTY_SPACE},
			{EMPTY_SPACE, EMPTY_SPACE, BOX},
			{EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE},
	};
	auto locations = std::vector<Point>{{0, 0},
	                                    {1, 2}};
	CHECK(isSolved(board, locations));
}

TEST_CASE("isSolved returns false when not boxes are at locations", "[sokobanlib]") {
	Board board = {
			{EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE},
			{EMPTY_SPACE, BOX,         BOX},
			{EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE},
	};
	auto locations = std::vector<Point>{{0, 0},
	                                    {1, 2}};
	CHECK_FALSE(isSolved(board, locations));
}

TEST_CASE("readBoard reads board as a string input", "[sokobanlib]") {
	std::stringstream ss;
	ss << "3 3" << std::endl;
	ss << "O##" << std::endl;
	ss << " *-" << std::endl;
	ss << "# #" << std::endl;
	size_t width, height;
	auto board = Board();
	Point workerPos;
	std::vector<Point> locations;
	readBoard(width, height, board, ss, workerPos, locations);

	CHECK(board.size() == 3);
	for(auto &it: board) {
		CHECK(it.size() == 3);
	}
	CHECK(board[0][0] == BOX);
	CHECK(board[0][2] == WALL);
	CHECK(board[1][0] == WALL);
	CHECK(board[1][1] == EMPTY_SPACE);
	CHECK(board[2][0] == WALL);
	CHECK(board[2][1] == WORKER);
	CHECK(board[2][2] == WALL);

	CHECK(workerPos == Point{2, 1});

	CHECK(locations.size() == 1);
	CHECK(locations[0] == Point{1,1});
	CHECK(std::find(locations.begin(), locations.end(), (Point) {1, 1}) != locations.end());
}

TEST_CASE("isPointInBoardRange should return true for points within board range", "[sokobanlib]") {
	CHECK(isPointInBoardRange(3, 3, 2, 2));
	CHECK(isPointInBoardRange(3, 3, 0, 0));
	CHECK(isPointInBoardRange(3, 3, 1, 2));
}

TEST_CASE("isPointInBoardRange should return false for points not in board range", "[sokobanlib]") {
	CHECK_FALSE(isPointInBoardRange(3, 3, 0, 3));
	CHECK_FALSE(isPointInBoardRange(3, 3, 3, 0));
	CHECK_FALSE(isPointInBoardRange(3, 3, 2, 4));
	CHECK_FALSE(isPointInBoardRange(3, 3, -1, 2));
}

TEST_CASE("can move should return false when pulling is not possible", "[sokobanlib]") {
	std::stringstream ss;
	ss << "3 3" << std::endl;
	ss << "#O#" << std::endl;
	ss << "O-O" << std::endl;
	ss << "#O#" << std::endl;
	size_t width, height;
	Board board;
	Point workerPos;
	std::vector<Point> locations;
	readBoard(width, height, board, ss, workerPos, locations);
	CHECK_FALSE(couldMoveInDirection(1, 1, MOVE_UP.dx, MOVE_UP.dy, board));
	CHECK_FALSE(couldMoveInDirection(1, 1, MOVE_UP.dx, MOVE_UP.dy, board));
	CHECK_FALSE(couldMoveInDirection(1, 1, MOVE_UP.dx, MOVE_UP.dy, board));
	CHECK_FALSE(couldMoveInDirection(1, 1, MOVE_UP.dx, MOVE_UP.dy, board));
}

Board &getBoard(Board &board, std::istream &in) {
	size_t width, height;
	Point workerPos;
	std::vector<Point> locations;
	readBoard(width, height, board, in, workerPos, locations);
	return board;
}

TEST_CASE("pullBoxIfItIsPossible should return true and modify board when pulling up is possible", "[sokobanlib]") {
	std::stringstream ss;
	ss << "3 3" << std::endl;
	ss << "# #" << std::endl;
	ss << "O-O" << std::endl;
	ss << "#O#" << std::endl;
	Board board;
	getBoard(board, ss);
	CHECK(pullBoxIfItIsPossible(1, 1, MOVE_UP.dx, MOVE_UP.dy, board));
	CHECK(board[1][0] == WORKER);
	CHECK(board[1][1] == BOX);
}

TEST_CASE("pullBoxIfItIsPossible should return true and modify board when pulling right is possible", "[sokobanlib]") {
	std::stringstream ss;
	ss << "3 3" << std::endl;
	ss << "#O#" << std::endl;
	ss << "O-*" << std::endl;
	ss << "#O#" << std::endl;
	Board board;
	getBoard(board, ss);
	CHECK(pullBoxIfItIsPossible(1, 1, MOVE_RIGHT.dx, MOVE_RIGHT.dy, board));
	CHECK(board[2][1] == WORKER);
	CHECK(board[1][1] == BOX);
}

TEST_CASE("pullBoxIfItIsPossible should return true and modify board when pulling down is possible", "[sokobanlib]") {
	std::stringstream ss;
	ss << "3 3" << std::endl;
	ss << "#O#" << std::endl;
	ss << "O-O" << std::endl;
	ss << "# #" << std::endl;
	Board board;
	getBoard(board, ss);
	CHECK(pullBoxIfItIsPossible(1, 1, MOVE_DOWN.dx, MOVE_DOWN.dy, board));
	CHECK(board[1][2] == WORKER);
	CHECK(board[1][1] == BOX);
}

TEST_CASE("pullBoxIfItIsPossible should return true and modify board when pulling left is possible", "[sokobanlib]") {
	std::stringstream ss;
	ss << "3 3" << std::endl;
	ss << "# #" << std::endl;
	ss << "*-O" << std::endl;
	ss << "#O#" << std::endl;
	Board board;
	getBoard(board, ss);
	CHECK(pullBoxIfItIsPossible(1, 1, MOVE_LEFT.dx, MOVE_LEFT.dy, board));
	CHECK(board[0][1] == WORKER);
	CHECK(board[1][1] == BOX);
}

TEST_CASE("move should change worker position", "[sokobanlib]") {
	std::stringstream ss;
	ss << "3 3" << std::endl;
	ss << "# #" << std::endl;
	ss << "*- " << std::endl;
	ss << "#O#" << std::endl;
	Board board;
	getBoard(board, ss);
	move(1, 1, MOVE_LEFT.dx, MOVE_LEFT.dy, board);
	CHECK(board[0][1] == WORKER);
	CHECK(board[1][1] == EMPTY_SPACE);
}

TEST_CASE("getPositionsFromBoard should translate board into positions of player and boxes", "[sokobanlib]") {
	std::stringstream ss;
	ss << "3 3" << std::endl;
	ss << "# #" << std::endl;
	ss << "*- " << std::endl;
	ss << "#O#" << std::endl;
	Board board;
	getBoard(board, ss);
	std::map<Point, char> positions;
	getPositionsFromBoard(board, positions);
	CHECK(positions[{1,1}] == WORKER);
	CHECK(positions[{1,2}] == BOX);
}

