#ifndef ZONE_HH
#define ZONE_HH

#include <stdlib.h>
#include <string>
#include <vector>
#include <cstdlib>

#include "district.hh"


class Zone
{
    int circumference;
    std::vector<District> districts;
    
public:
    Zone(int circumference);
    
    std::vector<District>& get_districts();

    std::string str();
};

#endif
