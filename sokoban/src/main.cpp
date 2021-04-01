#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <sokobanlib.h>
#include <chrono>

using namespace std;

int main() {
	size_t height = 0, width = 0;
	Board startingBoard;
	Point workerPosition;
	queue<BoardState> states;
	vector<Point> targetLocations;
	set<Positions> previousPositions;
	vector<ActionInfo> actions = {MOVE_UP, MOVE_RIGHT, MOVE_DOWN, MOVE_LEFT};

	readBoard(width, height, startingBoard, cin, workerPosition, targetLocations);

	states.push({startingBoard, workerPosition.x, workerPosition.y, ""});
	size_t iteration = 0;
	auto start = chrono::steady_clock::now();
	while (!states.empty()) {
		auto state = states.front();
		states.pop();
		Board board = state.board;

		if (isSolved(board, targetLocations)) {
			cout << state.path << endl;
			break;
		}

		map<Point, char> currentPositions;
		getPositionsFromBoard(board, currentPositions);
		if (previousPositions.find(currentPositions) != previousPositions.end())
			continue;
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
		++iteration;
	}

	auto diff = chrono::steady_clock::now() - start;
	cout << "Iterations: " << iteration << endl;
	cout << chrono::duration <double, milli> (diff).count() << " ms" << endl;

	return 0;
}