#ifndef MODELS_HH
#define MODELS_HH

#include <sstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <dirent.h>
#include <set>

#include <GL/glu.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "modell.hh"

class Models
{
   std::string pfad;
   
    static std::set<std::string> valid_extensions;
    
    std::unordered_map<std::string, Modell*> models;
    
    void load();

public:
    Models(std::string pfad);
    
    Modell* get(std::string label);
};

#endif
