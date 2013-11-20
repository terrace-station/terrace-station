#ifndef FONTTEXTURES_HH
#define FONTTEXTURES_HH

#include <sstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <dirent.h>
#include <set>

#include <GL/glu.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

class Fonttextures
{
    static std::set<std::string> valid_extensions;
    
    std::unordered_map<std::string, TTF_Font*> font_ids;
    std::unordered_map<std::string, GLuint> texture_ids;
    
    void load_fonts();

public:
    GLuint get_id(std::string text, std::string label, std::string font, unsigned char r,  unsigned char g,  unsigned char b);
    TTF_Font* get_font(std::string label);
    void text_rendern_m(std::string text, std::string label, float hoehe, std::string font, unsigned char r, unsigned char g, unsigned char b, unsigned char a);
    
    Fonttextures();
};


#endif
