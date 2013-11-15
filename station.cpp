#include "station.hh"

#define PI    3.14159265358979323846
#define CF_MIN      600     // Minimum circumference
#define CF_DELTA    100     // Difference in circumference
#define NR_OF_ZONES 4

Station::Station()
{
    int x, y, width, height, cf, nr, nr_of_decks;
    float radius;
//     std::srand(std::time(0));
    for (int zone = 0; zone < NR_OF_ZONES; ++zone)
    {
        cf = CF_MIN + zone * CF_DELTA;
        radius = cf / (2 * PI);
        nr = rand() % 3 + 1;
        if (nr == 1) {
            width = cf;
        } else {
            width = cf / (2 * nr) + rand() % (cf / (3 * nr));
        }
        nr_of_decks = rand() % 3 + 2;
        y = - (rand() % 100 + 1);
        height = 100 + rand() % 100 + 1;
        for (int i = 0; i < nr; ++i)
        {
            x = i * cf / nr;
            District district(radius, x, y, width, height, nr_of_decks);
            districts.push_back(district);
        }
    }
}

std::vector<District>& Station::get_districts() {
    return districts;
}
    
std::string Station::str()
{
    std::stringstream ss;
    ss << "Station:" << std::endl;
    for (std::vector<District>::iterator it = districts.begin(); it != districts.end(); it++)
    {
        ss << it->str();
    }
    return ss.str();
}
