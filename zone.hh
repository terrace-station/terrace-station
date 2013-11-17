#ifndef ZONE_HH
#define ZONE_HH

#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <math.h>

class Station;
class District;

class Zone
{
    int circumference;
    float omega;
    float angle;
    
    Station* station;
    std::vector<District> districts;
    
public:
    Zone(int circumference, std::string style, Station* station);
    
    float get_radius();
    float get_omega();
    float get_angle();
    
    void set_angle(float angle_);
    
    std::vector<District>& get_districts();

    std::string str();
};

#endif
