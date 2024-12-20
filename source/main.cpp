/*
    INCLUDING LIBRARIES
*/
// Standard Libraries
#include <iostream>
#include <vector>
#include <cmath>

// Graphics Libraries: 
#include <SDL2/SDL.h>

// Header Files:
#include "input.h"
#include "grid.h"
#include "particle.h"
#include "djkgrid.h"

using namespace std;

int windowWidth = 700;
int windowHeight = 700;
int cellSize = 30;


int main(int argc, char* argv[]) {

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        cerr << "error in sdl video: " << SDL_GetError() << "\n";
        return 1;
    }
    SDL_Window* window = SDL_CreateWindow(
        "Dijkstra's Algorithm Pathfinding",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        windowWidth, windowHeight,
        SDL_WINDOW_SHOWN
    );
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (!window) {
        cerr << "Window creation error : " << SDL_GetError() << "\n";
        SDL_Quit();
        return 1;
    }
    if (!renderer) {
        cerr << "Renderer creation error : " << SDL_GetError() << "\n";
        SDL_Quit();
        return 1;
    }

    /* 
        CREATE OBJECTS HERE
    */
    Grid grid(windowWidth/ cellSize, windowHeight / cellSize, cellSize);
    Particle particle(0, 0, cellSize, {0, 255, 0, 255});
    

    // Variables for destination
    int endX = -1, endY = -1;
    vector<pair<int, int>> path;
    size_t pathIndex = 0;

    SDL_Event e;
    bool running = true;

    while (running) {

        while (SDL_PollEvent(&e) != 0) {
            
            if (e.type == SDL_QUIT) {
                running = false;
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN) {
                int mouseX = e.button.x / cellSize;
                int mouseY = e.button.y / cellSize;

                if (e.button.button == SDL_BUTTON_LEFT) {
                    grid.setCell(mouseX, mouseY, OBSTACLE);
                } else if (e.button.button == SDL_BUTTON_RIGHT) {
                    grid.setCell(mouseX, mouseY, DESTINATION);
                    endX = mouseX; // Set destination coordinates
                    endY = mouseY;
                }
            } else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_RETURN) {
                    if (e.key.keysym.sym == SDLK_RETURN && endX != -1 && endY != -1) {
                        
                        cout << "running path finder algorithm" << "\n";
                        path = Dijkstra::findPath(grid, particle.getX(), particle.getY(), endX, endY);
                        pathIndex = 0;

                    }
                }
            }
            handleInput(e, grid);

        }

        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        if (!path.empty()) {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); 
            for (const auto& point : path) {
                SDL_Rect rect = {
                    point.first * cellSize, 
                    point.second * cellSize,
                    cellSize, cellSize 
                };
                SDL_RenderDrawRect(renderer, &rect); 
            }
        }

        grid.render(renderer);

        if (pathIndex < path.size()) {
            particle.moveTo(path[pathIndex].first, path[pathIndex].second);
            pathIndex++;
            SDL_Delay(200);
        }
        particle.render(renderer);

        SDL_RenderPresent(renderer);

    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;

}