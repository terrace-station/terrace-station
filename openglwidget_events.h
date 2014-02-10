void music_start();

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
#define ZOOM_CAP_MAX 20
         
      case SDLK_PLUS:
         zoom_soll = zoom_soll*0.98;
         if (zoom_soll < ZOOM_CAP_MIN) zoom_soll = ZOOM_CAP_MIN;
         break;

      case '-' :
         zoom_soll = zoom_soll*1.02;
         if (zoom_soll > ZOOM_CAP_MAX) zoom_soll = ZOOM_CAP_MAX;
         break;
         
      case 'a' :
         phi_soll   -= sin(psi*RAD)*0.5/pos_radius*GRAD;
         pos_z_soll += cos(psi*RAD)*0.5;
         if (phi_soll > 360)
         {
            phi -= 360; 
            phi_soll -= 360; 
         }
         break;

      case 'd' : // ...nach rechts...
         phi_soll   += sin(psi*RAD)*0.5/pos_radius*GRAD;
         pos_z_soll -= cos(psi*RAD)*0.5;
         if (phi_soll < 0)
         {
            phi += 360; 
            phi_soll += 360; 
         }
         break;

      case 'w' : // ...nach oben...
         phi_soll   -= cos(psi*RAD)*0.5/pos_radius*GRAD;
         pos_z_soll -= sin(psi*RAD)*0.5;
         if (phi_soll > 360)
         {
            phi -= 360; 
            phi_soll -= 360; 
         }
         break;

      case 's' : // ...nach unten
         phi_soll   += cos(psi*RAD)*0.5/pos_radius*GRAD;
         pos_z_soll += sin(psi*RAD)*0.5;
         if (phi_soll > 360)
         {
            phi -= 360; 
            phi_soll -= 360; 
         }
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
         theta_soll += 1.5;
         if (theta_soll > 90)
         {
            theta_soll = 90;
         }
         break;

      case SDLK_DOWN: // ...nach unten...
         theta_soll -= 1.5;
         if (theta_soll < 0)
         {
            theta_soll = 0.01;
         }
         break;

      case SDLK_LEFT:
         psi_soll -= 1.5;
         if (psi_soll < 0)
         {
            psi_soll += 360;
            psi += 360;
         }
         break;

      case SDLK_RIGHT:
         psi_soll += 1.5;
         if (psi_soll > 360)
         {
            psi_soll -= 360;
            psi -= 360;
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

        case SDLK_F3:
            if (station->get_active_district() != NULL) {
                station->get_active_district()->set_alarm(!station->get_active_district()->get_alarm());
            }
            break;

        case SDLK_m:
            audio->music_toggle_mute();
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
         LOG(DEBUG) << "Objekt getroffen, id: " << target_id << ", bei (" << target_x << ", " << target_y << ", " << target_z << ")";
         interact_with(get_target(), button);
         break;
         
      case SDL_BUTTON_WHEELUP:
         zoom_soll -= zoom_soll*0.15;
         if (zoom_soll < ZOOM_CAP_MIN) zoom_soll = ZOOM_CAP_MIN;
         break;

      case SDL_BUTTON_WHEELDOWN:
         zoom_soll += zoom_soll*0.15;
         if (zoom_soll > ZOOM_CAP_MAX) zoom_soll = ZOOM_CAP_MAX;
         if (station->active_district != NULL && zoom_soll > 0.8*ZOOM_CAP_MAX)
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
         LOG(DEBUG) << "Objekt getroffen, id: " << target_id << ", bei (" << target_x << ", " << target_y << ", " << target_z << ")";
         interact_with(get_target(), button);
         break;
         
      case SDL_BUTTON_RIGHT:
         break;
   }
}
