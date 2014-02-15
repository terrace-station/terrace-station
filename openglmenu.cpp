#include "openglmenu.hh"

#include "openglwidget.hh"

Openglmenu::Openglmenu(Openglwidget* glwidget) : glwidget(glwidget)
{
    button_count = 0;
    menu_bg = 0;
    menu_bg_soll = 0;
    
// Hintergrundfarbe
    bg_color_r = 0.0;
    bg_color_g = 0.2;
    bg_color_b = 0.1;
    
// Titel
    Openglwidget::fonttextures->load_id("Terrace Station", "terrace station",    "Overhaul", 180, 255, 180);
    add_label("terrace station", 0.0, 3.2, 0.5);
    
    Openglwidget::fonttextures->load_id("Game Menu", "gamemenu",    "jupiter", 180, 255, 180);
    add_label("gamemenu", 0.0, 2.5, 1.5);
    
// Fullscreen-Button
    Opengltogglebutton button_fullscreen(&(glwidget->fullscreen));
    button_fullscreen.set_callback(toggle_fullscreen_callback);
    button_fullscreen.set_modell(Openglwidget::models->get("button_gruen"), Openglwidget::models->get("button_rot"));
    add_togglebutton(&button_fullscreen, 2.0, 1.0, 0.7, 0.7);
    
    Openglwidget::fonttextures->load_id("fullscreen", "fullscreen", "jupiter", 180, 255, 180);
    add_label("fullscreen",-2.0, 1.0, 0.8);
    
// Anti-Aliasing-Button
    Opengltogglebutton button_aa(&(glwidget->antialiasing));
    button_aa.set_callback(toggle_antialiasing_callback);
    button_aa.set_modell(Openglwidget::models->get("button_gruen"), Openglwidget::models->get("button_rot"));
    add_togglebutton(&button_aa, 2.0, 0.0, 0.7, 0.7);
    
    Openglwidget::fonttextures->load_id("anti-aliasing", "aa",      "jupiter", 180, 255, 180);
    add_label("aa",-2.0, 0.0, 0.8);
    
// Return-Button
    Openglbutton button_return;
    button_return.set_callback(return_callback);
    button_return.set_modell(Openglwidget::models->get("button_menu"));
    add_button(&button_return, -3, -3, 3, 1); // pos_x, pos_y, scale_x, scale_y
    
    Openglwidget::fonttextures->load_id("Return", "return",         "jupiter", 180, 255, 180);
    add_label("return",-3.0,-3.0, 0.8);
    
// Close-Button
    Openglbutton button_close;
    button_close.set_callback(close_callback);
    button_close.set_modell(Openglwidget::models->get("button_menu"));
    add_button(&button_close, 2, -3, 5, 1); // pos_x, pos_y, scale_x, scale_y
    
    Openglwidget::fonttextures->load_id("Leave Program", "close",   "jupiter", 180, 255, 180);
    add_label("close", 2.0,-3.0, 0.8);
}

void Openglmenu::add_button(Openglbutton* button, float x_, float y_, float sx_, float sy_)
{
    buttons.push_back({*button, x_, y_, sx_, sy_});
    ++button_count;
}

void Openglmenu::add_togglebutton(Opengltogglebutton* button, float x_, float y_, float sx_, float sy_)
{
    togglebuttons.push_back({*button, x_, y_, sx_, sy_});
    ++button_count;
}

void Openglmenu::add_label(std::string label, float x_, float y_, float s_)
{
    labels.push_back({label, x_, y_, s_});
}


