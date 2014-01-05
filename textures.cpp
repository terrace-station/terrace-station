#include "textures.hh"
#include "log.hh"

#define DEFAULT_TEXTURE_LABEL "error"

std::set<std::string> Textures::valid_extensions = {"png", "jpg", "jpeg",
                                                    "PNG", "JPG", "JPEG"};

Textures::Textures(std::string pfad): pfad(pfad)
{
    load();
}

GLuint Textures::get_id(std::string label)
{
    if (texture_ids.count(label)) {
        return texture_ids[label];
    } else {
        LOG(WARNING) << "Texture '" << label << "' not found. Using texture '" << DEFAULT_TEXTURE_LABEL << "' instead.";
        return texture_ids[DEFAULT_TEXTURE_LABEL];
    }
}

void Textures::load()
{
    LOG(INFO) << "Loading textures ...";
    std::string label, filepath, ext;
    int delim;
    DIR *dir;
    struct dirent *ent;
    dir = opendir (pfad.c_str());
    while ((ent = readdir (dir)) != NULL) {
        std::stringstream ss;
        ss << pfad << "/" << ent->d_name;
        filepath = ss.str();
        label = ent->d_name;
        delim = label.find_last_of(".");
        ext = label.substr(delim + 1);
        label = label.substr(0, delim);
        if (valid_extensions.count(ext) == 1) {
            LOG(DEBUG) << "Loading texture '" << label << "' from file '" << filepath << "' ...";
            GLuint texture_id;
            SDL_Surface* surface = IMG_Load(filepath.c_str());
            int mode, source_mode;
            if (surface->format->BytesPerPixel == 3) {
                mode = GL_RGB;
            } else if (surface->format->BytesPerPixel == 4) {
                mode = GL_RGBA;
            } else {
                SDL_FreeSurface(surface);
                LOG(INFO) << "Skipping '" << filepath << "' (unknown mode)";
            }
            glGenTextures(1, &texture_id);
            glBindTexture(GL_TEXTURE_2D, texture_id);
//             glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
//             glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
// // // // // // Anisotrope Filterung
            if (strstr((char*)glGetString(GL_EXTENSIONS), "GL_EXT_texture_filter_anisotropic") != NULL)
            {
                float maxwert;
                LOG(DEBUG) << "Anisotrope Filterung: " << maxwert << "-fach.";
                glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxwert);
                glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, maxwert);
            }
// // // // // // // // // // 
            gluBuild2DMipmaps(GL_TEXTURE_2D, mode, surface->w, surface->h, mode, GL_UNSIGNED_BYTE, surface->pixels);
//             glTexImage2D(GL_TEXTURE_2D, 0, mode, surface->w, surface->h, 0, mode, GL_UNSIGNED_BYTE, surface->pixels);
            glBindTexture(GL_TEXTURE_2D, 0);
            SDL_FreeSurface(surface);
            texture_ids[label] = texture_id;
        } else {
            LOG(DEBUG) << "Skipping '" << filepath << "'";
        }
    }
    closedir (dir);
    IMG_Quit();
}
