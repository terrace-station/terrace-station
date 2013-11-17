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
    
public:
    District(int x, int y, int size_x, int size_y,
             int nr_of_decks, bool circular, Zone* zone);
    
    float get_radius();
    float get_radius_min();
    float get_radius_max();
    float get_phi_min();
    float get_phi_max();
    float get_z_min();
    float get_z_max();
    std::vector<Deck>& get_decks();
    
    std::string str();
};

#endif
