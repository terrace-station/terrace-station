#ifndef STATION_HH
#define STATION_HH

#include <sstream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

class Zone;

class Station
{
    std::vector<Zone> zones;
    
public:
    Station();
    
    std::vector<Zone>& get_zones();

    std::string str();
};

#endif
