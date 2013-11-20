#include "tile.hh"
#include "rect.hh"
#include "room.hh"
#include "deck.hh"
#include "district.hh"
#include "zone.hh"
#include "station.hh"

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
    set_style_group(style_group);
    this->rects.push_back(rect);
    update_tiles();
}

void Room::update_tiles() {
    //~ std::cout << "Updating tiles ...";
    // update floor tiles:
    floor_tiles.clear();
    floor_tiles.reserve(get_area());
    for (std::list<Rect>::iterator it = rects.begin(); it!=rects.end(); it++)
    {
        Rect& rect = *it;
        for (int x = rect.get_left(); x < rect.get_right(); ++x) {
            for (int y = rect.get_top(); y < rect.get_bottom(); ++y) {
                floor_tiles.push_back(Tile(x, y, deck->get_district()->get_radius(), deck->get_radius()));
            }
        }
    }
    // update wall tiles:
    // (only a workaround: won't work correctly for rooms with more than one rect)
    wall_tiles.clear();
    wall_tiles.reserve(get_wall_length());
    for (std::list<Rect>::iterator it = rects.begin(); it!=rects.end(); it++)
    {
        Rect& rect = *it;
        for (int x = rect.get_left(); x < rect.get_right(); ++x) {
            // add northern wall-tiles:
            wall_tiles.push_back(Tile(x, rect.get_top(), deck->get_district()->get_radius(), deck->get_radius(), 1, false));
            // add southern wall-tiles:
            wall_tiles.push_back(Tile(x, rect.get_bottom(), deck->get_district()->get_radius(), deck->get_radius(), 3, false));
        }
        for (int y = rect.get_top(); y < rect.get_bottom(); ++y) {
            // add western wall tiles:
            wall_tiles.push_back(Tile(rect.get_left(), y, deck->get_district()->get_radius(), deck->get_radius(), 0, false));
            // add eastern wall tiles:
            wall_tiles.push_back(Tile(rect.get_right(), y, deck->get_district()->get_radius(), deck->get_radius(), 2, false));
        }
    }
    // update wall-top tiles:
    // (only a workaround: won't work correctly for rooms with more than one rect)
    wall_top_tiles.clear();
    wall_top_tiles.reserve(get_wall_length());
    for (std::list<Rect>::iterator it = rects.begin(); it!=rects.end(); it++)
    {
        Rect& rect = *it;
        for (int x = rect.get_left(); x < rect.get_right(); ++x) {
            // add northern wall-tiles:
            wall_top_tiles.push_back(Tile(x, rect.get_top(), deck->get_district()->get_radius(), deck->get_radius(), 1, true));
            // add southern wall-tiles:
            wall_top_tiles.push_back(Tile(x, rect.get_bottom(), deck->get_district()->get_radius(), deck->get_radius(), 3, true));
        }
        for (int y = rect.get_top(); y < rect.get_bottom(); ++y) {
            // add western wall tiles:
            wall_top_tiles.push_back(Tile(rect.get_left(), y, deck->get_district()->get_radius(), deck->get_radius(), 0, true));
            // add eastern wall tiles:
            wall_top_tiles.push_back(Tile(rect.get_right(), y, deck->get_district()->get_radius(), deck->get_radius(), 2, true));
        }
    }
    //~ std::cout << " done." << std::endl;
}

std::string Room::get_floor_texture_label() { return "floor-" + style; }
std::string Room::get_wall_texture_label() { return "wall-" + style; }

std::vector<Tile>& Room::get_floor_tiles() { return floor_tiles; }
std::vector<Tile>& Room::get_wall_tiles() { return wall_tiles; }
std::vector<Tile>& Room::get_wall_top_tiles() { return wall_top_tiles; }

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
    update_tiles();
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

Deck* Room::get_deck() {
    return deck;
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
