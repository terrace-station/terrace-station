#ifndef ROOM_HH
#define ROOM_HH

#include <sstream>
#include <stdlib.h>
#include <string>
#include <list>
#include <vector>

class Deck;
class Rect;
class Tile;


class Room
{
    static std::vector<std::string> room_styles;
    static std::vector<std::string> corridor_styles;
    
    std::string style_group;
    std::string style;
    Deck* deck;
    std::list<Rect> rects;
    
    std::vector<Tile> floor_tiles;
    std::vector<Tile> wall_tiles;
    std::vector<Tile> wall_top_tiles;
    
public:
    Room(std::string style, Rect rect, Deck* deck);
    
    void update_tiles();
    
    std::string get_floor_texture_label();
    std::string get_wall_texture_label();
    
    std::vector<Tile>& get_floor_tiles();
    std::vector<Tile>& get_wall_tiles();
    std::vector<Tile>& get_wall_top_tiles();
    
    int get_area();
    int get_wall_length();
    bool intersects(Rect other);
    bool intersects(Room other);
    std::string get_style();
    std::string get_style_group();
    std::list<Rect>& get_rects();
    Deck* get_deck();
    
    std::string str();
    
};

#endif
