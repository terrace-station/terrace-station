#ifndef AUDIO_HH
#define AUDIO_HH

#include <sstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <dirent.h>
#include <list>
#include <set>

#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

class Audio
{
    static std::set<std::string> valid_extensions;
    
    /** A map, assigning each playlist-label a list of filenames */
    std::unordered_map<std::string, std::list<std::string> > playlists;
    
    static std::list<std::string>* current_playlist;
    static std::list<std::string>::iterator current_track_it;
    static Mix_Music* music;
    
    void audio_init();
    void load_music();
    static void music_start();
    static void music_stop();
    static void music_next_track();

public:
    Audio();
    ~Audio();
    void set_music_playlist(std::string label);
    void music_toggle_mute();
    //~ void set_music_volume(int v);
    //~ int get_music_volume();
};

#endif
