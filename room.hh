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
    static std::vector<std::string> room_styles;
    static std::vector<std::string> corridor_styles;
    
    std::string style;
    Deck* deck;
    std::list<Rect> rects;
    
public:
    Room(std::string style, Rect rect, Deck* deck);
    
    std::string get_floor_texture_label();
    std::string get_wall_texture_label();
    int get_area();
    bool intersects(Rect other);
    bool intersects(Room other);
    std::string get_style();
    std::list<Rect>& get_rects();
    
    std::string str();
    
};

#endif
