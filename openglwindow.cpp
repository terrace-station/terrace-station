#include "openglwindow.hh"

#include "openglwidget.hh"


void Openglwindow::redraw()
{
//     draw_children();
   glwidget->redraw();
   infomenu->redraw();
}


// void Openglwindow::add_monitor(Monitor_3d* monitor_, int breite_, int hoehe_)
// {
//     if (w()>=h())
//     {
//         int hoehe_alt = h();
//         resize(0, 0, (breite_>w())?breite_:w(), h()+hoehe_ );
//         Openglwidget* glfenster = new Openglwidget(space, monitor_, 0, hoehe_alt, breite_, hoehe_, "");
//         add(*glfenster);
//         glwidget_list.push_back(glfenster);
//     }
//     else
//     {
//         int breite_alt = w();
//         resize(0, 0, w()+breite_, (hoehe_>h())?hoehe_:h() );
//         Openglwidget* glfenster = new Openglwidget(space, monitor_, breite_alt, 0, breite_, hoehe_, "");
//         add(*glfenster);
//         glwidget_list.push_back(glfenster);
//     }
//     this->resizable(NULL);
// }

void esc_callback(Fl_Widget* w, void*)
{
    std::cout << "Schließe Openglfenster" << std::endl;
    Openglwindow* fenster = (Openglwindow*) w;
    if (fl_choice("Fenster schließen?", fl_no, fl_yes, 0))
    {
        fenster->glwidget->hide();
        fenster->hide();//exit(0);
    }
}


void Openglwindow::resize(int position_x_, int position_y_, int breite_, int hoehe_)
{
    Fl_Window::resize(position_x_, position_y_, breite_, hoehe_);

//     Fl_Image* bild_tmp = rahmen_bg_scaled;
//     rahmen_bg_scaled = rahmen_bg->copy(200,rahmen->h());
//     delete bild_tmp;
//     rahmen->image(rahmen_bg_scaled);
}


Openglwindow::Openglwindow(int breite_, int hoehe_, const char* titel_) : Fl_Window(breite_, hoehe_, titel_)
{
   this->callback(esc_callback);
    
   this->begin();

   glwidget = new Openglwidget(0, 0, w()-200, h(), titel_);
   glwidget->end();
   

//     rahmen_bg = new Fl_PNG_Image("artwork/bg.png");
//     rahmen_bg_scaled = rahmen_bg->copy(200,h());
//     rahmen = new Fl_Box(w()-200, 0, 200, h());
//     rahmen->image(rahmen_bg_scaled);

//     baumenu = new Baumenu(w()-190, 0, 180, h());
//     baumenu->hide();
//     baumenu->end();
    
   infomenu = new Targetinfomenu(glwidget, w()-190, 0, 180, h());
   infomenu->end();
    
   this->resizable(glwidget);

   this->end();
}

Openglwindow::~Openglwindow(){}


