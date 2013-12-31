#include "audio.hh"
#include "log.hh"

#define MUSIC_DIR   "music"
#define SOUNDS_DIR  "sounds"

std::set<std::string> Audio::valid_extensions = {"ogg", "mp3"};

std::list<std::string>* Audio::current_playlist;
std::list<std::string>::iterator Audio::current_track_it;
Mix_Music* Audio::music;
    
Audio::Audio()
{
    audio_init();
    load_music();
}

Audio::~Audio()
{
    Mix_CloseAudio();
}

void Audio::audio_init()
{
    int audio_rate = 22050;
    Uint16 audio_format = AUDIO_S16; /* 16-bit stereo */
    int audio_channels = 2;
    int audio_buffers = 4096;
    
    if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers)) {
        LOG(CRITICAL) << "Unable to open audio!";
        exit(1);
    }
}

void Audio::load_music()
{
    LOG(INFO) << "Loading music tracks ...";
    std::string label, playlist_path;
    DIR *music_dir;
    struct dirent *music_ent;
    music_dir = opendir (MUSIC_DIR);
    while ((music_ent = readdir (music_dir)) != NULL) {
        std::stringstream playlist_path_ss;
        playlist_path_ss << MUSIC_DIR << "/" << music_ent->d_name;
        playlist_path = playlist_path_ss.str();
        if (music_ent->d_name[0] == '.' || opendir(playlist_path.c_str()) == NULL) { continue; }
        label = music_ent->d_name;
        
        LOG(DEBUG) << "Loading playlist '" << label << "'";
        
        std::list<std::string> new_playlist;
        
        std::string filepath, ext;
        int delim;
        DIR *dir;
        struct dirent *ent;
        dir = opendir (playlist_path.c_str());
        while ((ent = readdir (dir)) != NULL) {
            std::stringstream ss;
            ss << playlist_path << "/" << ent->d_name;
            filepath = ss.str();
            if (ent->d_name[0] == '.') { continue; }
            delim = filepath.find_last_of(".");
            ext = filepath.substr(delim + 1);
            if (valid_extensions.count(ext) == 1) {
                LOG(DEBUG) << "  Loading music track '" << filepath << "'";
                new_playlist.push_back(filepath);
            } else {
                LOG(DEBUG) << "  Skipping '" << filepath << "'";
            }
        }
        if (new_playlist.size() == 0) {
            LOG(DEBUG) << "Playlist '" << label << "' is empty and will be ignored.";
        } else {
            LOG(DEBUG) << "Playlist '" << label << "' contains " << new_playlist.size() << " tracks.";
            playlists[label] = new_playlist;
        }
        
        closedir(dir);
    }
    closedir(music_dir);
}

void Audio::set_music_playlist(std::string label)
{
    if (playlists.count(label)) {
        if (current_playlist == &playlists[label])
        {
            LOG(DEBUG) << "Music: Playlist '" << label << "' already playing.";
        } else {
            current_playlist = &playlists[label];
            current_track_it = current_playlist->begin();
            LOG(DEBUG) << "Music: Switching to playlist '" << label << "'.";
            music_start();
        }
    } else {
        LOG(WARNING) << "Music: Playlist '" << label << "' not found.";
    }
}

void Audio::music_start()
{
    music = Mix_LoadMUS((*current_track_it).c_str());
    Mix_PlayMusic(music, 0);
    Mix_HookMusicFinished(music_next_track);
    LOG(INFO) << "Music: Now playing '" << *current_track_it << "' ...";
}

void Audio::music_stop()
{
    Mix_HaltMusic();
    Mix_FreeMusic(music);
    music = NULL;
}

void Audio::music_next_track()
{
    music_stop();
    current_track_it++;
    if (current_track_it == current_playlist->end()) {
        current_track_it = current_playlist->begin();
    }
    music_start();
}

void Audio::music_toggle_mute()
{
    if (Mix_VolumeMusic(-1) == 0) {
        LOG(INFO) << "Music: mute";
        Mix_VolumeMusic(MIX_MAX_VOLUME);
    } else {
        LOG(INFO) << "Music: un-mute";
        Mix_VolumeMusic(0);
    }
}
