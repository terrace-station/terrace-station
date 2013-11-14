#include "rect.hh"
#include "room.hh"
#include "deck.hh"
#include "district.hh"
#include "zone.hh"
#include "station.hh"

Deck::Deck(float radius, int x, int y, int size_x, int size_y, District& district) :
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
    Room room1("room", rect1, *this);
    Room room2("corridor", rect2, *this);
    Room room3("corridor", rect3, *this);
    Room room4("room", rect4, *this);
    rooms.push_back(room1);
    rooms.push_back(room2);
    rooms.push_back(room3);
    rooms.push_back(room4);
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
