#include <iostream>

#include <sokobanlib.h>
#include <chrono>

using namespace std;

int main() {
	Board board;
	readBoard(board, cin);
	auto start = chrono::steady_clock::now();

	auto boxToTheTarget = findPathFromTheBoxToTheTarget(board);
	auto workerToTheBox = findPathToTheBox(board);

	auto diff = chrono::steady_clock::now() - start;

	for (const auto &elem: workerToTheBox) {
		cout << elem;
	}
	for (const auto &elem: boxToTheTarget) {
		cout << elem;
	}
	cout << endl;

	cout << chrono::duration<double, milli>(diff).count() << " ms" << endl;
	return 0;
}