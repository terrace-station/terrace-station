#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>

Mix_Music* music = NULL;
bool music_loop = true;

void music_done();

void audio_init()
{
    int audio_rate = 22050;
    Uint16 audio_format = AUDIO_S16; /* 16-bit stereo */
    int audio_channels = 2;
    int audio_buffers = 4096;
    
    if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers)) {
    printf("Unable to open audio!\n");
    exit(1);
  }
}

void audio_cleanup()
{
    Mix_CloseAudio();
}

void music_start()
{
    music = Mix_LoadMUS("music/canton_Benbient.ogg");
    //~ music = Mix_LoadMUS("music/Mads-Emil-Nielsen_Machine.ogg");
    Mix_PlayMusic(music, 0);
    Mix_HookMusicFinished(music_done);
}

void music_stop()
{
    Mix_HaltMusic();
    Mix_FreeMusic(music);
    music = NULL;
}

void music_done()
{
    if (music_loop) {
        music_start();
    } else {
        music_stop();
    }
}
