#ifndef SYSTEM_HH
#define SYSTEM_HH

#include <FL/glu.h>
#include <FL/gl.h>
#include <stdlib.h>


#include "glhilf.h"


class Planet;



class System
{
public:
   
   int anzahl_planeten;
   float position[3];
   float sonnenradius;
   float abstand_max;
   float abstand_umlaufbahn;
   
   Planet* planeten;
   void zeichne_system();
   
   System();
   System(float pos_x_, float pos_y_, float pos_z_);
   System(int anzahl_, float pos_x_, float pos_y_, float pos_z_);
};



class Planet
{
public:
   float temperatur;
   float radius;
   char klasse;
   int spezial;
   float phase;
   int textur_ind;
   
   void erstelle_zufall();
};



#endif