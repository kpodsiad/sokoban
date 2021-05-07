#include <iostream>

#include <sokobanlib.h>
#include <chrono>

using namespace std;

int main() {
	Board board;
	Points boxes;
	Points targets;
	Point worker;
	readBoard(board, boxes, targets, worker, cin);
	auto start = chrono::steady_clock::now();

	auto path = solveProblem(board, boxes, targets, worker);

	auto diff = chrono::steady_clock::now() - start;

	for (const auto &elem: path) {
		cout << elem;
	}

	cout << endl;
	cout << chrono::duration<double, milli>(diff).count() << " ms" << endl;
	return 0;
}