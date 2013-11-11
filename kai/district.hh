#ifndef DISTRICT_HH
#define DISTRICT_HH

#include <stdlib.h>
#include <string>
#include <list>
#include <vector>

#include "deck.hh"

/**
 * Station district
 */
class District
{
public:
    std::list<Deck> decks;

    /**
     * Default constructor
     */
    District();
    
    std::string str();
    
};

#endif
