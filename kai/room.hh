#ifndef ROOM_HH
#define ROOM_HH

#include <stdlib.h>
#include <string>
#include <list>
#include <vector>

#include "wall.hh"
#include "door.hh"
#include "rect.hh"

/**
 * Room
 */
class Room
{
public:
    std::string style;
    std::list<Rect> rects;

    /**
     * Default constructor
     */
    Room(std::string style, std::list<Rect> rects);
    
    int area();
    bool intersects(Rect other);
    bool intersects(Room other);
    std::string str();
    
};

#endif
