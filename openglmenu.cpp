#include "openglmenu.hh"


Openglmenu::Openglmenu()
{
   button_count = 0;
}

void Openglmenu::add_button(Openglbutton* button, float x_, float y_, float sx_, float sy_)
{
   buttons.push_back({*button, x_, y_, sx_, sy_});
   ++button_count;
}

void Openglmenu::add_togglebutton(Opengltogglebutton* button, float x_, float y_, float sx_, float sy_)
{
   togglebuttons.push_back({*button, x_, y_, sx_, sy_});
   ++button_count;
}