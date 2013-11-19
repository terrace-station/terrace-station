#ifndef TILE_HH
#define TILE_HH

#include <sstream>
#include <string>

class Tile
{
    int x, y;
    
public:
    Tile(int x, int y);
    
    int get_x();
    int get_y();
    
    std::string str();
};

#endif
