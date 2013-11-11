#ifndef TEXTURENSAMMLUNG_HH
#define TEXTURENSAMMLUNG_HH

#include "textur.hh"



class Texturensammlung
{
public:  
   
   Textur* tex_stars;
   Textur* tex_sonne;
   Textur* tex_district;
   Textur* tex_flare[5];
   Textur* tex_planet[10];
   
   void texturen_laden();
   
   Texturensammlung();
   ~Texturensammlung();
};



#endif