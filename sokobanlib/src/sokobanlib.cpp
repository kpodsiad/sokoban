#include <sokobanlib.h>

void readBoard(Board &board, std::istream &in) {
	char c;
	int x = 0, y = -1, read = 0;
	in >> board.height >> board.width;
	auto flags = in.flags();
	in.unsetf(std::ios_base::skipws);
	while (in && read != board.height * board.width) {
		in >> c;
		switch (c) {
			case NEWLINE:
				x = 0;
				++y;
				break;
			case WORKER:
				board.worker = {x, y};
				break;
			case TARGET:
				board.target = {x, y};
				break;
			case BOX:
				board.box = {x, y};
				break;
			case WALL:
				board.walls.insert({x, y});
				break;
			default:
				break;
		}
		if (c != NEWLINE) {
			++x;
			++read;
		}
	}
	in.setf(flags);
}

bool isValidPoint(Board &board, Point &point) {
	if (point.x < 0 || point.x >= board.width || point.y < 0 || point.y >= board.height) {
		return false;
	}
	if (board.walls.find(point) != board.walls.end()) {
		return false;
	}
	return true;
}

size_t dist(ActionInfo const &action, Point &target, Point &currentPos) {
	Point newPos = {currentPos.x + action.dx, currentPos.y + action.dy};
	return target.dist(newPos);
}

bool dfs(Board &board, std::deque<char> &stack, std::set<Point> &visited, Point &currentPos) {
	if (board.target.x == currentPos.x && board.target.y == currentPos.y) {
		return true;
	}
	std::array<std::tuple<size_t, ActionInfo>, 4> actions = {
			std::make_pair(dist(MOVE_UP, board.target, currentPos), MOVE_UP),
			std::make_pair(dist(MOVE_RIGHT, board.target, currentPos), MOVE_RIGHT),
			std::make_pair(dist(MOVE_DOWN, board.target, currentPos), MOVE_DOWN),
			std::make_pair(dist(MOVE_LEFT, board.target, currentPos), MOVE_LEFT)
	};
	sort(actions.begin(), actions.end(),
	     [](std::tuple<size_t, ActionInfo> a, std::tuple<size_t, ActionInfo> b) {
		     return std::get<0>(a) < std::get<0>(b);
	     });

	visited.insert(currentPos);
	for (const std::tuple<size_t, ActionInfo> &tuple: actions) {
		auto action = std::get<1>(tuple);
		Point newPos = {currentPos.x + action.dx, currentPos.y + action.dy};
		if (visited.find(newPos) == visited.end() && isValidPoint(board, newPos)) {
			stack.push_back(action.moveChar);
			if (dfs(board, stack, visited, newPos)) {
				return true;
			} else {
				stack.pop_back();
			}
		}
	}
	return false;
}

ActionInfo getActionInfoFromLetter(char letter) {
	switch (letter) {
		case MOVE_UP.pullChar:
		case MOVE_UP.moveChar:
			return MOVE_UP;
		case MOVE_RIGHT.pullChar:
		case MOVE_RIGHT.moveChar:
			return MOVE_RIGHT;
		case MOVE_DOWN.pullChar:
		case MOVE_DOWN.moveChar:
			return MOVE_DOWN;
		case MOVE_LEFT.pullChar:
		case MOVE_LEFT.moveChar:
			return MOVE_LEFT;
	}
}

bool isBoxValidPoint(Board &board, Point &newBoxPosition, ActionInfo &action) {
	auto newWorkerPos = Point{newBoxPosition.x + action.dx, newBoxPosition.y + action.dy};
	if (newWorkerPos.x < 0 || newWorkerPos.x >= board.width || newWorkerPos.y < 0 || newWorkerPos.y >= board.height) {
		return false;
	}
	if (board.walls.find(newBoxPosition) != board.walls.end() || board.walls.find(newWorkerPos) != board.walls.end()) {
		return false;
	}
	return true;
}

bool boxDfs(Board &board, std::deque<char> &stack, std::set<Point> &visited, Point &currentPos) {
	if (board.target.x == currentPos.x && board.target.y == currentPos.y) {
		return true;
	}
	std::array<std::tuple<size_t, ActionInfo>, 4> actions = {
			std::make_pair(dist(MOVE_UP, board.target, currentPos), MOVE_UP),
			std::make_pair(dist(MOVE_RIGHT, board.target, currentPos), MOVE_RIGHT),
			std::make_pair(dist(MOVE_DOWN, board.target, currentPos), MOVE_DOWN),
			std::make_pair(dist(MOVE_LEFT, board.target, currentPos), MOVE_LEFT)
	};
	sort(actions.begin(), actions.end(),
	     [](std::tuple<size_t, ActionInfo> a, std::tuple<size_t, ActionInfo> b) {
		     return std::get<0>(a) < std::get<0>(b);
	     }
	);
	char lastMove = 'E';
	if (!stack.empty()) {
		lastMove = stack.back();
	}

	visited.insert(currentPos);
	for (const std::tuple<size_t, ActionInfo> &tuple: actions) {
		auto action = std::get<1>(tuple);
		Point newPos = {currentPos.x + action.dx, currentPos.y + action.dy};
		std::deque<char> workerMoves;

		bool isValid = isBoxValidPoint(board, newPos, action) && visited.find(newPos) == visited.end();
		if (isValid && lastMove != 'E' && lastMove != action.pullChar) {
			std::set<Point> workerVisited;
			auto target = board.target;
			board.target = newPos;
			auto lastAction = getActionInfoFromLetter(lastMove);
			auto lastWorkerPos = Point{currentPos.x + lastAction.dx, currentPos.y + lastAction.dy};
			board.walls.insert(currentPos);
			isValid = dfs(board, workerMoves, workerVisited, lastWorkerPos);
			board.walls.erase(currentPos);
			board.target = target;
			if (!isValid) {
				workerMoves.clear();
			}
		}
		if (isValid) {
			for (const auto &elem: workerMoves) {
				stack.push_back(elem);
			}
			workerMoves.clear();
			stack.push_back(action.pullChar);
			if (boxDfs(board, stack, visited, newPos)) {
				return true;
			} else if (!stack.empty()) {
				auto elem = stack.back();
				while (elem == MOVE_UP.moveChar || elem == MOVE_RIGHT.moveChar || elem == MOVE_DOWN.moveChar ||
				       elem == MOVE_LEFT.moveChar) {
					stack.pop_back();
					elem = stack.back();
				}
				if (!stack.empty()) {
					stack.pop_back();
				}
				if (!stack.empty()) {
					elem = stack.back();
					while (elem == MOVE_UP.moveChar || elem == MOVE_RIGHT.moveChar || elem == MOVE_DOWN.moveChar ||
					       elem == MOVE_LEFT.moveChar) {
						stack.pop_back();
						elem = stack.back();
					}
				}
			}
		}
	}
	return false;
}

std::deque<char> findPathToTheBox(Board &board) {
	std::deque<char> stack;
	std::set<Point> visited;
	dfs(board, stack, visited, board.worker);
	return stack;
}

std::deque<char> findPathFromTheBoxToTheTarget(Board &board) {
	std::deque<char> stack;
	std::set<Point> visited;
	boxDfs(board, stack, visited, board.box);
	auto action = getActionInfoFromLetter(stack.front());
	board.target = Point{board.box.x + action.dx, board.box.y + action.dy};
	return stack;
}