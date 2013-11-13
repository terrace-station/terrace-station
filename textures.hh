#ifndef TEXTURES_HH
#define TEXTURES_HH

#include <sstream>
#include <iostream>
#include <string>
#include <map>
#include <dirent.h>

#include <GL/glu.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

class Textures
{
    std::map<std::string, GLuint> texture_ids;
    
    void load();
public:
    Textures();
    
    GLuint get_id(std::string label);
};

#endif
