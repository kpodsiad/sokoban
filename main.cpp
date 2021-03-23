#include <iostream>
using namespace std;

int main() {
	size_t height = 0, width = 0;
	char c;
	cin >> height >> width;
	cout << height << endl << width << endl;

	while (cin) {
		cin >> c;
		cout << c;
	}
	cout << "Hello, World!" << std::endl;
	return 0;
}
