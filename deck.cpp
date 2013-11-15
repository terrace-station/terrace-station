#include "rect.hh"
#include "room.hh"
#include "deck.hh"
#include "district.hh"
#include "zone.hh"
#include "station.hh"

Deck::Deck(float radius, int x, int y, int size_x, int size_y, District* district) :
    radius(radius), x(x), y(y), size_x(size_x), size_y(size_y), district(district)
{
    Deck::init();
}

void Deck::init()
{
    Rect rect1(x, y, x + size_x / 2, y + size_y / 2);
    Rect rect2(x + size_x / 2, y, x + size_x, y + size_y / 2);
    Rect rect3(x, y + size_y / 2, x + size_x / 2, y + size_y);
    Rect rect4(x + size_x / 2, y + size_y / 2, x + size_x, y + size_y);
    rooms.emplace_back("room", rect1, this);
    rooms.emplace_back("corridor", rect2, this);
    rooms.emplace_back("corridor", rect3, this);
    rooms.emplace_back("room", rect4, this);
}

std::list<Room> Deck::get_rooms() {
    return rooms;
}

std::string Deck::str()
{
    std::stringstream ss;
    ss << "      Deck:      (radius = " << radius;
    ss << ", x = " << x;
    ss << ", y = " << y;
    ss << ", size_x = " << size_x;
    ss << ", size_y = " << size_y << ")" << std::endl;
    for (std::list<Room>::iterator it = rooms.begin(); it != rooms.end(); it++)
    {
        ss << it->str();
    }
    return ss.str();
}
