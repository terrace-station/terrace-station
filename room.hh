#ifndef ROOM_HH
#define ROOM_HH

#include <sstream>
#include <stdlib.h>
#include <string>
#include <list>
#include <vector>

#include "mausobjekt.hh"

class Deck;
class Door;
class Rect;
class Lamp;
class Tile;


class Room: public Mausobjekt
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
    std::vector<Tile> roof_tiles;
    
    bool visible;
    bool light_on;
    
    std::vector<std::vector<GLfloat> > bounding_box;
    
public:
    bool inview;
    
    Room(std::string style, Rect rect, Deck* deck);
    
    void update();
    
    bool is_visible();
    bool is_light_on();

    void set_visible(bool new_value);
    void set_light_on(bool new_value);

    std::string get_floor_texture_label();
    std::string get_wall_texture_label();
    
    std::vector<Tile>& get_floor_tiles();
    std::vector<Tile>& get_wall_tiles();
    std::vector<Tile>& get_wall_top_tiles();
    std::vector<Tile>& get_door_top_tiles();
    std::vector<Tile>& get_roof_tiles();
    
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
    std::list<Door*>& get_doors();
    void add_rect(Rect rect);
    void add_door(Door* door);
    void add_lamp(Lamp lamp);
    Deck* get_deck();
    
    std::list<Room*> get_neighbours();
    
    std::string str();
    bool onscreen;
    std::vector<std::vector<GLfloat> >& get_bounding_box();
    
};

#endif
