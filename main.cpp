#include <iostream>
#include <map>
#include <vector>

using namespace std;

enum Field {
	wall = '#', box = '0', target = '*', worker = '-', newline = '\n', empty = ' '
};

typedef tuple<size_t, size_t> Point;
typedef map<Point, char> Board;

Board &readBoard(size_t &width, size_t &height, Board &board);
bool isSolved(Board &board, vector<Point> &locations);

int main() {
	size_t height = 0, width = 0;
	map<tuple<size_t, size_t>, char> board;
	readBoard(width, height, board);

	for(auto & it : board)
		cout << "(" << get<0>(it.first) << ", " << get<1>(it.first) << "): " << it.second << endl;

	cout << board.size() << " " << width << " " << height;

	return 0;
}

Board &readBoard(size_t &width, size_t &height, Board &board) {
	char c;
	size_t x = 0, y = 0;
	cin >> height >> width;
	cout << height << " " << width << endl;
	cin.unsetf(ios_base::skipws);
	while (cin && (x != width || y != height)) {
		cin >> c;
		if (c != empty && c != newline) {
			board[make_tuple(x, y)] = c;
		}
		if (c == newline) {
			x = 1;
			++y;
		} else {
			++x;
		}
	}
	cin.setf(ios_base::skipws);
	return board;
}

bool isSolved(Board &board, vector<Point> &locations) {
	for (auto &it : locations) {
		auto found = board.find(it);
		if (found == board.end() || found->second != box) {
			return false;
		}
	}
	return true;
}
