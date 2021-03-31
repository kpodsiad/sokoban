#ifndef SOKOBAN_SOKOBANLIB_H
#define SOKOBAN_SOKOBANLIB_H

#include <map>
#include <vector>

typedef struct ActionInfo {
	int dx;
	int dy;
	char moveChar;
	char pullChar;
} ActionInfo;

#define MOVE_UP    ActionInfo{0, -1, 'u', 'U'}
#define MOVE_DOWN ActionInfo{0, 1,  'd', 'D'}
#define MOVE_RIGHT  ActionInfo{1, 0,  'r', 'R'}
#define MOVE_LEFT ActionInfo{-1, 0, 'l', 'L'}

#define WALL '#'
#define BOX 'O'
#define TARGET '*'
#define WORKER '-'
#define NEWLINE '\n'
#define EMPTY_SPACE ' '

typedef struct Point {
	size_t x;
	size_t y;

	bool operator<(const Point &other) const {
		return std::tie(x, y) < std::tie(other.x, other.y);
	};

	bool operator==(const Point &other) const {
		return x == other.x && y == other.y;
	};
} Point;

typedef std::vector<std::vector<char>> Board;

typedef struct BoardState {
	Board board;
	size_t workerPosX;
	size_t workerPosY;
	std::string path;
} BoardState;

typedef std::map<Point, char> Positions;


bool isSolved(Board &, std::vector<Point> &);

void readBoard(size_t &w, size_t &h, Board &b, std::istream &in, Point &workerPos, std::vector<Point> &locations);

bool isPointInBoardRange(size_t height, size_t width, long x, long y);

bool couldMoveInDirection(size_t x, size_t y, int dx, int dy, Board &board);

void move(size_t x, size_t y, int dx, int dy, Board &board);

bool pullBoxIfItIsPossible(size_t x, size_t y, int dx, int dy, Board &board);

void getPositionsFromBoard(Board &board, Positions &positions);

#endif //SOKOBAN_SOKOBANLIB_H