#pragma once
#include <string>

class Map
{
public:
    // Map constructor
    Map(std::string tID, int ms, int ts);

    // Map destructor
    ~Map();

    // Create the map of the argument array
    void loadMap(std::string path, int sizeX, int sizeY);

    // Add a tile to the game at position x, y with specified 
    // source rectangle
    void addTile(int srcX, int srcY, int xpos, int ypos);

private:
    std::string textureID;
    int mapScale;
    int tileSize;
    int scaledSize;
};