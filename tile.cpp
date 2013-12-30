#include "tile.hh"

#include "openglwidget.hh"

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
    
    v1x = x1;
    v1y = y1;
    v1z = y;
    
    v2x = x1;
    v2y = y1;
    v2z = y + 1;
    
    v3x = x2;
    v3y = y2;
    v3z = y + 1;
    
    v4x = x2;
    v4y = y2;
    v4z = y;
    
    nx = cos(phi);
    ny = sin(phi);
    nz = 0.0;
    
    tx = (v3x - v4x);
    ty = (v3y - v4y);
    tz = (v3z - v4z);
    
    bx = (v1x - v4x);
    by = (v1y - v4y);
    bz = (v1z - v4z);
    
    hilf::normieren(tx, ty, tz);
    hilf::normieren(bx, by, bz);
    
//     std::cout << "Tangent:    " << tx << ", " << ty << ", " << tz << std::endl;
//     std::cout << "Bitangent:  " << bx << ", " << by << ", " << bz << std::endl;
//     std::cout << "Normal:     " << nx << ", " << ny << ", " << nz << std::endl;
//     std::cout << std::endl;
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
            nx = cos(phi);
            ny = sin(phi);
            nz = 0.0;
        
            float x1 = radius2 * cos(phi_d);
            float x2 = radius2 * cos(phi);
            float y1 = radius2 * sin(phi_d);
            float y2 = radius2 * sin(phi);
            
            v1x = x1;
            v1y = y1;
            v1z = y;
            
            v2x = x1;
            v2y = y1;
            v2z = y + 1;
            
            v3x = x2;
            v3y = y2;
            v3z = y + 1;
            
            v4x = x2;
            v4y = y2;
            v4z = y;
        } else {
            nx = sin(phi_d);
            ny = -cos(phi_d);
            nz = 0.0;
        
            float x1 = radius * cos(phi_d);
            float x2 = radius2 * cos(phi_d);
            float y1 = radius * sin(phi_d);
            float y2 = radius2 * sin(phi_d);
            
            v2x = x1;
            v2y = y1;
            v2z = y;
            
            v1x = x1;
            v1y = y1;
            v1z = y + 1;
            
            v4x = x2;
            v4y = y2;
            v4z = y + 1;
            
            v3x = x2;
            v3y = y2;
            v3z = y;
        }
    } else if (orientation == 1) { // south wall:
        if (top) {
            nx = cos(phi1);
            ny = sin(phi1);
            nz = 0.0;
            
            float x1 = radius2 * cos(phi1);
            float x2 = radius2 * cos(phi2);
            float y1 = radius2 * sin(phi1);
            float y2 = radius2 * sin(phi2);
        
            v1x = x1;
            v1y = y1;
            v1z = y + HALF_WALL_THICKNESS;
            
            v2x = x2;
            v2y = y2;
            v2z = y + HALF_WALL_THICKNESS;
            
            v3x = x2;
            v3y = y2;
            v3z = y;
            
            v4x = x1;
            v4y = y1;
            v4z = y;
        } else {
            nx = 0.0;
            ny = 0.0;
            nz = -1.0;
            
            float x1 = radius2 * cos(phi1);
            float x2 = radius * cos(phi1);
            float x3 = radius * cos(phi2);
            float x4 = radius2 * cos(phi2);
            float y1 = radius2 * sin(phi1);
            float y2 = radius * sin(phi1);
            float y3 = radius * sin(phi2);
            float y4 = radius2 * sin(phi2);
        
            v1x = x2;
            v1y = y2;
            v1z = y + HALF_WALL_THICKNESS;
            
            v2x = x3;
            v2y = y3;
            v2z = y + HALF_WALL_THICKNESS;
            
            v3x = x4;
            v3y = y4;
            v3z = y + HALF_WALL_THICKNESS;
            
            v4x = x1;
            v4y = y1;
            v4z = y + HALF_WALL_THICKNESS;
        }
    } else if (orientation == 2) { // west wall:
        float phi = x / district_radius;
        float phi_d = (x - HALF_WALL_THICKNESS) / district_radius;
        
        if (top) {
            nx = cos(phi);
            ny = sin(phi);
            nz = 0.0;
            
            float x1 = radius2 * cos(phi_d);
            float x2 = radius2 * cos(phi);
            float y1 = radius2 * sin(phi_d);
            float y2 = radius2 * sin(phi);
        
            v1x = x1;
            v1y = y1;
            v1z = y + 1;
            
            v2x = x1;
            v2y = y1;
            v2z = y;
            
            v3x = x2;
            v3y = y2;
            v3z = y;
            
            v4x = x2;
            v4y = y2;
            v4z = y + 1;
        } else {
            nx = -sin(phi_d);
            ny = cos(phi_d);
            nz = 0.0;
            
            float x1 = radius * cos(phi_d);
            float x2 = radius2 * cos(phi_d);
            float y1 = radius * sin(phi_d);
            float y2 = radius2 * sin(phi_d);
        
            v1x = x1;
            v1y = y1;
            v1z = y;
            
            v2x = x1;
            v2y = y1;
            v2z = y + 1;
            
            v3x = x2;
            v3y = y2;
            v3z = y + 1;
            
            v4x = x2;
            v4y = y2;
            v4z = y;
        }
    } else { // north wall:
        if (top) {
            nx = cos(phi1);
            ny = sin(phi1);
            nz = 0.0;
            
            float x1 = radius2 * cos(phi1);
            float x2 = radius2 * cos(phi2);
            float y1 = radius2 * sin(phi1);
            float y2 = radius2 * sin(phi2);
        
            v1x = x1;
            v1y = y1;
            v1z = y - HALF_WALL_THICKNESS;
            
            v2x = x2;
            v2y = y2;
            v2z = y - HALF_WALL_THICKNESS;
            
            v3x = x2;
            v3y = y2;
            v3z = y;
            
            v4x = x1;
            v4y = y1;
            v4z = y;
        } else {
            nx = 0.0;
            ny = 0.0;
            nz = 1.0;
            
            float x1 = radius2 * cos(phi1);
            float x2 = radius * cos(phi1);
            float x3 = radius * cos(phi2);
            float x4 = radius2 * cos(phi2);
            float y1 = radius2 * sin(phi1);
            float y2 = radius * sin(phi1);
            float y3 = radius * sin(phi2);
            float y4 = radius2 * sin(phi2);
        
            v2x = x2;
            v2y = y2;
            v2z = y - HALF_WALL_THICKNESS;
            
            v1x = x3;
            v1y = y3;
            v1z = y - HALF_WALL_THICKNESS;
            
            v4x = x4;
            v4y = y4;
            v4z = y - HALF_WALL_THICKNESS;
            
            v3x = x1;
            v3y = y1;
            v3z = y - HALF_WALL_THICKNESS;
        }
    }
    
    tx = v3x - v4x;
    ty = v3y - v4y;
    tz = v3z - v4z;
    
    bx = v1x - v4x;
    by = v1y - v4y;
    bz = v1z - v4z;
    
    hilf::normieren(tx, ty, tz);
    hilf::normieren(bx, by, bz);
}


void Tile::setLightColor(float quelle_x, float quelle_y, float quelle_z)
{
   float tmp_x = 0.5*(v1x + v3x) - quelle_x;  // vec position - vec quelle - vektor vom licht zur aktuellen position zeigt
   float tmp_y = 0.5*(v1y + v3y) - quelle_y;
   float tmp_z = 0.5*(v1z + v1z) - quelle_z;
   hilf::normieren(tmp_x, tmp_y, tmp_z);
   
   cr = tmp_x*tx  + tmp_y*ty  + tmp_z*tz;
   cg = tmp_x*bx  + tmp_y*by  + tmp_z*bz;
   cb = tmp_x*nx  + tmp_y*ny  + tmp_z*nz;

   cr *= 0.5; cr += 0.5;
   cg *= 0.5; cg += 0.5;
   cb *= 0.5; cb += 0.5;
//    c1b *= 0.25; c1b += 0.75;
   
   Openglwidget::light_inc[0] = cr;
   Openglwidget::light_inc[1] = cg;
   Openglwidget::light_inc[2] = cb;
}


std::string Tile::str()
{
    std::stringstream ss;
    ss << "            Tile" << std::endl;
    return ss.str();
}
