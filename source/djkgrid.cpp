#include "djkgrid.h"
#include <queue>
#include <climits>
#include <unordered_map>
#include <bits/algorithmfwd.h>
#include <algorithm>

std::vector<std::pair<int, int>> Dijkstra::findPath(Grid& grid, int startX, int startY, int& endX, int& endY) {
    std::priority_queue<std::pair<int, std::pair<int, int>>,
        std::vector<std::pair<int, std::pair<int, int>>>,
        std::greater<>> pq; // the min heap

    std::unordered_map<int, std::pair<int, int>> cameFrom;
    std::unordered_map<int, int> distances; // Distance from start
    
    int width = grid.getWidth();
    int height = grid.getHeight();

    // Lambda function to get a unique index for a cell
    auto index = [&](int x, int y) { return x * width + y; };

    
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            distances[index(x, y)] = INT_MAX;
        }
    }

    // Starting node setup
    pq.emplace(0, std::make_pair(startX, startY));
    distances[index(startX, startY)] = 0;

    // Dijkstras loop
    while (!pq.empty()) {
        auto [currentDist, current] = pq.top();
        pq.pop();

        int currentX = current.first;
        int currentY = current.second;

        // Stop if we've reached the destination
        if (grid.isDestination(currentX, currentY)) {
            endX = currentX;
            endY = currentY;
            break;
        }

        // Iterate through the neghbours
        for (const auto& [nx, ny] : grid.getNeighbors(currentX, currentY)) {
            int newDist = currentDist + 1; // Constant dist of 1 btwn cells

            if (newDist < distances[index(nx, ny)]) {
                distances[index(nx, ny)] = newDist;
                pq.emplace(newDist, std::make_pair(nx, ny));
                cameFrom[index(nx, ny)] = std::make_pair(currentX, currentY);
            }
        }
    }

    // Reconstruct the path
    std::vector<std::pair<int, int>> path;
    auto current = std::make_pair(endX, endY);

    while (cameFrom.find(index(current.first, current.second)) != cameFrom.end()) {
        path.push_back(current);
        current = cameFrom[index(current.first, current.second)];
    }

    path.push_back(std::make_pair(startX, startY)); // add strt node

    
    std::reverse(path.begin(), path.end()); 

    return path;

}