#include "district.hh"

#define DECK_HEIGHT 3

District::District(float radius, int x, int y, int size_x, int size_y, int nr_of_decks)
{
    this->radius = radius;
    this->x = x;
    this->y = y;
    this->size_x = size_x;
    this->size_y = size_y;
    for (int i = 0; i < nr_of_decks; ++i)
    {
        float deck_radius = radius + i * DECK_HEIGHT- 2.5;
        Deck deck(deck_radius, x, y, size_x, size_y);
        decks.push_back(deck);
    }
}

float District::get_radius_min() {
    return this->radius - decks.size() * DECK_HEIGHT / 2.0;
}
float District::get_radius_max() {
    return this->radius + decks.size() * DECK_HEIGHT / 2.0;
}

float District::get_phi_min() {
    return x / radius;
}
float District::get_phi_max() {
    return (size_x + x) / radius;
}

float District::get_z_min() {
    return y;
}
float District::get_z_max() {
    return y + size_y;
}
std::vector<Deck> District::get_decks() {
    return decks;
}

std::string District::str()
{
    std::stringstream ss;
    ss << "  District:  (radius = " << radius;
    ss << ", x = " << x;
    ss << ", y = " << y;
    ss << ", size_x = " << size_x;
    ss << ", size_y = " << size_y << ")" << std::endl;
    for (std::vector<Deck>::iterator it = decks.begin(); it != decks.end(); it++)
    {
        ss << it->str();
    }
    return ss.str();
}
