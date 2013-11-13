#include "mausobjekt.hh"

int Mausobjekt::objekt_id_zaehler=1;

Mausobjekt::Mausobjekt()
{
   objekt_id = objekt_id_zaehler;
   objekt_id_zaehler++;
}


