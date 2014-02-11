void music_start();

void limit_value(float& wert, float& wert_min, float& wert_max)
{
    if (wert > wert_max)
        wert = wert_max;
    else if (wert < wert_min)
        wert = wert_min;
}

void limit_angle(float& wert, float& wert_min, float& wert_max)
{
    if (wert > wert_max)
        wert = wert_max;
    else if (wert > 360)
        wert -= 360; 
    else if (wert < wert_min)
        wert = wert_min;
    else if (wert < -360)
        wert += 360;
}

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
        active_cam->zoom = active_cam->zoom*0.98;
        limit_value(active_cam->zoom, active_cam->zoom_min, active_cam->zoom_max);
        break;

      case '-' :
        active_cam->zoom = active_cam->zoom*1.02;
        limit_value(active_cam->zoom, active_cam->zoom_min, active_cam->zoom_max);
        break;
         
      case 'a' :
        active_cam->phi   -= sin(active_cam->psi*RAD)*0.5/active_cam->radius*GRAD;
        active_cam->z     += cos(active_cam->psi*RAD)*0.5;
        limit_angle(active_cam->phi, active_cam->phi_min, active_cam->phi_max);
        limit_value(active_cam->z, active_cam->z_min, active_cam->z_max);
        break;

      case 'd' : // ...nach rechts...
        active_cam->phi += sin(active_cam->psi*RAD)*0.5/active_cam->radius*GRAD;
        active_cam->z   -= cos(active_cam->psi*RAD)*0.5;
        limit_angle(active_cam->phi, active_cam->phi_min, active_cam->phi_max);
        limit_value(active_cam->z, active_cam->z_min, active_cam->z_max);
        break;

      case 'w' : // ...nach oben...
        active_cam->phi -= cos(active_cam->psi*RAD)*0.5/active_cam->radius*GRAD;
        active_cam->z   -= sin(active_cam->psi*RAD)*0.5;
        limit_angle(active_cam->phi, active_cam->phi_min, active_cam->phi_max);
        limit_value(active_cam->z, active_cam->z_min, active_cam->z_max);
        break;

      case 's' : // ...nach unten
        active_cam->phi += cos(active_cam->psi*RAD)*0.5/active_cam->radius*GRAD;
        active_cam->z   += sin(active_cam->psi*RAD)*0.5;
        limit_angle(active_cam->phi, active_cam->phi_min, active_cam->phi_max);
        limit_value(active_cam->z, active_cam->z_min, active_cam->z_max);
        break;

      case 'q' : // district verlassen
        if (station->active_district != NULL)
        {
            std_cam.phi = active_cam->phi + station->active_district->get_angle();
            station->set_active_district(NULL);
            active_cam  = &std_cam;
        }
        break;

      case 'e' : // ...nach oben
         break;
         
      case 'f' : // fullscreen
         toggle_fullscreen();
         break;



#define Z_UNIT 1.5
         
    case SDLK_UP:
        active_cam->theta += 1.5;
        limit_angle(active_cam->theta, active_cam->theta_min, active_cam->theta_max);
        break;

    case SDLK_DOWN: // ...nach unten...
        active_cam->theta -= 1.5;
        limit_angle(active_cam->theta, active_cam->theta_min, active_cam->theta_max);
        break;

    case SDLK_LEFT:
        active_cam->psi -= 1.5;
        limit_angle(active_cam->psi, active_cam->psi_min, active_cam->psi_max);
        break;

    case SDLK_RIGHT:
        active_cam->psi += 1.5;
        limit_angle(active_cam->psi, active_cam->psi_min, active_cam->psi_max);
        break;

    case SDLK_PAGEUP:
        active_cam->theta += 1;
        limit_angle(active_cam->theta, active_cam->theta_min, active_cam->theta_max);
        break;

    case SDLK_PAGEDOWN:
        active_cam->theta -= 1;
        limit_angle(active_cam->theta, active_cam->theta_min, active_cam->theta_max);
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
        active_cam->zoom -= active_cam->zoom*0.15;
        limit_value(active_cam->zoom, active_cam->zoom_min, active_cam->zoom_max);
        break;

    case SDL_BUTTON_WHEELDOWN:
        active_cam->zoom += active_cam->zoom*0.15;
        limit_value(active_cam->zoom, active_cam->zoom_min, active_cam->zoom_max);
        if (station->active_district != NULL && active_cam->zoom > 0.9*active_cam->zoom_max)
        {
            active_cam->zoom = 0.9*active_cam->zoom_max;
            std_cam.phi = active_cam->phi + station->active_district->get_angle();
            station->set_active_district(NULL);
            active_cam  = &std_cam;
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
