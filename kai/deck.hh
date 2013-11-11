#ifndef DECK_HH
#define DECK_HH

#include <stdlib.h>
#include <string>
#include <list>
#include <vector>

#include "room.hh"
#include "wall.hh"
#include "door.hh"
#include "rect.hh"

/**
 * Station deck
 */
class Deck
{
public:
    

    /**
     * Default constructor
     */
    Deck();
    
    std::string str();
    
};

#endif
