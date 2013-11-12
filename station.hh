#ifndef STATION_HH
#define STATION_HH

#include <stdlib.h>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "district.hh"


class Station
{
    std::vector<District> districts;
    
public:
    Station();
    
    std::vector<District> get_districts();

    std::string str();
};

#endif
