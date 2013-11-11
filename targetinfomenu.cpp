#include "targetinfomenu.hh"
#include "openglwidget.hh"
#include "openglwindow.hh"


Targetinfomenu::Targetinfomenu(Openglwidget* glwidget_, int pos_x_, int pos_y_, int breite_, int hoehe_) : Fl_Pack(pos_x_, pos_y_, breite_, hoehe_, 0)
{
   glwidget = glwidget_;
//     type(Fl_Pack::VERTICAL);
//     this->begin();
// 
//     Fl_Box* label_breite = new Fl_Box(0,0,50,30,"Breite");
// 
//     breite = new Fl_Spinner(0,0,50,30,"");
//     breite->type(FL_FLOAT_INPUT);
//     breite->step(0.1);
//     breite->range(0.5,100);
// 
//     Fl_Box* label_laenge = new Fl_Box(0,0,50,30,"Länge");
// 
//     laenge = new Fl_Spinner(0,0,50,30,"");
//     laenge->type(FL_FLOAT_INPUT);
//     laenge->step(0.1);
//     laenge->range(0.5,100);
// 
//     Fl_Box* label_orientierung = new Fl_Box(0,0,50,30,"Orientierung");
// 
//     orientierung = new Fl_Spinner(0,0,50,30,"");
//     orientierung->type(FL_INT_INPUT);
//     orientierung->step(5);
//     orientierung->value(0);
//     orientierung->range(0,360);
// 
//     Fl_Box* label_gebaeudetyp = new Fl_Box(0,0,50,30,"Gebäudetyp");
// 
//     gebaeudetyp = new Fl_Choice(0,0,50,30,"");
//     gebaeudetyp->add("ZELTBAU|PFOSTENBAU|FACHWERKBAU|MAUERWERK|BEFESTIGUNG");
//     gebaeudetyp->value(1);
// 
//     this->end();
}

Targetinfomenu::~Targetinfomenu(){}

void Targetinfomenu::redraw()
{
   this->clear();
   this->hide();
   set_info(glwidget->get_target());
//    Fl_Pack::redraw();
   this->show();
}

void Targetinfomenu::set_info(Mausobjekt* target)
{
//    Gebiet* gebiet1 = (Gebiet*) target;
//    
//    if(target == NULL)
//    {
//       return;
//    }
//    else if(target->mo_typ == mo_gebiet)
//    {
//       Gebiet* gebiet = (Gebiet*) target;
//       
//       type(Fl_Pack::VERTICAL);
//       this->begin();
//       gebietsname = gebiet->name;
//       std::cout << gebiet->name << std::endl;
//       Fl_Box* label = new Fl_Box(0,0,50,20, gebietsname.c_str());


/*      
      this->end();
   }
   else
   {
      std::cout << "Kein Target darzustellen." << std::endl;
   }*/
}


