#include "openglwidget.hh"

   float Openglwidget::laufzeit = 0.0;
   float Openglwidget::fps_average = 0.0;
   float Openglwidget::light_inc[3] = {0.5, 0.5, 1.0};
   
   Textures* Openglwidget::textures = NULL;
   Textures* Openglwidget::normalmaps = NULL;
   Models* Openglwidget::models = NULL;
   Fonttextures* Openglwidget::fonttextures = NULL;
   
#include "openglmenu.hh"
#include "station.hh"
#include "zone.hh"
#include "district.hh"
#include "deck.hh"
#include "door.hh"
#include "room.hh"
#include "rect.hh"
#include "tile.hh"
#include "log.hh"

#include "openglwidget_material.h"
#include "openglwidget_events.h"
#include "openglwidget_zeichne.h"

#define TEXTURES_DIR    "textures"
#define NORMALMAPS_DIR  "textures/normalmaps"
#define MODELS_DIR      "models"

Openglwidget::Openglwidget(int breite_, int hoehe_)
{
    //~ audio_init();
    textures = new Textures(TEXTURES_DIR);
    normalmaps = new Textures(NORMALMAPS_DIR);
    fonttextures = new Fonttextures;
    audio = new Audio;
    audio->set_music_playlist("default");
    
    gettimeofday(&zeit, 0);
    models   = new Models(MODELS_DIR);
    lights   = new Lights(laufzeit);
    
    running = true;
    antialiasing = true;
    fullscreen = false;
    gamemenu = false;
    
    picking = false;
    
    info = SDL_GetVideoInfo();
    
    fenster_modus = SDL_OPENGL;
    
    bpp = info->vfmt->BitsPerPixel;
    fullscreen_x = info->current_w;
    fullscreen_y = info->current_h;
    
    window_x = breite_;
    window_y = hoehe_;

    fenster_breite = window_x;
    fenster_hoehe =  window_y;
    
    view_angle = 45;
    
    fps_counter = 0;
    fps_sum = 0.0;

    kamera_x = 0;
    kamera_y = 0;
    kamera_z = 0;
    
    oben_x = 0;
    oben_y = 0;
    oben_z = 0;
    
    pos_x = 0;
    pos_y = 0;
    pos_z = 0;
    
    target_id = 0;
    target_x = 0;
    target_y = 0;
    target_z = 0;
    
    menu = new Openglmenu(this);
   
    station = NULL;
    active_cam = &std_cam;
    std_cam.set_start(5, 250, 0, 600, -30, 90);
    std_cam.set_boundaries(10, 10,
                           -1000, 1000,
                           -1000, 1000,
                           10, 1000,
                           -90, 90, 
                           90, 90);
    std_cam.set_upside(3);
   
    initialisiere_gl();
}


void Openglwidget::set_station(Station* station_)
{
   station = station_;
}


void regelung(float& ist_wert, float& soll_wert, float& zeit_faktor, float geschwindigkeit, float toleranz)
{
    if (fabs(soll_wert-ist_wert) > toleranz)
    {
        ist_wert += 0.9*(soll_wert - ist_wert)*zeit_faktor*geschwindigkeit;
    }
    else if (soll_wert != ist_wert)
        ist_wert = soll_wert;
}


void Openglwidget::parameter_regelung()
{
//    if (phi != phi_soll || pos_z != pos_z_soll || theta != theta_soll || zoom != zoom_soll || pos_radius != pos_radius_soll || menu_bg != menu_bg_soll)
    {
        float zeit_faktor;
        if (zeit_frame > 0.1)
            zeit_faktor = 0.1;
        else
            zeit_faktor = zeit_frame;
        
        regelung(kamera_x, active_cam->kamera_x, zeit_faktor, 4, 0.005);
        regelung(kamera_y, active_cam->kamera_y, zeit_faktor, 4, 0.005);
        regelung(kamera_z, active_cam->kamera_z, zeit_faktor, 4, 0.005);
        regelung(pos_x, active_cam->pos_x, zeit_faktor, 4, 0.005);
        regelung(pos_y, active_cam->pos_y, zeit_faktor, 4, 0.005);
        regelung(pos_z, active_cam->pos_z, zeit_faktor, 4, 0.005);
        regelung(oben_x, active_cam->oben_x, zeit_faktor, 2, 0.005);
        regelung(oben_y, active_cam->oben_y, zeit_faktor, 2, 0.005);
        regelung(oben_z, active_cam->oben_z, zeit_faktor, 2, 0.005);
        regelung(menu->menu_bg, menu->menu_bg_soll, zeit_faktor, 5, 0.001);
    }
}


void Openglwidget::interact_with(Mausobjekt& mo_, SDL_MouseButtonEvent& button)
{
    if (mo_.objekt_typ == "District" && button.button == SDL_BUTTON_LEFT) {
        District& dis = (District&) mo_;
        if ( &dis != station->get_active_district() ) {
            station->set_active_district(&dis);
            active_cam = &(dis.camera);
        }
    } 
    else if (mo_.objekt_typ == "Room" && button.button == SDL_BUTTON_RIGHT) {
        Room& room = (Room&) mo_;
        room.set_light_on(!room.is_light_on());
    } 
//     else if (mo_.objekt_typ == "Room" && button.button == SDL_BUTTON_MIDDLE) {
//         Room& room = (Room&) mo_;
//         std::list<Room*> neighbours = room.get_neighbours();
//         for (std::list<Room*>::iterator room_it = neighbours.begin(); room_it != neighbours.end(); room_it++)
//         {
//             (*room_it)->set_visible(true);
//         }
//     } 
    else if (mo_.objekt_typ == "Door" && button.button == SDL_BUTTON_LEFT) {
        Door& door = (Door&) mo_;
        if(door.get_state() == "closed")
        {
            LOG(DEBUG) << "Tür geöffnet";
            door.room1->set_visible(true);
            door.room2->set_visible(true);
            door.set_state("open");
        }
        else if (door.get_state() == "open")
        {
            LOG(DEBUG) << "Tür geschlossen";
            door.set_state("closed");
        }
    } 
    else if (mo_.objekt_typ == "Openglbutton" && button.button == SDL_BUTTON_LEFT) {
        LOG(DEBUG) << "Openglbutton gedrückt";
        Openglbutton& but = (Openglbutton&) mo_;
        but.callback_fkt(*this);
    } 
    else if (mo_.objekt_typ == "Opengltogglebutton" && button.button == SDL_BUTTON_LEFT) {
        LOG(DEBUG) << "Opengltogglebutton gedrückt";
        Opengltogglebutton& but = (Opengltogglebutton&) mo_;
        but.callback_fkt(*this);
    }
}


Mausobjekt& Openglwidget::get_target()
{
   if (target_id == 0)
      return nichts;
   
    for (std::vector<Zone>::iterator zone_it = station->get_zones().begin(); zone_it != station->get_zones().end(); zone_it++)
    {
        for (std::vector<District>::iterator district_it = zone_it->get_districts().begin(); district_it != zone_it->get_districts().end(); district_it++)
        {
            if (district_it->objekt_id == target_id) { return (Mausobjekt&) (*district_it); }
            for (std::vector<Deck>::iterator deck_it = district_it->get_decks().begin(); deck_it != district_it->get_decks().end(); deck_it++)
            {
                //~ if (deck_it->objekt_id == target_id) { return (Mausobjekt&) (*deck_it); }
                for (std::list<Room>::iterator room_it = deck_it->get_rooms().begin(); room_it != deck_it->get_rooms().end(); room_it++)
                {
                    if (room_it->objekt_id == target_id) { return (Mausobjekt&) (*room_it); }
                }
                for (std::list<Door>::iterator door_it = deck_it->get_doors().begin(); door_it != deck_it->get_doors().end(); door_it++)
                {
                    if (door_it->objekt_id == target_id) { return (Mausobjekt&) (*door_it); }
                }
            }
        }
    }

    for (std::list<Togglebutton_and_coords>::iterator it = menu->togglebuttons.begin(); it != menu->togglebuttons.end(); it++)
    {
        if (it->button.objekt_id == target_id) { return (Mausobjekt&) it->button; }
    }

    for (std::list<Button_and_coords>::iterator it = menu->buttons.begin(); it != menu->buttons.end(); it++)
    {
        if (it->button.objekt_id == target_id) { return (Mausobjekt&) it->button; }
    }
    //    if(target_id == button_fullscreen->objekt_id) // Hier soll dann über eine Liste aus buttons iteriert werden
    //       return (Mausobjekt&) *button_fullscreen;

    //    if(target_id == button_close->objekt_id)
    //       return (Mausobjekt&) *button_close;

    return nichts;
}


void Openglwidget::get_id()
{
   float maus_x = event.button.x;
   float maus_y = fenster_hoehe-event.button.y;
   
   glSelectBuffer (128, sel_buffer);
   GLint hits = 0;

   glViewport(0, 0, fenster_breite, fenster_hoehe);

   glMatrixMode(GL_PROJECTION);
   glRenderMode(GL_SELECT);
   glLoadIdentity();
   gluPickMatrix(maus_x, maus_y, 2, 2, viewport); // nur an der Mausposition gucken
   gluPerspective(view_angle,breite_zu_hoehe,NEAR_CLIP,FAR_CLIP);
// // // // // // // // // render
   glMatrixMode(GL_MODELVIEW);
   picking = true;
   zeichne_szene();
   picking = false;
// // // // // // // // //
   hits = glRenderMode(GL_RENDER);
   
   LOG(DEBUG) << "x: " << event.button.x << ", y:" << event.button.y << " - " <<  hits << " Objekte getroffen";

   if (hits) // wenn was angeklickt wurde, soll das "vorderste" gewählt werden
   {
   //  Organisation des Buffers:
   //     Anzahl der Namen auf dem Stack
   //     Kleinster Abstand
   //     Größter Abstand
   //     Objektname
      if (sel_buffer[0] != 1)
         LOG(WARNING) << "Achtung, mehr als eine Objekt_id geladen.";
      LOG(DEBUG) << "1: ID:" << sel_buffer[3] << ", Abstand:" << sel_buffer[1];

      target_id = sel_buffer[3];
      int abstand = sel_buffer[1];
      
      for (int i = 1; i <hits; i++)
      {
         if (sel_buffer[i*4] != 1)
            LOG(WARNING) << "Achtung, mehr als eine Objekt_id geladen.";
         
         LOG(DEBUG) << i+1 << ": ID:" << sel_buffer[i*4+3] << ", Abstand:" << sel_buffer[i*4+1];
         
         if (sel_buffer[(i*4)+1] < abstand)
         {
            target_id = sel_buffer[(i*4)+3];
            abstand   = sel_buffer[(i*4)+1];
         }
      }
   }
   else
      target_id = 0; // nichts gefunden :(

}


void Openglwidget::get_pos()
{
    if (target_id)
    {
        float maus_x = event.button.x;
        float maus_y = fenster_hoehe-event.button.y;
        float abstand;
        
        glReadPixels(maus_x, maus_y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &abstand);
        gluUnProject(maus_x, maus_y, abstand, model_matrix, project_matrix, viewport, &target_x, &target_y, &target_z);
    }
    else
    {
        target_x = -1;
        target_y = -1;
        target_z = -1;
    }
}


void Openglwidget::get_coordinates(float& deck_x, float& deck_y)
{
    get_pos();
    hilf::station2deck(target_x, target_y, target_z, deck_x, deck_y);
    if (station->get_active_district() != NULL) {
        deck_x -= (station->get_active_district()->get_radius()-0.5)*(station->get_active_district()->get_angle())*RAD;
    }
}


void Openglwidget::initialisiere_gl()
{

//     glLineWidth(2);
//     glPolygonOffset(1.0,1.0);
//     glEnable(GL_POLYGON_OFFSET_FILL);
    glClearColor(0.0, 0.0, 0.0, 1.0);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glFrontFace(GL_CW);

    glShadeModel(GL_SMOOTH); // glShadeModel(GL_SMOOTH) oder  glShadeModel(GL_FLAT)

    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //     glBlendFunc(GL_SRC_ALPHA,GL_ONE);
    //     glBlendFunc(GL_ONE, GL_ONE);

    set_material_std();
    lights->init_lights();
    lights->set_sonne_pos(sys.position[0], 0.0, 0.0, 1.0);

    breite_zu_hoehe = float(fenster_breite) / float(fenster_hoehe);
}


void Openglwidget::zeichne_system(System& system_)
{
   for(int i=0; i<system_.anzahl_planeten; i++)
   {
      switch(system_.planeten[i].klasse)
      {
         glColor3f(0.5, 0.5, 0.5);
         case 'A':
         glPushMatrix();
            glRotatef(system_.planeten[i].phase, 0.0, 0.0, 1.0);
            glTranslatef((i+1)*10+system_.abstand_umlaufbahn, 0, 0);
            
   //           glColor3f(0.6, 0.4, 0.4);
            glColor3f(1.0, 1.0, 1.0);
            glRotatef(5, 1.0, 1.0, 0.0);
            glBindTexture(GL_TEXTURE_2D, textures->get_id(system_.planeten[i].texture_label));
            
            for (int j=0; j<system_.planeten[i].spezial; j++)
            {
               glhilf::zeichne_ring(system_.planeten[i].radius*(1.2+j*j*0.2), system_.planeten[i].radius*(0.4*j+0.15), 80);
            }
            
            glColor3f(0.8, 0.8, 0.8);
            glhilf::draw_texture_sphere(system_.planeten[i].radius, 20, 40);
            glBindTexture(GL_TEXTURE_2D, 0);
         glPopMatrix();
         break;
         
         case 'K':
         glPushMatrix();
            glRotatef(system_.planeten[i].phase, 0.0, 0.0, 1.0);
            glTranslatef((i+1)*10+system_.abstand_umlaufbahn, 0, 0);
            glBindTexture(GL_TEXTURE_2D, textures->get_id(system_.planeten[i].texture_label));
            glhilf::draw_texture_sphere(system_.planeten[i].radius, 20, 40);
            glBindTexture(GL_TEXTURE_2D, 0);
         glPopMatrix();
         break;
         
         case 'M':
         glPushMatrix();
            glRotatef(system_.planeten[i].phase, 0.0, 0.0, 1.0);
            glTranslatef((i+1)*10+system_.abstand_umlaufbahn, 0, 0);
            glBindTexture(GL_TEXTURE_2D, textures->get_id(system_.planeten[i].texture_label));
            glColor3f(1.0, 1.0, 1.0);
            glhilf::draw_texture_sphere(system_.planeten[i].radius, 20, 40);
            glBindTexture(GL_TEXTURE_2D, 0);
         glPopMatrix();
         break;
      }
  }
  
   glDisable(GL_LIGHTING);
   glBindTexture(GL_TEXTURE_2D, textures->get_id("space-stars"));
   glColor3f(1.0, 1.0, 1.0);
   glhilf::draw_star_map(system_.abstand_max, 1, 2);
   glBindTexture(GL_TEXTURE_2D, 0);
// // // // // // // // // // // // // Sonne
   glTranslatef(system_.position[0], 0.0, 0.0);
   glColor3f(1.0, 1.0, 0.7);
   glhilf::draw_texture_sphere(system_.sonnenradius, 100, 100);
   
   glBlendFunc(GL_SRC_ALPHA,GL_ONE);
      glBindTexture(GL_TEXTURE_2D, textures->get_id("space-sun"));
      glColor4f(1.0, 1.0, 0.7, 0.4);
      glBegin(GL_QUADS);
         glTexCoord2f(0,0); glVertex3f(0.0,-system_.sonnenradius*3,-system_.sonnenradius*3);
         glTexCoord2f(0,1); glVertex3f(0.0,-system_.sonnenradius*3, system_.sonnenradius*3);
         glTexCoord2f(1,1); glVertex3f(0.0, system_.sonnenradius*3, system_.sonnenradius*3);
         glTexCoord2f(1,0); glVertex3f(0.0, system_.sonnenradius*3,-system_.sonnenradius*3);
      glEnd();
      glTranslatef(-system_.position[0], 0.0, 0.0);
      
   glGetIntegerv(GL_VIEWPORT, viewport_system);
   glGetDoublev(GL_MODELVIEW_MATRIX, model_matrix_system);
   glGetDoublev(GL_PROJECTION_MATRIX, project_matrix_system);
   
   gluProject(system_.position[0]-system_.sonnenradius*2, 0, 0, model_matrix_system, project_matrix_system, viewport_system, &fenster_x, &fenster_y, &fenster_z);
      
   
   if(flare_theta < 0.5*PI && fenster_x >= 0 && fenster_x <= fenster_breite && fenster_y >= 0 && fenster_y <= fenster_hoehe) // Flare zeichnen
   {
      GLfloat z_tmp;
      glReadPixels(fenster_x, fenster_y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z_tmp);
//       std::cout << fenster_x << " , " << fenster_y << " , " << fenster_z << " , " << z_tmp << " , " << std::endl;
      
      if (fabs(z_tmp-fenster_z) < 1e-3)
      {
         glColor4f(1.0, 1.0, 0.7, 0.4);
         glDisable(GL_DEPTH_TEST);
         glRotatef(flare_phi/RAD, 1, 0, 0);
      
         glRotatef(flare_theta*10, 0, 0, 1);
         glTranslatef(system_.position[0], 0.0, 0.0);
         glBindTexture(GL_TEXTURE_2D, textures->get_id("space-flare1"));
         glBegin(GL_QUADS);
            glTexCoord2f(0,0); glVertex3f(0.0,-0.25*system_.position[0],-0.25*system_.position[0]);
            glTexCoord2f(0,1); glVertex3f(0.0,-0.25*system_.position[0], 0.25*system_.position[0]);
            glTexCoord2f(1,1); glVertex3f(0.0, 0.25*system_.position[0], 0.25*system_.position[0]);
            glTexCoord2f(1,0); glVertex3f(0.0, 0.25*system_.position[0],-0.25*system_.position[0]);
         glEnd();
         glTranslatef(-system_.position[0], 0.0, 0.0);
         glRotatef(-flare_theta*20, 0, 0, 1);
         
         glRotatef(flare_theta*30, 0, 0, 1);
         glTranslatef(system_.position[0], 0.0, 0.0);
         glBindTexture(GL_TEXTURE_2D, textures->get_id("space-flare2"));
         glBegin(GL_QUADS);
            glTexCoord2f(0,0); glVertex3f(0.0,-0.25*system_.position[0],-0.25*system_.position[0]);
            glTexCoord2f(0,1); glVertex3f(0.0,-0.25*system_.position[0], 0.25*system_.position[0]);
            glTexCoord2f(1,1); glVertex3f(0.0, 0.25*system_.position[0], 0.25*system_.position[0]);
            glTexCoord2f(1,0); glVertex3f(0.0, 0.25*system_.position[0],-0.25*system_.position[0]);
         glEnd();
         glTranslatef(-system_.position[0], 0.0, 0.0);
         glRotatef(-flare_theta*20, 0, 0, 1);
         
         glRotatef(flare_theta*40, 0, 0, 1);
         glTranslatef(system_.position[0], 0.0, 0.0);
         glBindTexture(GL_TEXTURE_2D, textures->get_id("space-flare3"));
         glBegin(GL_QUADS);
            glTexCoord2f(0,0); glVertex3f(0.0,-0.5*system_.position[0],-0.25*system_.position[0]);
            glTexCoord2f(0,1); glVertex3f(0.0,-0.5*system_.position[0], 0.25*system_.position[0]);
            glTexCoord2f(1,1); glVertex3f(0.0, 0.5*system_.position[0], 0.25*system_.position[0]);
            glTexCoord2f(1,0); glVertex3f(0.0, 0.5*system_.position[0],-0.25*system_.position[0]);
         glEnd();
         glTranslatef(-system_.position[0], 0.0, 0.0);
         glRotatef(-flare_theta*20, 0, 0, 1);
         
         glRotatef(flare_theta*50, 0, 0, 1);
         glTranslatef(system_.position[0], 0.0, 0.0);
         glBindTexture(GL_TEXTURE_2D, textures->get_id("space-flare4"));
         glBegin(GL_QUADS);
            glTexCoord2f(0,0); glVertex3f(0.0,-0.25*system_.position[0],-0.25*system_.position[0]);
            glTexCoord2f(0,1); glVertex3f(0.0,-0.25*system_.position[0], 0.25*system_.position[0]);
            glTexCoord2f(1,1); glVertex3f(0.0, 0.25*system_.position[0], 0.25*system_.position[0]);
            glTexCoord2f(1,0); glVertex3f(0.0, 0.25*system_.position[0],-0.25*system_.position[0]);
         glEnd();
         glTranslatef(-system_.position[0], 0.0, 0.0);
         glRotatef(-flare_theta*20, 0, 0, 1);
         glRotatef(-active_cam->phi*2, 0, 0, 1);
         
         glRotatef(flare_theta*50, 0, 0, 1);
         glTranslatef(system_.position[0], 0.0, 0.0);
         glBindTexture(GL_TEXTURE_2D, textures->get_id("space-flare5"));
         glBegin(GL_QUADS);
            glTexCoord2f(0,0); glVertex3f(0.0,-system_.position[0],-system_.position[0]);
            glTexCoord2f(0,1); glVertex3f(0.0,-system_.position[0], system_.position[0]);
            glTexCoord2f(1,1); glVertex3f(0.0, system_.position[0], system_.position[0]);
            glTexCoord2f(1,0); glVertex3f(0.0, system_.position[0],-system_.position[0]);
         glEnd();
         glTranslatef(-system_.position[0], 0.0, 0.0);
         glRotatef(-flare_theta*20, 0, 0, 1);
         
         glEnable(GL_DEPTH_TEST);
      }
   }
   
   glBindTexture(GL_TEXTURE_2D, 0);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   glEnable(GL_LIGHTING);
}


void Openglwidget::toggle_fullscreen()
{
         if (fullscreen)
            set_fullscreen(false);
         else
            set_fullscreen(true);
}


void Openglwidget::toggle_antialiasing()
{
         if(!antialiasing)
         {
            LOG(DEBUG) << "Aktiviere AA";
            glEnable(GL_MULTISAMPLE);
            antialiasing = true;
         }
         else
         {
            LOG(DEBUG) << "Deaktiviere AA";
            glDisable(GL_MULTISAMPLE);
            antialiasing = false;
         }
}


void Openglwidget::set_fullscreen(bool wert)
{
         if (!wert)
         {
            fenster_breite = window_x;
            fenster_hoehe  = window_y;
            fenster_modus = SDL_OPENGL;
            SDL_SetVideoMode(window_x, window_y, bpp, fenster_modus);
            initialisiere_gl();
            fullscreen = false;
            LOG(INFO) << "Swiching to window " << window_x << "x" << window_y;
         }
         else
         {
            fenster_modus = SDL_OPENGL | SDL_FULLSCREEN;
            SDL_Surface* screen = SDL_SetVideoMode(fullscreen_x, fullscreen_y, bpp, fenster_modus);
            fenster_breite = fullscreen_x;
            fenster_hoehe  = fullscreen_y;
            initialisiere_gl();
            fullscreen = true;
            LOG(INFO) << "Swiching to fullscreen " << fullscreen_x << "x" << fullscreen_y;
         }
}



