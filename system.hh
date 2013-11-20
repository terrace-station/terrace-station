#ifndef SYSTEM_HH
#define SYSTEM_HH

#include <string>
#include <vector>
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
    static std::vector<std::string> rock_texture_labels;
    static std::vector<std::string> gas_texture_labels;
   float temperatur;
   float radius;
   char klasse;
   int spezial;
   float phase;
   std::string texture_label;
   
   void erstelle_zufall();
};



#endif
