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
	int i =0;
	while (!states.empty()) {
		auto state = states.front();
		Point workerPos = state.workerPos;
		Board board = state.board;

		if (isSolved(board, locations)) {
			cout << state.history;
			break;
		}

		for (auto &action: actions) {
			size_t x = workerPos.x; size_t y = workerPos.y; int dx = action.dx; int dy = action.dy;

			if (isPointInBoardRange(height, width, x + dx, y + dy) && canMoveInDirection(x, y, dx, dy, board)) {
				Point newPos = {x + dx, y + dy};
				// if box is adjacent to worker maybe he can pull it?
				if (pull(x, y, dx, dy, board) /* todo add board history */) {
					states.push({board, newPos, state.history + action.pullChar});
				} else  {
					move(x, y, dx, dy, board);
					states.push({board, newPos, state.history + action.moveChar});
				}
				// back to default state
				board = state.board;
			}
		}

		states.pop();
		++i;
	}

	return 0;
}