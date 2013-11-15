#include "rect.hh"
#include "room.hh"
#include "deck.hh"
#include "district.hh"
#include "zone.hh"
#include "station.hh"

#define DECK_HEIGHT 3

District::District(int x, int y, int size_x, int size_y,
                   int nr_of_decks, Zone* zone) :
    x(x), y(y), size_x(size_x), size_y(size_y), zone(zone)
{
    decks.reserve(nr_of_decks);
    for (int i = 0; i < nr_of_decks; ++i)
    {
        float deck_radius = get_radius() + i * DECK_HEIGHT - 2.5;
        decks.emplace_back(deck_radius, x, y, size_x, size_y, this);
    }
    
    objekt_typ = "District";
}

float District::get_radius() {
    return zone->get_radius();
}

float District::get_radius_min() {
    return get_radius() - decks.size() * DECK_HEIGHT / 2.0;
}
float District::get_radius_max() {
    return get_radius() + decks.size() * DECK_HEIGHT / 2.0;
}

float District::get_phi_min() {
    return x / get_radius();
}
float District::get_phi_max() {
    return (size_x + x) / get_radius();
}

float District::get_z_min() {
    return y;
}
float District::get_z_max() {
    return y + size_y;
}
std::vector<Deck>& District::get_decks() {
    return decks;
}

std::string District::str()
{
    std::stringstream ss;
    ss << "    District:  (radius = " << get_radius();
    ss << ", x = " << x;
    ss << ", y = " << y;
    ss << ", size_x = " << size_x;
    ss << ", size_y = " << size_y << ")" << std::endl;
    for (std::vector<Deck>::iterator it = decks.begin(); it != decks.end(); it++)
    {
        ss << it->str();
    }
    return ss.str();
}
