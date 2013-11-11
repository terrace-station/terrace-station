#include "station.hh"

Station::Station()
{
    District district;
    districts.push_back(district);
}

std::string Station::str()
{
    return "Station";
}
