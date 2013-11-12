#include "rect.hh"
#include "room.hh"

Rect::Rect(int left, int top, int right, int bottom)
{
    this->left = left;
    this->top = top;
    this->right = right;
    this->bottom = bottom;
}

int Rect::width()
{
    return right - left;
}

int Rect::height()
{
    return bottom - top;
}

int Rect::area()
{
    return width() * height();
}

float Rect::aspect()
{
    float w = width();
    float h = height();
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
    return left < other.right && other.left < right && top < other.bottom && other.top < bottom;
}

bool Rect::intersects(Room other) {
    return other.intersects(*this);
}

std::string Rect::str()
{
    std::stringstream ss;
    ss << "Rect: left = " << left << ", top = " << top;
    ss << ", right = " << right << ", bottom = " << bottom;
    ss << ", area = " << area() << ", aspect = " << aspect();
    return ss.str();
}
