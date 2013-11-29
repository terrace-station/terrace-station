#include "rect.hh"
#include "lamp.hh"
#include "door.hh"
#include "room.hh"
#include "deck.hh"
#include "district.hh"
#include "zone.hh"
#include "station.hh"

Rect::Rect(int left, int top, int right, int bottom):
    left(left), top(top), right(right), bottom(bottom)
{
    
}

int Rect::get_left() { return left; }
int Rect::get_top() { return top; }
int Rect::get_right() { return right; }
int Rect::get_bottom() { return bottom; }

int Rect::get_width() { return right - left; }
int Rect::get_height() { return bottom - top; }

int Rect::get_area() { return get_width() * get_height(); }
float Rect::get_aspect() { return float(get_width()) / float(get_height()); }

bool Rect::contains(int x, int y) {
    if (left <= x && x < right && top <= y && y < bottom) {
        return true;
    } else {
        return false;
    }
}

bool Rect::intersects(Rect other) {
    return left < other.get_right() && other.get_left() < right && top < other.get_bottom() && other.get_top() < bottom;
}

bool Rect::intersects(Room other) {
    return other.intersects(*this);
}

std::string Rect::str() {
    std::stringstream ss;
    ss << "          Rect:      (left = " << left << ", top = " << top;
    ss << ", right = " << right << ", bottom = " << bottom;
    ss << ", aspect = " << get_aspect() << ")" << std::endl;
    return ss.str();
}
