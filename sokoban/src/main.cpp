#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <sokobanlib.h>

using namespace std;

int main() {
	size_t height = 0, width = 0;
	Board startingBoard;
	Point workerPosition;
	queue<BoardState> states;
	vector<Point> targetLocations;
	set<string> previousPaths;
	set<Positions> previousPositions;
	vector<ActionInfo> actions = {MOVE_UP, MOVE_RIGHT, MOVE_DOWN, MOVE_LEFT};

	readBoard(width, height, startingBoard, cin, workerPosition, targetLocations);

	states.push({startingBoard, workerPosition.x, workerPosition.y, ""});
	while (!states.empty()) {
		auto state = states.front();
		states.pop();
		Board board = state.board;

		if (isSolved(board, targetLocations)) {
			cout << state.path;
			break;
		}

		if (previousPaths.find(state.path) != previousPaths.end()) {
			continue;
		}

		map<Point, char> currentPositions;
		getPositionsFromBoard(board, currentPositions);
		if (previousPositions.find(currentPositions) != previousPositions.end()) {
			continue;
		}

		previousPaths.insert(state.path);
		previousPositions.insert(currentPositions);

		for (auto &action: actions) {
			size_t x = state.workerPosX, y = state.workerPosY;
			int dx = action.dx, dy = action.dy;

			if (isPointInBoardRange(height, width, x + dx, y + dy) && couldMoveInDirection(x, y, dx, dy, board)) {
				char actionLetter;
				// if box is adjacent to worker maybe he can pullBoxIfItIsPossible it?
				if (pullBoxIfItIsPossible(x, y, dx, dy, board)) {
					actionLetter = action.pullChar;
				} else {
					move(x, y, dx, dy, board);
					actionLetter = action.moveChar;
				}

				states.push({board, x + dx, y + dy, state.path + actionLetter});
				// back to default state
				board = state.board;
			}
		}
	}

	return 0;
}