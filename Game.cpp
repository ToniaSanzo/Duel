#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"


// Our Game map
Map *map = nullptr;

// Initialize the renderer to be reassigned within the init function
SDL_Renderer *Game::renderer = nullptr;
SDL_Event Game::event;
Manager manager;

// Initialize our asset manager after manager was made
AssetManager *Game::assets = new AssetManager(&manager);

// This will create our player, and map tiles for us
auto &warrior(manager.addEntity());
auto &wizard(manager.addEntity());
auto &ranger(manager.addEntity());

// Game constructor
Game::Game() {

}

// Game destructor
Game::~Game() {

}

// Function for initializing the game and SDL
void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen) {
    // If fullscreen is true set the flags to make the SDL window
    // fullscreen.
    int flags = 0;
    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN_DESKTOP;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        cnt = 0;
        // Successfully initilialized the SDL subsystems
        std::cout << "Subsystems initialized!..." << std::endl;

        // Create a window with the argument values
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if (window) {
            // The window has successfully been created
            std::cout << "window created!" << std::endl;
        }

        // Create a window with the window, index, and flags
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer) {
            // The renderer has successfully been created
            std::cout << "renderer created!" << std::endl;

            // Set the render draw color
            SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
        }

        isRunning = true;
    }
    
    assets->addTexture("terrain", "Assets/MapTileSet.png");
    assets->addTexture("warrior", "Assets/warrior_anim.png");
    assets->addTexture("ranger", "Assets/ranger_anim.png");
    assets->addTexture("wizard", "Assets/wizard_anim.png");

    // Make the map
    map = new Map("terrain", 2, 32);
    map->loadMap("Assets/map0.map", 23, 10);

    // Add the components to the warrior entity
    warrior.addComponent<TransformComponent>(0, 0, 32, 64, 4);
    warrior.addComponent<SpriteComponent>("warrior", true);
    warrior.addComponent<KeyboardController>();
    warrior.addComponent<ColliderComponent>("warrior");
    warrior.addGroup(groupPlayers);

    // Add the components to the warrior entity
    wizard.addComponent<TransformComponent>(0, 0, 32, 64, 4);
    wizard.addComponent<SpriteComponent>("wizard", true);
    wizard.addComponent<KeyboardController>();
    wizard.addComponent<ColliderComponent>("wizard");
    wizard.addGroup(groupPlayers);
    wizard.getComponent<TransformComponent>().setPos(700, 400);
    
    // Add the components to the ranger entity
    ranger.addComponent<TransformComponent>(0, 0, 32, 64, 4);
    ranger.addComponent<SpriteComponent>("ranger", true);
    ranger.addComponent<KeyboardController>();
    ranger.addComponent<ColliderComponent>("ranger");
    ranger.addGroup(groupPlayers);
    ranger.getComponent<TransformComponent>().setPos(300, 300);
}

// This will create our player for us
auto &tiles(manager.getGroup(Game::groupMap));
auto &players(manager.getGroup(Game::groupPlayers));
auto &colliders(manager.getGroup(Game::groupColliders));

// Handle the events
void Game::handleEvents() {
    // Poll the event, this needs the address of the event
    SDL_PollEvent(&event);

    // Execute certain code based on the type of the event
    switch (event.type) {
    case SDL_QUIT:
        isRunning = false;
        break;
    default:
        break;
    }
}

// Go through and update our game objects
void Game::update() {
    // update's our entities which in turn updates all the 
    // components, than print the component
    manager.refresh();
    manager.update();
    
    // Get the entities position and collider
    SDL_Rect warriorPos = warrior.getComponent<ColliderComponent>().collider;
    SDL_Rect wizardPos = wizard.getComponent<ColliderComponent>().collider;
    SDL_Rect rangerPos = ranger.getComponent<ColliderComponent>().collider;

    
    // ranger and wizard collision
    if (Collision::AABB(rangerPos, wizardPos)){
        // If the ranger is attacking than kill the wizard
        if (ranger.getComponent<KeyboardController>().attacking && !wizard.getComponent<KeyboardController>().dead) {
            std::cout << "wizard died" << std::endl;
            wizard.getComponent<SpriteComponent>().play("death");
            wizard.getComponent<KeyboardController>().dead = true;
            wizard.getComponent<TransformComponent>().score--;
            ranger.getComponent<TransformComponent>().score++;
            std::cout << "[-]Wizard score: " << wizard.getComponent<TransformComponent>().score << std::endl;
            std::cout << "[+]Ranger score: " << ranger.getComponent<TransformComponent>().score << std::endl;
        }
        else if (wizard.getComponent<KeyboardController>().attacking && !ranger.getComponent<KeyboardController>().dead) {
            std::cout << "ranger died" << std::endl;
            ranger.getComponent<SpriteComponent>().play("death");
            ranger.getComponent<KeyboardController>().dead = true;
            wizard.getComponent<TransformComponent>().score++;
            ranger.getComponent<TransformComponent>().score--;
            std::cout << "[+]Wizard score: " << wizard.getComponent<TransformComponent>().score << std::endl;
            std::cout << "[-]Ranger score: " << ranger.getComponent<TransformComponent>().score << std::endl;
        }
    }

    // wizard and warrior collision
    if (Collision::AABB(warriorPos, wizardPos)) {
        // If the wizard and warrior collided
        if (wizard.getComponent<KeyboardController>().attacking && !warrior.getComponent<KeyboardController>().dead) {
            std::cout << "warrior died" << std::endl;
            warrior.getComponent<SpriteComponent>().play("death");
            warrior.getComponent<KeyboardController>().dead = true;
            wizard.getComponent<TransformComponent>().score++;
            warrior.getComponent<TransformComponent>().score--;
            std::cout << "[+]Wizard score: " << wizard.getComponent<TransformComponent>().score << std::endl;
            std::cout << "[-]Warrior score: " << warrior.getComponent<TransformComponent>().score << std::endl;
        }
        else if (warrior.getComponent<KeyboardController>().attacking && !wizard.getComponent<KeyboardController>().dead) {
            std::cout << "wizard died" << std::endl;
            wizard.getComponent<SpriteComponent>().play("death");
            wizard.getComponent<KeyboardController>().dead = true;
            wizard.getComponent<TransformComponent>().score--;
            warrior.getComponent<TransformComponent>().score++;
            std::cout << "[-]Wizard score: " << wizard.getComponent<TransformComponent>().score << std::endl;
            std::cout << "[+]Warrior score: " << warrior.getComponent<TransformComponent>().score << std::endl;
        }
    }

    // warrior and ranger collision
    if (Collision::AABB(warriorPos, rangerPos)) {
        // If the warrior is attacking than kill the ranger
        if (warrior.getComponent<KeyboardController>().attacking && !ranger.getComponent<KeyboardController>().dead) {
            
            ranger.getComponent<SpriteComponent>().play("death");
            ranger.getComponent<KeyboardController>().dead = true;
            ranger.getComponent<TransformComponent>().score--;
            warrior.getComponent<TransformComponent>().score++;
            std::cout << "[-]Ranger score: " << ranger.getComponent<TransformComponent>().score << std::endl;
            std::cout << "[+]Warrior score: " << warrior.getComponent<TransformComponent>().score << std::endl;
        }
        else if (ranger.getComponent<KeyboardController>().attacking && !warrior.getComponent<KeyboardController>().dead) {
            std::cout << "warrior died" << std::endl;
            warrior.getComponent<SpriteComponent>().play("death");
            warrior.getComponent<KeyboardController>().dead = true;
            warrior.getComponent<TransformComponent>().score--;
            ranger.getComponent<TransformComponent>().score++;
            std::cout << "[-]Warrior score: " << warrior.getComponent<TransformComponent>().score << std::endl;
            std::cout << "[+]Ranger score: " << ranger.getComponent<TransformComponent>().score << std::endl;
        }
    }
}

// Draw/Render the scene to the screen
// We are going to add the textures, this uses a painters
// algorithm so what ever you render first moves to the 
// background as you render more textures.
void Game::render() {
    // First you clear whats in the renderers buffer
    SDL_RenderClear(renderer);
    
    // First draw each tile
    for (auto t : tiles) {
        t->draw();
    }

    // than draw each player
    for (auto &p : players) {
        p->draw();
    }

    //// Than draw each enemy
    //for (auto &c : colliders) {
    //    c->draw();
    //}

    // This is where we would add stuff to render
    SDL_RenderPresent(renderer);

}

// Memory management
void Game::clean() {
    // Deallocate the window
    SDL_DestroyWindow(window);

    // Deallocate the renderer
    SDL_DestroyRenderer(renderer);
    
    // Turn off the SDL subsystems
    SDL_Quit();

    std::cout << "Game cleaned" << std::endl;
}

// Return a boolean depending on if the game class is running
bool Game::running() { return isRunning; }
