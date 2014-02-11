#include "tile.hh"
#include "lamp.hh"
#include "rect.hh"
#include "door.hh"
#include "room.hh"
#include "deck.hh"
#include "district.hh"
#include "zone.hh"
#include "station.hh"
#include "log.hh"

#define DECK_DISTANCE 3

/**
 * Creates a new district
 * 
 * \param   x           the x-position of this district
 * \param   y           the y-position of this district
 * \param   size_x      the width of this district
 * \param   size_y      the height of this district
 * \param   nr_of_decks the number of decks in this district
 * \param   circular    if true, this district is ring-shaped
 * \param   zone        the zone this district belongs to
 */
District::District(int x, int y, int size_x, int size_y,
                   int nr_of_decks, bool circular, Zone* zone) :
    x(x), y(y), size_x(size_x), size_y(size_y), circular(circular), zone(zone)
{
    LOG(DEBUG) << "Building district...";
    decks.reserve(nr_of_decks);
    for (int i = 0; i < nr_of_decks; ++i)
    {
        float radius_offset = - i * DECK_DISTANCE;
        decks.emplace_back(radius_offset, this);
    }
    
    alarm = false;
    objekt_typ = "District";
    
    camera.set_start(get_radius_min(), 0.5*(get_phi_min()*GRAD+get_phi_max()*GRAD), 0.5*(get_z_min()+get_z_max()), 10, 45, 10);
    camera.set_boundaries(get_radius_min(),   get_radius_min(), 
                          get_phi_min()*GRAD, get_phi_max()*GRAD, 
                          get_z_min(),        get_z_max(), 
                          1, 30,
                          0, 90, 
                          -1000, 1000);
    camera.set_upside(-1);
}

int District::get_x() { return x; }
int District::get_y() { return y; }

int District::get_size_x() { return size_x; }
int District::get_size_y() { return size_y; }

float District::get_radius() { return zone->get_radius(); }

float District::get_radius_min() { return get_radius() - decks.size() * DECK_DISTANCE; }
float District::get_radius_max() { return get_radius(); }

float District::get_phi_min() { return x / get_radius(); }
float District::get_phi_max() { return (size_x + x) / get_radius(); }

float District::get_z_min() { return y; }
float District::get_z_max() { return y + size_y; }

float District::get_angle() { return zone->get_angle(); }

bool District::is_circular() { return circular; }

std::vector<Deck>& District::get_decks() { return decks; }

Zone* District::get_zone() { return zone; }

bool District::get_alarm() { return alarm; }
void District::set_alarm(bool new_value) { alarm = new_value; }

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
