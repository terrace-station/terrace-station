#include "rect.hh"
#include "room.hh"
#include "deck.hh"
#include "district.hh"
#include "zone.hh"
#include "station.hh"

#define CF_MIN      600     // Minimum circumference
#define CF_DELTA    100     // Difference in circumference
#define NR_OF_ZONES 4

Station::Station()
{
    for (int i = 0; i < NR_OF_ZONES; ++i)
    {
        int cf = CF_MIN + i * CF_DELTA;
        Zone zone(cf, *this);
        zones.push_back(zone);
    }
}

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
