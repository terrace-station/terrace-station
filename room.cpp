#include "rect.hh"
#include "room.hh"
#include "deck.hh"
#include "district.hh"
#include "zone.hh"
#include "station.hh"

std::vector<std::string> Room::room_styles = {"industrial-chrome-clean",
                                            "industrial-chrome-dirty",
                                            "industrial-gold-clean",
                                            "industrial-gold-dirty",
                                            "industrial-copper-clean",
                                            "industrial-copper-dirty",
                                            "lab-chrome-clean",
                                            "lab-chrome-dirty",
                                            "lab-gold-clean",
                                            "lab-gold-dirty",
                                            "lab-copper-clean",
                                            "lab-copper-dirty",
                                            "holo"};

std::vector<std::string> Room::corridor_styles = {"corridor-chrome-clean",
                                               "corridor-chrome-dirty",
                                               "corridor-gold-clean",
                                               "corridor-gold-dirty",
                                               "corridor-copper-clean",
                                               "corridor-copper-dirty"};

Room::Room(std::string style, Rect rect, Deck* deck):
    style(style), deck(deck)
{
    int i;
    if (this->style == "corridor") {
        i = rand() % corridor_styles.size();
        this->style = corridor_styles[i];
    } else if (this->style == "room") {
        i = rand() % room_styles.size();
        this->style = room_styles[i];
    }
    this->rects.push_back(rect);
}

std::string Room::get_floor_texture_label() {
    return "floor-" + style;
}

std::string Room::get_wall_texture_label() {
    return "wall-" + style;
}

int Room::get_area()
{
    int result = 0;
    for (std::list<Rect>::iterator it = rects.begin(); it!=rects.end(); it++)
    {
        result += it->get_area();
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

std::string Room::get_style() {
    return style;
}

std::list<Rect>& Room::get_rects() {
    return rects;
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
    return ss.str();
}
