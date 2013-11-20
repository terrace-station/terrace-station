#include "fonttextures.hh"

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
      SDL_Color color = {r, g, b, 0};
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


TTF_Font* Fonttextures::get_font(std::string label)
{
   if (font_ids.count(label))
   {
      return font_ids[label];
   } else 
   {
      std::cout << "Font '" << label << "' not found. Using font '" << DEFAULT_FONT_LABEL << "' instead." << std::endl;
      return font_ids[DEFAULT_FONT_LABEL];
   }
}

void Fonttextures::load_fonts()
{
//     std::cout << std::endl << "Loading Fonts ..." << std::endl;
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
            std::cout << "Loading Font '" << label << "' from file '" << filepath << "' ...";
            TTF_Font* font = TTF_OpenFont(filepath.c_str(), 100);
            font_ids[label] = font;
            std::cout << " done." << std::endl;
        } else 
        {
            std::cout << "Skipping '" << filepath << "'" << std::endl;
        }
    }
    closedir (dir);
    IMG_Quit();
}
