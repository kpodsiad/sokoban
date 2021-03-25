#include <iostream>
#include <vector>
#include <queue>
#include <sokobanlib.h>

using namespace std;

int main() {
	size_t height = 0, width = 0;
	Board startingBoard;
	Point workerPosition;
	queue<BoardState> states;
	vector<Point> locations;

	readBoard(width, height, startingBoard, cin, workerPosition, locations);
	vector<ActionInfo> actions = {MOVE_UP, MOVE_RIGHT, MOVE_DOWN, MOVE_LEFT};

	states.push({startingBoard, workerPosition, ""});
	while (!states.empty()) {
		auto state = states.front();
		Point workerPos = state.workerPos;
		Board board = state.board;
		if (isSolved(board, locations)) {
			cout << state.history;
		}
		for (auto &action: actions) {
			size_t x = workerPos.x, y = workerPos.y;
			int dx = action.dx, dy = action.dy;
			Point newPos = {x + dx, y + dy};
			if (isPointInBoardRange(height, width, newPos)) {
				if(board[x - dx][y - dy] == BOX) {
					if(pull(x, y, dx, dy, board) /* todo add board history */) {
						states.push({board, newPos, state.history + action.pullChar});
					}
				}
			}
		}

		states.pop();
	}

	return 0;
}