#include <sokobanlib.h>
#include <cctype>

void readBoard(Board &board, Points &boxes, Points &targets, Point &worker, std::istream &in) {
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
				worker = {x, y};
				break;
			case TARGET:
				targets.insert({x, y});
				break;
			case BOX:
				boxes.insert({x, y});
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

inline bool isValidPoint(Board &board, Point &point) {
	if (point.x < 0 || point.x >= board.width || point.y < 0 || point.y >= board.height) {
		return false;
	}
	if (board.walls.find(point) != board.walls.end()) {
		return false;
	}
	return true;
}

inline size_t dist(ActionInfo const &action, Point &target, Point &currentPos) {
	Point newPos = {currentPos.x + action.dx, currentPos.y + action.dy};
	return target.dist(newPos);
}

bool dfs(Board &board, std::deque<char> &deque, Points &visited, Point &currentPos, Point &target) {
	if (target.x == currentPos.x && target.y == currentPos.y) {
		return true;
	}
	std::array<std::tuple<size_t, ActionInfo>, 4> actions = {
			std::make_pair(dist(MOVE_UP, target, currentPos), MOVE_UP),
			std::make_pair(dist(MOVE_RIGHT, target, currentPos), MOVE_RIGHT),
			std::make_pair(dist(MOVE_DOWN, target, currentPos), MOVE_DOWN),
			std::make_pair(dist(MOVE_LEFT, target, currentPos), MOVE_LEFT)
	};
	// sort
	sort(actions.begin(), actions.end(),
	     [](std::tuple<size_t, ActionInfo> a, std::tuple<size_t, ActionInfo> b) {
		     return std::get<0>(a) < std::get<0>(b);
	     });

	visited.insert(currentPos);
	for (const std::tuple<size_t, ActionInfo> &tuple: actions) {
		auto action = std::get<1>(tuple);
		Point newPos = {currentPos.x + action.dx, currentPos.y + action.dy};
		if (visited.find(newPos) == visited.end() && isValidPoint(board, newPos)) {
			deque.push_back(action.moveChar);
			if (dfs(board, deque, visited, newPos, target)) {
				return true;
			} else {
				deque.pop_back();
			}
		}
	}
	return false;
}

inline ActionInfo getActionInfoFromLetter(char letter) {
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

inline bool isBoxValidPoint(Board &board, Point &newBoxPosition, ActionInfo &action) {
	auto newWorkerPos = Point{newBoxPosition.x + action.dx, newBoxPosition.y + action.dy};
	if (newWorkerPos.x < 0 || newWorkerPos.x >= board.width || newWorkerPos.y < 0 || newWorkerPos.y >= board.height) {
		return false;
	}
	if (board.walls.find(newBoxPosition) != board.walls.end() || board.walls.find(newWorkerPos) != board.walls.end()) {
		return false;
	}
	return true;
}

bool boxDfs(Board &board, std::deque<char> &deque, Points &visited, Point &currentPos, Point &target) {
	if (target.x == currentPos.x && target.y == currentPos.y) {
		return true;
	}
	std::array<std::tuple<size_t, ActionInfo>, 4> actions = {
			std::make_pair(dist(MOVE_UP, target, currentPos), MOVE_UP),
			std::make_pair(dist(MOVE_RIGHT, target, currentPos), MOVE_RIGHT),
			std::make_pair(dist(MOVE_DOWN, target, currentPos), MOVE_DOWN),
			std::make_pair(dist(MOVE_LEFT, target, currentPos), MOVE_LEFT)
	};
	sort(actions.begin(), actions.end(),
	     [](std::tuple<size_t, ActionInfo> a, std::tuple<size_t, ActionInfo> b) {
		     return std::get<0>(a) < std::get<0>(b);
	     }
	);
	char lastMove = 'E';
	if (!deque.empty()) {
		lastMove = deque.back();
	}

	visited.insert(currentPos);
	for (const std::tuple<size_t, ActionInfo> &tuple: actions) {
		auto action = std::get<1>(tuple);
		Point newPos = {currentPos.x + action.dx, currentPos.y + action.dy};
		std::deque<char> workerMoves;

		bool isValid = isBoxValidPoint(board, newPos, action) && visited.find(newPos) == visited.end();
		if (isValid && lastMove != 'E' && lastMove != action.pullChar) {
			Points workerVisited;
			auto lastAction = getActionInfoFromLetter(lastMove);
			auto lastWorkerPos = Point{currentPos.x + lastAction.dx, currentPos.y + lastAction.dy};
			board.walls.insert(currentPos);
			isValid = dfs(board, workerMoves, workerVisited, lastWorkerPos, newPos);
			board.walls.erase(currentPos);
			if (!isValid) {
				workerMoves.clear();
			}
		}
		if (isValid) {
			for (const auto &elem: workerMoves) {
				deque.push_back(elem);
			}
			workerMoves.clear();
			deque.push_back(action.pullChar);
			if (boxDfs(board, deque, visited, newPos, target)) {
				return true;
			} else if (!deque.empty()) { // else get rid of invalid moves from queue
				auto elem = deque.back();
				// islower(elem) == elem is move letter
				while (islower(elem)) {
					deque.pop_back();
					elem = deque.back();
				}
				if (!deque.empty()) {
					deque.pop_back();
				}
				if (!deque.empty()) {
					elem = deque.back();
					while (islower(elem)) {
						deque.pop_back();
						elem = deque.back();
					}
				}
			}
		}
	}
	return false;
}

std::tuple<std::deque<char>, bool> findPathToTheBox(Board &board, Point &worker, Point &target) {
	std::deque<char> deque;
	Points visited;
	auto result = dfs(board, deque, visited, worker, target);
	return std::make_pair(deque, result);
}

std::deque<char> findPathFromTheBoxToTheTarget(Board &board, Point &box, Point &target) {
	std::deque<char> deque;
	Points visited;
	boxDfs(board, deque, visited, box, target);
	return deque;
}

bool isStateValid(Board &board, Point &worker, Point &box) {
	std::array<ActionInfo, 4> actions = {MOVE_UP, MOVE_RIGHT, MOVE_DOWN, MOVE_LEFT};
	for (const ActionInfo &action: actions) {
		Point boxAdjacent = {box.x + action.dx, box.y + action.dy};
		auto t = findPathToTheBox(board, worker, boxAdjacent);
		if (std::get<1>(t)) {
			return true;
		}
	}
	return false;
}

std::deque<char> solveProblem(Board &board, Points boxes, Points targets, Point worker) {
	std::deque<char> deque;
	Point workerPosition = worker;
	for(Point box: boxes) {
		board.walls.insert(box);
	}

	auto boxesVec = std::vector<Point>(boxes.begin(), boxes.end());

	// for every box move it to "the best" target
	while(!boxesVec.empty()) {
		Point box = boxesVec[0];
		std::vector<std::tuple<size_t, Point>> sortedTargets;
		for (Point target: targets) {
			sortedTargets.emplace_back(std::make_pair(box.dist(target), target));
		}
		sort(sortedTargets.begin(), sortedTargets.end(),
		     [](std::tuple<size_t, Point> a, std::tuple<size_t, Point> b) {
			     return std::get<0>(a) < std::get<0>(b);
		     }
		);
		auto boxTarget = std::get<1>(sortedTargets.front());
		auto boxPath = findPathFromTheBoxToTheTarget(board, box, boxTarget);

		if (!boxPath.empty()) {
			auto action = getActionInfoFromLetter(boxPath.back());
			if (boxes.size() > 1 && boxesVec.size() > 1) {
				auto nextBox = boxesVec[1];
				board.walls.insert(boxTarget);
				auto p = Point{boxTarget.x + action.dx, boxTarget.y + action.dy};
				auto isInvalidState = !isStateValid(board, p, nextBox);
				board.walls.erase(boxTarget);
				if(isInvalidState) {
					boxesVec.erase(boxesVec.begin());
					boxesVec.emplace_back(box);
					continue;
				}
			}

			action = getActionInfoFromLetter(boxPath.front());
			auto workerTarget = Point{box.x + action.dx, box.y + action.dy};
			auto tuple = findPathToTheBox(board, workerPosition, workerTarget);
			auto workerPath = std::get<0>(tuple);

			for (const auto &elem: workerPath)
				deque.emplace_back(elem);

			action = getActionInfoFromLetter(boxPath.back());
			workerPosition = Point{boxTarget.x + action.dx, boxTarget.y + action.dy};
		}
		for (const auto &elem: boxPath)
			deque.emplace_back(elem);

		targets.erase(boxTarget);
		boxesVec.erase(boxesVec.begin());
		board.walls.erase(box);
		board.walls.insert(boxTarget);
	}
	return deque;
}