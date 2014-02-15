#ifndef Openglwidget_HH
#define Openglwidget_HH

#include <sstream>
#include <iostream>

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "glcam.hh"
#include "glhilf.h"
#include "mausobjekt.hh"
#include "textures.hh"
#include "fonttextures.hh"
#include "audio.hh"
#include "modell.hh"
#include "models.hh"
#include "system.hh"
#include "zeit.h"
#include "enumerationen.h"
#include "openglbutton.hh"
#include "callback_funktionen.hh"
#include "openglmenu.hh"
#include "lights.hh"
#include "lamp.hh"


class Station;
class Zone;
class District;
class Deck;

void idle_redraw(void* arg);

class Openglwidget
{
private:
   
   SDL_Event event;
   
   float flare_theta;
   float flare_phi;
   
   GLuint sel_buffer[128];
   
public:
   
//    Lamp lamp; // TEST
   
   Openglmenu* menu;
   
   bool gamemenu;
   bool fullscreen;
   bool idle_redraw;
   bool antialiasing;
   
   bool picking;
   
   int fullscreen_x, fullscreen_y;
   int window_x, window_y;
   int bpp;
   int fenster_modus;
   
   const SDL_VideoInfo* info;
   bool running;

   float view_angle;
   
   GLint viewport[4];
   GLdouble model_matrix[16];
   GLdouble project_matrix[16];

   GLint viewport_system[4];
   GLdouble model_matrix_system[16];
   GLdouble project_matrix_system[16];

   GLint viewport_menu[4];
   GLdouble model_matrix_menu[16];
   GLdouble project_matrix_menu[16];

   GLdouble fenster_x, fenster_y, fenster_z;
   GLint aktuelle_id;
   void draw();
   void initialisiere_gl();
   void parameter_regelung();
//    int handle(int);
   
   void events();
   void handle_keydown(SDL_keysym& keysym);
   void handle_keydown_menu(SDL_keysym& keysym);
   void handle_mousebuttondown(SDL_MouseButtonEvent& button);
   void handle_mousebuttondown_menu(SDL_MouseButtonEvent& button);

   void zeichne_szene();
   void selektiere_id();
   void selektiere_pos();
   
   void bindTextures(std::string label);
   void unbindTextures();

   void resize(int position_x_, int position_y_, int breite_, int hoehe_);

   
// // // // // // sonstiges

   System sys;
   Mausobjekt nichts;
   
// // // // // // 
   
   Station* station;
   
   
   timeval zeit;
   float zeit_ende, zeit_frame, zeit_anfang;
   
   int fps_counter;
   float fps_sum;
   
   static float fps_average;
   static float laufzeit;
   static float light_inc[3];
   
   static Textures* textures;
   static Textures* normalmaps;
   static Models* models;
   static Fonttextures* fonttextures;
   Audio* audio;
   Lights* lights;
   
   int fenster_breite;
   int fenster_hoehe;
    
   GLint target_id;
   double target_x;
   double target_y;
   double target_z;

   float breite_zu_hoehe;
   
   Glcam* active_cam;
   Glcam std_cam;
   
   float kamera_x, kamera_y, kamera_z;
   float pos_x, pos_y, pos_z;
   float oben_x, oben_y, oben_z;
   
   int fenster1;
   
   GLfloat mat_ambi[4];
   GLfloat mat_diff[4];
   GLfloat mat_spec[4];
   GLfloat mat_shin;
   
   void set_fullscreen(bool wert);
   void toggle_fullscreen();
   void toggle_antialiasing();
   
   void set_material_ambi(float ambi1, float ambi2, float ambi3, float ambi4);
   void set_material_diff(float diff1, float diff2, float diff3, float diff4);
   void set_material_spec(float spec1, float spec2, float spec3, float spec4);
   void set_material_shin(float shin1);
   void set_material_std();
   void set_material(MATERIAL material);
   
   Mausobjekt& get_target();
   void interact_with(Mausobjekt& mo_, SDL_MouseButtonEvent& button);

   void set_station(Station* station_);
   void zeichne_system(System& system_);
   void zeichne_gamemenu();
   
   void zeichne_station();
   void zeichne_zone(Zone& zone);
   void zeichne_district(District& district);
   void zeichne_district_outside(District& district);
   void zeichne_deck(Deck& deck);

   Openglwidget(int breite_, int hoehe_);
};


#endif


