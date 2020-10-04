#pragma once

#include <map>
#include <string>
#include "TextureManager.h"
#include "Vector2D.h"
#include "ECS\ECS.h"

class AssetManager
{
public:
    // Default constructor
    AssetManager() {}

    // Constructor, takes a pointer to the manager
    AssetManager(Manager *mManager);

    // Destructor for AssetManager
    ~AssetManager();

    // Adds a texture to the asset
    void addTexture(std::string id, const char *path);
    
    // Gets the assets texture
    SDL_Texture *getTexture(std::string id);

private:
    // Assets texture or image
    std::map<std::string, SDL_Texture *> textures;

    // Pointer to the asset managers manager
    Manager *manager;
};