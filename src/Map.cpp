#include "Map.h"
#include "Game.h"
#include <fstream>
#include "ECS\ECS.h"
#include "ECS\Components.h"

// Same manager as the manager defined in Game.cpp
extern Manager manager;

// Map constructor
Map::Map(std::string tID, int ms, int ts) : textureID(tID), mapScale(ms), tileSize(ts)
{
    scaledSize = ms * ts;
}

// Map destructor
Map::~Map()
{
}

// Create the map from the argument
void Map::loadMap(std::string path, int sizeX, int sizeY)
{
    // Tile is the current character read from the fstream
    char c;

    // A stream created from the map file
    std::fstream mapFile;
    mapFile.open(path);

    // We need our source position for our different terrains
    int srcX, srcY;

    // Iterate through each row of the map
    for (int y = 0; y < sizeY; y++) {
        // Iterate through each of the maps collumns
        for (int x = 0; x < sizeX; x++) {
            mapFile.get(c);
            srcY = atoi(&c) * tileSize;
            mapFile.get(c);
            srcX = atoi(&c) * tileSize;
            addTile(srcX, srcY, x * scaledSize, y * scaledSize);
            mapFile.ignore();
        }
    }

    /*mapFile.ignore();*/
    //// Loop that we will pass through the gris of characters
    //for (int y = 0; y < sizeY; y++) {
    //    for (int x = 0; x < sizeX; x++) {
    //        mapFile.get(c);
    //        if (c == '1') {
    //            auto &tcol(manager.addEntity());
    //            tcol.addComponent<ColliderComponent>("terrain", x * scaledSize, y * scaledSize, scaledSize);
    //            tcol.addGroup(Game::groupColliders);
    //        }
    //        mapFile.ignore();
    //    }
    //}

    mapFile.close();
}

// Add a tile to the screen
void Map::addTile(int srcX, int srcY, int xpos, int ypos)
{
    auto &tile(manager.addEntity());
    tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos, tileSize, mapScale, textureID);
    tile.addGroup(Game::groupMap);
}
