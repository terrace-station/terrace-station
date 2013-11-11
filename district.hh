#ifndef DISTRICT_HH
#define DISTRICT_HH

#include <stdlib.h>
#include <iostream>

#include "mausobjekt.hh"

#include "hilfsfunktionen.h"
#define STEP 0.05

class Deck;

class District: public Mausobjekt
{
public:
   int deck_count;
   int size_x, size_y;
   
   float radius_min, radius_max;
   float phi_min, phi_max;
   float z_min, z_max;
   
   float bogenlaenge;
   
   Deck* deck;
   bool aktiv;
   
   void text_ausgabe();
   
   District();
   ~District();
};


#endif