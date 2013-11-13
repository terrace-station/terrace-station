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
            handle_mousebuttondown(event.button);
            break;
         
         case SDL_KEYDOWN:
            handle_keydown(event.key.keysym);
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
         running = false;
         break;
         
      case SDLK_SPACE:
         break;
         
      default:
         break;
         
      case SDLK_PLUS:
         zoom_soll = zoom_soll*0.98;
         if (zoom_soll < 0.1) zoom_soll = 0.1;
         break;
         
#define ZOOM_CAP 5
         
      case '-' :
         zoom_soll = zoom_soll*1.02;
         if (zoom_soll > ZOOM_CAP) zoom_soll = ZOOM_CAP;
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



#define UNIT 1.0
         
      case SDLK_UP:
         pos_z_soll += UNIT;
         break;

      case SDLK_DOWN: // ...nach unten...
         pos_z_soll -= UNIT;
         break;

      case SDLK_LEFT:
         phi_soll += 5;
         if (phi_soll > 360)
         {
            phi -= 360; 
            phi_soll -= 360; 
         }
         break;

      case SDLK_RIGHT:
         phi_soll -= 5;
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
         
         
//             case FL_F+1 :
//                if(!antialiasing)
//                {
//                   mode(FL_RGB | FL_DEPTH | FL_MULTISAMPLE | FL_DOUBLE);
//                   glEnable(GL_MULTISAMPLE);
//                   antialiasing = true;
//                }
//                else
//                {
//                   mode(FL_RGB | FL_DEPTH | FL_DOUBLE);
//                   glDisable(GL_MULTISAMPLE);
//                   antialiasing = false;
//                }
//                
//                redraw();
//                return 1;
//     //
//     //         case FL_F+2 : // Nur die y-Komponente des E-Feldes wird angezeigt.
//     //           monitor->feld_num=1;
//     //           redraw();
//     //           return 1;
         
   }
}


void Openglwidget::handle_mousebuttondown(SDL_MouseButtonEvent& button)
{
   switch(button.button)
   {
      case SDL_BUTTON_LEFT:
         selektiere_id();
         selektiere_pos();
         std::cout << "Objekt getroffen, id: " << target_id << ", bei (" << target_x << ", " << target_y << ", " << target_z << ")" << std::endl;
         set_view_to(get_target());
         break;
         
      case SDL_BUTTON_RIGHT:
         break;
         
      case SDL_BUTTON_WHEELUP:
         zoom_soll -= zoom_soll*0.15;
         if (zoom_soll < 0.1) zoom_soll = 0.1;
         break;

      case SDL_BUTTON_WHEELDOWN:
         zoom_soll += zoom_soll*0.15;
         if (zoom_soll > ZOOM_CAP) zoom_soll = ZOOM_CAP;
         break;
   }
}