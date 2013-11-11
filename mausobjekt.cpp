#include "mausobjekt.hh"

Mausobjekt::Mausobjekt()
{
   objekt_id = objekt_id_zaehler;
   objekt_id_zaehler++;
}

int Mausobjekt::objekt_id_zaehler=1;

