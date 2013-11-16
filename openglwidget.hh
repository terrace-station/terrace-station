#ifndef Openglwidget_HH
#define Openglwidget_HH

#include <sstream>
#include <iostream>

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "glhilf.h"
#include "textur.hh"
#include "mausobjekt.hh"
#include "texturensammlung.hh"
#include "textures.hh"
#include "modell.hh"
#include "system.hh"
#include "zeit.h"
#include "enumerationen.h"
#include "openglbutton.hh"
#include "openglmenu.hh"

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
   
public:
   
   Openglmenu menu;
   
   bool gamemenu;
   bool fullscreen;
   bool idle_redraw;
   bool antialiasing;
   
   float menu_bg;
   float menu_bg_soll;
   
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

   void resize(int position_x_, int position_y_, int breite_, int hoehe_);

   
// // // // // // sonstiges

   System sys;
   Mausobjekt nichts;
   
// // // // // // 
   
   Station* station;
   
   
   timeval zeit;
   float zeit_ende, zeit_frame, zeit_anfang;
   
   Texturensammlung* tex;
   Textures* tex2;
   
   int fenster_breite;
   int fenster_hoehe;
    
   GLint target_id;
   double target_x;
   double target_y;
   double target_z;

   float breite_zu_hoehe;
   float pos_x, pos_y, pos_z;
   float pos_radius, pos_phi;
   
   float pos_z_soll;
   float pos_radius_soll;
   
   float kamera_x, kamera_y, kamera_z;
   float kamera_radius, kamera_phi;
   
   float oben_x, oben_y, oben_z;
   
   float theta, phi;
   float theta_soll, phi_soll;
   
   float zoom;
   float zoom_soll;

   float x_offset, y_offset, z_offset;
   
   int fenster1;

   GLfloat sonne_pos [4];
   GLfloat sonne_ambi [4];
   GLfloat sonne_diff [4];
   GLfloat sonne_spec [4];
   
   GLfloat licht_pos [4];
   GLfloat licht_ambi[4];
   GLfloat licht_diff[4];
   GLfloat licht_spec[4];
   
   GLfloat spot_pos [4];
   GLfloat spot_dir [3];
   GLfloat spot_ambi[4];
   GLfloat spot_diff[4];
   GLfloat spot_spec[4];
   
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
   
   int fps_counter;
   float fps_average;
   float fps_sum;

   Mausobjekt& get_target();
   void set_view_to(Mausobjekt& mo_);

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


