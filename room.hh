#ifndef ROOM_HH
#define ROOM_HH

#include <stdlib.h>
#include <string>
#include <list>
#include <vector>

#include "wall.hh"
#include "door.hh"

class Rect;


class Room
{
    std::string style;
    std::list<Rect> rects;
    
public:
    Room(std::string style, Rect rect);
    
    int get_area();
    bool intersects(Rect other);
    bool intersects(Room other);
    std::string get_style();
    std::list<Rect>& get_rects();
    
    std::string str();
    
};

#endif
