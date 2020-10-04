#pragma once
// So we get the SDL includes
#include "Game.h"

// Makes generating textures easier
#include "TextureManager.h"

class GameObject
{
public:
    // GameObject constructor
    GameObject(const char *textureSheet, int x, int y);

    // GameObject destructor
    ~GameObject();

    // Makes updating and rendering each GameObject easier
    void update();
    void render();

private:
    int xpos;                   // GameObjects x-coordinate
    int ypos;                   // GameObjects y-coordinate

    SDL_Texture *objTexture;    // The GameObjects image as a texture
    SDL_Rect srcRect, destRect; // srcRect = [ what part of the texture 
                                // you want to draw ], destRect = [ where 
                                // you want to draw the gameobject ]
};

