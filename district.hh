#ifndef DISTRICT_HH
#define DISTRICT_HH

#include <sstream>
#include <stdlib.h>
#include <string>
#include <vector>

#include "mausobjekt.hh"

class Zone;
class Deck;

class District: public Mausobjekt
{
    int x;
    int y;
    int size_x;
    int size_y;
    bool circular;
    Zone* zone;
    std::vector<Deck> decks;
    bool alarm;
    
public:
    District(int x, int y, int size_x, int size_y,
             int nr_of_decks, bool circular, Zone* zone);
             
    int get_x();
    int get_y();
    int get_size_x();
    int get_size_y();

    float get_radius();
    float get_radius_min();
    float get_radius_max();
    float get_phi_min();
    float get_phi_max();
    float get_z_min();
    float get_z_max();
    float get_angle();
    bool is_circular();
    std::vector<Deck>& get_decks();
    Zone* get_zone();
    bool get_alarm();
    void set_alarm(bool new_value);
    
    std::string str();
};

#endif
