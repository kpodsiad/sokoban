#ifndef SOKOBAN_SOKOBANLIB_H
#define SOKOBAN_SOKOBANLIB_H

#include <map>
#include <vector>
#include <unordered_set>
#include <sstream>

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

	inline bool operator==(const Point &other) const {
		return x == other.x && y == other.y;
	};

	std::string toString() const {
		std::stringstream ss;
		ss << "(" << this->x << ", " << this->y << ")";
		return ss.str();
	}
} Point;

namespace std
{
	template<>
	struct hash<Point>
	{
		size_t operator()(const Point & point) const {
			return ((uint64_t)point.x << 32) | point.y;
		}
	};
}

typedef std::unordered_set<Point> Points;

typedef struct Board {
	size_t width;
	size_t height;
	Points walls;
	Point worker;
	Point box;
	Point target;
} Board;


void readBoard(Board &board, std::istream &in);

std::string findPathToTheBox(Board &board);

bool isPointInBoardRange(size_t height, size_t width, long x, long y);

bool couldMoveInDirection(size_t x, size_t y, int dx, int dy, Points &board);

void move(size_t x, size_t y, int dx, int dy, Points &board);

bool pullBoxIfItIsPossible(size_t x, size_t y, int dx, int dy, Points &board);


#endif //SOKOBAN_SOKOBANLIB_H