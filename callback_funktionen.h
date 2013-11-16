


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
