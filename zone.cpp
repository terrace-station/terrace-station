#include "tile.hh"
#include "lamp.hh"
#include "rect.hh"
#include "door.hh"
#include "room.hh"
#include "deck.hh"
#include "district.hh"
#include "zone.hh"
#include "station.hh"
#include "log.hh"

#define PI  3.14159265358979323846
#define MIN_RANDOM_Z_OFFSET -100
#define MAX_RANDOM_Z_OFFSET 100
#define MIN_RING_DISTRICT_HEIGHT 50
#define MAX_RING_DISTRICT_HEIGHT 100
#define MIN_RING_DISTRICT_DISTANCE 50
#define MAX_RING_DISTRICT_DISTANCE 100
#define MIN_NR_OF_DISTRICTS 2
#define MAX_NR_OF_DISTRICTS 4
#define MIN_DISTRICT_HEIGHT 150
#define MAX_DISTRICT_HEIGHT 300

Zone::Zone(int circumference, std::string style, Station* station) :
    circumference(circumference), station(station)
{
    LOG(DEBUG) << "Building zone...";
    int nr_of_decks = 1; // + rand() % 4
    int nr_of_districts, x, y, width, height;
    int z_offset = MIN_RANDOM_Z_OFFSET + rand() % (MAX_RANDOM_Z_OFFSET - MIN_RANDOM_Z_OFFSET + 1);
    if (style == "rings") {
        // create two narrow fully circular districts:
        nr_of_districts = 2;
        x = 0;
        width = circumference;
        districts.reserve(nr_of_districts);
        
        height = MIN_RING_DISTRICT_HEIGHT + rand() % (MAX_RING_DISTRICT_HEIGHT - MIN_RING_DISTRICT_HEIGHT + 1);
        y = - (MIN_RING_DISTRICT_DISTANCE + rand() % (MAX_RING_DISTRICT_DISTANCE - MIN_RING_DISTRICT_DISTANCE + 1)) / 2 - height + z_offset;
        districts.emplace_back(x, y, width, height, nr_of_decks, true, this);
        
        height = MIN_RING_DISTRICT_HEIGHT + rand() % (MAX_RING_DISTRICT_HEIGHT - MIN_RING_DISTRICT_HEIGHT + 1);
        y = (MIN_RING_DISTRICT_DISTANCE + rand() % (MAX_RING_DISTRICT_DISTANCE - MIN_RING_DISTRICT_DISTANCE + 1)) / 2 + z_offset;
        districts.emplace_back(x, y, width, height, nr_of_decks, true, this);
    } else {
        // symmetrically create a few districts:
        nr_of_districts = MIN_NR_OF_DISTRICTS + rand() % (MAX_NR_OF_DISTRICTS - MIN_NR_OF_DISTRICTS + 1);
        width = circumference / (2 * nr_of_districts) + rand() % (circumference / (3 * nr_of_districts));
        height = MIN_DISTRICT_HEIGHT + rand() % (MAX_DISTRICT_HEIGHT - MIN_DISTRICT_HEIGHT + 1);
        y = - height / 2 + z_offset;
        districts.reserve(nr_of_districts);
        for (int i = 0; i < nr_of_districts; ++i)
        {
            x = i * circumference / nr_of_districts;
            districts.emplace_back(x, y, width, height, nr_of_decks, false, this);
        }
    }
    
    omega = sqrt(9.81/(this->get_radius())) / 10.0;
}

float Zone::get_radius() {
    return circumference / (2 * PI);
}

float Zone::get_omega() {
    return omega;
}

float Zone::get_angle() {
   return angle;
}

void Zone::set_angle(float angle_) {
   angle = angle_;
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
