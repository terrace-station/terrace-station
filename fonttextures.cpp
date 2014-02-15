#include "fonttextures.hh"
#include "log.hh"

#define FONTS_DIR "fonts"
#define DEFAULT_FONT_LABEL "Overhaul"

std::set<std::string> Fonttextures::valid_extensions = {"ttf", "TTF"};

Fonttextures::Fonttextures()
{
    load_fonts();
}

GLuint Fonttextures::get_id(std::string text, std::string label, std::string font, unsigned char r, unsigned char g, unsigned char b)
{
    if (texture_ids.count(label))
    {
        return texture_ids[label];
    } else 
    {
        SDL_Color color = {b, g, r, 150};
        SDL_Surface *surface = TTF_RenderText_Blended(get_font(font), text.c_str(), color);
        GLuint texture_id;
        int mode = GL_RGBA;
        glGenTextures(1, &texture_id);
        glBindTexture(GL_TEXTURE_2D, texture_id);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    //       glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    //       glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //       gluBuild2DMipmaps(GL_TEXTURE_2D, mode, surface->w, surface->h, mode, GL_UNSIGNED_BYTE, surface->pixels);
        glTexImage2D(GL_TEXTURE_2D, 0, mode, surface->w, surface->h, 0, mode, GL_UNSIGNED_BYTE, surface->pixels);
        glBindTexture(GL_TEXTURE_2D, 0);
        SDL_FreeSurface(surface);
        texture_ids[label] = texture_id;
        return texture_id;
   }
}


void Fonttextures::load_id(std::string text, std::string label, std::string font, unsigned char r, unsigned char g, unsigned char b)
{
    if (texture_ids.count(label))
    {
        return;
    } else 
    {
        SDL_Color color = {b, g, r, 150};
        SDL_Surface *surface = TTF_RenderText_Blended(get_font(font), text.c_str(), color);
        GLuint texture_id;
        int mode = GL_RGBA;
        glGenTextures(1, &texture_id);
        glBindTexture(GL_TEXTURE_2D, texture_id);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    //       glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    //       glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //       gluBuild2DMipmaps(GL_TEXTURE_2D, mode, surface->w, surface->h, mode, GL_UNSIGNED_BYTE, surface->pixels);
        glTexImage2D(GL_TEXTURE_2D, 0, mode, surface->w, surface->h, 0, mode, GL_UNSIGNED_BYTE, surface->pixels);
        glBindTexture(GL_TEXTURE_2D, 0);
        SDL_FreeSurface(surface);
        texture_ids[label] = texture_id;
    }
}


GLuint Fonttextures::get_id(std::string label)
{
   if (texture_ids.count(label))
   {
      return texture_ids[label];
   }
   else
       return get_id("Error", "default", DEFAULT_FONT_LABEL, 100, 100, 100);
}


TTF_Font* Fonttextures::get_font(std::string label)
{
   if (font_ids.count(label))
   {
      return font_ids[label];
   } else 
   {
      LOG(WARNING)  << "Font '" << label << "' not found. Using font '" << DEFAULT_FONT_LABEL << "' instead.";
      return font_ids[DEFAULT_FONT_LABEL];
   }
}

void Fonttextures::load_fonts()
{
    LOG(INFO) << "Loading fonts ...";
    std::string label, filepath, ext;
    int delim;
    DIR *dir;
    struct dirent *ent;
    dir = opendir (FONTS_DIR);
    while ((ent = readdir (dir)) != NULL) {
        std::stringstream ss;
        ss << FONTS_DIR << "/" << ent->d_name;
        filepath = ss.str();
        label = ent->d_name;
        delim = label.find_last_of(".");
        ext = label.substr(delim + 1);
        label = label.substr(0, delim);
        if (valid_extensions.count(ext) == 1) 
        {
            LOG(DEBUG) << "Loading font '" << label << "' from file '" << filepath << "' ...";
            TTF_Font* font = TTF_OpenFont(filepath.c_str(), 100);
            font_ids[label] = font;
        } else 
        {
            LOG(DEBUG) << "Skipping '" << filepath << "'";
        }
    }
    closedir (dir);
    IMG_Quit();
}

void Fonttextures::text_rendern_m(std::string text, std::string label, float hoehe, std::string font, unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255)
{
   float breite, x, y;
   GLfloat breite_tex, hoehe_tex;
   glBindTexture(GL_TEXTURE_2D, get_id(text, label, font, r, g, b));
   glGetTexLevelParameterfv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &breite_tex);
   glGetTexLevelParameterfv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &hoehe_tex);   //    glBindTexture(GL_TEXTURE_2D, textures->get_id("Test"));
   breite = hoehe*breite_tex/hoehe_tex;
   x = breite*0.5;
   y = hoehe*0.5;
   glColor4f(1.0, 1.0, 1.0, a/float(255));
   glBegin(GL_QUADS);
      glNormal3f(0.0, 0.0, 1.0);
      glTexCoord2f(0.0, 0.0); glVertex3f(-x, y, 0.0);
      glTexCoord2f(0.99, 0.0); glVertex3f( x, y, 0.0);
      glTexCoord2f(0.99, 0.99); glVertex3f( x,-y, 0.0);
      glTexCoord2f(0.0,  0.99); glVertex3f(-x,-y, 0.0);
   glEnd();
   glBindTexture(GL_TEXTURE_2D, 0);
}
   

void Fonttextures::text_rendern_m(std::string label, float hoehe, unsigned char a)
{
   float breite, x, y;
   GLfloat breite_tex, hoehe_tex;
   glBindTexture(GL_TEXTURE_2D, get_id(label));
   glGetTexLevelParameterfv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &breite_tex);
   glGetTexLevelParameterfv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &hoehe_tex);   //    glBindTexture(GL_TEXTURE_2D, textures->get_id("Test"));
   breite = hoehe*breite_tex/hoehe_tex;
   x = breite*0.5;
   y = hoehe*0.5;
   glColor4f(1.0, 1.0, 1.0, a/float(255));
   glBegin(GL_QUADS);
      glNormal3f(0.0, 0.0, 1.0);
      glTexCoord2f(0.0, 0.0); glVertex3f(-x, y, 0.0);
      glTexCoord2f(0.99, 0.0); glVertex3f( x, y, 0.0);
      glTexCoord2f(0.99, 0.99); glVertex3f( x,-y, 0.0);
      glTexCoord2f(0.0,  0.99); glVertex3f(-x,-y, 0.0);
   glEnd();
   glBindTexture(GL_TEXTURE_2D, 0);
}
   
