


void toggle_antialiasing_callback(Openglwidget& w)
{
   w.toggle_antialiasing();
}

void toggle_fullscreen_callback(Openglwidget& w)
{
   w.toggle_fullscreen();
}

void close_callback(Openglwidget& w)
{
   w.running = false;
}

void return_callback(Openglwidget& w)
{
   w.gamemenu = false;
   w.menu_bg_soll = 0.0;
   w.menu_bg      = 0.0;
   SDL_EnableKeyRepeat(20, 20);
}
