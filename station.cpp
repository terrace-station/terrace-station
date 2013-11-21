#include "tile.hh"
#include "rect.hh"
#include "room.hh"
#include "deck.hh"
#include "district.hh"
#include "zone.hh"
#include "station.hh"

#define PI    3.14159265358979323846
#define CF_MIN      400     // Minimum circumference
#define CF_DELTA    110     // Difference in circumference
#define NR_OF_ZONES 4

Station::Station()
{
    std::cout << "Building station...";
    zones.reserve(NR_OF_ZONES);
    int ring_zone = rand() % NR_OF_ZONES;
    for (int i = 0; i < NR_OF_ZONES; ++i)
    {
        int cf = CF_MIN + i * CF_DELTA;
        if (i == ring_zone) {
            zones.emplace_back(cf, "rings", this);
        } else {
            zones.emplace_back(cf, "segments", this);
        }
    }
    
    active_district = NULL;
}

void Station::set_active_district(District* dis) { active_district = dis; }
District* Station::get_active_district() { return active_district; }

std::vector<Zone>& Station::get_zones() {
    return zones;
}
    
std::string Station::str()
{
    std::stringstream ss;
    ss << "Station:" << std::endl;
    for (std::vector<Zone>::iterator it = zones.begin(); it != zones.end(); it++)
    {
        ss << it->str();
    }
    return ss.str();
}
