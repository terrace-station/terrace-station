#include "tile.hh"
#include "lamp.hh"
#include "rect.hh"
#include "door.hh"
#include "room.hh"
#include "deck.hh"
#include "district.hh"
#include "zone.hh"
#include "station.hh"

Door::Door(std::string style, int x, int y, int orientation, int width) :
    style(style), x(x), y(y), orientation(orientation)
{
    
}

int Door::get_x() { return x; }
int Door::get_y() { return y; }
int Door::get_orientation() { return orientation; }
int Door::get_width() { return width; }
    
std::string Door::str()
{
    std::stringstream ss;
    ss << "      Door:      (style = " << style << ", x = " << x;
    ss << ", y = " << y << ", orientation = " << orientation;
    ss << ", width = " << width << ")" << std::endl;
    ss << room1->str() << room2->str();
    return ss.str();
}
