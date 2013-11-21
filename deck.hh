#ifndef DECK_HH
#define DECK_HH

#include <sstream>
#include <stdlib.h>
#include <string>
#include <list>

class District;
class Room;
class Door;

struct CorridorBuilder {
    int     x;
    int     y;
    int     direction;
    int     width;
    bool    active;
};

class Deck
{
    float radius_offset;
    District* district;
    std::list<Room> rooms;
    std::list<Door> doors;
    void init();
    
public:
    Deck(float radius_offset, District* district);
    
    float get_radius();
    std::list<Room>& get_rooms();
    District* get_district();
    
    std::string str();
    
};

#endif
