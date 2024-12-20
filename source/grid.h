#ifndef GRID_H
#define GRID_H

#include <SDL2/SDL.h>
#include <vector>

enum CellType { EMPTY, OBSTACLE, DESTINATION };

class Grid {
private:
    int width, height, cellSize;
    std::vector<std::vector<CellType>> cells;
    int endX, endY; // Track the position of the current end node

public:
    Grid(int gridWidth, int gridHeight, int cellSize);
    void render(SDL_Renderer* renderer);
    void setCell(int x, int y, CellType type);
    CellType getCell(int x, int y) const;
    int getCellSize() const;
    int getWidth() const;  // Add this
    int getHeight() const; // Add this
    std::vector<std::pair<int, int>> getNeighbors(int x, int y) const;
    bool isObstacle(int x, int y) const;
    bool isDestination(int x, int y) const;
};

#endif 
