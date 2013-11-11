#ifndef STATION_HH
#define STATION_HH

#include <stdlib.h>
#include <iostream>

class District;


class Station
{
public:
   
   int district_count;
   
   District* district;
   
   void text_ausgabe();
   void set_aktiv(District* dis_);
   
   Station();
   Station(int district_count_);
   ~Station();
};


#endif