#include "textures.hh"

#define TEXTURES_DIR "textures";

TextureCollection::TextureCollection()
{
    load();
}

GLuint TextureCollection::get_id(std::string label)
{
    return texture_ids[label];
}

void TextureCollection::load()
{
    std::string filepath = "TEXTURES_DIRfloor-room.png";
    std::string label = "floor-room";
    GLuint texture_id;
    
    std::cout << "Loading texture '" << filepath << "' ...";
    
    SDL_Surface* surface = IMG_Load(filepath.c_str());
    
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGB, GL_UNSIGNED_BYTE, surface->pixels);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    SDL_FreeSurface(surface);
    
    texture_ids[label] = texture_id;
    
    std::cout << "done." << std::endl;
    
}
