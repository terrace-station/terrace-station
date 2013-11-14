#include "rect.hh"
#include "room.hh"
#include "deck.hh"
#include "district.hh"
#include "zone.hh"
#include "station.hh"

Room::Room(std::string style, Rect rect, Deck& deck):
    style(style), deck(deck)
{
    this->rects.push_back(rect);
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
