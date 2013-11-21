#ifndef DOOR_HH
#define DOOR_HH

#include <stdlib.h>
#include <string>
#include <list>
#include <vector>

#include "room.hh"


class Door
{
    std::string style;
    int x;
    int y;
    int orientation;
    int width;
    
public:
    Door(std::string style, int x, int y, int orientation, int width);
    
    Room* room1;
    Room* room2;
    
    int get_x();
    int get_y();
    int get_orientation();
    int get_width();
    
    std::string str();
};

#endif
