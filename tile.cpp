#include "tile.hh"

#define DECK_HEIGHT 2
#define HALF_WALL_THICKNESS 0.05

/**
 * Creates a new floor tile
 * 
 * \param   x       x-position in local deck-coordinates
 * \param   y       y-position in local deck-coordinates
 * \param   radius  deck radius
 */
Tile::Tile(int x, int y, float radius)
{
    vertex1.reserve(3);
    vertex2.reserve(3);
    vertex3.reserve(3);
    vertex4.reserve(3);
    normal.reserve(3);
    
    float phi1 = x / radius;
    float phi2 = (x + 1) / radius;
    float phi = (x + 0.5) / radius;
    
    float x1 = radius * cos(phi1);
    float x2 = radius * cos(phi2);
    float y1 = radius * sin(phi1);
    float y2 = radius * sin(phi2);
    
    vertex1.push_back(x1);
    vertex1.push_back(y1);
    vertex1.push_back(y);
    
    vertex2.push_back(x1);
    vertex2.push_back(y1);
    vertex2.push_back(y + 1);
    
    vertex3.push_back(x2);
    vertex3.push_back(y2);
    vertex3.push_back(y + 1);
    
    vertex4.push_back(x2);
    vertex4.push_back(y2);
    vertex4.push_back(y);
    
    normal.push_back(cos(phi));
    normal.push_back(sin(phi));
    normal.push_back(0.0);
}

/**
 * Creates a new wall tile
 * 
 * \param   x           x-position in local deck-coordinates
 * \param   y           y-position in local deck-coordinates
 * \param   radius      deck radius
 * \param   orientation wall-orientation (west: 0, north:1, east: 2, south:3)
 */
Tile::Tile(int x, int y, float radius, int orientation)
{
    vertex1.reserve(3);
    vertex2.reserve(3);
    vertex3.reserve(3);
    vertex4.reserve(3);
    normal.reserve(3);
    
    float phi1 = x / radius;
    float phi2 = (x + 1) / radius;
    float radius2 = radius - DECK_HEIGHT;
    
    if (orientation == 0) { // east wall:
        float phi1 = (x + HALF_WALL_THICKNESS) / radius;
        
        normal.push_back(-sin(phi1));
        normal.push_back(-cos(phi1));
        normal.push_back(0.0);
        
        float x1 = radius * cos(phi1);
        float x2 = radius2 * cos(phi1);
        float y1 = radius * sin(phi1);
        float y2 = radius2 * sin(phi1);
    
        vertex1.push_back(x1);
        vertex1.push_back(y1);
        vertex1.push_back(y);
        
        vertex2.push_back(x1);
        vertex2.push_back(y1);
        vertex2.push_back(y + 1);
        
        vertex3.push_back(x2);
        vertex3.push_back(y2);
        vertex3.push_back(y + 1);
        
        vertex4.push_back(x2);
        vertex4.push_back(y2);
        vertex4.push_back(y);
    } else if (orientation == 1) { // south wall:
        normal.push_back(0.0);
        normal.push_back(0.0);
        normal.push_back(1.0);
        
        float x1 = radius2 * cos(phi1);
        float x2 = radius * cos(phi1);
        float x3 = radius * cos(phi2);
        float x4 = radius2 * cos(phi2);
        float y1 = radius2 * sin(phi1);
        float y2 = radius * sin(phi1);
        float y3 = radius * sin(phi2);
        float y4 = radius2 * sin(phi2);
    
        vertex1.push_back(x2);
        vertex1.push_back(y2);
        vertex1.push_back(y + HALF_WALL_THICKNESS);
        
        vertex2.push_back(x3);
        vertex2.push_back(y3);
        vertex2.push_back(y + HALF_WALL_THICKNESS);
        
        vertex3.push_back(x4);
        vertex3.push_back(y4);
        vertex3.push_back(y + HALF_WALL_THICKNESS);
        
        vertex4.push_back(x1);
        vertex4.push_back(y1);
        vertex4.push_back(y + HALF_WALL_THICKNESS);
    } else if (orientation == 2) { // west wall:
        float phi1 = (x - HALF_WALL_THICKNESS) / radius;
        
        normal.push_back(sin(phi1));
        normal.push_back(-cos(phi1));
        normal.push_back(0.0);
        
        float x1 = radius * cos(phi1);
        float x2 = radius2 * cos(phi1);
        float y1 = radius * sin(phi1);
        float y2 = radius2 * sin(phi1);
    
        vertex1.push_back(x1);
        vertex1.push_back(y1);
        vertex1.push_back(y);
        
        vertex2.push_back(x1);
        vertex2.push_back(y1);
        vertex2.push_back(y + 1);
        
        vertex3.push_back(x2);
        vertex3.push_back(y2);
        vertex3.push_back(y + 1);
        
        vertex4.push_back(x2);
        vertex4.push_back(y2);
        vertex4.push_back(y);
    } else { // north wall:
        normal.push_back(0.0);
        normal.push_back(0.0);
        normal.push_back(-1.0);
        
        float x1 = radius2 * cos(phi1);
        float x2 = radius * cos(phi1);
        float x3 = radius * cos(phi2);
        float x4 = radius2 * cos(phi2);
        float y1 = radius2 * sin(phi1);
        float y2 = radius * sin(phi1);
        float y3 = radius * sin(phi2);
        float y4 = radius2 * sin(phi2);
    
        vertex1.push_back(x2);
        vertex1.push_back(y2);
        vertex1.push_back(y - HALF_WALL_THICKNESS);
        
        vertex2.push_back(x3);
        vertex2.push_back(y3);
        vertex2.push_back(y - HALF_WALL_THICKNESS);
        
        vertex3.push_back(x4);
        vertex3.push_back(y4);
        vertex3.push_back(y - HALF_WALL_THICKNESS);
        
        vertex4.push_back(x1);
        vertex4.push_back(y1);
        vertex4.push_back(y - HALF_WALL_THICKNESS);
    }    
}

std::vector<float>& Tile::get_vertex1() { return vertex1; }
std::vector<float>& Tile::get_vertex2() { return vertex2; }
std::vector<float>& Tile::get_vertex3() { return vertex3; }
std::vector<float>& Tile::get_vertex4() { return vertex4; }
std::vector<float>& Tile::get_normal() { return normal; }

std::string Tile::str()
{
    std::stringstream ss;
    ss << "            Tile" << std::endl;
    return ss.str();
}
