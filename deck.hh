#ifndef DECK_HH
#define DECK_HH

#include <stdlib.h>
#include <string>
#include <list>

#include "room.hh"
#include "wall.hh"
#include "door.hh"
#include "rect.hh"


class Deck
{
    std::list<Room> rooms;
    void init();
    
public:
    Deck(float radius, int x, int y, int size_x, int size_y);
    
    float radius;
    int x;
    int y;
    int size_x;
    int size_y;
    std::list<Room> get_rooms();
    
    std::string str();
    
};

#endif
