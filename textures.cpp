#include "textures.hh"

#define TEXTURES_DIR "textures"

std::set<std::string> Textures::valid_extensions = {"png", "jpg", "jpeg",
                                                    "PNG", "JPG", "JPEG"};

Textures::Textures()
{
    load();
}

GLuint Textures::get_id(std::string label)
{
    if (texture_ids.count(label)) {
        return texture_ids[label];
    } else {
        return texture_ids["error"];
    }
}

void Textures::load()
{
    std::cout << std::endl << "Loading Textures" << std::endl << "================" << std::endl;
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
        if (valid_extensions.count(ext) == 1) {
            std::cout << "Loading texture '" << label << "' from file '" << filepath << "' ...";
            GLuint texture_id;
            SDL_Surface* surface = IMG_Load(filepath.c_str());
            int mode, source_mode;
            if (surface->format->BytesPerPixel == 3) {
                mode = GL_RGB;
            } else if (surface->format->BytesPerPixel == 4) {
                mode = GL_RGBA;
            } else {
                SDL_FreeSurface(surface);
                std::cout << "Skipping '" << filepath << "' (unknown mode)" << std::endl;
            }
            glGenTextures(1, &texture_id);
            glBindTexture(GL_TEXTURE_2D, texture_id);
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
            glTexImage2D(GL_TEXTURE_2D, 0, mode, surface->w, surface->h, 0, mode, GL_UNSIGNED_BYTE, surface->pixels);
            glBindTexture(GL_TEXTURE_2D, 0);
            SDL_FreeSurface(surface);
            texture_ids[label] = texture_id;
            std::cout << " done." << std::endl;
        } else {
            std::cout << "Skipping '" << filepath << "'" << std::endl;
        }
    }
    closedir (dir);
    IMG_Quit();
}
