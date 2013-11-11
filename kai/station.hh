#ifndef STATION_HH
#define STATION_HH

#include <stdlib.h>
#include <string>
#include <list>
#include <vector>

#include "district.hh"

/**
 * Space Station
 */
class Station
{
public:
    std::list<District> districts;

    /**
     * Default constructor
     */
    Station();
    
    std::string str();
    
};

#endif
