#include <iostream>
#include <math.h>
#include <stdlib.h>

#include "openglwindow.hh"
#include "openglwidget.hh"


int main()
{
   srand (time(NULL));
   
   Openglwindow fenster1(800, 600, "Test");
   fenster1.show();
   
   Station station1;
   station1.text_ausgabe();
   fenster1.glwidget->set_station(&station1);
   
   Fl::run();
   return 0;
}