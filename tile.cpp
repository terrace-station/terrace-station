#include "tile.hh"

#define DECK_HEIGHT 2
#define HALF_WALL_THICKNESS 0.05

/**
 * Creates a new floor tile
 * 
 * \param   x               x-position in local deck-coordinates
 * \param   y               y-position in local deck-coordinates
 * \param   district_radius district radius
 * \param   deck_radius     deck radius
 */
Tile::Tile(int x, int y, float district_radius, float deck_radius)
{
    float radius = deck_radius;
    float phi1 = x / district_radius;
    float phi2 = (x + 1) / district_radius;
    float phi = (x + 0.5) / district_radius;
    
    float x1 = radius * cos(phi1);
    float x2 = radius * cos(phi2);
    float y1 = radius * sin(phi1);
    float y2 = radius * sin(phi2);
    
    vertex1x = x1;
    vertex1y = y1;
    vertex1z = y;
    
    vertex2x = x1;
    vertex2y = y1;
    vertex2z = y + 1;
    
    vertex3x = x2;
    vertex3y = y2;
    vertex3z = y + 1;
    
    vertex4x = x2;
    vertex4y = y2;
    vertex4z = y;
    
    normalx = cos(phi);
    normaly = sin(phi);
    normalz = 0.0;
}

/**
 * Creates a new wall tile or a wall-top tile
 * 
 * \param   x               x-position in local deck-coordinates
 * \param   y               y-position in local deck-coordinates
 * \param   district_radius district radius
 * \param   deck_radius     deck radius
 * \param   orientation     wall-orientation (west: 0, north:1, east: 2, south:3)
 * \param   top             if true, create a wall-top tile
 */
Tile::Tile(int x, int y, float district_radius, float deck_radius, int orientation, bool top)
{
    float radius = deck_radius;
    float phi1 = x / district_radius;
    float phi2 = (x + 1) / district_radius;
    float radius2 = radius - DECK_HEIGHT;
    
    if (orientation == 0) { // east wall:
        float phi = x / district_radius;
        float phi_d = (x + HALF_WALL_THICKNESS) / district_radius;
        
        if (top) {
            normalx = cos(phi);
            normaly = sin(phi);
            normalz = 0.0;
        
            float x1 = radius2 * cos(phi_d);
            float x2 = radius2 * cos(phi);
            float y1 = radius2 * sin(phi_d);
            float y2 = radius2 * sin(phi);
            
            vertex1x = x1;
            vertex1y = y1;
            vertex1z = y;
            
            vertex2x = x1;
            vertex2y = y1;
            vertex2z = y + 1;
            
            vertex3x = x2;
            vertex3y = y2;
            vertex3z = y + 1;
            
            vertex4x = x2;
            vertex4y = y2;
            vertex4z = y;
        } else {
            normalx = -sin(phi_d);
            normaly = -cos(phi_d);
            normalz = 0.0;
        
            float x1 = radius * cos(phi_d);
            float x2 = radius2 * cos(phi_d);
            float y1 = radius * sin(phi_d);
            float y2 = radius2 * sin(phi_d);
            
            vertex1x = x1;
            vertex1y = y1;
            vertex1z = y;
            
            vertex2x = x1;
            vertex2y = y1;
            vertex2z = y + 1;
            
            vertex3x = x2;
            vertex3y = y2;
            vertex3z = y + 1;
            
            vertex4x = x2;
            vertex4y = y2;
            vertex4z = y;
        }
    } else if (orientation == 1) { // south wall:
        if (top) {
            normalx = cos(phi1);
            normaly = sin(phi1);
            normalz = 0.0;
            
            float x1 = radius2 * cos(phi1);
            float x2 = radius2 * cos(phi2);
            float y1 = radius2 * sin(phi1);
            float y2 = radius2 * sin(phi2);
        
            vertex1x = x1;
            vertex1y = y1;
            vertex1z = y + HALF_WALL_THICKNESS;
            
            vertex2x = x2;
            vertex2y = y2;
            vertex2z = y + HALF_WALL_THICKNESS;
            
            vertex3x = x2;
            vertex3y = y2;
            vertex3z = y;
            
            vertex4x = x1;
            vertex4y = y1;
            vertex4z = y;
        } else {
            normalx = 0.0;
            normaly = 0.0;
            normalz = 1.0;
            
            float x1 = radius2 * cos(phi1);
            float x2 = radius * cos(phi1);
            float x3 = radius * cos(phi2);
            float x4 = radius2 * cos(phi2);
            float y1 = radius2 * sin(phi1);
            float y2 = radius * sin(phi1);
            float y3 = radius * sin(phi2);
            float y4 = radius2 * sin(phi2);
        
            vertex2x = x2;
            vertex2y = y2;
            vertex2z = y + HALF_WALL_THICKNESS;
            
            vertex1x = x3;
            vertex1y = y3;
            vertex1z = y + HALF_WALL_THICKNESS;
            
            vertex4x = x4;
            vertex4y = y4;
            vertex4z = y + HALF_WALL_THICKNESS;
            
            vertex3x = x1;
            vertex3y = y1;
            vertex3z = y + HALF_WALL_THICKNESS;
        }
    } else if (orientation == 2) { // west wall:
        float phi = x / district_radius;
        float phi_d = (x - HALF_WALL_THICKNESS) / district_radius;
        
        if (top) {
            normalx = cos(phi);
            normaly = sin(phi);
            normalz = 0.0;
            
            float x1 = radius2 * cos(phi_d);
            float x2 = radius2 * cos(phi);
            float y1 = radius2 * sin(phi_d);
            float y2 = radius2 * sin(phi);
        
            vertex1x = x1;
            vertex1y = y1;
            vertex1z = y + 1;
            
            vertex2x = x1;
            vertex2y = y1;
            vertex2z = y;
            
            vertex3x = x2;
            vertex3y = y2;
            vertex3z = y;
            
            vertex4x = x2;
            vertex4y = y2;
            vertex4z = y + 1;
        } else {
            normalx = sin(phi_d);
            normaly = cos(phi_d);
            normalz = 0.0;
            
            float x1 = radius * cos(phi_d);
            float x2 = radius2 * cos(phi_d);
            float y1 = radius * sin(phi_d);
            float y2 = radius2 * sin(phi_d);
        
            vertex1x = x1;
            vertex1y = y1;
            vertex1z = y;
            
            vertex2x = x1;
            vertex2y = y1;
            vertex2z = y + 1;
            
            vertex3x = x2;
            vertex3y = y2;
            vertex3z = y + 1;
            
            vertex4x = x2;
            vertex4y = y2;
            vertex4z = y;
        }
    } else { // north wall:
        if (top) {
            normalx = cos(phi1);
            normaly = sin(phi1);
            normalz = 0.0;
            
            float x1 = radius2 * cos(phi1);
            float x2 = radius2 * cos(phi2);
            float y1 = radius2 * sin(phi1);
            float y2 = radius2 * sin(phi2);
        
            vertex1x = x1;
            vertex1y = y1;
            vertex1z = y - HALF_WALL_THICKNESS;
            
            vertex2x = x2;
            vertex2y = y2;
            vertex2z = y - HALF_WALL_THICKNESS;
            
            vertex3x = x2;
            vertex3y = y2;
            vertex3z = y;
            
            vertex4x = x1;
            vertex4y = y1;
            vertex4z = y;
        } else {
            normalx = 0.0;
            normaly = 0.0;
            normalz = -1.0;
            
            float x1 = radius2 * cos(phi1);
            float x2 = radius * cos(phi1);
            float x3 = radius * cos(phi2);
            float x4 = radius2 * cos(phi2);
            float y1 = radius2 * sin(phi1);
            float y2 = radius * sin(phi1);
            float y3 = radius * sin(phi2);
            float y4 = radius2 * sin(phi2);
        
            vertex1x = x2;
            vertex1y = y2;
            vertex1z = y - HALF_WALL_THICKNESS;
            
            vertex2x = x3;
            vertex2y = y3;
            vertex2z = y - HALF_WALL_THICKNESS;
            
            vertex3x = x4;
            vertex3y = y4;
            vertex3z = y - HALF_WALL_THICKNESS;
            
            vertex4x = x1;
            vertex4y = y1;
            vertex4z = y - HALF_WALL_THICKNESS;
        }
    }    
}

GLfloat& Tile::get_vertex1x() { return vertex1x; }
GLfloat& Tile::get_vertex1y() { return vertex1y; }
GLfloat& Tile::get_vertex1z() { return vertex1z; }
GLfloat& Tile::get_vertex2x() { return vertex2x; }
GLfloat& Tile::get_vertex2y() { return vertex2y; }
GLfloat& Tile::get_vertex2z() { return vertex2z; }
GLfloat& Tile::get_vertex3x() { return vertex3x; }
GLfloat& Tile::get_vertex3y() { return vertex3y; }
GLfloat& Tile::get_vertex3z() { return vertex3z; }
GLfloat& Tile::get_vertex4x() { return vertex4x; }
GLfloat& Tile::get_vertex4y() { return vertex4y; }
GLfloat& Tile::get_vertex4z() { return vertex4z; }
GLfloat& Tile::get_normalx()  { return normalx; }
GLfloat& Tile::get_normaly()  { return normaly; }
GLfloat& Tile::get_normalz()  { return normalz; }

std::string Tile::str()
{
    std::stringstream ss;
    ss << "            Tile" << std::endl;
    return ss.str();
}
