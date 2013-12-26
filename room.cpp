#include "tile.hh"
#include "lamp.hh"
#include "rect.hh"
#include "door.hh"
#include "room.hh"
#include "deck.hh"
#include "district.hh"
#include "zone.hh"
#include "station.hh"
#include "hilfsfunktionen.h"

#define DEFAULT_STYLE_GROUP "error"

std::vector<std::string> Room::room_styles = {
                                                //~ "corridor-chrome-clean",
                                                //~ "corridor-chrome-dirty",
                                                "corridor-gold-clean",
                                                "corridor-gold-dirty",
                                                "corridor-copper-clean",
                                                "corridor-copper-dirty",
                                                //~ "industrial-chrome-clean",
                                                //~ "industrial-chrome-dirty",
                                                "industrial-gold-clean",
                                                "industrial-gold-dirty",
                                                "industrial-copper-clean",
                                                "industrial-copper-dirty",
                                                //~ "lab-chrome-clean",
                                                //~ "lab-chrome-dirty",
                                                "lab-gold-clean",
                                                "lab-gold-dirty",
                                                "lab-copper-clean",
                                                "lab-copper-dirty",
                                                "holo"
                                                };

std::vector<std::string> Room::corridor_styles = {
                                                "corridor-chrome-clean",
                                                "corridor-chrome-dirty",
                                                //~ "corridor-gold-clean",
                                                //~ "corridor-gold-dirty",
                                                //~ "corridor-copper-clean",
                                                //~ "corridor-copper-dirty",
                                                "industrial-chrome-clean",
                                                "industrial-chrome-dirty",
                                                //~ "industrial-gold-clean",
                                                //~ "industrial-gold-dirty",
                                                //~ "industrial-copper-clean",
                                                //~ "industrial-copper-dirty",
                                                "lab-chrome-clean",
                                                "lab-chrome-dirty",
                                                //~ "lab-gold-clean",
                                                //~ "lab-gold-dirty",
                                                //~ "lab-copper-clean",
                                                //~ "lab-copper-dirty",
                                                //~ "holo"
                                                };

/**
 * Creates a new rectangular room
 * 
 * \param   style_group "room" or "corridor"
 * \param   rect        A rect, describing the shape of this room
 * \param   deck        the deck this room belongs to
 */
Room::Room(std::string style_group, Rect rect, Deck* deck):
    deck(deck)
{
    visible = false;
    light_on = false;
    set_style_group(style_group);
    this->rects.push_back(rect);
    update();
    objekt_typ = "Room";
}

/**
 * Update cached data
 * 
 * Some redundant data - like tiles and the bounding box - are cached for better
 * performance. This method must be called, whenever this rooms geometry
 * changes to reflect the current state of this room.
 */
void Room::update() {
    // update bounding box:
    bounding_box.clear();
    int left = rects.front().get_left();
    int right = rects.front().get_right();
    int top = rects.front().get_top();
    int bottom = rects.front().get_bottom();
    for (std::list<Rect>::iterator rect_it = rects.begin(); rect_it != rects.end(); rect_it++)
    {
        if (rect_it->get_left() < left) { left = rect_it->get_left(); }
        if (rect_it->get_right() > right) { right = rect_it->get_right(); }
        if (rect_it->get_top() < top) { top = rect_it->get_top(); }
        if (rect_it->get_bottom() > bottom) { bottom = rect_it->get_bottom(); }
    }
    std::vector<GLfloat> point(3);
    hilf::deck2station(right, bottom, deck->get_district()->get_radius(), deck->get_radius(), point[0], point[1], point[2]);
    bounding_box.push_back(point);
    hilf::deck2station(left, bottom, deck->get_district()->get_radius(), deck->get_radius(), point[0], point[1], point[2]);
    bounding_box.push_back(point);
    hilf::deck2station(left, top, deck->get_district()->get_radius(), deck->get_radius(), point[0], point[1], point[2]);
    bounding_box.push_back(point);
    hilf::deck2station(right, top, deck->get_district()->get_radius(), deck->get_radius(), point[0], point[1], point[2]);
    bounding_box.push_back(point);
    
    // update floor tiles:
    floor_tiles.clear();
    floor_tiles.reserve(get_area());
    for (std::list<Rect>::iterator rect_it = rects.begin(); rect_it != rects.end(); rect_it++)
    {
        for (int x = rect_it->get_left(); x < rect_it->get_right(); ++x) {
            for (int y = rect_it->get_top(); y < rect_it->get_bottom(); ++y) {
                floor_tiles.push_back(Tile(x, y, deck->get_district()->get_radius(), deck->get_radius(), TileType::FLOOR));
            }
        }
    }
    
    // update roof tiles:
    roof_tiles.clear();
    roof_tiles.reserve(get_area());
    for (std::list<Rect>::iterator rect_it = rects.begin(); rect_it != rects.end(); rect_it++)
    {
        for (int x = rect_it->get_left(); x < rect_it->get_right(); ++x) {
            for (int y = rect_it->get_top(); y < rect_it->get_bottom(); ++y) {
                roof_tiles.push_back(Tile(x, y, deck->get_district()->get_radius(), deck->get_radius(), TileType::ROOF));
            }
        }
    }
    
    // update wall tiles:
    wall_tiles.clear();
    wall_tiles.reserve(get_wall_length());
    wall_top_tiles.clear();
    wall_top_tiles.reserve(get_wall_length());
    for (std::list<Rect>::iterator rect_it = rects.begin(); rect_it!=rects.end(); rect_it++)
    {
        for (int x = rect_it->get_left(); x < rect_it->get_right(); ++x) {
            // add southern wall-tiles:
            if (!contains(x, rect_it->get_top() - 1)) {
                bool is_door = false;
                for (std::list<Door*>::iterator door_it = doors.begin(); door_it != doors.end(); door_it++)
                {
                    if ((*door_it)->get_x() == x && (*door_it)->get_y() == rect_it->get_top() && (*door_it)->get_orientation() % 2 == 1) {
                        door_top_tiles.push_back(Tile(x, rect_it->get_top(), deck->get_district()->get_radius(), deck->get_radius(), TileType::WALL_ROOF_SOUTH));
                        is_door = true;
                        break;
                    }
                }
                if (!is_door) {
                    wall_tiles.push_back(Tile(x, rect_it->get_top(), deck->get_district()->get_radius(), deck->get_radius(), TileType::WALL_SOUTH));
                    wall_top_tiles.push_back(Tile(x, rect_it->get_top(), deck->get_district()->get_radius(), deck->get_radius(), TileType::WALL_ROOF_SOUTH));
                }
            }
            // add northern wall-tiles:
            if (!contains(x, rect_it->get_bottom())) {
                bool is_door = false;
                for (std::list<Door*>::iterator door_it = doors.begin(); door_it != doors.end(); door_it++)
                {
                    if ((*door_it)->get_x() == x && (*door_it)->get_y() == rect_it->get_bottom() && (*door_it)->get_orientation() % 2 == 1) {
                        door_top_tiles.push_back(Tile(x, rect_it->get_bottom(), deck->get_district()->get_radius(), deck->get_radius(), TileType::WALL_ROOF_NORTH));
                        is_door = true;
                        break;
                    }
                }
                if (!is_door) {
                    wall_tiles.push_back(Tile(x, rect_it->get_bottom(), deck->get_district()->get_radius(), deck->get_radius(), TileType::WALL_NORTH));
                    wall_top_tiles.push_back(Tile(x, rect_it->get_bottom(), deck->get_district()->get_radius(), deck->get_radius(), TileType::WALL_ROOF_NORTH));
                }
            }
        }
        for (int y = rect_it->get_top(); y < rect_it->get_bottom(); ++y) {
            // add eastern wall-tiles:
            if (!contains(rect_it->get_left() - 1, y)) {
                bool is_door = false;
                for (std::list<Door*>::iterator door_it = doors.begin(); door_it != doors.end(); door_it++)
                {
                    if ((*door_it)->get_x() == rect_it->get_left() && (*door_it)->get_y() == y && (*door_it)->get_orientation() % 2 == 0) {
                        door_top_tiles.push_back(Tile(rect_it->get_left(), y, deck->get_district()->get_radius(), deck->get_radius(), TileType::WALL_ROOF_EAST));
                        is_door = true;
                        break;
                    }
                }
                if (!is_door) {
                    wall_tiles.push_back(Tile(rect_it->get_left(), y, deck->get_district()->get_radius(), deck->get_radius(), TileType::WALL_EAST));
                    wall_top_tiles.push_back(Tile(rect_it->get_left(), y, deck->get_district()->get_radius(), deck->get_radius(), TileType::WALL_ROOF_EAST));
                }
            }
            // add western wall-tiles:
            if (!contains(rect_it->get_right(), y)) {
                bool is_door = false;
                for (std::list<Door*>::iterator door_it = doors.begin(); door_it!=doors.end(); door_it++)
                {
                    if ((*door_it)->get_x() == rect_it->get_right() && (*door_it)->get_y() == y && (*door_it)->get_orientation() % 2 == 0) {
                        door_top_tiles.push_back(Tile(rect_it->get_right(), y, deck->get_district()->get_radius(), deck->get_radius(), TileType::WALL_ROOF_WEST));
                        is_door = true;
                        break;
                    }
                }
                if (!is_door) {
                    wall_tiles.push_back(Tile(rect_it->get_right(), y, deck->get_district()->get_radius(), deck->get_radius(), TileType::WALL_WEST));
                    wall_top_tiles.push_back(Tile(rect_it->get_right(), y, deck->get_district()->get_radius(), deck->get_radius(), TileType::WALL_ROOF_WEST));
                }
            }
        }
    }
}

bool Room::is_visible() { return visible; }
bool Room::is_light_on() { return light_on; }

void Room::set_visible(bool new_value) { visible = new_value; }
void Room::set_light_on(bool new_value) { light_on = new_value; }

std::string Room::get_floor_texture_label() { return "floor-" + style; }
std::string Room::get_wall_texture_label() { return "wall-" + style; }

std::vector<Tile>& Room::get_floor_tiles() { return floor_tiles; }
std::vector<Tile>& Room::get_wall_tiles() { return wall_tiles; }
std::vector<Tile>& Room::get_wall_top_tiles() { return wall_top_tiles; }
std::vector<Tile>& Room::get_door_top_tiles() { return door_top_tiles; }
std::vector<Tile>& Room::get_roof_tiles() { return roof_tiles; }

int Room::get_area()
{
    int result = 0;
    for (std::list<Rect>::iterator it = rects.begin(); it!=rects.end(); it++)
    {
        result += it->get_area();
    }
    return result;
}

int Room::get_wall_length()
{
    // (only a workaround: won't work correctly for rooms with more than one rect)
    int result = 0;
    for (std::list<Rect>::iterator it = rects.begin(); it!=rects.end(); it++)
    {
        result += 2 * it->get_width() + 2 * it->get_height();
    }
    return result;
}

bool Room::contains(int x, int y) {
    for (std::list<Rect>::iterator it = rects.begin(); it!=rects.end(); it++)
    {
        if (it->contains(x, y)) {
            return true;
        }
    }
    return false;
}

bool Room::intersects(Rect other)
{
    for (std::list<Rect>::iterator it = rects.begin(); it!=rects.end(); it++)
    {
        if (it->intersects(other)) {
            return true;
        }
    }
    return false;
}

void Room::add_rect(Rect rect)
{
    rects.push_back(rect);
    update();
}

void Room::add_door(Door* door)
{
    doors.push_back(door);
    update();
}

void Room::add_lamp(Lamp lamp)
{
    lamps.push_back(lamp);
}

bool Room::intersects(Room other)
{
    for (std::list<Rect>::iterator it = rects.begin(); it!=rects.end(); it++)
    {
        if (other.intersects(*it)) {
            return true;
        }
    }
    return false;
}

void Room::set_style_group(std::string style_group) {
    this->style_group = style_group;
    int i;
    if (style_group == "corridor") {
        i = rand() % corridor_styles.size();
        this->style = corridor_styles[i];
    } else if (style_group == "room") {
        i = rand() % room_styles.size();
        this->style = room_styles[i];
    } else {
        this->style = DEFAULT_STYLE_GROUP;
    }
}

std::string Room::get_style_group() {
    return style_group;
}

std::string Room::get_style() {
    return style;
}

std::list<Rect>& Room::get_rects() {
    return rects;
}

std::list<Lamp>& Room::get_lamps() {
    return lamps;
}

std::vector<std::vector<GLfloat> >& Room::get_bounding_box() {
    return bounding_box;
}

Deck* Room::get_deck() {
    return deck;
}

std::list<Room*> Room::get_neighbours() {
    std::list<Room*> neighbours;
    for (std::list<Door*>::iterator door_it = doors.begin(); door_it != doors.end(); door_it++) {
        if ((*door_it)->room1 != this) {
            neighbours.push_back((*door_it)->room1);
        } else {
            neighbours.push_back((*door_it)->room2);
        }
    }
    return neighbours;
}

std::string Room::str()
{
    std::stringstream ss;
    ss << "        Room:      (style = " << style << ", area = " << get_area();
    ss << ", nr of rects = " << rects.size() << ")" << std::endl;
    for (std::list<Rect>::iterator it = rects.begin(); it != rects.end(); it++)
    {
        ss << it->str();
    }
    //~ for (std::vector<Tile>::iterator it = floor_tiles.begin(); it != floor_tiles.end(); it++)
    //~ {
        //~ ss << it->str();
    //~ }
    return ss.str();
}
