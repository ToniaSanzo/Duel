/**
* main.cpp
* 2D_GameEngine
* 
* Written by Tonia Sanzo on 9/20/2020.
* Acknowledgement Carl Birch.
*/

#include "Game.h"

Game *game = nullptr;

int main(int argc, char *argv[]) {
    
    // Target frames per second we want
    const int FPS = 60;

    // Max time we have between delays
    const int frameDelay = 1000 / FPS;

    // Used to make the game clock
    Uint32 frameStart; 
    int frameTime;
    
    // Construct a new game and add it to the heap.
    game = new Game();
    
    // Initialize the game, the width and height are divisible 
    // by 32
    game->init("Wyatt & Tonia Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1216, 640, false);

    // While the game is running, we'll run our statements
    while (game->running()) {
        // frameStart is the number of ticks since the SDL was
        // initialized
        frameStart = SDL_GetTicks();

        game->handleEvents();
        game->update();
        game->render();

        // Frame time will tell you how long  handleEvents(), 
        // update(), and render() took in milliseconds
        frameTime = SDL_GetTicks() - frameStart;
        
        // This keeps us from displaying more frames than 60
        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    // Deallocate the memory
    game->clean();
    delete game;

    return 0;
}