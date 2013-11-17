#ifndef MODEL_HH // bedingtes Einbinden
#define MODEL_HH

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <GL/glu.h>
#include <GL/gl.h>

#include "textur.hh"
#include "hilfsfunktionen.h"


struct Knoten
{
  float x,y,z;
  float n_x,n_y,n_z;
};

struct TexKoord
{
  float tx,ty;
};

struct Dreieck
{
  int ecke[4];
  int texecke[4];
  
  bool viereck = false;
  
  float normal_x;
  float normal_y;
  float normal_z;
};

struct Material
{
  std::string name;
  
  float Kar, Kag, Kab;
  float Kdr, Kdg, Kdb;
  float Ksr, Ksg, Ksb;
  
  float Ns;
  float Ni;
  
  float alpha;
  int illum;
  
  bool textur;
  std::string textur_datei;
  GLuint textur_id;
  
/*  
Ns 96.078431 //shiness
Ka 0.000000 0.000000 0.000000 // ambient rgb
Kd 0.640000 0.640000 0.640000 // diffuse rgp
Ks 0.500000 0.500000 0.500000 // specular rgb
Ni 1.000000  // refraction
d 1.000000 // alpha
illum 2  
map_Kd /home/hb/opengl/rdz/modelle/test.bmp
*/
};

struct Element
{
  int anzahl_dreiecke;
  
  Material* material;
  
  Dreieck* dreiecke;
};

class Modell
{
  
public:
  int anzahl_knoten;
  int anzahl_texkoords;
  int anzahl_objekte;
  int anzahl_materialien;
  
  bool flat_shading;
  
  Element* objekte;
  Knoten* knoten;
  TexKoord* texkoords;
  Material* materialien;
  
  void lade_textur();
  void zeichne();
  
  Modell(bool flat_shading_);
};
 
Modell* lade_modell(std::string dateiname, bool flat_shading_);
void lese_material(std::string dateiname, Modell* modell);


#endif 
