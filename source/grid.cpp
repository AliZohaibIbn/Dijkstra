#include "grid.h"
#include <algorithm>

Grid::Grid(int gridWidth, int gridHeight, int cellSize)
    : width(gridWidth), height(gridHeight), cellSize(cellSize), endX(-1), endY(-1) {
    cells = std::vector<std::vector<CellType>>(width, std::vector<CellType>(height, EMPTY));
}

void Grid::render(SDL_Renderer* renderer) {
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            SDL_Rect cell = {x * cellSize, y * cellSize, cellSize, cellSize};

            switch (cells[x][y]) {
                case EMPTY:
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White
                    break;
                case OBSTACLE:
                    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Blue
                    break;
                case DESTINATION:
                    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red
                    break;
            }

            SDL_RenderFillRect(renderer, &cell);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Grid lines
            SDL_RenderDrawRect(renderer, &cell);
        }
    }
}

void Grid::setCell(int x, int y, CellType type) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        if (type == DESTINATION) {
            
            if (endX >= 0 && endY >= 0) {
                cells[endX][endY] = EMPTY;
            }

            // Set the new end node
            endX = x;
            endY = y;
        }

        cells[x][y] = type;
    }
}

CellType Grid::getCell(int x, int y) const {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        return cells[x][y];
    }
    return EMPTY;
}

int Grid::getCellSize() const {
    return cellSize;
}

bool Grid::isObstacle(int x, int y) const {
    return getCell(x,y) == OBSTACLE;
}

bool Grid::isDestination(int x, int y) const {
    return getCell(x, y) == DESTINATION;
}

std::vector<std::pair<int, int>> Grid::getNeighbors(int x, int y) const {
    
    std::vector<std::pair<int, int>> neighbors;
    const std::vector<std::pair<int, int>> directions({{0, 1}, {1, 0}, {0, -1}, {-1, 0}});
    for (const auto& [dx,dy] : directions) {
        int nx = x + dx;
        int ny = y + dy;
        if (nx >= 0 && nx < width && ny >= 0 && ny < height && !isObstacle(nx, ny)) {
            neighbors.emplace_back(nx, ny);
        }
    }
    return neighbors;
}

int Grid::getWidth() const {
    return width;
}

int Grid::getHeight() const {
    return height;
}
