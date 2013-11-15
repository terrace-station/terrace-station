#ifndef DECK_HH
#define DECK_HH

#include <sstream>
#include <stdlib.h>
#include <string>
#include <list>

class District;
class Room;

class Deck
{
    float radius;
    int x;
    int y;
    int size_x;
    int size_y;
    District* district;
    std::list<Room> rooms;
    void init();
    
public:
    Deck(float radius, int x, int y, int size_x, int size_y, District* district);
    
    std::list<Room> get_rooms();
    
    std::string str();
    
};

#endif
