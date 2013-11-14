#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include "openglwidget.hh"
#include "rect.hh"
#include "room.hh"
#include "deck.hh"
#include "district.hh"
#include "zone.hh"
#include "station.hh"



int main(int argc, char* argv[])
{
   srand (time(NULL));
   SDL_Init(SDL_INIT_VIDEO);
   
   Openglwidget glwidget(800, 600);
   
   Station station1;
   std::cout << station1.str();
   glwidget.set_station(&station1);
   
   SDL_Init(SDL_INIT_VIDEO);

   const SDL_VideoInfo* info = SDL_GetVideoInfo( );
   
   SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
   SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
   SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
   
   SDL_SetVideoMode(glwidget.fenster_breite, glwidget.fenster_hoehe, glwidget.bpp, SDL_OPENGL);
   
   SDL_EnableKeyRepeat(20, 20);
   glwidget.tex->texturen_laden();
   glwidget.initialisiere_gl();

   while(glwidget.running)
   {
      glwidget.events();
      glwidget.draw();
   }

   return 0;
}
