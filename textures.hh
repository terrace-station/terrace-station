#ifndef TEXTURES_HH
#define TEXTURES_HH

#include <iostream>
#include <string>
#include <map>

#include <GL/glu.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

class TextureCollection
{
    std::map<std::string, GLuint> texture_ids;
    
public:
    TextureCollection();
    
    GLuint get_id(std::string label);
    
    void load();
};

#endif
