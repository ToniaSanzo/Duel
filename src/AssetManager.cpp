#include "AssetManager.h"

// AssetManager constructor, this makes a AssetManager with a 
// manager
AssetManager::AssetManager(Manager *mManager) : manager(mManager)
{}

// Desturctor asset manager
AssetManager::~AssetManager()
{}

// Adds this assets textures
void AssetManager::addTexture(std::string id, const char *path)
{
    textures.emplace(id, TextureManager::LoadTexture(path));
}

// Gets this asset managers texture
SDL_Texture *AssetManager::getTexture(std::string id)
{
    return textures[id];
}
