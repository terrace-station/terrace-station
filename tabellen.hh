#ifndef TABELLEN_HH
#define TABELLEN_HH


static double get_leistung(GEBAEUDE gebaeude, MATERIAL material, int level)
{
   int geb = int(gebaeude)*10000;
   int mat = int(material)*100;
   int lvl = level;
   
   double leistung = 0.0;
   
   switch(gebaeude)
   {
      case GEB_WOHNHAUS: leistung=1.0; break;
      default: leistung = 1.0;
   }
   
   switch(material)
   {
      case MAT_STROH: leistung *= 1; break;
      default: leistung *= 1.0;
   }
   
   switch (lvl)
   {
      case 1: leistung *= 1; break;
      case 2: leistung *= 2; break;
      default: leistung *= 1.0;
   }
   
   return leistung;
}

#endif