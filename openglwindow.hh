#ifndef Openglwindow_HH
#define Openglwindow_HH

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Gl_Window.H>
#include <FL/fl_ask.H>
#include <FL/Fl_Box.H>
// #include <FL/Fl_JPEG_Image.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_Shared_Image.H>
// #include <FL/Fl_Value_Slider.H>
// #include <FL/Fl_Widget.H>


#include <string>
#include <math.h>
#include <list>

// #include "baumenu.hh"
#include "targetinfomenu.hh"

class Openglwidget;

class Openglwindow : public Fl_Window
{

private:

   void resize(int position_x_, int position_y_, int breite_, int hoehe_);
    
public:

   Openglwidget* glwidget;
//     Baumenu* baumenu;
   Targetinfomenu* infomenu; 
    
//     Fl_PNG_Image* rahmen_bg;
//     Fl_Image* rahmen_bg_scaled;
//     Gebiet* gebiet;
//     Fl_Box* rahmen;
    
   void* karte;
    
   void redraw();

   Openglwindow(int breite_, int hoehe_, const char* titel=0);
   ~Openglwindow();
};


#endif

