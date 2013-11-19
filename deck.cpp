#include "tile.hh"
#include "rect.hh"
#include "room.hh"
#include "deck.hh"
#include "district.hh"
#include "zone.hh"
#include "station.hh"

#define DECK_HEIGHT 2

/**
 * Creates a new deck
 * 
 * \param   radius_offset   radius offset with respect to the district
 * \param   district        the district this deck belongs to
 */
Deck::Deck(float radius_offset, District* district) :
    radius_offset(radius_offset), district(district)
{
    Deck::init();
}

void Deck::init()
{
    int x = district->get_x();
    int y = district->get_y();
    int size_x = district->get_size_x();
    int size_y = district->get_size_y();
    Rect rect1(x, y, x + size_x / 2, y + size_y / 2);
    Rect rect2(x + size_x / 2, y, x + size_x, y + size_y / 2);
    Rect rect3(x, y + size_y / 2, x + size_x / 2, y + size_y);
    Rect rect4(x + size_x / 2, y + size_y / 2, x + size_x, y + size_y);
    rooms.emplace_back("room", rect1, this);
    rooms.emplace_back("corridor", rect2, this);
    rooms.emplace_back("corridor", rect3, this);
    rooms.emplace_back("room", rect4, this);
}

float Deck::get_radius() {
    return district->get_radius() + radius_offset;
}

std::list<Room> Deck::get_rooms() {
    return rooms;
}

std::string Deck::str()
{
    std::stringstream ss;
    ss << "      Deck:      (radius_offset = " << radius_offset << ")" << std::endl;
    for (std::list<Room>::iterator it = rooms.begin(); it != rooms.end(); it++)
    {
        ss << it->str();
    }
    return ss.str();
}
