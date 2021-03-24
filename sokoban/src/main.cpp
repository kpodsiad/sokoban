#include <iostream>
#include <map>
#include <vector>

#include <sokobanlib.h>

using namespace std;

Board &readBoard(size_t &width, size_t &height, Board &board)
{
    char c;
    size_t x = 0, y = 0;
    cin >> height >> width;
    cout << height << " " << width << endl;
    cin.unsetf(ios_base::skipws);
    while (cin && (x != width || y != height))
    {
        cin >> c;
        if (c != empty && c != newline)
        {
            board[make_tuple(x, y)] = c;
        }
        if (c == newline)
        {
            x = 1;
            ++y;
        }
        else
        {
            ++x;
        }
    }
    cin.setf(ios_base::skipws);
    return board;
}

int main()
{
    size_t height = 0, width = 0;
    map<tuple<size_t, size_t>, char> board;
    readBoard(width, height, board);

    for (auto &it : board)
        cout << "(" << get<0>(it.first) << ", " << get<1>(it.first) << "): " << it.second << endl;

    cout << board.size() << " " << width << " " << height;

    return 0;
}