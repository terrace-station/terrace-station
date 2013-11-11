#ifndef TEXTUR_HH // bedingtes Einbinden
#define TEXTUR_HH

#include <string>
#include <fstream>
#include <FL/glu.h>

class Textur 
{
public:
   GLuint id;
  
   unsigned int groesse_x;
   unsigned int groesse_y;
   char *daten;
      
   void lade_Textur(std::string dateiname, int farbtiefe);
   unsigned int vierbyte_lesen(std::ifstream& bilddatei);
   void bitmapdaten_lesen(std::ifstream& bilddatei, char* daten, int datenmenge);

   
   Textur(std::string dateiname, int farbtiefe);
};

#endif