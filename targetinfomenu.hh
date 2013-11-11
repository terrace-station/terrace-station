#ifndef TARGETINFOMENU_HH
#define TARGETINFOMENU_HH

#include <FL/Fl.H>
#include <FL/Fl_Pack.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Spinner.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Button.H>

#include <typeinfo>
#include <sstream>

#include "mausobjekt.hh"

class Openglwidget;

class Targetinfomenu : public Fl_Pack
{

private:
public:

   Openglwidget* glwidget;
   std::string gebietsname;
//    std::string gebaeudefunktion;
//    std::string groesse;
   
//    std::string* stockwerke;
//    Fl_Choice* baumaterial;

//    Fl_Button* abbrechen_stockwerk; 
//    Fl_Button* neues_stockwerk; 
   
   void redraw();
   
   void set_info(Mausobjekt* target);

   Targetinfomenu(Openglwidget* glwidget_, int pos_x_, int pos_y_, int breite_, int hoehe_);
   ~Targetinfomenu();
};


#endif

