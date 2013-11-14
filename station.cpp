#include "station.hh"

#define PI          3.14159265358979323846
#define CF_MIN      600     // Minimum circumference
#define CF_DELTA    100     // Difference in circumference
#define NR_OF_ZONES 4

Station::Station()
{
    int x, y, width, height, cf, nr, nr_of_decks;
    float radius;
    for (int i = 0; i < NR_OF_ZONES; ++i)
    {
        cf = CF_MIN + i * CF_DELTA;
        Zone zone(cf);
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
