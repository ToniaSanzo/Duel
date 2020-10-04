#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <vector>
#include "AssetManager.h"
class AssetManager;
class ColliderComponent;

class Game
{
public:
    // Contructor for when we open the game loop
    Game();

    // Destructor for when we close the game loop
    ~Game();

    // Function for initializing the game
    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

    // Handle the events
    void handleEvents();

    // Go through and update our game objects
    void update();

    // Draw/Render the scene to the screen
    void render();

    // Memory management
    void clean();

    // Return a boolean depending on if the game class is running
    bool running();

    static SDL_Renderer *renderer;      // Pointer to the SDL renderer
    static SDL_Event event;             // SDL event object
    
    static AssetManager *assets;

    // Some of our group labels
    enum groupLabels : std::size_t {
        groupMap,
        groupPlayers,
        groupEnemies,
        groupColliders
    };

private:
    int cnt = 0;                        // Counts the number of times the 
                                        // game loop executed
    bool isRunning = false;             // true while the game class is 
                                        // running
    SDL_Window *window = nullptr;       // Pointer to the SDL window   
};

