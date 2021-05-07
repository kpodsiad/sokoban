#ifndef SOKOBAN_SOKOBANLIB_H
#define SOKOBAN_SOKOBANLIB_H

#include <map>
#include <vector>
#include <unordered_set>
#include <sstream>
#include <stack>
#include <deque>
#include <set>
#include <queue>
#include <set>
#include <cstdlib>
#include <iostream>
#include <array>
#include <functional>
#include <algorithm>

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
	int x;
	int y;

	inline bool operator<(const Point &other) const {
		return std::tie(x, y) < std::tie(other.x, other.y);
	};

	inline bool operator==(const Point &other) const {
		return x == other.x && y == other.y;
	};

	inline size_t dist(Point &other) {
		size_t dx = abs(x - other.x);
		size_t dy = abs(y - other.y);
		return dx + dy;
	};

	std::string toString() const {
		std::stringstream ss;
		ss << "(" << this->x << ", " << this->y << ")";
		return ss.str();
	}
} Point;

namespace std {
	template<>
	struct hash<Point> {
		long operator()(const Point &point) const {
			return ((long) point.x << 32) | point.y;
		}
	};
}

typedef std::unordered_set<Point> Points;

typedef struct Board {
	int width;
	int height;
	Points walls;
} Board;


void readBoard(Board &board, Points &boxes, Points &targets, Point &worker, std::istream &in);

std::tuple<std::deque<char>, bool> findPathToTheBox(Board &board, Point &worker, Point &target);

std::deque<char> findPathFromTheBoxToTheTarget(Board &board, Point &box, Point &target);

std::deque<char> solveProblem(Board &board, Points boxes, Points targets, Point worker);

#endif //SOKOBAN_SOKOBANLIB_H