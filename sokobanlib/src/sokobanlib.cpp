#include <sokobanlib.h>
#include <iostream>

bool isSolved(Board &board, std::vector<Point> &locations) {
	for (auto &it : locations) {
		auto found = board[it.x][it.y];
		if (found  != BOX) {
			return false;
		}
	}
	return true;
}

Board &readBoard(size_t &width, size_t &height, Board &board, std::istream &in, Point &workerPosition,
                 std::vector<Point> &locations) {
	char c;
	size_t x = 0, y = -1, read = 0;
	in >> height >> width;
	for(int i=0; i<height; ++i) {
		std::vector<char> v(width, EMPTY_SPACE);
		board.push_back(v);
	}
	auto flags = in.flags();
	in.unsetf(std::ios_base::skipws);
	while (in && read != height * width) {
		in >> c;
		if (c != EMPTY_SPACE && c != NEWLINE) {
			board[x][y] = c;
			if (c == WORKER) {
				workerPosition = {x, y};
			}
			if (c == TARGET) {
				locations.push_back({x, y});
			}
		}
		if (c == NEWLINE) {
			x = 0;
			++y;
		} else {
			++x;
			++read;
		}
	}
	in.setf(flags);
	return board;
}

bool isPointInBoardRange(size_t height, size_t width, long x, long y) {
	return x >= 0 && x < width && y >= 0 && y < height;
}

bool canMoveInDirection(size_t x, size_t y, int dx, int dy, Board &board) {
	auto workerNext = board[x + dx][y + dy];
	if (workerNext != EMPTY_SPACE && workerNext != TARGET) {
		return false;
	}
	return true;
}

void move(size_t x, size_t y, int dx, int dy, Board &board) {
	board[x + dx][y + dy] = WORKER;
	board[x][y] = EMPTY_SPACE;
}

bool pull(size_t x, size_t y, int dx, int dy, Board &board) {
	auto boxInRange = isPointInBoardRange(board.size(), board[0].size(), x - dx, y - dy);
	if (!boxInRange || board[x - dx][y - dy] != BOX)
		return false;
	
	board[x + dx][y + dy] = WORKER;
	board[x][y] = BOX;
	board[x - dx][y - dy] = EMPTY_SPACE;
	return true;
}