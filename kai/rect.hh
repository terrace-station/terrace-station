#ifndef RECT_HH
#define RECT_HH

#include <sstream>
#include <stdlib.h>
#include <string>
#include <list>
#include <vector>

class Room;

/**
 * Rect
 */
class Rect
{
public:
    int left, top, right, bottom;

    /**
     * Default constructor
     */
    Rect(int left, int top, int right, int bottom);
    
    int width();
    int height();
    int area();
    float aspect();
    bool intersects(Rect other);
    bool intersects(Room other);
    std::string str();
    
};

#endif
