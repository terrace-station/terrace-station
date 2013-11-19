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
   if (station->active_district != NULL) glRotatef(-station->active_district->get_angle(), 0.0, 0.0, 1.0);
   
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
   glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION,    0.005);
   glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.0);

   sonne_pos[0] = sys.position[0];  // Sonnenlicht
   sonne_pos[1] = 0.0;
   sonne_pos[2] = 0.0;
   sonne_pos[3] = 1.0;
   glLightfv(GL_LIGHT1, GL_POSITION, sonne_pos);
   glLightfv(GL_LIGHT1, GL_AMBIENT, sonne_ambi);
   glLightfv(GL_LIGHT1, GL_DIFFUSE, sonne_diff);
   glLightfv(GL_LIGHT1, GL_SPECULAR, sonne_spec);
   glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION,  1.0);
   glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION,    0.0);
   glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.0);
   
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
   
   zeichne_szene();
   
   zeit_frame = zeit_diff(zeit);
//    std::cout << zeit_frame << std::endl;
   parameter_regelung();
   if (!gamemenu) 
      laufzeit += zeit_frame;
   
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


void Openglwidget::zeichne_szene()
{
// // // // // // // // // // // // // // // // // // // // // // // //    clear buffer(s)
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
// // // // // // // // // // // // // // // // // // // // // // // //     Matrix vorbereiten

   glInitNames(); // Namen fuer das picking initialisieren
   glPushName(0);
   zeichne_station();
   
   glGetIntegerv(GL_VIEWPORT, viewport);
   glGetDoublev(GL_MODELVIEW_MATRIX, model_matrix);
   glGetDoublev(GL_PROJECTION_MATRIX, project_matrix);
   
// // // // // // // // // // // // // // // Umgebung // // // // // //
   
   set_material_std();
   glDisable(GL_LIGHT0);
   glEnable(GL_LIGHT1);

   glLoadName(0);
   zeichne_system(sys);
   
   if (gamemenu)
   {
// // // // // // // // // // // // // // // // // // // // // // // // //    UI Elemente zeichnen
      glLoadIdentity();
      gluLookAt(0, 0, 10,   0, 0, 0,   0, 1, 0);
      zeichne_gamemenu();
   }
}


void Openglwidget::zeichne_gamemenu()
{
   glClear(GL_DEPTH_BUFFER_BIT);
   
   glDisable(GL_LIGHTING);
   glDisable(GL_DEPTH_TEST);
   
   glColor4f(0.3, 0.3, 0.5, 0.5*menu_bg);
   glBegin(GL_QUADS);
      glVertex3f(-100.0, -100.0, -10.0);
      glVertex3f( 100.0, -100.0, -10.0);
      glVertex3f( 100.0,  100.0, -10.0);
      glVertex3f(-100.0,  100.0, -10.0);
   glEnd();
   
   glEnable(GL_DEPTH_TEST);
   glEnable(GL_LIGHTING);
   glDisable(GL_LIGHT1);
   glEnable(GL_LIGHT0);
   licht_pos[0] = 10.0;
   licht_pos[1] =  8.0;
   licht_pos[2] = 10.0;
   licht_pos[3] = 1.0;
   glLightfv(GL_LIGHT0, GL_POSITION, licht_pos);
   glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION,  1.5);
   glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION,    0.0);
   glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.0);
   
   set_material_ambi(0.00, 0.00, 0.00, 1.0);
   set_material_diff(0.30, 0.30, 0.50, 1.0);
   set_material_spec(1.00, 1.00, 1.00, 1.0);
   set_material_shin(100.0);

   glTranslatef(0.0, 0.0, (1.0-menu_bg)*10);
   
   for (std::list<Togglebutton_and_coords>::iterator it = menu.togglebuttons.begin(); it != menu.togglebuttons.end(); it++)
   {
      glPushMatrix();
         glTranslatef(it->x, it->y, 0.0);
         glScalef(it->sx, it->sy, 1);
         it->button.zeichne();
      glPopMatrix();
   }
   
   for (std::list<Button_and_coords>::iterator it = menu.buttons.begin(); it != menu.buttons.end(); it++)
   {
      glPushMatrix();
         glTranslatef(it->x, it->y, 0.0);
         glScalef(it->sx, it->sy, 1);
         it->button.zeichne();
      glPopMatrix();
   }
   
   glGetIntegerv(GL_VIEWPORT, viewport);
   glGetDoublev(GL_MODELVIEW_MATRIX, model_matrix);
   glGetDoublev(GL_PROJECTION_MATRIX, project_matrix);
   
}


void Openglwidget::zeichne_station()
{
   if (station == NULL)
      return;

   for (int i=station->get_zones().size()-1; i >= 0; i--)
   {
      float winkel = laufzeit*station->get_zones()[i].get_omega()/RAD;
      if(i%2==0) winkel*=-1;
      station->get_zones()[i].set_angle(winkel);
      
      glPushMatrix();
      glRotatef(winkel, 0.0, 0.0, 1.0);
         zeichne_zone(station->get_zones()[i]);
      glPopMatrix();
      
      // do not draw inner zones, if a district is activated:
      if (station->get_active_district() != NULL) {
         Zone& current_zone = station->get_zones()[i];
         Zone& active_zone = *station->get_active_district()->get_zone();
         if (&current_zone == &active_zone) {
            break;
         }
      }
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
   
   glBindTexture(GL_TEXTURE_2D, textures->get_id("district-hull"));
   
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




