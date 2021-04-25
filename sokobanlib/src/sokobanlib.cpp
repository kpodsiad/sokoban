#include <sokobanlib.h>
#include <iostream>

void readBoard(Board &board, std::istream &in) {
	char c;
	size_t x = 0, y = -1, read = 0;
	in >> board.height >> board.width;
	auto flags = in.flags();
	in.unsetf(std::ios_base::skipws);
	while (in && read != board.height * board.width) {
		in >> c;
		switch(c) {
			case NEWLINE:
				x = 0; ++y; break;
			case WORKER:
				board.worker = {x, y}; break;
			case TARGET:
				board.target = {x, y}; break;
			case BOX:
				board.box = {x, y}; break;
			case WALL:
				board.walls.insert({x,y}); break;
			default:
				break;
		}
		if (c != NEWLINE) {
			++x; ++read;
		}
	}
	in.setf(flags);
}

std::string findPathToTheBox(Board &board) {
	return "";
}