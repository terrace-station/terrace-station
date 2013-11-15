#include "rect.hh"
#include "room.hh"
#include "deck.hh"
#include "district.hh"
#include "zone.hh"
#include "station.hh"

#define PI  3.14159265358979323846

Zone::Zone(int circumference, Station& station) :
    circumference(circumference), station(station)
{
    int nr_of_districts = rand() % 3 + 1;
    int width;
    if (nr_of_districts == 1) {
        width = circumference;
    } else {
        width = circumference / (2 * nr_of_districts) + rand() % (circumference / (3 * nr_of_districts));
    }
    int nr_of_decks = rand() % 3 + 2;
    int y = - (rand() % 100 + 1);
    int height = 100 + rand() % 100 + 1;
    int x;
    for (int i = 0; i < nr_of_districts; ++i)
    {
        x = i * circumference / nr_of_districts;
        District district(x, y, width, height, nr_of_decks, *this);
        districts.push_back(district);
    }
    std::cout << this->circumference << std::endl;
}

float Zone::get_radius() {
    //~ std::cout << circumference << std::endl;
    //~ return circumference / (2 * PI);
    return 100.0;
}

std::vector<District>& Zone::get_districts() {
    return districts;
}
    
std::string Zone::str()
{
    std::stringstream ss;
    ss << "  Zone: (circumference = " << circumference << ")" << std::endl;
    for (std::vector<District>::iterator it = districts.begin(); it != districts.end(); it++)
    {
        ss << it->str();
    }
    return ss.str();
}
