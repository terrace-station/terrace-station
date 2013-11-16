#include "openglbutton.hh"

#include "openglwidget.hh"

Openglbutton::Openglbutton()
{
   bool_modell = false;
   bool_callback = false;
   objekt_typ = "Openglbutton";
}


void Openglbutton::set_callback(void (*callback_fkt_)(Openglwidget&))
{
   callback_fkt = callback_fkt_;
   bool_callback = true;
}


void Openglbutton::set_modell(Modell* modell_)
{
   modell = modell_;
   bool_modell = true;
}

// // // // // // // // // // // // // // // // // // Opengltogglebutton

Opengltogglebutton::Opengltogglebutton(bool* bool_wert_): bool_wert(bool_wert_)
{
   objekt_typ = "Opengltogglebutton";
}


void Opengltogglebutton::zeichne()
{
   glLoadName(objekt_id);
   if (*bool_wert)
      zeichne_true();
   else
      zeichne_false();
}


void Opengltogglebutton::set_booltotoggle(bool* bool_wert_)
{
   bool_wert = bool_wert_;
}


void Opengltogglebutton::set_modell(Modell* modell_, Modell* modell_false_)
{
   modell       = modell_;
   modell_false = modell_false_;
   bool_modell = true;
}


void Opengltogglebutton::zeichne_true()
{
   if (bool_modell)
      modell->zeichne();
   else
   {
      glColor3f(0.0, 1.0, 0.0);
      glBegin(GL_QUADS);
         glVertex3f(-0.5,-0.5, 0.0);
         glVertex3f( 0.5,-0.5, 0.0);
         glVertex3f( 0.5, 0.5, 0.0);
         glVertex3f(-0.5, 0.5, 0.0);
      glEnd();
   }
}


void Opengltogglebutton::zeichne_false()
{
   if (bool_modell)
      modell_false->zeichne();
   else
   {
      glColor3f(1.0, 0.0, 0.0);
      glBegin(GL_QUADS);
         glVertex3f(-0.5,-0.5, 0.0);
         glVertex3f( 0.5,-0.5, 0.0);
         glVertex3f( 0.5, 0.5, 0.0);
         glVertex3f(-0.5, 0.5, 0.0);
      glEnd();
   }
}

