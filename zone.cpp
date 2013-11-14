#include "zone.hh"

#define PI          3.14159265358979323846
#define CF_MIN      600     // Minimum circumference
#define CF_DELTA    100     // Difference in circumference

Zone::Zone(int circumference)
{
    this->circumference = circumference;
    
    int x, y, width, height, nr, nr_of_decks;
    float radius = circumference / (2 * PI);
    nr = rand() % 3 + 1;
    if (nr == 1) {
        width = circumference;
    } else {
        width = circumference / (2 * nr) + rand() % (circumference / (3 * nr));
    }
    nr_of_decks = rand() % 3 + 2;
    y = - (rand() % 100 + 1);
    height = 100 + rand() % 100 + 1;
    for (int i = 0; i < nr; ++i)
    {
        x = i * circumference / nr;
        District district(radius, x, y, width, height, nr_of_decks);
        districts.push_back(district);
    }
}

std::vector<District>& Zone::get_districts() {
    return districts;
}
    
std::string Zone::str()
{
    std::stringstream ss;
    ss << "  Zone:" << std::endl;
    for (std::vector<District>::iterator it = districts.begin(); it != districts.end(); it++)
    {
        ss << it->str();
    }
    return ss.str();
}
