#include "openglwidget.hh"


#include "openglwidget_material.h"
#include "openglwidget_events.h"

#include "station.hh"
#include "zone.hh"
#include "district.hh"
#include "deck.hh"

// // // //  Modelle/Texturen definieren
// #include "modelle.hh"


Openglwidget::Openglwidget(int breite_, int hoehe_)
{
   gettimeofday(&zeit, 0);
   tex = new Texturensammlung;
   
//    idle_redraw = false;
   running = true;
   antialiasing = false;
   fullscreen = false;
   
   info = SDL_GetVideoInfo();
   
   bpp = info->vfmt->BitsPerPixel;
   
   fullscreen_x = info->current_w;
   fullscreen_y = info->current_h;
   
   window_x = breite_;
   window_y = hoehe_;

   fenster_breite = window_x;
   fenster_hoehe =  window_y;
   
//     modelle_laden();
   
   
   licht_pos[0]  = 0  ; licht_pos[1]  = 0  ; licht_pos[2]  = 0  ; licht_pos[3]  = 0  ;
   
   licht_ambi[0] = 0.0; licht_ambi[1] = 0.0; licht_ambi[2] = 0.0; licht_ambi[3] = 1.0;
   licht_diff[0] = 1.0; licht_diff[1] = 1.0; licht_diff[2] = 1.0; licht_diff[3] = 1.0;
   licht_spec[0] = 1.0; licht_spec[1] = 1.0; licht_spec[2] = 1.0; licht_spec[3] = 1.0;

   sonne_ambi[0] = 0.0; sonne_ambi[1] = 0.0; sonne_ambi[2] = 0.0; sonne_ambi[3] = 1.0;
   sonne_diff[0] = 1.0; sonne_diff[1] = 1.0; sonne_diff[2] = 1.0; sonne_diff[3] = 1.0;
   sonne_spec[0] = 1.0; sonne_spec[1] = 1.0; sonne_spec[2] = 1.0; sonne_spec[3] = 1.0;

   spot_pos[0]  = 0  ; spot_pos[1]  = 0  ; spot_pos[2]  = 4  ; spot_pos[3]  = 0  ;
   spot_dir[0]  = 1  ; spot_dir[1]  = 1  ; spot_dir[2]  = 0  ;
   spot_ambi[0] = 1.0; spot_ambi[1] = 0.8; spot_ambi[2] = 0.0; spot_ambi[3] = 1.0;
   spot_diff[0] = 1.0; spot_diff[1] = 0.5; spot_diff[2] = 0.5; spot_diff[3] = 1.0;
   spot_spec[0] = 1.0; spot_spec[1] = 0.5; spot_spec[2] = 0.5; spot_spec[3] = 1.0;

   view_angle = 45;
   
   fps_counter = 0;
   fps_average = 0.0;
   fps_sum = 0.0;

   kamera_x = 0;
   kamera_y = 0;
   kamera_z = 0;
   
   x_offset = 0;
   y_offset = 0;
   z_offset = 0;
   
   kamera_radius = 0;
   kamera_phi = 0;
   
   pos_x = 0;
   pos_y = 0;
   pos_z = 0;
   pos_z_soll = 0;
   
   pos_radius = 95;
   pos_radius_soll = 95;
   pos_phi = 0;
   
   phi   = 0;
   phi_soll = 0;
   theta = 45;
   theta_soll = 45;
   zoom  = 1.0;
   zoom_soll  = 1.0;
   
   target_id = 0;
   target_x = 0;
   target_y = 0;
   target_z = 0;

   station = NULL;
   
//    mode(FL_RGB | FL_DEPTH | FL_DOUBLE);// | FL_STEREO);
}

void Openglwidget::set_station(Station* station_)
{
   station = station_;
}


// void Openglwidget::resize(int position_x_, int position_y_, int breite_, int hoehe_)
// {
//    Fl_Gl_Window::resize(position_x_, position_y_, breite_, hoehe_);
//    fenster_breite = breite_;
//    fenster_hoehe = hoehe_;
//    breite_zu_hoehe = float(fenster_breite) / float(fenster_hoehe);
// }


#define NEAR_CLIP 1.00
#define FAR_CLIP 20000



void Openglwidget::draw()
{

// // // // // // // // // // // // // // // // // // // // // // // //    perspektive setzen
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glViewport(0, 0, fenster_breite, fenster_hoehe);
   gluPerspective(view_angle,breite_zu_hoehe,NEAR_CLIP,FAR_CLIP);
// // // // // // // // // // // // // // // // // // // // // // // //    

   kamera_x = (1.0-zoom)*pos_radius*cos(phi*RAD)          +x_offset;
   kamera_y = (1.0-zoom)*pos_radius*sin(phi*RAD)          +y_offset;
   kamera_z = pos_z-pow(zoom,1.3)*pos_radius/tan(theta*RAD);// +z_offset;
   
   pos_x = pos_radius*cos(phi*RAD) +x_offset;
   pos_y = pos_radius*sin(phi*RAD) +y_offset;
//    pos_z = pos_z                   +z_offset;
   
   oben_x = 0;//cos(phi*RAD)*sin(theta*RAD);
   oben_y = 0;//sin(phi*RAD)*sin(theta*RAD);
   oben_z = 1;//cos(theta*RAD);
   
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluLookAt(kamera_x, kamera_y, kamera_z, pos_x, pos_y, pos_z, oben_x, oben_y, oben_z);
   
   flare_theta = atan2(sqrt(pow(pos_y-kamera_y,2) + pow(pos_z-kamera_z,2)),pos_x-kamera_x);
   flare_phi = atan2(pos_z-kamera_z,pos_y-kamera_y);

// // // // // // // // // // // // // // // // // // // // // // // //     Licht
    
   licht_pos[0] = kamera_x;  // Kameralicht
   licht_pos[1] = kamera_y;
   licht_pos[2] = kamera_z;
   licht_pos[3] = 1.0;
   glLightfv(GL_LIGHT0, GL_POSITION, licht_pos);
   glLightfv(GL_LIGHT0, GL_AMBIENT, licht_ambi);
   glLightfv(GL_LIGHT0, GL_DIFFUSE, licht_diff);
   glLightfv(GL_LIGHT0, GL_SPECULAR, licht_spec);
   glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION,  1.0);
   glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION,    0.0);
   glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.0);

   sonne_pos[0] = 1000.0;  // Sonnenlicht
   sonne_pos[1] = 0.0;
   sonne_pos[2] = 0.0;
   sonne_pos[3] = 0.0;
   glLightfv(GL_LIGHT1, GL_POSITION, sonne_pos);
   glLightfv(GL_LIGHT1, GL_AMBIENT, sonne_ambi);
   glLightfv(GL_LIGHT1, GL_DIFFUSE, sonne_diff);
   glLightfv(GL_LIGHT1, GL_SPECULAR, sonne_spec);
   glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 1.0);
   
// // // // // // // // //    Testlicht
   
//    float zeit_tmp = zeit_aktuell();
//    spot_pos[0] = 0.0;
//    spot_pos[1] = 0.0;
//    spot_pos[2] = 4.0;
//    spot_pos[3] = 0.5;
//    spot_dir[0] = cos(zeit_tmp*4);
//    spot_dir[1] = sin(zeit_tmp*4);
//    glLightfv(GL_LIGHT2, GL_POSITION,       spot_pos);
//    glLightf (GL_LIGHT2, GL_SPOT_CUTOFF,    20);
//    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot_dir);
//    glLightf (GL_LIGHT2, GL_SPOT_EXPONENT,  30);
//    glLightfv(GL_LIGHT2, GL_AMBIENT,        spot_ambi);
//    glLightfv(GL_LIGHT2, GL_DIFFUSE,        spot_diff);
//    glLightfv(GL_LIGHT2, GL_SPECULAR,       spot_spec);
//    glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION,  1.0);
//    glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION,    0.0);
//    glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.0);
//    glEnable (GL_LIGHT2);
   
// // // // // // // // // // // // // // // // // // // // // // // //    
   
   glEnable(GL_LIGHTING);
   glDisable(GL_LIGHT1);
   glEnable(GL_LIGHT0);
   
   zeichne();
   
   glGetIntegerv(GL_VIEWPORT, viewport);
   glGetDoublev(GL_MODELVIEW_MATRIX, model_matrix);
   glGetDoublev(GL_PROJECTION_MATRIX, project_matrix);
   
// // // // // // // // // // // // // // // Umgebung // // // // // //
   
   set_material_std();
   glDisable(GL_LIGHT0);
   glEnable(GL_LIGHT1);

//    glRotatef( 90, 1.0, 0.0, 0.0);
   zeichne_system(sys);
//    glRotatef(-90, 1.0, 0.0, 0.0);
   
   
// // // // // // // // // // // // // // // // // // // // // // // // //    UI Elemente zeichnen
//     
// #define LEISTE_U_HOEHE 100
// 
//     glPushMatrix();
//     glMatrixMode(GL_PROJECTION);
//     glPushMatrix();
//     
//     glDisable(GL_LIGHTING);
//     glDisable(GL_DEPTH_TEST);
//     
//     glViewport(0, 0, fenster_breite, LEISTE_U_HOEHE);
//     glLoadIdentity();
//     glOrtho(0.0, 1.0, 0.0, 1.0, -10, 10);
// //     gluPerspective(45,breite_zu_hoehe,NEAR_CLIP,FAR_CLIP);
//     glMatrixMode(GL_MODELVIEW);
//     glLoadIdentity();
//     
//     gluLookAt(0, 0, 0, 
//               0, 0,-1,
//               0, 1, 0);
// 
//     glColor3f(1.0, 1.0, 1.0);
//     std::stringstream text;
// //     text.precision(4);
//     
//     text << gebiet->rohstoffe[R_HOLZ];
//     glRasterPos3f(0.1,0.5,0); gl_font(1, 12); gl_draw(text.str().c_str());
//     text.str(""); text.clear();
//     
//     text << gebiet->rohstoffe[R_LEHM];
//     glRasterPos3f(0.2,0.5,0); gl_font(1, 12); gl_draw(text.str().c_str());
//     text.str(""); text.clear();
// 
//     text << gebiet->rohstoffe[R_STROH];
//     glRasterPos3f(0.3,0.5,0); gl_font(1, 12); gl_draw(text.str().c_str());
//     text.str(""); text.clear();
// 
//     text << gebiet->produktion[R_BAU];
//     glRasterPos3f(0.4,0.5,0); gl_font(1, 12); gl_draw(text.str().c_str());
//     text.str(""); text.clear();
// 
//     glEnable(GL_LIGHTING);
//     glEnable(GL_DEPTH_TEST);
//     
//     glPopMatrix();
//     glMatrixMode(GL_PROJECTION);
//     glPopMatrix();
   
   zeit_frame = zeit_diff(zeit);
//    std::cout << zeit_frame << std::endl;
   
   if (phi != phi_soll || pos_z != pos_z_soll || theta != theta_soll || zoom != zoom_soll || pos_radius != pos_radius_soll)
   {
      float zeit_faktor;
      if (zeit_frame > 0.1)
         zeit_faktor = 0.1;
      else
         zeit_faktor = zeit_frame;
      
      if (fabs(phi_soll-phi) > 0.1)
      {
         phi += 0.9*(phi_soll - phi)*zeit_faktor*8;
      }
      else
         phi = phi_soll;
      
      if (fabs(pos_z_soll - pos_z) > 0.001)
      {
         pos_z += 0.9*(pos_z_soll - pos_z)*zeit_faktor*8;
      }
      else
         pos_z = pos_z_soll;
      
      if (fabs(theta_soll - theta) > 0.01)
      {
         theta += 0.9*(theta_soll - theta)*zeit_faktor*8;
      }
      else
         theta = theta_soll;
      
      if (fabs(zoom_soll - zoom) > 0.001)
      {
         zoom += 0.9*(zoom_soll - zoom)*zeit_faktor*8;
      }
      else
         zoom = zoom_soll;
      
      if (fabs(pos_radius_soll - pos_radius) > 0.001)
      {
         pos_radius += 0.9*(pos_radius_soll - pos_radius)*zeit_faktor*8;
      }
      else
         pos_radius = pos_radius_soll;
      
//       if (!idle_redraw)
//       {
//          idle_redraw = true;
//          Fl::add_idle(idle_draw, this);
//       }
   }
//    else
//    {
//       idle_redraw = false;
//       Fl::remove_idle(idle_draw, this);
//    }
   
   fps_counter++;
   fps_sum += 1.0/zeit_frame;
   
   if (fps_counter>=40)
   {
      fps_average = fps_sum/40.0;
      fps_sum = 0.0;
      fps_counter = 0;
      std::cout << "FPS: " << fps_average << "\r" << std::flush;
   }
   
   SDL_GL_SwapBuffers();
}



void Openglwidget::zeichne()
{
// // // // // // // // // // // // // // // // // // // // // // // //    clear buffer(s)
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
// // // // // // // // // // // // // // // // // // // // // // // //     Matrix vorbereiten

   glInitNames();
   glPushName(0);
   zeichne_station();

//    glLoadName(aktuelle_id++); //

//    glhilf::draw_tube_mesh(0, 0, 0, 0, 0, 1, 1, 20);
//    glTranslatef(0,0,1);
//    glhilf::draw_tube_mesh(0, 0, 0, 0, 0, 1, 1, 20);
//    glTranslatef(0,0,1);
//    glhilf::draw_tube_mesh(0, 0, 0, 0, 0, 1, 1, 20);
//    glTranslatef(0,0,1);
//    glhilf::draw_tube_mesh(0, 0, 0, 0, 0, 1, 1, 20);
//    glTranslatef(0,0,-3);
   
}


void Openglwidget::zeichne_station()
{
   if (station == NULL)
      return;

    for (std::vector<Zone>::iterator it = station->get_zones().begin(); it != station->get_zones().end(); it++)
    {
        zeichne_zone(*it);
    }
}

void Openglwidget::zeichne_zone(Zone& zone)
{
    for (std::vector<District>::iterator it = zone.get_districts().begin(); it != zone.get_districts().end(); it++)
    {
        zeichne_district(*it);
    }
}

#define STEP 0.05

void Openglwidget::zeichne_district(District& district)
{
   //~ if (!district.aktiv)
      zeichne_district_outside(district);
   //~ else
   //~ {
   //~ float x1, y1, z1, x2, y2, z2;
   //~ float delta_p = STEP/district.radius_min;
   //~ float radius_;
   //~ 
   //~ for(int r=0; r<=district.deck_count; r++)
   //~ {
//       if (r%3==0) glColor3f(1,0,0);
//       if (r%3==1) glColor3f(0,1,0);
//       if (r%3==2) glColor3f(0,0,1);
      //~ glColor3f(0.5, 0.5, 0.5+r*0.1);
      //~ glColor3f(0.5, 0.5, 0.5+r*0.1);
      //~ glColor3f(0.5, 0.5, 0.5+r*0.1);
      //~ 
      //~ for(int y=0; y<district.size_y; y=y+1)
      //~ {
         //~ for(int x=0; x<district.size_x; x=x+1)
         //~ {
            //~ radius_ = district.radius_min + 2*r*STEP;
            //~ 
               //~ x1 = cos((x  )*delta_p + district.phi_min)*radius_;
               //~ y1 = sin((x  )*delta_p + district.phi_min)*(radius_);
               //~ z1 = y*STEP + district.z_min;
               //~ 
               //~ x2 = cos((x+1)*delta_p + district.phi_min)*radius_;
               //~ y2 = sin((x+1)*delta_p + district.phi_min)*(radius_);
               //~ z2 = z1;
               //~ 
            //~ glBegin(GL_LINES);
               //~ glVertex3f(x1, y1, z1);
               //~ glVertex3f(x2, y2, z2);
               //~ 
               //~ x2 = x1;
               //~ y2 = y1;
               //~ z2 = (y+1)*STEP + district.z_min;
               //~ 
               //~ glVertex3f(x1, y1, z1);
               //~ glVertex3f(x2, y2, z2);
               //~ 
               //~ x2 = cos((x)*delta_p + district.phi_min)*(radius_+2*STEP);
               //~ y2 = sin((x)*delta_p + district.phi_min)*(radius_+2*STEP);
               //~ z2 = z1;
               //~ 
               //~ glVertex3f(x1, y1, z1);
               //~ glVertex3f(x2, y2, z2);
            //~ glEnd();
         //~ }
         //~ 
      //~ }
   //~ }
//    
//    for (int i=0; i<district.deck_count; i++)
//       zeichne_deck(district.deck[i]);
   //~ }
}

#define DELTA_P 0.1

void Openglwidget::zeichne_district_outside(District& district)
{
   glLoadName(district.objekt_id);
   glEnable(GL_LIGHT1);
   
   glColor3f(0.5, 0.5, 0.5);
   
   set_material_ambi(0.00, 0.00, 0.00, 1.0);
   set_material_diff(0.30, 0.30, 0.50, 1.0);
   set_material_spec(0.70, 0.70, 1.00, 1.0);
   set_material_shin(90.0);
   
   float x1, y1, z1;
   float x2, y2, z2;
   float x3, y3, z3;
   float x4, y4, z4;
   
   float p_min = district.get_phi_min();
   float p_max = district.get_phi_max();
   
   if (p_max < p_min) p_max += 2*PI;
   
   float r_min = district.get_radius_min();
   float r_max = district.get_radius_max();
   
   float z_min = district.get_z_min();
   float z_max = district.get_z_max();

   float cosp1 = cos(p_min);
   float sinp1 = sin(p_min);
   float cosp2, sinp2;
   
   float texcoord_x1, texcoord_y1;
   float texcoord_x2, texcoord_y2;
   
   x1 = r_min * cosp1;
   y1 = r_min * sinp1;
   
   x2 = r_max * cosp1;
   y2 = r_max * sinp1;
   
   glBegin(GL_QUADS);
         glNormal3f(sinp1, -cosp1, 0.0);
      glVertex3f(x1, y1, z_min);
      glVertex3f(x1, y1, z_max);
      glVertex3f(x2, y2, z_max);
      glVertex3f(x2, y2, z_min);
   glEnd();
   
   glBindTexture(GL_TEXTURE_2D, tex->tex_district->id);
//    glBindTexture(GL_TEXTURE_2D, tex2->get_id("floor-room"));
//    glBindTexture(GL_TEXTURE_2D, tex2->get_id("floor-corridor"));
//    glBindTexture(GL_TEXTURE_2D, tex2->get_id("floor-lab"));
   
   while(p_min != p_max)
   {
      texcoord_x1 = z_min*0.01;
      texcoord_x2 = z_max*0.01;
      
      texcoord_y1 = p_min*2/(PI);
      
      p_min += DELTA_P;
      if (p_min > p_max) p_min = p_max;
      
      texcoord_y2 = p_min*2/(PI);
      
      cosp2 = cosp1;
      sinp2 = sinp1;
      
      cosp1 = cos(p_min);
      sinp1 = sin(p_min);
      
      x3 = r_min * cosp1;
      y3 = r_min * sinp1;
      
      x4 = r_max * cosp1;
      y4 = r_max * sinp1;
      
      glBegin(GL_QUADS);
            glNormal3f(0.0, 0.0, -1.0);
         glVertex3f(x3, y3, z_min);
         glVertex3f(x1, y1, z_min);
         glVertex3f(x2, y2, z_min);
         glVertex3f(x4, y4, z_min);
         
            glNormal3f(cosp1, sinp1, 0.0);
         glTexCoord2f(texcoord_x1, texcoord_y1);   glVertex3f(x4, y4, z_min);
            glNormal3f(cosp2, sinp2, 0.0);
         glTexCoord2f(texcoord_x1, texcoord_y2);   glVertex3f(x2, y2, z_min);
         glTexCoord2f(texcoord_x2, texcoord_y2);   glVertex3f(x2, y2, z_max);
            glNormal3f(cosp1, sinp1, 0.0);
         glTexCoord2f(texcoord_x2, texcoord_y1);   glVertex3f(x4, y4, z_max);
         
            glNormal3f(0.0, 0.0, 1.0);
         glVertex3f(x4, y4, z_max);
         glVertex3f(x2, y2, z_max);
         glVertex3f(x1, y1, z_max);
         glVertex3f(x3, y3, z_max);
         
            glNormal3f(-cosp1, -sinp1, 0.0);
         glTexCoord2f(texcoord_x1, texcoord_y1);   glVertex3f(x3, y3, z_max);
            glNormal3f(-cosp2, -sinp2, 0.0);
         glTexCoord2f(texcoord_x1, texcoord_y2);   glVertex3f(x1, y1, z_max);
         glTexCoord2f(texcoord_x2, texcoord_y2);   glVertex3f(x1, y1, z_min);
            glNormal3f(-cosp1, -sinp1, 0.0);
         glTexCoord2f(texcoord_x2, texcoord_y1);   glVertex3f(x3, y3, z_min);
      glEnd();
      
      x1 = x3; y1 = y3;
      x2 = x4; y2 = y4;
   }
   
   glBegin(GL_QUADS);
         glNormal3f(-sinp1, cosp1, 0.0);
      glVertex3f(x2, y2, z_min);
      glVertex3f(x2, y2, z_max);
      glVertex3f(x1, y1, z_max);
      glVertex3f(x1, y1, z_min);
   glEnd();
   
   glBindTexture(GL_TEXTURE_2D, 0);
   set_material_std();
   glDisable(GL_LIGHT1);
}


void Openglwidget::set_view_to(Mausobjekt& mo_)
{
   if (mo_.objekt_typ == "District")
   {
      District& dis = (District&) mo_;
      //~ station->set_aktiv(dis);
      pos_radius_soll = dis.get_radius_min();
      pos_z_soll = (dis.get_z_min()+dis.get_z_max())*0.5;
      phi_soll = dis.get_phi_min()<dis.get_phi_max()?(dis.get_phi_min()+dis.get_phi_max())*0.5/RAD:(dis.get_phi_min()+dis.get_phi_max()+2*PI)*0.5/RAD;
      zoom_soll = 0.4; 
   }
}


void Openglwidget::zeichne_deck(Deck& deck)
{
   
}


Mausobjekt& Openglwidget::get_target()
{
   if (target_id == 0)
      return nichts;
   
    for (std::vector<Zone>::iterator zone_it = station->get_zones().begin(); zone_it != station->get_zones().end(); zone_it++)
    {
        for (std::vector<District>::iterator district_it = zone_it->get_districts().begin(); district_it != zone_it->get_districts().end(); district_it++)
        {
            return (Mausobjekt&) (*district_it);
        }
    }
}


void Openglwidget::selektiere_id()
{
    float maus_x = event.button.x;
    float maus_y = fenster_hoehe-event.button.y;
    
    std::cout << "x: " << event.button.x << ", y:" << event.button.y << std::endl;
    
    GLuint sel_buffer[256];
    glSelectBuffer (256, sel_buffer);
    GLint hits = 0;

    glViewport(0, 0, fenster_breite, fenster_hoehe);

    glMatrixMode(GL_PROJECTION);
    glRenderMode(GL_SELECT);
    glLoadIdentity();
    gluPickMatrix(maus_x, maus_y, 1, 1, viewport); // nur an der Mausposition gucken
    gluPerspective(view_angle,breite_zu_hoehe,NEAR_CLIP,FAR_CLIP);
// // // // // // // // // render
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity;
    zeichne();
// // // // // // // // //
    hits = glRenderMode(GL_RENDER);
    std::cout << hits << " Objekte getroffen" << std::endl;

    if (hits) // wenn was angeklickt wurde, soll das "vorderste" gewählt werden
    {
    //  Organisation des Buffers:
    //     Anzahl der Namen auf dem Stack
    //     Kleinster Abstand
    //     Größter Abstand
    //     Objektname

        target_id = sel_buffer[3];
        int abstand = sel_buffer[1];

        for (int i = 1; i <hits; i++)
        {
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




void Openglwidget::selektiere_pos()
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


void Openglwidget::initialisiere_gl()
{
   tex2 = new Textures;
    
   glLineWidth(2);
   glPolygonOffset(1.0,1.0);
   glEnable(GL_POLYGON_OFFSET_FILL);
   glClearColor(0.0, 0.0, 0.0, 1.0);

   glEnable(GL_DEPTH_TEST);
   glDepthFunc(GL_LEQUAL);

   glEnable(GL_LIGHT0);
   glEnable(GL_LIGHT1);
   glEnable(GL_LIGHT2);
   glEnable(GL_COLOR_MATERIAL);
   glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
   glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
   glFrontFace(GL_CW);

   glShadeModel(GL_SMOOTH); // glShadeModel(GL_SMOOTH) oder  glShadeModel(GL_FLAT)

   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//     glBlendFunc(GL_SRC_ALPHA,GL_ONE);
//     glBlendFunc(GL_ONE, GL_ONE);
   
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
            glTranslatef((i+1)*system_.abstand_umlaufbahn, 0, 0);
            
   //           glColor3f(0.6, 0.4, 0.4);
            glColor3f(1.0, 1.0, 1.0);
            glRotatef(5, 1.0, 1.0, 0.0);
            glBindTexture(GL_TEXTURE_2D, tex->tex_planet[system_.planeten[i].textur_ind]->id);
            
            for (int j=0; j<system_.planeten[i].spezial; j++)
            {
               glhilf::zeichne_ring(system_.planeten[i].radius*(1.2+j*j*0.2), system_.planeten[i].radius*(0.4*j+0.15), 40);
            }
            
            glColor3f(0.8, 0.8, 0.8);
            glhilf::draw_texture_sphere(system_.planeten[i].radius, 20, 40);
            glBindTexture(GL_TEXTURE_2D, 0);
         glPopMatrix();
         break;
         
         case 'K':
         glPushMatrix();
            glRotatef(system_.planeten[i].phase, 0.0, 0.0, 1.0);
            glTranslatef((i+1)*system_.abstand_umlaufbahn, 0, 0);
            glBindTexture(GL_TEXTURE_2D, tex->tex_planet[system_.planeten[i].textur_ind]->id);
            glhilf::draw_texture_sphere(system_.planeten[i].radius, 20, 40);
            glBindTexture(GL_TEXTURE_2D, 0);
         glPopMatrix();
         break;
         
         case 'M':
         glPushMatrix();
            glRotatef(system_.planeten[i].phase, 0.0, 0.0, 1.0);
            glTranslatef((i+1)*system_.abstand_umlaufbahn, 0, 0);
            glBindTexture(GL_TEXTURE_2D, tex->tex_planet[system_.planeten[i].textur_ind]->id);
            glColor3f(1.0, 1.0, 1.0);
            glhilf::draw_texture_sphere(system_.planeten[i].radius, 20, 40);
            glBindTexture(GL_TEXTURE_2D, 0);
         glPopMatrix();
         break;
         
      }
  }
  
   glDisable(GL_LIGHTING);
   glBindTexture(GL_TEXTURE_2D, tex->tex_stars->id);
   glColor3f(1.0, 1.0, 1.0);
   glhilf::draw_star_map(system_.abstand_max, 1, 2);
   glBindTexture(GL_TEXTURE_2D, 0);
// // // // // // // // // // // // // Sonne
   glTranslatef(system_.position[0], 0.0, 0.0);
   glColor3f(1.0, 1.0, 0.7);
   glhilf::draw_texture_sphere(system_.sonnenradius, 100, 100);
   
   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA,GL_ONE);
      glBindTexture(GL_TEXTURE_2D, tex->tex_sonne->id);
      glColor4f(1.0, 1.0, 0.7, 0.4);
      glBegin(GL_QUADS);
         glTexCoord2f(0,0); glVertex3f(0.0,-system_.sonnenradius*3,-system_.sonnenradius*3);
         glTexCoord2f(0,1); glVertex3f(0.0,-system_.sonnenradius*3, system_.sonnenradius*3);
         glTexCoord2f(1,1); glVertex3f(0.0, system_.sonnenradius*3, system_.sonnenradius*3);
         glTexCoord2f(1,0); glVertex3f(0.0, system_.sonnenradius*3,-system_.sonnenradius*3);
      glEnd();
      glTranslatef(-system_.position[0], 0.0, 0.0);
      
   glGetIntegerv(GL_VIEWPORT, viewport2);
   glGetDoublev(GL_MODELVIEW_MATRIX, model_matrix2);
   glGetDoublev(GL_PROJECTION_MATRIX, project_matrix2);
   
   gluProject(system_.position[0]-system_.sonnenradius*2, 0, 0, model_matrix2, project_matrix2, viewport2, &fenster_x, &fenster_y, &fenster_z);
      
   
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
         glBindTexture(GL_TEXTURE_2D, tex->tex_flare[0]->id);
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
         glBindTexture(GL_TEXTURE_2D, tex->tex_flare[1]->id);
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
         glBindTexture(GL_TEXTURE_2D, tex->tex_flare[2]->id);
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
         glBindTexture(GL_TEXTURE_2D, tex->tex_flare[3]->id);
         glBegin(GL_QUADS);
            glTexCoord2f(0,0); glVertex3f(0.0,-0.25*system_.position[0],-0.25*system_.position[0]);
            glTexCoord2f(0,1); glVertex3f(0.0,-0.25*system_.position[0], 0.25*system_.position[0]);
            glTexCoord2f(1,1); glVertex3f(0.0, 0.25*system_.position[0], 0.25*system_.position[0]);
            glTexCoord2f(1,0); glVertex3f(0.0, 0.25*system_.position[0],-0.25*system_.position[0]);
         glEnd();
         glTranslatef(-system_.position[0], 0.0, 0.0);
         glRotatef(-flare_theta*20, 0, 0, 1);
         glRotatef(-phi*2, 0, 0, 1);
         
         glRotatef(flare_theta*50, 0, 0, 1);
         glTranslatef(system_.position[0], 0.0, 0.0);
         glBindTexture(GL_TEXTURE_2D, tex->tex_flare[4]->id);
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
   glDisable(GL_BLEND);
}


void Openglwidget::toggle_fullscreen()
{
         if (fullscreen)
            set_fullscreen(false);
         else
            set_fullscreen(true);
}


void Openglwidget::set_fullscreen(bool wert)
{
         if (!wert)
         {
            fenster_breite = window_x;
            fenster_hoehe  = window_y;
            SDL_SetVideoMode(window_x, window_y, bpp, SDL_OPENGL);
            initialisiere_gl();
            fullscreen = false;
         }
         else
         {
            fenster_breite = fullscreen_x;
            fenster_hoehe  = fullscreen_y;
            SDL_SetVideoMode(fullscreen_x, fullscreen_y, bpp, SDL_OPENGL | SDL_FULLSCREEN);
            initialisiere_gl();
            fullscreen = true;
         }
}



