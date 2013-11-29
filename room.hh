#ifndef ROOM_HH
#define ROOM_HH

#include <sstream>
#include <stdlib.h>
#include <string>
#include <list>
#include <vector>

class Deck;
class Door;
class Rect;
class Lamp;
class Tile;


class Room
{
    static std::vector<std::string> room_styles;
    static std::vector<std::string> corridor_styles;
    
    std::string style_group;
    std::string style;
    Deck* deck;
    std::list<Rect> rects;
    std::list<Door*> doors;
    std::list<Lamp> lamps;
    
    std::vector<Tile> floor_tiles;
    std::vector<Tile> wall_tiles;
    std::vector<Tile> wall_top_tiles;
    std::vector<Tile> door_top_tiles;
    
public:
    Room(std::string style, Rect rect, Deck* deck);
    
    void update_tiles();
    
    std::string get_floor_texture_label();
    std::string get_wall_texture_label();
    
    std::vector<Tile>& get_floor_tiles();
    std::vector<Tile>& get_wall_tiles();
    std::vector<Tile>& get_wall_top_tiles();
    std::vector<Tile>& get_door_top_tiles();
    
    int get_area();
    int get_wall_length();
    bool contains(int x, int y);
    bool intersects(Rect other);
    bool intersects(Room other);
    std::string get_style();
    std::string get_style_group();
    void set_style_group(std::string style_group);
    std::list<Rect>& get_rects();
    std::list<Lamp>& get_lamps();
    void add_rect(Rect rect);
    void add_door(Door* door);
    void add_lamp(Lamp lamp);
    Deck* get_deck();
    
    std::string str();
    
};

#endif
