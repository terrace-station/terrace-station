#define NEAR_CLIP 1.00
#define FAR_CLIP 25000

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
    
   lights->set_kamera_pos(kamera_x, kamera_y, kamera_z, 1.0); // kameralicht
   lights->set_kamera_att(1.0, 0.01, 0.0);
   
//    lamp.set_position(-61.0, 2.87188, 5.75743);
//    lamp.lampbegin();
   
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
   
   if (station->active_district != NULL) glRotatef(-station->active_district->get_angle(), 0.0, 0.0, 1.0); // sorgt dafür, dass die Kamera ausgewählten Distrikten folgt

   lights->set_sonne_pos();
   
   glEnable(GL_LIGHTING);
   lights->kamera_on();
   lights->sonne_on();
   
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
   lights->kamera_off();
   lights->sonne_on();

   glLoadName(0);
   glPushMatrix();
   glTranslatef(0.0, 0.0, 4000.0);
   glRotatef(-10, 1.0, 0.0, 0.0);
   zeichne_system(sys);
   glPopMatrix();
   
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
   
   glColor4f(0.0, 0.2, 0.1, 0.5*menu_bg); // hintergrund des Menüs
   glBegin(GL_QUADS);
      glVertex3f(-100.0, -100.0, -10.0);
      glVertex3f( 100.0, -100.0, -10.0);
      glVertex3f( 100.0,  100.0, -10.0);
      glVertex3f(-100.0,  100.0, -10.0);
   glEnd();
   
   glEnable(GL_DEPTH_TEST);
   glEnable(GL_LIGHTING);
   lights->sonne_off();
   lights->kamera_on();
   lights->set_kamera_pos(10.0, 8.0, 10.0);
   lights->set_kamera_att(1.5, 0.0, 0.0);
   
   set_material_ambi(0.00, 0.00, 0.00, 1.0);
   set_material_diff(0.10, 0.10, 0.20, 1.0);
   set_material_spec(1.00, 1.00, 1.00, 1.0);
   set_material_shin(128.0);

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
   glLoadName(0);
   
   glDisable(GL_DEPTH_TEST);
   glPushMatrix(); glTranslatef(0.0, 3.0, 0.0); fonttextures->text_rendern_m("Game Menu", "gamemenu", 1.5, "jupiter", 180, 255, 180, 150); glPopMatrix();
   glPushMatrix(); glTranslatef(-2.0, 1.0, 0.0); fonttextures->text_rendern_m("fullscreen", "fullscreen", 0.8, "jupiter", 180, 255, 180, 150); glPopMatrix();
   glPushMatrix(); glTranslatef(-2.0, 0.0, 0.0); fonttextures->text_rendern_m("anti-aliasing", "aa", 0.8, "jupiter", 180, 250, 180, 150); glPopMatrix();
   glPushMatrix(); glTranslatef(2.0,-3.0, 0.0); fonttextures->text_rendern_m("Leave Program", "close", 0.8, "jupiter", 180, 255, 180, 150); glPopMatrix();
   glPushMatrix(); glTranslatef(-3.0,-3.0, 0.0); fonttextures->text_rendern_m("Return", "return", 0.8, "jupiter", 180, 255, 180, 150); glPopMatrix();
   glEnable(GL_DEPTH_TEST);
   
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
      glPushMatrix();
      glRotatef(station->get_zones()[i].get_angle(), 0.0, 0.0, 1.0);
         zeichne_zone(station->get_zones()[i]);
      glPopMatrix();
      
      float winkel = laufzeit*station->get_zones()[i].get_omega()/RAD;
      if(i%2==0) winkel*=-1;
      station->get_zones()[i].set_angle(winkel);
      
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
    zeichne_district_outside(district);

    District& active_district = *station->get_active_district();
    if (&district == &active_district) {
        //only draw the first (outermost) deck for now:
        zeichne_deck(district.get_decks()[0]);
    }
}

void Openglwidget::zeichne_deck(Deck& deck)
{
    Room* room;
    Tile* tile;
   
    lights->sonne_off();
    lights->kamera_off();
    
    glGetIntegerv(GL_VIEWPORT, viewport_system);
    glGetDoublev(GL_MODELVIEW_MATRIX, model_matrix_system);
    glGetDoublev(GL_PROJECTION_MATRIX, project_matrix_system);
        
    for (std::list<Room>::iterator room_it = deck.get_rooms().begin(); room_it != deck.get_rooms().end(); room_it++)
    {
        
        gluProject(room_it->get_lamps().front().position[0], room_it->get_lamps().front().position[1], room_it->get_lamps().front().position[2], model_matrix_system, project_matrix_system, viewport_system, &fenster_x, &fenster_y, &fenster_z);
        
        if(fenster_x >= -100 && fenster_x <= fenster_breite+100 && fenster_y >= -100 && fenster_y <= fenster_hoehe+100)
           room_it->onscreen = true;
        else
           room_it->onscreen = false;
    }
           
    for (std::list<Room>::iterator room_it = deck.get_rooms().begin(); room_it != deck.get_rooms().end(); room_it++)
    {
       if (room_it->onscreen)
       {
         room = &(*room_it);
         
         for (std::list<Lamp>::iterator lamp_it = room->get_lamps().begin(); lamp_it != room->get_lamps().end(); lamp_it++)
         {
               lamp_it->lampbegin();
         }
         //~ lights->warn1_on();
         //~ lights->set_warn1_pos(room->get_wall_tiles().front().v1x, room->get_wall_tiles().front().v1y, room->get_wall_tiles().front().v1z);
         
         // draw floor:
         glBindTexture(GL_TEXTURE_2D, textures->get_id(room->get_floor_texture_label()));
         glColor3f(1.0, 1.0, 1.0);
         set_material_ambi(0.2, 0.2, 0.2, 1.0);
         set_material_diff(0.8, 0.8, 0.8, 1.0);
         set_material_spec(0.0, 0.0, 0.0, 1.0);
         for (std::vector<Tile>::iterator tile_it = room->get_floor_tiles().begin(); tile_it != room->get_floor_tiles().end(); tile_it++)
         {
               tile = &(*tile_it);
               
               glBegin(GL_QUADS);
                  glNormal3f(tile->nx, tile->ny, tile->nz);
                  glTexCoord2f(0e0, 1e0);
                  glVertex3f(tile->v1x, tile->v1y, tile->v1z);
                  glTexCoord2f(1e0, 1e0);
                  glVertex3f(tile->v2x, tile->v2y, tile->v2z);
                  glTexCoord2f(1e0, 0e0);
                  glVertex3f(tile->v3x, tile->v3y, tile->v3z);
                  glTexCoord2f(0e0, 0e0);
                  glVertex3f(tile->v4x, tile->v4y, tile->v4z);
               glEnd();
         }
         
         // draw walls:
         glBindTexture(GL_TEXTURE_2D, textures->get_id(room->get_wall_texture_label()));
         glColor3f(1.0, 1.0, 1.0);
         set_material_ambi(0.01, 0.01, 0.01, 1.0);
         set_material_diff(0.8, 0.8, 0.8, 1.0);
         set_material_spec(0.0, 0.0, 0.0, 1.0);
         for (std::vector<Tile>::iterator tile_it = room->get_wall_tiles().begin(); tile_it != room->get_wall_tiles().end(); tile_it++)
         {
               tile = &(*tile_it);
               
               glBegin(GL_QUADS);
                  glNormal3f(tile->nx, tile->ny, tile->nz);
                  glTexCoord2f(0e0, 1e0);
                  glVertex3f(tile->v1x, tile->v1y, tile->v1z);
                  glTexCoord2f(1e0, 1e0);
                  glVertex3f(tile->v2x, tile->v2y, tile->v2z);
                  glTexCoord2f(1e0, 0e0);
                  glVertex3f(tile->v3x, tile->v3y, tile->v3z);
                  glTexCoord2f(0e0, 0e0);
                  glVertex3f(tile->v4x, tile->v4y, tile->v4z);
               glEnd();
         }
         
         // draw wall-tops:
         glColor3f(0.0, 0.0, 0.0);
         set_material_ambi(0.0, 0.0, 0.0, 1.0);
         set_material_diff(0.0, 0.0, 0.0, 1.0);
         set_material_spec(0.0, 0.0, 0.0, 1.0);
         for (std::vector<Tile>::iterator tile_it = room->get_wall_top_tiles().begin(); tile_it != room->get_wall_top_tiles().end(); tile_it++)
         {
               tile = &(*tile_it);
               
               glBegin(GL_QUADS);
                  glNormal3f(tile->nx, tile->ny, tile->nz);
                  glVertex3f(tile->v1x, tile->v1y, tile->v1z);
                  glVertex3f(tile->v2x, tile->v2y, tile->v2z);
                  glVertex3f(tile->v3x, tile->v3y, tile->v3z);
                  glVertex3f(tile->v4x, tile->v4y, tile->v4z);
               glEnd();
         }
         
         // draw door-tops:
         glColor3f(1.0, 0.0, 0.0);
         set_material_ambi(1.0, 0.0, 0.0, 1.0);
         set_material_diff(1.0, 0.0, 0.0, 1.0);
         set_material_spec(0.0, 0.0, 0.0, 1.0);
         for (std::vector<Tile>::iterator tile_it = room->get_door_top_tiles().begin(); tile_it != room->get_door_top_tiles().end(); tile_it++)
         {
               tile = &(*tile_it);
               
               glBegin(GL_QUADS);
                  glNormal3f(tile->nx, tile->ny, tile->nz);
                  glVertex3f(tile->v1x, tile->v1y, tile->v1z);
                  glVertex3f(tile->v2x, tile->v2y, tile->v2z);
                  glVertex3f(tile->v3x, tile->v3y, tile->v3z);
                  glVertex3f(tile->v4x, tile->v4y, tile->v4z);
               glEnd();
         }
         
         set_material_std();
         for (std::list<Lamp>::iterator lamp_it = room->get_lamps().begin(); lamp_it != room->get_lamps().end(); lamp_it++)
         {
               lamp_it->lampend();
         }
       }
    }
    //~ lights->warn1_off();
}

#define DELTA_P 0.1

void setLightColor(float tang1_x,  float tang1_y,  float tang1_z,
                   float tang2_x,  float tang2_y,  float tang2_z,
                   float normal_x, float normal_y, float normal_z,
                   float position_x, float position_y, float position_z,
                   float quelle_x, float quelle_y, float quelle_z)
{
   quelle_x = position_x - quelle_x;  // vec position - vec quelle - vektor vom licht zur aktuellen position zeigt
   quelle_y = position_y - quelle_y;
   quelle_z = position_z - quelle_z;
   
   GLfloat licht_x = quelle_x*tang1_x  + quelle_y*tang1_y  + quelle_z*tang1_z;
   GLfloat licht_y = quelle_x*tang2_x  + quelle_y*tang2_y  + quelle_z*tang2_z;
   GLfloat licht_z = quelle_x*normal_x + quelle_y*normal_y + quelle_z*normal_z;

   hilf::normieren(licht_x, licht_y, licht_z);

   licht_x *= 0.5; licht_x += 0.5;
   licht_y *= 0.5; licht_y += 0.5;
   licht_z *= 0.5; licht_z += 0.5;
//    licht_z *= 0.25; licht_z += 0.75;

   glColor3f(licht_x, licht_y, licht_z);
//    std::cout << "licht:  " << licht_x << ",  " << licht_y << ",  " << licht_z << std::endl;
}

void Openglwidget::zeichne_district_outside(District& district)
{
   District& active_district = *station->get_active_district();
   
   glLoadName(district.objekt_id);
   lights->kamera_on();
   lights->sonne_on();
   
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
   
   // cut of the active districts hull right above the first deck:
   // (this only works for the first deck in the district)
   if (station->get_active_district() != NULL && &district == &active_district) {
      r_min = district.get_decks()[0].get_radius() - 2;
   }
   
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
   
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // 
   
   glDisable(GL_BLEND);
      
   glActiveTexture(GL_TEXTURE0);
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, normalmaps->get_id("district-hull"));
   glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);
   glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB, GL_DOT3_RGB) ;
   glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE0_RGB, GL_PRIMARY_COLOR) ;
   glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE1_RGB, GL_TEXTURE) ;

   glActiveTexture(GL_TEXTURE1);
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, textures->get_id("district-hull"));
   glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // 

   // phi_min:
   // do not draw, if district is circular:
   if (!district.is_circular()) {
      glBegin(GL_QUADS);
            glNormal3f(sinp1, -cosp1, 0.0);
         glVertex3f(x1, y1, z_min);
         glVertex3f(x1, y1, z_max);
         glVertex3f(x2, y2, z_max);
         glVertex3f(x2, y2, z_min);
      glEnd();
      
      //~ glBegin(GL_QUADS);
            //~ glNormal3f(-sinp1, cosp1, 0.0);
         //~ glVertex3f(x2, y2, z_min);
         //~ glVertex3f(x2, y2, z_max);
         //~ glVertex3f(x1, y1, z_max);
         //~ glVertex3f(x1, y1, z_min);
      //~ glEnd();
   }
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
         // z_min:
            glNormal3f(0.0, 0.0, -1.0);
         glVertex3f(x3, y3, z_min);
         glVertex3f(x1, y1, z_min);
         glVertex3f(x2, y2, z_min);
         glVertex3f(x4, y4, z_min);
         
         // district outer hull:
setLightColor(0.0, 0.0, 1.0,    sinp1, -cosp1, 0.0,    cosp1, sinp1, 0.0,   10000*cos(-district.get_angle()*RAD), 10000*sin(-district.get_angle()*RAD), 0, x4, y4, z_min);
            glNormal3f(cosp1, sinp1, 0.0);
         glMultiTexCoord2fARB(GL_TEXTURE0, texcoord_x1, texcoord_y2);
         glMultiTexCoord2fARB(GL_TEXTURE1, texcoord_x1, texcoord_y2);
//          glTexCoord2f(texcoord_x1, texcoord_y1);
            glVertex3f(x4, y4, z_min);
            
setLightColor(0.0, 0.0, 1.0,    sinp2, -cosp2, 0.0,    cosp2, sinp2, 0.0,   10000*cos(-district.get_angle()*RAD), 10000*sin(-district.get_angle()*RAD), 0, x2, y2, z_min);
            glNormal3f(cosp2, sinp2, 0.0);
         glMultiTexCoord2fARB(GL_TEXTURE0, texcoord_x1, texcoord_y1);
         glMultiTexCoord2fARB(GL_TEXTURE1, texcoord_x1, texcoord_y1);
//          glTexCoord2f(texcoord_x1, texcoord_y2);
            glVertex3f(x2, y2, z_min);
            
setLightColor(0.0, 0.0, 1.0,    sinp2, -cosp2, 0.0,    cosp2, sinp2, 0.0,   10000*cos(-district.get_angle()*RAD), 10000*sin(-district.get_angle()*RAD), 0, x2, y2, z_max);
         glMultiTexCoord2fARB(GL_TEXTURE0, texcoord_x2, texcoord_y1);
         glMultiTexCoord2fARB(GL_TEXTURE1, texcoord_x2, texcoord_y1);
//          glTexCoord2f(texcoord_x2, texcoord_y2);   
            glVertex3f(x2, y2, z_max);
            
setLightColor(0.0, 0.0, 1.0,    sinp1, -cosp1, 0.0,    cosp1, sinp1, 0.0,   10000*cos(-district.get_angle()*RAD), 10000*sin(-district.get_angle()*RAD), 0, x4, y4, z_max);
            glNormal3f(cosp1, sinp1, 0.0);
         glMultiTexCoord2fARB(GL_TEXTURE0, texcoord_x2, texcoord_y2);
         glMultiTexCoord2fARB(GL_TEXTURE1, texcoord_x2, texcoord_y2);
//          glTexCoord2f(texcoord_x2, texcoord_y1);   
            glVertex3f(x4, y4, z_max);
         
         // z_max:
            glNormal3f(0.0, 0.0, 1.0);
         glVertex3f(x4, y4, z_max);
         glVertex3f(x2, y2, z_max);
         glVertex3f(x1, y1, z_max);
         glVertex3f(x3, y3, z_max);
         
         // district inner hull:
         // do not draw, if district is active:
         if (station->get_active_district() == NULL || &district != &active_district) {
            
setLightColor(0.0, 0.0, 1.0,    sinp1, -cosp1, 0.0,    -cosp1, -sinp1, 0.0,   10000*cos(-district.get_angle()*RAD), 10000*sin(-district.get_angle()*RAD), 0, x3, y3, z_max);
                glNormal3f(-cosp1, -sinp1, 0.0);
         glMultiTexCoord2fARB(GL_TEXTURE0, texcoord_x1, texcoord_y1);
         glMultiTexCoord2fARB(GL_TEXTURE1, texcoord_x1, texcoord_y1);
//              glTexCoord2f(texcoord_x1, texcoord_y1);   
                glVertex3f(x3, y3, z_max);
                
setLightColor(0.0, 0.0, 1.0,    sinp2, -cosp2, 0.0,    -cosp2, -sinp2, 0.0,   10000*cos(-district.get_angle()*RAD), 10000*sin(-district.get_angle()*RAD), 0, x1, y1, z_max);
                glNormal3f(-cosp2, -sinp2, 0.0);
         glMultiTexCoord2fARB(GL_TEXTURE0, texcoord_x1, texcoord_y2);
         glMultiTexCoord2fARB(GL_TEXTURE1, texcoord_x1, texcoord_y2);
//              glTexCoord2f(texcoord_x1, texcoord_y2);
                glVertex3f(x1, y1, z_max);
                
         glMultiTexCoord2fARB(GL_TEXTURE0, texcoord_x2, texcoord_y2);
         glMultiTexCoord2fARB(GL_TEXTURE1, texcoord_x2, texcoord_y2);
//              glTexCoord2f(texcoord_x2, texcoord_y2);   
                glVertex3f(x1, y1, z_min);
                
setLightColor(0.0, 0.0, 1.0,    sinp1, -cosp1, 0.0,    -cosp1, -sinp1, 0.0,   10000*cos(-district.get_angle()*RAD), 10000*sin(-district.get_angle()*RAD), 0, x3, y3, z_min);
                glNormal3f(-cosp1, -sinp1, 0.0);
         glMultiTexCoord2fARB(GL_TEXTURE0, texcoord_x2, texcoord_y1);
         glMultiTexCoord2fARB(GL_TEXTURE1, texcoord_x2, texcoord_y1);
//              glTexCoord2f(texcoord_x2, texcoord_y1);   
                glVertex3f(x3, y3, z_min);
         }
      glEnd();
      
      x1 = x3; y1 = y3;
      x2 = x4; y2 = y4;
   }
   
   cosp1 = cos(p_max);
   sinp1 = sin(p_max);
   
   // phi_max:
   // do not draw, if district is circular:
   if (!district.is_circular()) {
      //~ glBegin(GL_QUADS);
            //~ glNormal3f(sinp1, -cosp1, 0.0);
         //~ glVertex3f(x1, y1, z_min);
         //~ glVertex3f(x1, y1, z_max);
         //~ glVertex3f(x2, y2, z_max);
         //~ glVertex3f(x2, y2, z_min);
      //~ glEnd();
      
      glBegin(GL_QUADS);
            glNormal3f(-sinp1, cosp1, 0.0);
         glVertex3f(x2, y2, z_min);
         glVertex3f(x2, y2, z_max);
         glVertex3f(x1, y1, z_max);
         glVertex3f(x1, y1, z_min);
      glEnd();
   }
   
// // // // // // // // // // // // // // // // // // // //    
   
//    glDisable(GL_REGISTER_COMBINERS_NV);
   glActiveTextureARB(GL_TEXTURE1); // Texturen leeren
   glBindTexture(GL_TEXTURE_2D, 0);
   glActiveTexture(GL_TEXTURE0);
   glBindTexture(GL_TEXTURE_2D, 0);
   glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
   glEnable(GL_BLEND);
   set_material_std();
}




