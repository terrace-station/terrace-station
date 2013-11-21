#include "tile.hh"
#include "rect.hh"
#include "room.hh"
#include "deck.hh"
#include "district.hh"
#include "zone.hh"
#include "station.hh"

#define DECK_HEIGHT 2
#define ROOM_MAX_ASPECT_RATIO 4
#define ROOM_MAX_AREA 100
#define CORRIDOR_MIN_WIDTH 1
#define CORRIDOR_MAX_WIDTH 4
#define CORRIDOR_MIN_DISTANCE 4
#define CORRIDOR_CONNECT_DISTANCE 8
#define CORRIDOR_FORK_CHANCE_PERCENT 50
#define CORRIDOR_SPAWN_POINTS 6
#define CORRIDOR_SPAWN_POINT_MARGIN 20
#define CORRIDOR_MIN_LENGTH 0
#define CORRIDOR_MIN_LENGTH_PER_WIDTH 2
#define CORRIDOR_MAX_LENGTH_PER_WIDTH 8

/**
 * Creates a new deck
 * 
 * \param   radius_offset   radius offset with respect to the district
 * \param   district        the district this deck belongs to
 */
Deck::Deck(float radius_offset, District* district) :
    radius_offset(radius_offset), district(district)
{
    //tic
    Deck::init();
    //toc
}

void Deck::init()
{
    // preparations:
    int x = district->get_x();
    int y = district->get_y();
    int size_x = district->get_size_x();
    int size_y = district->get_size_y();
    std::vector<std::vector<Room*> > tiles_occupied(size_x, std::vector<Room*>(size_y, NULL));
    
    // drill corridors:
    std::list<CorridorBuilder> cbs;
    for (int i=0; i < CORRIDOR_SPAWN_POINTS; ++i) {
        int cb_x = x + CORRIDOR_SPAWN_POINT_MARGIN + rand() % (size_x - 2 * CORRIDOR_SPAWN_POINT_MARGIN);
        int cb_y = y + CORRIDOR_SPAWN_POINT_MARGIN + rand() % (size_y - 2 * CORRIDOR_SPAWN_POINT_MARGIN);
        int cb_d = rand() % 4;
        CorridorBuilder cb = {cb_x, cb_y, cb_d, CORRIDOR_MAX_WIDTH, true};
        cbs.push_back(cb);
    }
    int active_cbs = 1;
    while (active_cbs > 0) {
        std::list<CorridorBuilder> new_cbs;
        for (std::list<CorridorBuilder>::iterator cb_it = cbs.begin(); cb_it != cbs.end(); cb_it++)
        {
            CorridorBuilder& cb = *cb_it;
            if (cb.active) {
                Rect* rect;
                Rect* rect_padding;
                int length = CORRIDOR_MIN_LENGTH + CORRIDOR_MIN_LENGTH_PER_WIDTH * cb.width + rand() % (CORRIDOR_MIN_LENGTH + CORRIDOR_MAX_LENGTH_PER_WIDTH * cb.width);
                if (cb.direction == 0) { // go west:
                    rect = new Rect(cb.x - length, cb.y, cb.x, cb.y + cb.width);
                    rect_padding = new Rect(cb.x - length - CORRIDOR_MIN_DISTANCE, cb.y - CORRIDOR_MIN_DISTANCE, cb.x, cb.y + cb.width + CORRIDOR_MIN_DISTANCE);
                    cb.x -= length;
                } else if (cb.direction == 1) { // go north:
                    rect = new Rect(cb.x, cb.y - length, cb.x + cb.width, cb.y);
                    rect_padding = new Rect(cb.x - CORRIDOR_MIN_DISTANCE, cb.y - length - CORRIDOR_MIN_DISTANCE, cb.x + cb.width + CORRIDOR_MIN_DISTANCE, cb.y);
                    cb.y -= length;
                } else if (cb.direction == 2) { // go east:
                    rect = new Rect(cb.x, cb.y, cb.x + length, cb.y + cb.width);
                    rect_padding = new Rect(cb.x, cb.y - CORRIDOR_MIN_DISTANCE, cb.x + length + CORRIDOR_MIN_DISTANCE, cb.y + cb.width + CORRIDOR_MIN_DISTANCE);
                    cb.x += length;
                } else { // go south:
                    rect = new Rect(cb.x, cb.y, cb.x + cb.width, cb.y + length);
                    rect_padding = new Rect(cb.x - CORRIDOR_MIN_DISTANCE, cb.y, cb.x + cb.width + CORRIDOR_MIN_DISTANCE, cb.y + length + CORRIDOR_MIN_DISTANCE);
                    cb.y += length;
                }
                
                if (rect_padding->get_left() < x || rect_padding->get_top() < y || rect_padding->get_right() > x + size_x || rect_padding->get_bottom() > y + size_y) {
                    // too close to space:
                    cb.active = false;
                    continue;
                } else {
                    bool overlapping = false;
                    //~ for (std::list<Room>::iterator room_it = rooms.begin(); room_it != rooms.end(); room_it++) {
                        //~ if (rect->intersects(*room_it)) {
                            //~ overlapping = true;
                        //~ }
                    //~ }
                    for (int i = 0; i < rect_padding->get_width(); ++i) {
                        for (int j = 0; j < rect_padding->get_height(); ++j) {
                            if (tiles_occupied[rect_padding->get_left() - x + i][rect_padding->get_top() - y + j] != NULL) {
                                overlapping = true;
                                break;
                            }
                        }
                        if (overlapping) { break; }
                    }
                    if (overlapping) {
                        // overlapping:
                        cb.active = false;
                        continue;
                    }
                }
                
                // create the new corridor segment and a door:
                rooms.emplace_back("corridor", *rect, this);
                for (int i = 0; i < rect->get_width(); ++i) {
                    for (int j = 0; j < rect->get_height(); ++j) {
                        tiles_occupied[rect->get_left() - x + i][rect->get_top() - y + j] = &rooms.back();
                    }
                }
                //~ self.doors.append(Door("door", cb.x, cb.y, cb.direction, cb.width))
                
                // spawn additional corridor builders:
                int new_width;
                if (cb.width > CORRIDOR_MIN_WIDTH) {
                    new_width = CORRIDOR_MIN_WIDTH + rand() % (cb.width - CORRIDOR_MIN_WIDTH);
                } else {
                   new_width = CORRIDOR_MIN_WIDTH;
                }
                if (rand() % 100 < CORRIDOR_FORK_CHANCE_PERCENT) {
                    if (cb.direction % 2 == 0) {
                        // horizontal corridor, upward fork:
                        CorridorBuilder new_cb = {cb.x - cb.direction / 2 * new_width, cb.y, 1, new_width, true};
                        new_cbs.push_back(new_cb);
                        //~ self.doors.append(Door("door", new_cb.x, new_cb.y, new_cb.direction, new_cb.width))
                    } else {
                        // vertical corridor, left fork:
                        CorridorBuilder new_cb = {cb.x, cb.y - cb.direction / 2 * new_width, 0, new_width, true};
                        new_cbs.push_back(new_cb);
                        //~ self.doors.append(Door("door", new_cb.x, new_cb.y, new_cb.direction, new_cb.width))
                    }
                }
                if (rand() % 100 < CORRIDOR_FORK_CHANCE_PERCENT) {
                    if (cb.direction % 2 == 0) {
                        // horizontal corridor, downward fork:
                        CorridorBuilder new_cb = {cb.x - cb.direction / 2 * new_width, cb.y + cb.width, 3, new_width, true};
                        new_cbs.push_back(new_cb);
                        //~ self.doors.append(Door("door", new_cb.x, new_cb.y, new_cb.direction, new_cb.width))
                    } else {
                        // vertical corridor, right fork:
                        CorridorBuilder new_cb = {cb.x + cb.width, cb.y - cb.direction / 2 * new_width, 2, new_width, true};
                        new_cbs.push_back(new_cb);
                        //~ self.doors.append(Door("door", new_cb.x, new_cb.y, new_cb.direction, new_cb.width))
                    }
                }
            }
        }
        
        for (std::list<CorridorBuilder>::iterator new_cb_it = new_cbs.begin(); new_cb_it != new_cbs.end(); new_cb_it++) {
            cbs.push_back(*new_cb_it);
        }
        
        active_cbs = 0;
        for (std::list<CorridorBuilder>::iterator cb_it = cbs.begin(); cb_it != cbs.end(); cb_it++) {
            active_cbs += (*cb_it).active;
        }
    }
    
    // fill free space with rooms:
    int nx, ny;
    for (int i = 0; i < size_x * size_y; ++i) {
        nx = i % size_x;
        ny = i / size_x;
        Rect* rect = new Rect(x + nx, y + ny, x + nx + 1, y + ny + 1);
        if (tiles_occupied[rect->get_left() - x][rect->get_top() - y] == NULL) {
            rect->right += 1;
            rect->bottom += 1;
            while (rect->right <= x + size_x && rect->bottom <= y + size_y
                                            && rect->get_aspect() <= ROOM_MAX_ASPECT_RATIO
                                            && 1.0 / rect->get_aspect() <= ROOM_MAX_ASPECT_RATIO) {
                bool overlapping = false;
                for (int k = 0; k < rect->get_width(); ++k) {
                    for (int l = 0; l < rect->get_height(); ++l) {
                        if (tiles_occupied[rect->get_left() - x + k][rect->get_top() - y + l] != NULL) {
                            overlapping = true;
                            break;
                        }
                    }
                    if (overlapping) { break; }
                }
                if (overlapping) {
                    break;
                } else {
                    rect->right += 1;
                    rect->bottom += 1;
                }
            }
            rect->right -= 1;
            rect->bottom -= 1;
            while (rect->right <= x + size_x && rect->bottom <= y + size_y
                                            && rect->get_aspect() <= ROOM_MAX_ASPECT_RATIO
                                            && 1.0 / rect->get_aspect() <= ROOM_MAX_ASPECT_RATIO) {
                bool overlapping = false;
                for (int k = 0; k < rect->get_width(); ++k) {
                    for (int l = 0; l < rect->get_height(); ++l) {
                        if (tiles_occupied[rect->get_left() - x + k][rect->get_top() - y + l] != NULL) {
                            overlapping = true;
                            break;
                        }
                    }
                    if (overlapping) { break; }
                }
                if (overlapping) {
                    break;
                } else {
                    rect->right += 1;
                }
            }
            rect->right -= 1;
            while (rect->right <= x + size_x && rect->bottom <= y + size_y
                                            && rect->get_aspect() <= ROOM_MAX_ASPECT_RATIO
                                            && 1.0 / rect->get_aspect() <= ROOM_MAX_ASPECT_RATIO) {
                bool overlapping = false;
                for (int k = 0; k < rect->get_width(); ++k) {
                    for (int l = 0; l < rect->get_height(); ++l) {
                        if (tiles_occupied[rect->get_left() - x + k][rect->get_top() - y + l] != NULL) {
                            overlapping = true;
                            break;
                        }
                    }
                    if (overlapping) { break; }
                }
                if (overlapping) {
                    break;
                } else {
                    rect->bottom += 1;
                }
            }
            rect->bottom -= 1;
            if (rect->get_area() > 0) {
                rooms.emplace_back("room", *rect, this);
                for (int k = 0; k < rect->get_width(); ++k) {
                    for (int l = 0; l < rect->get_height(); ++l) {
                        tiles_occupied[rect->get_left() - x + k][rect->get_top() - y + l] = &rooms.back();
                    }
                }
            }
        }
    }
    
    // split large rooms:
    bool found_a_large_room = false;
    //~ int counter = 0;
    while (true) {
        found_a_large_room = false;
        for (std::list<Room>::iterator room_it = rooms.begin(); room_it != rooms.end(); room_it++) {
            if (room_it->get_style_group() == "room" && room_it->get_area() > ROOM_MAX_AREA) {
                Rect& rect = room_it->get_rects().front();
                Rect* new_rect;
                int split;
                if (rect.get_aspect() > 1.0) {
                    // vertical split:
                    split = rect.get_left() + rect.get_width() / 2;
                    new_rect = new Rect(rect.get_left(), rect.get_top(), split, rect.get_bottom());
                    rooms.emplace_back("room", *new_rect, this);
                    new_rect = new Rect(split, rect.get_top(), rect.get_right(), rect.get_bottom());
                    rooms.emplace_back("room", *new_rect, this);
                } else {
                    // horizontal split:
                    split = rect.get_top() + rect.get_height() / 2;
                    new_rect = new Rect(rect.get_left(), rect.get_top(), rect.get_right(), split);
                    rooms.emplace_back("room", *new_rect, this);
                    new_rect = new Rect(rect.get_left(), split, rect.get_right(), rect.get_bottom());
                    rooms.emplace_back("room", *new_rect, this);
                }
                rooms.erase(room_it);
                found_a_large_room = true;
                break;
            }
        }
        if (!found_a_large_room) { break; }
        
        //~ // Notbremse:
        //~ counter++;
        //~ if (counter > 30) { break; }
    }
    
    // turn narrow rooms into corridors:
    for (std::list<Room>::iterator room_it = rooms.begin(); room_it != rooms.end(); room_it++) {
        if (room_it->get_rects().front().get_width() == 1 || room_it->get_rects().front().get_height() == 1) {
            room_it->set_style_group("corridor");
        }
    }
    
    // randomly join some rooms:
    int counter = 0;
    while (counter < 50) {
        // find small rooms:
        std::list<Room> small_rooms_list;
        for (std::list<Room>::iterator room_it = rooms.begin(); room_it != rooms.end(); room_it++) {
            if (room_it->get_style_group() == "room" && room_it->get_area() < 50) {
                small_rooms_list.push_back(*room_it);
            }
        }
        std::vector<Room> small_rooms;
        small_rooms.reserve(small_rooms_list.size());
        for (std::list<Room>::iterator room_it = small_rooms_list.begin(); room_it != small_rooms_list.end(); room_it++) {
            small_rooms.push_back(*room_it);
        }
        // choose a random small room:
        Room* room = &small_rooms[rand() % small_rooms.size()];
        Rect& rect = room->get_rects().front();
        // choose a random direction:
        int direction;
        if (rect.get_aspect() > 1.0) {
            direction = 1 + 2 * (rand() % 2);
        } else {
            direction = 2 * (rand() % 2);
        }
        int rx, ry;
        if (direction == 0) {
            // join west:
            if (rect.get_left() == x) { continue; }
            rx = rect.get_left() - 1;
            ry = rect.get_top() + rand() % rect.get_height();
        } else if (direction == 1) {
            // join north:
            if (rect.get_top() == y) { continue; }
            rx = rect.get_left() + rand() % rect.get_width();
            ry = rect.get_top() - 1;
        } else if (direction == 2) {
            // join east:
            if (rect.get_right() == x + size_x) { continue; }
            rx = rect.get_right();
            ry = rect.get_top() + rand() % rect.get_height();
        } else {
            // join south:
            if (rect.get_bottom() == y + size_y) { continue; }
            rx = rect.get_left() + rand() % rect.get_width();
            ry = rect.get_bottom();
        }
        // find the room next door:
        //~ std::cout << x << " " << y << " " << size_x << " " << size_y << " " << rx << " " << ry << " " << std::endl;
//         Room* next_room = tiles_occupied[rx - x][ry - y];
//         if (next_room->get_style_group() == "room" && next_room != room) {
            // add next_room's rects to room:
            //~ for (std::list<Rect>::iterator rect_it = next_room->get_rects().begin(); rect_it != next_room->get_rects().end(); rect_it++) {
                //~ room->add_rect(*rect_it);
                //~ // update tile map:
                //~ for (int k = 0; k < rect_it->get_width(); ++k) {
                    //~ for (int l = 0; l < rect_it->get_height(); ++l) {
                        //~ tiles_occupied[rect_it->get_left() - x + k][rect_it->get_top() - y + l] = room;
                    //~ }
                //~ }
            //~ }
            //~ // remove next_room:
            //~ for (std::list<Room>::iterator room_it = rooms.begin(); room_it != rooms.end(); room_it++) {
                //~ if (&(*room_it) == next_room) {
                    //~ rooms.erase(room_it);
                    //~ break;
                //~ }
            //~ }
            ++counter;
//         }
        //~ ++counter;
    }
}

float Deck::get_radius() {
    return district->get_radius() + radius_offset - 0.5;
}

std::list<Room>& Deck::get_rooms() {
    return rooms;
}

District* Deck::get_district() {
    return district;
}

std::string Deck::str()
{
    std::stringstream ss;
    ss << "      Deck:      (radius_offset = " << radius_offset << ")" << std::endl;
    //~ for (std::list<Room>::iterator it = rooms.begin(); it != rooms.end(); it++)
    //~ {
        //~ ss << it->str();
    //~ }
    return ss.str();
}
