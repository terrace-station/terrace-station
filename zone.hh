#ifndef ZONE_HH
#define ZONE_HH

#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <vector>

class Station;
class District;

class Zone
{
    int circumference;
    Station* station;
    std::vector<District> districts;
    
public:
    Zone(int circumference, std::string style, Station* station);
    
    float get_radius();
    std::vector<District>& get_districts();

    std::string str();
};

#endif
