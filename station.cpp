#include "station.hh"

#include "district.hh"

Station::Station(int district_count_)
{
   district_count = district_count_;
   
   district = new District[district_count];
   
}


Station::Station()
{
   district_count = rand()%12+1;
   
   district = new District[district_count];
   
}


Station::~Station()
{
   delete[] district;
}


void Station::set_aktiv(District* dis_)
{
   for (int i=0; i<district_count; i++)
   {
      if (&district[i] == dis_)
         district[i].aktiv = true;
      else
         district[i].aktiv = false;
   }
}


void Station::text_ausgabe()
{
   std::cout << "station:" << std::endl;
   std::cout << "\tdistricts: " << district_count << std::endl;
   
   for (int i=0; i< district_count; i++)
   {
      std::cout << "district: " << i+1 << " :" << std::endl;
      district[i].text_ausgabe();
      std::cout << std::endl;
   }
}