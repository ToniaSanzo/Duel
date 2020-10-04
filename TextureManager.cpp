#include "TextureManager.h"

SDL_Texture *TextureManager::LoadTexture(const char *filename) {
    // Create a temporary surface from the image at the 
    // filename, this will be used to make the texture.
    SDL_Surface *tmpSurface = IMG_Load(filename);

    // Create a SDL_Texture from the tmpSurface
    SDL_Texture *tex = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
    
    // Clean the Surface
    SDL_FreeSurface(tmpSurface);

    // Return the texture that was generated
    return tex;
}

// Quick utility method for drawing textures
void TextureManager::Draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip) {
    SDL_RenderCopyEx(Game::renderer, tex, &src, &dest, NULL, NULL, flip);
}