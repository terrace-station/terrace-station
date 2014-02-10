#include "tile.hh"
#include "lamp.hh"
#include "rect.hh"
#include "door.hh"
#include "room.hh"
#include "deck.hh"
#include "district.hh"
#include "zone.hh"
#include "station.hh"

Door::Door(std::string style, int x, int y, int orientation, int width) :
    style(style), x(x), y(y), orientation(orientation)
{
    objekt_typ = "Door";
    set_dynmodel();
}

int Door::get_x() { return x; }
int Door::get_y() { return y; }
int Door::get_orientation() { return orientation; }
int Door::get_width() { return width; }
    
std::string Door::str()
{
    std::stringstream ss;
    ss << "      Door:      (style = " << style << ", x = " << x;
    ss << ", y = " << y << ", orientation = " << orientation;
    ss << ", width = " << width << ")" << std::endl;
    ss << room1->str() << room2->str();
    return ss.str();
}


void Door::set_dynmodel()
{
    switch(rand()%2)
    {
        case 0:
            add_model("door1frame");
            add_model("door1leaf");
            add_state("closed");
                states[0].add_transformation(1, TRA_TRANSLATE, 0.0, 0.0, 0.0, -1.7);
                states[0].add_transformation(1, TRA_TRANSLATE, 2.0, 0.0, 0.0, 1.7);
            add_state("open");
                states[1].add_transformation(1, TRA_TRANSLATE, 2.0, 0.0, 0.0, -1.7);  // target, type, timedelay, arg1, arg2, arg3
                break;
            
        case 1:
            add_model("door1frame");
            add_model("door2leaf");
            add_model("door2leaf");
            add_state("closed");
                states[0].add_transformation(1, TRA_TRANSLATE, 0.0, 0.0, 0.35, 0.0);
                states[0].add_transformation(1, TRA_SCALE,     0.0, 1.0, 0.2, 1.0);
                states[0].add_transformation(1, TRA_SCALE,     1.0, 1.0, 5.0, 1.0);
                states[0].add_transformation(2, TRA_TRANSLATE, 0.0, 0.0,-0.35, 0.0);
                states[0].add_transformation(2, TRA_SCALE,     0.0, 1.0,-1.0, 1.0);
                states[0].add_transformation(2, TRA_SCALE,     0.0, 1.0, 0.2, 1.0);
                states[0].add_transformation(2, TRA_SCALE,     1.0, 1.0, 5.0, 1.0);
            add_state("open");
                states[1].add_transformation(1, TRA_TRANSLATE, 0.0, 0.0, 0.35, 0.0);
                states[1].add_transformation(1, TRA_SCALE,     1.0, 1.0, 0.2, 1.0);
                states[1].add_transformation(2, TRA_TRANSLATE, 0.0, 0.0,-0.35, 0.0);
                states[1].add_transformation(2, TRA_SCALE,     0.0, 1.0,-1.0, 1.0);
                states[1].add_transformation(2, TRA_SCALE,     1.0, 1.0, 0.2, 1.0);
                break;
    }
}