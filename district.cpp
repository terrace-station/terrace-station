#include "district.hh"

#include "deck.hh"


District::District()
{
   aktiv = false;
   
   deck_count = rand()%3+2;
   
   radius_min = rand()%30/10+3;
   radius_max = radius_min+deck_count*2*STEP;
   
   phi_min = rand()%360*RAD;
   phi_max = rand()%360*RAD;
   
   bogenlaenge = phi_max-phi_min;
   if(bogenlaenge < 0) bogenlaenge += 2*PI;
   bogenlaenge *= radius_min;
   
   do
   {
      z_min = rand()%80/10.0;
      z_max = rand()%80/10.0;
      
   } while (z_min == z_max);
   
   if(z_min > z_max)
   { float tmp = z_min; z_min = z_max; z_max = tmp; }
   
   size_x = bogenlaenge/STEP;
   size_y = (z_max-z_min)/STEP;
   
   deck = new Deck[deck_count];
   
   for (int i=0; i<deck_count; i++)
   {
      deck[i].size_x = size_x;
      deck[i].size_y = size_y;
   }
   
   objekt_typ = "District";
}


void District::text_ausgabe()
{
   std::cout << "\tRadius: Von " << radius_min << " bis " << radius_max << std::endl;
   std::cout << "\tPhi: Von " << phi_min/RAD << " bis " << phi_max/RAD << std::endl;
   std::cout << "\tZ: Von " << z_min << " bis " << z_max << std::endl;
   std::cout << std::endl;
   std::cout << "\tsize_x: " << size_x << std::endl;
   std::cout << "\tsize_y: " << size_y << std::endl;
   std::cout << "\tdecks: " << deck_count << std::endl;
}


District::~District()
{
   delete[] deck;
}



