#include "input.h"

void handleInput(const SDL_Event& e, Grid& grid) {
    if (e.type == SDL_MOUSEBUTTONDOWN) {
        int mouseX = e.button.x / grid.getCellSize();
        int mouseY = e.button.y / grid.getCellSize();

        // Ensure we don't overwrite destination or obstacle cells
        if (grid.getCell(mouseX, mouseY) == EMPTY) {
            grid.setCell(mouseX, mouseY, OBSTACLE);
        }
    }
}
