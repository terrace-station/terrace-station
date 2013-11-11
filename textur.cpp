#include <fstream>
#include <iostream>

#include "textur.hh"

Textur::Textur(std::string dateiname, int farbtiefe)
{
  lade_Textur(dateiname, farbtiefe);
}


void Textur::lade_Textur(std::string dateiname, int farbtiefe) 
{
  std::cout << "Lade Bitmap " << dateiname << std::endl;

  std::ifstream bilddatei;
  bilddatei.open(dateiname.c_str(), std::ios::in | std::ios::binary);  // 
  if (!bilddatei.is_open())
    std::cout << "Textur oeffnen fehlgeschlagen\n";
  
  bilddatei.seekg(18, std::ios::beg);
  
  groesse_x = vierbyte_lesen(bilddatei);
  groesse_y = vierbyte_lesen(bilddatei);
  int datenmenge = groesse_x*groesse_y*farbtiefe; // in byte
  
  bilddatei.seekg(28, std::ios::cur);
  
  daten = new char[datenmenge];
  bitmapdaten_lesen(bilddatei, daten, datenmenge);
  
  char tmp_;
  
  for (int i=0; i<datenmenge ; i+=farbtiefe)    // bgr nach rgb
  {
//     std::cout << daten[i] << "\t" << daten[i+1] << "\t" << daten[i+2] << std::endl;
    tmp_ = daten[i];
    daten[i] = daten[i+2];
    daten[i+2] = tmp_;
  }
  
  bilddatei.close();
}

unsigned int Textur::vierbyte_lesen(std::ifstream& bilddatei)
{
  int stelle[4];
  stelle[0] = bilddatei.get();
  stelle[1] = bilddatei.get();
  stelle[2] = bilddatei.get();
  stelle[3] = bilddatei.get();
  
  return (stelle[0] + stelle[1]*256 + stelle[2]*65536 + stelle[3]*16777216);
}

void Textur::bitmapdaten_lesen(std::ifstream& bilddatei, char* daten, int datenmenge)
{
  for (int i=0; i<datenmenge; i++)
  {
    daten[i] = bilddatei.get();
    
  }
}


