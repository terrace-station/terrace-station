#include "textures.hh"

#define TEXTURES_DIR "textures"

Textures::Textures()
{
    load();
}

GLuint Textures::get_id(std::string label)
{
    return texture_ids[label];
}

void Textures::load()
{
    std::string label, filepath, ext;
    int delim;
    DIR *dir;
    struct dirent *ent;
    dir = opendir (TEXTURES_DIR);
    while ((ent = readdir (dir)) != NULL) {
        std::stringstream ss;
        ss << TEXTURES_DIR << "/" << ent->d_name;
        filepath = ss.str();
        label = ent->d_name;
        delim = label.find_last_of(".");
        ext = label.substr(delim + 1);
        label = label.substr(0, delim);
        if (ext == "jpg" || ext == "png" || ext == "bmp") {
            std::cout << "Loading texture " << label << " from file " << filepath << " ...";
            GLuint texture_id;
            SDL_Surface* surface = IMG_Load(filepath.c_str());
            glGenTextures(1, &texture_id);
            glBindTexture(GL_TEXTURE_2D, texture_id);
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, surface->w, surface->h, 0, GL_RGB, GL_UNSIGNED_BYTE, surface->pixels);
            glBindTexture(GL_TEXTURE_2D, 0);
            SDL_FreeSurface(surface);
            texture_ids[label] = texture_id;
            std::cout << " done." << std::endl;
        }
    }
    closedir (dir);
}
