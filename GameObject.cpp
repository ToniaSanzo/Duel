#include "GameObject.h"


// GameObject constructor
GameObject::GameObject(const char *textureSheet, int x, int y)
{
    // Generate the GameObjects texture
    objTexture = TextureManager::LoadTexture(textureSheet);

    // Set the Game Objects initial position
    xpos = x;
    ypos = y;
}

// GameObject destructor
GameObject::~GameObject()
{
}

// All the movement code, position, and behavior is handled
// here
void GameObject::update()
{
    // Set the position
    xpos++;
    ypos++;

    // Set source rectangle
    srcRect.h = 32;
    srcRect.w = 32;
    srcRect.x = 0;
    srcRect.y = 0;

    // Set destination rectangle
    destRect.x = xpos;
    destRect.y = ypos;
    destRect.w = srcRect.w * 2;
    destRect.h = srcRect.h * 2;
}

// Called when you want to draw the game object to the screen
void GameObject::render()
{
    // To render we use the RenderCopy function, RenderCopy 
    // takes a renderer, a texture, a source rect (part of the 
    // the texture you want drawn), and a destination rect 
    // (what part of the window you want the texture drawn on
    // at).
    SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}
