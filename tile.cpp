#include "tile.hh"

Tile::Tile(int x, int y) :
    x(x), y(y)
{
    
}

std::string Tile::str()
{
    std::stringstream ss;
    ss << "            Tile:      (x = " << x << ", y = " << y << ")" << std::endl;
    return ss.str();
}
