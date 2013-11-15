#ifndef OPENGLBUTTON_HH
#define OPENGLBUTTON_HH

#include <GL/gl.h>
#include <GL/glu.h>

#include "mausobjekt.hh"
class Openglwidget;
class Modell; // ACHTUNG; Noch zu implementieren

class Openglbutton: public Mausobjekt
{
public:
   
   bool bool_modell;
   bool bool_callback;
   
   Modell* modell;
   void (*callback_fkt)(Openglwidget&);
   
   void set_callback(void (*callback_fkt_)(Openglwidget&));
   void set_modell(Modell* modell_);
   void zeichne();

   Openglbutton();
};


class Opengltogglebutton: public Openglbutton
{
public:
   
   bool& bool_wert;
   
   void zeichne();
   void zeichne_true();
   void zeichne_false();
   void set_booltotoggle(bool& wert_);
   
   Opengltogglebutton(bool& wert_);
};


#endif
