#ifndef OPENGLMENU_HH
#define OPENGLMENU_HH

#include <list>

#include "openglbutton.hh"

struct Button_and_coords
{
   Openglbutton button;
   float x;
   float y;
   float sx;
   float sy;
};

struct Togglebutton_and_coords
{
   Opengltogglebutton button;
   float x;
   float y;
   float sx;
   float sy;
};

class Openglmenu
{
public:
   
   std::list<Button_and_coords>       buttons;
   std::list<Togglebutton_and_coords> togglebuttons;
   
   int button_count;

   void add_button(Openglbutton*, float x_, float y_, float sx_, float sy_);
   void add_togglebutton(Opengltogglebutton*, float x_, float y_, float sx_, float sy_);
   Openglmenu();
};



#endif
