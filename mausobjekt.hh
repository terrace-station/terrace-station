#ifndef MAUSOBJEKT_HH
#define MAUSOBJEKT_HH

// enum mausobjekt_typ {mo_gebiet=0, mo_sonstiges};

#include <string>

class Mausobjekt
{
private:
   static int objekt_id_zaehler;
public:
   int objekt_id;
   std::string objekt_typ;
//    mausobjekt_typ mo_typ;
   
   Mausobjekt();
};

#endif
