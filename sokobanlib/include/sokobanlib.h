#ifndef SOKOBAN_SOKOBANLIB_H
#define SOKOBAN_SOKOBANLIB_H

#include <map>
#include <vector>

typedef std::tuple<size_t, size_t> Point;
typedef std::map<Point, char> Board;

enum Field
{
    wall = '#', box = '0', target = '*', worker = '-', newline = '\n', empty = ' '
};

bool isSolved(Board &, std::vector<Point> &);

#endif //SOKOBAN_SOKOBANLIB_H