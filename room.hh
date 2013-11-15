#ifndef ROOM_HH
#define ROOM_HH

#include <sstream>
#include <stdlib.h>
#include <string>
#include <list>
#include <vector>

class Deck;
class Rect;


class Room
{
    std::string style;
    Deck* deck;
    std::list<Rect> rects;
    
public:
    Room(std::string style, Rect rect, Deck* deck);
    
    int get_area();
    bool intersects(Rect other);
    bool intersects(Room other);
    std::string get_style();
    std::list<Rect>& get_rects();
    
    std::string str();
    
};

#endif
