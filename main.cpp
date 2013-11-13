#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include "openglwidget.hh"


int main(int argc, char* argv[])
{
   srand (time(NULL));
   Openglwidget glwidget(1024,768);
   
   Station station1;
   station1.text_ausgabe();
   glwidget.set_station(&station1);
   
   SDL_Init(SDL_INIT_VIDEO);

   const SDL_VideoInfo* info = SDL_GetVideoInfo( );
   
   int bpp = info->vfmt->BitsPerPixel;
   std::cout << "bpp: " << bpp << std::endl;

   SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
   SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
   SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
   
   SDL_SetVideoMode(glwidget.fenster_breite, glwidget.fenster_hoehe, bpp, SDL_OPENGL);
   
   SDL_EnableKeyRepeat(200, 10);
   glwidget.tex->texturen_laden();
   glwidget.initialisiere_gl();

   while(glwidget.running)
   {
      glwidget.events();
      glwidget.draw();
   }

   return 0;
}