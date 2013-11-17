#include "system.hh"

std::vector<std::string> Planet::rock_texture_labels = {"planet-rock1",
                                                        "planet-rock2",
                                                        "planet-rock3",
                                                        "planet-rock4",
                                                        "planet-rock5",
                                                        "planet-rock6"};

std::vector<std::string> Planet::gas_texture_labels = {"planet-gas1",
                                                       "planet-gas2",
                                                       "planet-gas3",
                                                       "planet-gas4"};

void Planet::erstelle_zufall()
  {
    phase = float(rand()%360);
    
    switch(rand()%3)
    {
      case 0:
        klasse = 'A';
        spezial = rand()%4;
        radius = 80.0 + float(rand()%5000)/500.0;
        texture_label = gas_texture_labels[rand() % 4];
        break;
        
      case 1:
        klasse = 'J';
        spezial = rand()%3;
        radius = 10.0 + float(rand()%4000)/400.0; 
        texture_label = rock_texture_labels[rand() % 4];
        break;
        
      case 2:
        klasse = 'K';
        spezial = rand()%3+3;
        radius = 10.0 + float(rand()%4000)/400.0; 
        texture_label = rock_texture_labels[rand() % 6];
        break;
      
    }
  }






System::System()
{
   sonnenradius = 150;
   
   position[0] = 10000;
   position[1] = 0;
   position[2] = 0;
   
   abstand_max = sqrt(pow(position[0],2) + pow(position[1],2) + pow(position[2],2)) + sonnenradius;
   abstand_umlaufbahn = 1000;
   
   anzahl_planeten = 3+rand()%6;
   
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
   
   abstand_max = sqrt(pow(position[0],2) + pow(position[1],2) + pow(position[2],2)) + sonnenradius;
   abstand_umlaufbahn = 1000;
   
   anzahl_planeten = 3+rand()%6;
   
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
   
   abstand_max = sqrt(pow(position[0],2) + pow(position[1],2) + pow(position[2],2)) + sonnenradius;
   abstand_umlaufbahn = 1000;
   
   planeten = new Planet[anzahl_planeten];
   
   for (int i = 0; i < anzahl_planeten; i++)
   {
      planeten[i].erstelle_zufall();
   }
}


