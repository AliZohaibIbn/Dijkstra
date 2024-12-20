#ifndef PARTICLE_H
#define PARTICLE_H

#include <SDL2/SDL.h>

class Particle {
    private:
        int x, y;
        int cellSize;
        SDL_Color color;

    public: 
        Particle(int startX, int startY, int cellSize, SDL_Color color);
        void render(SDL_Renderer* renderer);
        void moveTo(int targetX, int targetY);
        int getX() const;
        int getY() const;

};

#endif