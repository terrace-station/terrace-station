#include "room.hh"

Room::Room(std::string style, std::list<Rect> rects)
{
    this->style = style;
    for (std::list<Rect>::iterator it = rects.begin(); it!=rects.end(); it++)
    {
        this->rects.push_back(*it);
    }
}

int Room::area()
{
    int result = 0;
    for (std::list<Rect>::iterator it = rects.begin(); it!=rects.end(); it++)
    {
        result += it->area();
    }
    return result;
}

bool Room::intersects(Rect other)
{
    for (std::list<Rect>::iterator it = rects.begin(); it!=rects.end(); it++)
    {
        if (it->intersects(other)) {
            return true;
        }
    }
    return false;
}

bool Room::intersects(Room other)
{
    for (std::list<Rect>::iterator it = rects.begin(); it!=rects.end(); it++)
    {
        if (other.intersects(*it)) {
            return true;
        }
    }
    return false;
}

std::string Room::str()
{
    std::stringstream ss;
    ss << "Room: style = " << style << ", area = " << area();
    ss << ", nr of rects = " << rects.size();
    return ss.str();
}
