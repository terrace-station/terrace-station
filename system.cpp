#include "system.hh"

void Planet::erstelle_zufall()
  {
    phase = float(rand()%360);
    
    switch(rand()%3)
    {
      case 0:
        klasse = 'A';
        spezial = rand()%4;
        radius = 8.0 + float(rand()%500)/500.0;
        textur_ind = rand()%4+6;
        break;
        
      case 1:
        klasse = 'J';
        spezial = rand()%3;
        radius = 1.0 + float(rand()%400)/400.0; 
        textur_ind = rand()%4;
        break;
        
      case 2:
        klasse = 'K';
        spezial = rand()%3+3;
        radius = 1.0 + float(rand()%400)/400.0; 
        textur_ind = rand()%6;
        break;
      
    }
  }






System::System()
{
   sonnenradius = 10.0 + float(rand()%30);
   
   position[0] = 0;
   position[1] = 0;
   position[2] = 0;
   
   anzahl_planeten = 1+rand()%10;
   
   planeten = new Planet[anzahl_planeten];
   
   for (int i = 0; i < anzahl_planeten; i++)
   {
      planeten[i].erstelle_zufall();
   }
}


System::System(float pos_x_, float pos_y_, float pos_z_)
{
   sonnenradius = 10.0 + float(rand()%30);
   
   position[0] = pos_x_;
   position[1] = pos_y_;
   position[2] = pos_z_;
   
   anzahl_planeten = 1+rand()%10;
   
   planeten = new Planet[anzahl_planeten];
   
   for (int i = 0; i < anzahl_planeten; i++)
   {
      planeten[i].erstelle_zufall();
   }
}


System::System(int anzahl_, float pos_x_, float pos_y_, float pos_z_) : anzahl_planeten(anzahl_)
{
   sonnenradius = 10.0 + float(rand()%30);
   
   position[0] = pos_x_;
   position[1] = pos_y_;
   position[2] = pos_z_;
   
   planeten = new Planet[anzahl_planeten];
   
   for (int i = 0; i < anzahl_planeten; i++)
   {
      planeten[i].erstelle_zufall();
   }
}


