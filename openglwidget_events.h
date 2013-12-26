void Openglwidget::events()
{
   while(SDL_PollEvent(&event)) 
   {
      switch( event.type ) 
      {
//          case SDL_MOUSEMOTION:
//             handle_mousemotion
//             break;
//             
         case SDL_MOUSEBUTTONDOWN:
            if (!gamemenu)
               handle_mousebuttondown(event.button);
            else
               handle_mousebuttondown_menu(event.button);
            break;
         
         case SDL_KEYDOWN:
            if (!gamemenu)
               handle_keydown(event.key.keysym);
            else
               handle_keydown_menu(event.key.keysym);
            break;
            
         case SDL_QUIT:
            running = false;
            break;
        }
    }
}


void Openglwidget::handle_keydown(SDL_keysym& keysym)
{
   switch( keysym.sym )
   {
      case SDLK_ESCAPE:
         if(!gamemenu)
         {
            gamemenu = true;
            menu_bg_soll = 1.0;
            SDL_EnableKeyRepeat(0, 20);
         }
         else
         {
            gamemenu = false;
            menu_bg_soll = 0.0;
            menu_bg      = 0.0;
            SDL_EnableKeyRepeat(20, 20);
         }
         
//          running = false;
         break;
         
      case SDLK_SPACE:
         break;
         
      default:
         break;
         
#define ZOOM_CAP_MIN 0.001
#define ZOOM_CAP_MAX 10
         
      case SDLK_PLUS:
         zoom_soll = zoom_soll*0.98;
         if (zoom_soll < ZOOM_CAP_MIN) zoom_soll = ZOOM_CAP_MIN;
         break;

      case '-' :
         zoom_soll = zoom_soll*1.02;
         if (zoom_soll > ZOOM_CAP_MAX) zoom_soll = ZOOM_CAP_MAX;
         break;
         
      case 'a' : // Die Kamera bewegt sich "nach links" (An der Blickrichtung orientiert)
         y_offset -= 0.25;
         break;

      case 'd' : // ...nach rechts...
         y_offset += 0.25;
         break;

      case 'w' : // ...nach oben...
         x_offset += 0.25;
         break;

      case 's' : // ...nach unten
         x_offset -= 0.25;
         break;

      case 'q' : // ...nach unten...
         z_offset -= 0.25;
         break;

      case 'e' : // ...nach oben
         z_offset += 0.25;
         break;
         
      case 'f' : // fullscreen
         toggle_fullscreen();
         break;



#define Z_UNIT 1.5
         
      case SDLK_UP:
         pos_z_soll += Z_UNIT;
         break;

      case SDLK_DOWN: // ...nach unten...
         pos_z_soll -= Z_UNIT;
         break;

      case SDLK_LEFT:
         phi_soll += 1.5;
         if (phi_soll > 360)
         {
            phi -= 360; 
            phi_soll -= 360; 
         }
         break;

      case SDLK_RIGHT:
         phi_soll -= 1.5;
         if (phi_soll < 0)
         {
            phi += 360; 
            phi_soll += 360; 
         }
         break;

      case SDLK_PAGEUP:
         theta_soll += 1;
         if (theta_soll > 90)
         {
            theta_soll = 90;
         }
         break;

      case SDLK_PAGEDOWN:
         theta_soll -= 1;
         if (theta_soll < 10)
         {
            theta_soll = 10; 
         }
         break;
         
         
      case SDLK_F1 :
         toggle_antialiasing();
         break;
   }
}


void Openglwidget::handle_keydown_menu(SDL_keysym& keysym)
{
   switch( keysym.sym )
   {
      case SDLK_ESCAPE:
         if(!gamemenu)
         {
            gamemenu = true;
            menu_bg_soll = 1.0;
            SDL_EnableKeyRepeat(0, 20);
         }
         else
         {
            gamemenu = false;
            menu_bg_soll = 0.0;
            menu_bg      = 0.0;
            SDL_EnableKeyRepeat(20, 20);
         }
         break;
         
      case SDLK_SPACE:
         break;
         
      case 'f' : // fullscreen
         toggle_fullscreen();
         break;

      case 'q' : // quit
         running = false;
         break;
         
      case SDLK_UP:
         break;

      case SDLK_DOWN: // ...nach unten...
         break;

      case SDLK_LEFT:
         break;

      case SDLK_RIGHT:
         break;
   }
}



void Openglwidget::handle_mousebuttondown(SDL_MouseButtonEvent& button)
{
   switch(button.button)
   {
      case SDL_BUTTON_LEFT:
      case SDL_BUTTON_MIDDLE:
      case SDL_BUTTON_RIGHT:
         selektiere_id();
         selektiere_pos();
         std::cout << "Objekt getroffen, id: " << target_id << ", bei (" << target_x << ", " << target_y << ", " << target_z << ")" << std::endl;
         interact_with(get_target(), button);
         break;
         
      case SDL_BUTTON_WHEELUP:
         zoom_soll -= zoom_soll*0.15;
         if (zoom_soll < ZOOM_CAP_MIN) zoom_soll = ZOOM_CAP_MIN;
         break;

      case SDL_BUTTON_WHEELDOWN:
         zoom_soll += zoom_soll*0.15;
         if (zoom_soll > ZOOM_CAP_MAX) zoom_soll = ZOOM_CAP_MAX;
         if (station->active_district != NULL && zoom_soll > 0.5*ZOOM_CAP_MAX)
         {
            phi_soll += station->active_district->get_angle();
            phi = phi_soll;
            station->set_active_district(NULL);
         }
         break;
   }
}


void Openglwidget::handle_mousebuttondown_menu(SDL_MouseButtonEvent& button)
{
   switch(button.button)
   {
      case SDL_BUTTON_LEFT:
         selektiere_id();
         selektiere_pos();
         std::cout << "Objekt getroffen, id: " << target_id << ", bei (" << target_x << ", " << target_y << ", " << target_z << ")" << std::endl;
         interact_with(get_target(), button);
         break;
         
      case SDL_BUTTON_RIGHT:
         break;
   }
}
