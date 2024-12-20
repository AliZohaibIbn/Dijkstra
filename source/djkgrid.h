#ifndef DJKGRID_H
#define DJKGRID_H

#include "grid.h"
#include <vector>
#include <utility>

class Dijkstra {
    public:
        static std::vector<std::pair<int, int>> findPath(Grid& grid, int startX, int startY, int& endX, int& endY);
};

#endif