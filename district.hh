#ifndef DISTRICT_HH
#define DISTRICT_HH

#include <stdlib.h>
#include <string>
#include <vector>

#include "deck.hh"
#include "mausobjekt.hh"

class District: public Mausobjekt
{
    float radius;
    int x;
    int y;
    int size_x;
    int size_y;
    std::vector<Deck> decks;
    
public:
    District(float radius, int x, int y, int size_x, int size_y, int nr_of_decks);
    District();
    
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
