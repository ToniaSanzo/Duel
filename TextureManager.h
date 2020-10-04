#pragma once

// Include Game.h because it has SDL in it
#include "Game.h"

class TextureManager {
public:

    // Parameter: (filename) string literal of the filename
    // Return: An SDL_Texture pointer
    static SDL_Texture *LoadTexture(const char *filename);

    // Quick utility method for drawing textures
    static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip);
};
