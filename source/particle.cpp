#include "particle.h"

Particle::Particle(int startX, int startY, int cellSize, SDL_Color color)
    : x(startX), y(startY), cellSize(cellSize), color(color) {}

void Particle::render(SDL_Renderer* renderer) {
    SDL_Rect rect = {x * cellSize, y * cellSize, cellSize, cellSize};
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &rect);
}

void Particle::moveTo(int targetX, int targetY) {
    x = targetX;
    y = targetY;
}

int Particle::getX() const {
    return x;
}

int Particle::getY() const {
    return y;
}
