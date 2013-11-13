#include "rect.hh"
#include "room.hh"

Rect::Rect(int left, int top, int right, int bottom)
{
    this->left = left;
    this->top = top;
    this->right = right;
    this->bottom = bottom;
}

int Rect::get_left()
{
    return left;
}

int Rect::get_top()
{
    return top;
}

int Rect::get_right()
{
    return right;
}

int Rect::get_bottom()
{
    return bottom;
}

int Rect::get_width()
{
    return right - left;
}

int Rect::get_height()
{
    return bottom - top;
}

int Rect::get_area()
{
    return get_width() * get_height();
}

float Rect::get_aspect()
{
    float w = get_width();
    float h = get_height();
    if (w == h) {
        return 1.0;
    } else if (w > h) {
        return w / h;
    } else {
        return h / w;
    }
}

bool Rect::intersects(Rect other)
{
    return left < other.get_right() && other.get_left() < right && top < other.get_bottom() && other.get_top() < bottom;
}

bool Rect::intersects(Room other) {
    return other.intersects(*this);
}

std::string Rect::str()
{
    std::stringstream ss;
    ss << "        Rect:      (left = " << left << ", top = " << top;
    ss << ", right = " << right << ", bottom = " << bottom;
    ss << ", aspect = " << get_aspect() << ")" << std::endl;
    return ss.str();
}