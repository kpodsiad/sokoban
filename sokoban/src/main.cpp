#include <iostream>
#include <queue>
#include <set>
#include <sokobanlib.h>
#include <chrono>

using namespace std;

int main() {
	Board board;
	readBoard(board, cin);

	for (size_t y = 0; y < board.height; ++y) {
		for (size_t x = 0; x < board.width; ++x) {
			auto it = board.walls.find({x, y});
			if (it != board.walls.end()) {
				cout << "#";
			} else {
				cout << " ";
			}
		}
		cout << endl;
	}
	cout << "worker: " << board.worker.toString() << endl;
	cout << "target: " << board.target.toString() << endl;
	cout << "box: " << board.box.toString() << endl;

	size_t iteration = 0;
	auto start = chrono::steady_clock::now();

	auto diff = chrono::steady_clock::now() - start;
	cout << "Iterations: " << iteration << endl;
	cout << chrono::duration<double, milli>(diff).count() << " ms" << endl;

	return 0;
}