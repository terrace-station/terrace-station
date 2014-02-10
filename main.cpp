#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <omp.h>

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include "log.hh"
#include "openglwidget.hh"
#include "tile.hh"
#include "rect.hh"
#include "door.hh"
#include "room.hh"
#include "deck.hh"
#include "district.hh"
#include "zone.hh"
#include "station.hh"

int main(int argc, char* argv[])
{
    // initialize logging:
    Log::init(DEBUG, "dis.log", DEBUG);
    
    LOG(INFO) << "Starting program.";
    
    srand (2);
    //~ srand (time(NULL));
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    TTF_Init();

    Openglwidget glwidget(800, 600);

    Station station1;
    glwidget.set_station(&station1);

    const SDL_VideoInfo* info = SDL_GetVideoInfo();

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    //    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    //    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

    SDL_SetVideoMode(glwidget.fenster_breite, glwidget.fenster_hoehe, glwidget.bpp, SDL_OPENGL);

    SDL_EnableKeyRepeat(20, 20);
    glwidget.initialisiere_gl();
    
    omp_set_num_threads(2);
//     #pragma omp parallel
    {
        while(glwidget.running)
        {
//             #pragma omp master
//             {
               glwidget.events();
               glwidget.draw();
//             }
//             #pragma omp single nowait
//             {
               // Hier kommt dann anderer Kram rein, der nichts mit der Oberfläche zu tun hat
//             }
        }
    }

    LOG(INFO) << "Quitting program.";
    return 0;
}
