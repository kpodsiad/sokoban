#include <sokobanlib.h>

bool isSolved(Board &board, std::vector<Point> &locations)
{
    for (auto &it : locations)
    {
        auto found = board.find(it);
        if (found == board.end() || found->second != box)
        {
            return false;
        }
    }
    return true;
}
