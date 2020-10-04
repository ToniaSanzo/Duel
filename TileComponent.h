#pragma once

#include "ECS.h"
#include "SDL.h"
#include "../AssetManager.h"

class TileComponent : public Component
{
public:

    SDL_Texture *texture;
    SDL_Rect srcRect, destRect;

    // Default constructor
    TileComponent() = default;

    // TileComponent destructor
    ~TileComponent() {
        SDL_DestroyTexture(texture);
    }

    // Constructor to set the position and dimensions of the 
    // tile component
    TileComponent(int srcX, int srcY, int xpos, int ypos, int tsize, int tscale, std::string id) {
        texture = Game::assets->getTexture(id);

        // Set the source rectangle
        srcRect.x = srcX;
        srcRect.y = srcY;
        srcRect.w = srcRect.h = tsize;
        
        // Set the destination rectangle
        destRect.x = xpos;
        destRect.y = ypos;
        destRect.w = destRect.h = tsize * tscale;
    }

    void draw() override {
        TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
    }
};