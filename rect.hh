#ifndef RECT_HH
#define RECT_HH

#include <sstream>
#include <stdlib.h>
#include <string>
#include <list>
#include <vector>

class Room;

class Rect
{
public:
    int left, top, right, bottom;
    
    Rect(int left, int top, int right, int bottom);
    
    int get_left();
    int get_top();
    int get_right();
    int get_bottom();
    int get_width();
    int get_height();
    int get_area();
    float get_aspect();
    bool contains(int x, int y);
    bool intersects(Rect other);
    bool intersects(Room other);
    std::string str();
    
};

#endif
