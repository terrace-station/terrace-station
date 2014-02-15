#ifndef OPENGLMENU_HH
#define OPENGLMENU_HH

#include <list>
#include <string>

#include "openglbutton.hh"
#include "callback_funktionen.hh"

class Openglwidget;

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

struct Label_and_coords
{
   std::string label;
   float x;
   float y;
   float s;
};

class Openglmenu
{
public:
    
    GLfloat bg_color_r;
    GLfloat bg_color_g;
    GLfloat bg_color_b;
    
    Openglwidget* glwidget;
    
    float menu_bg;
    float menu_bg_soll;
    
    std::list<Button_and_coords>       buttons;
    std::list<Togglebutton_and_coords> togglebuttons;
    std::list<Label_and_coords>        labels;
    
    int button_count;

    void add_button(Openglbutton*, float x_, float y_, float sx_, float sy_);
    void add_togglebutton(Opengltogglebutton*, float x_, float y_, float sx_, float sy_);
    void add_label(std::string label, float x_, float y_, float s_);
    Openglmenu(Openglwidget* glwidget);
};



#endif
