#include "models.hh"
#include "log.hh"

#define DEFAULT_MODEL_LABEL "error"

std::set<std::string> Models::valid_extensions = {"obj", "Obj", "OBJ"};

Models::Models(std::string pfad): pfad(pfad)
{
    load();
}

Modell* Models::get(std::string label)
{
    if (models.count(label)) {
        return models[label];
    } else {
        LOG(WARNING) << "Model '" << label << "' not found. Using model '" << DEFAULT_MODEL_LABEL << "' instead." << std::endl;
        return models[DEFAULT_MODEL_LABEL];
    }
}

void Models::load()
{
    LOG(INFO) << "Loading models ...";
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
            LOG(DEBUG) << "Loading model '" << label << "' from file '" << filepath << "' ...";
            Modell* modell = new Modell(pfad + "/" + label, false);
            
            models[label] = modell;
        } else {
            LOG(DEBUG) << "Skipping " << filepath;
        }
    }
    closedir (dir);
    IMG_Quit();
}
