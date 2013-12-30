#include "tile.hh"
#include "hilfsfunktionen.h"

#include "openglwidget.hh"

#define DECK_HEIGHT 2
#define HALF_WALL_THICKNESS 0.1

/**
 * Creates a new tile
 * 
 * \param   x               x-position in local deck-coordinates
 * \param   y               y-position in local deck-coordinates
 * \param   district_radius district radius
 * \param   deck_radius     deck radius
 * \param   type            type of tile
 */
Tile::Tile(int x, int y, float district_radius, float deck_radius, TileType type)
{
    float phi;
    switch (type) {
        case WALL_ROOF_EAST:
            hilf::deck2station(x + HALF_WALL_THICKNESS, y,     district_radius, deck_radius - DECK_HEIGHT, v1x, v1y, v1z);
            hilf::deck2station(x + HALF_WALL_THICKNESS, y + 1, district_radius, deck_radius - DECK_HEIGHT, v2x, v2y, v2z);
            hilf::deck2station(x,                       y + 1, district_radius, deck_radius - DECK_HEIGHT, v3x, v3y, v3z);
            hilf::deck2station(x,                       y,     district_radius, deck_radius - DECK_HEIGHT, v4x, v4y, v4z);
            phi = x / district_radius;
            nx = cos(phi);
            ny = sin(phi);
            nz = 0.0;
            break;
            
        case WALL_EAST:
            hilf::deck2station(x + HALF_WALL_THICKNESS, y + 1, district_radius, deck_radius, v1x, v1y, v1z);
            hilf::deck2station(x + HALF_WALL_THICKNESS, y,     district_radius, deck_radius, v2x, v2y, v2z);
            hilf::deck2station(x + HALF_WALL_THICKNESS, y,     district_radius, deck_radius - DECK_HEIGHT, v3x, v3y, v3z);
            hilf::deck2station(x + HALF_WALL_THICKNESS, y + 1, district_radius, deck_radius - DECK_HEIGHT, v4x, v4y, v4z);
            phi = (x + HALF_WALL_THICKNESS) / district_radius;
            nx = sin(phi);
            ny = -cos(phi);
            nz = 0.0;
            break;
            
        case WALL_ROOF_SOUTH:
            hilf::deck2station(x,     y + HALF_WALL_THICKNESS, district_radius, deck_radius - DECK_HEIGHT, v1x, v1y, v1z);
            hilf::deck2station(x + 1, y + HALF_WALL_THICKNESS, district_radius, deck_radius - DECK_HEIGHT, v2x, v2y, v2z);
            hilf::deck2station(x + 1, y,                       district_radius, deck_radius - DECK_HEIGHT, v3x, v3y, v3z);
            hilf::deck2station(x,     y,                       district_radius, deck_radius - DECK_HEIGHT, v4x, v4y, v4z);
            phi = x / district_radius;
            nx = cos(phi);
            ny = sin(phi);
            nz = 0.0;
            break;
            
        case WALL_SOUTH:
            hilf::deck2station(x,     y + HALF_WALL_THICKNESS, district_radius, deck_radius, v1x, v1y, v1z);
            hilf::deck2station(x + 1, y + HALF_WALL_THICKNESS, district_radius, deck_radius, v2x, v2y, v2z);
            hilf::deck2station(x + 1, y + HALF_WALL_THICKNESS, district_radius, deck_radius - DECK_HEIGHT, v3x, v3y, v3z);
            hilf::deck2station(x,     y + HALF_WALL_THICKNESS, district_radius, deck_radius - DECK_HEIGHT, v4x, v4y, v4z);
            nx = 0.0;
            ny = 0.0;
            nz = -1.0;
            break;
            
        case WALL_ROOF_WEST:
            hilf::deck2station(x - HALF_WALL_THICKNESS, y + 1, district_radius, deck_radius - DECK_HEIGHT, v1x, v1y, v1z);
            hilf::deck2station(x - HALF_WALL_THICKNESS, y,     district_radius, deck_radius - DECK_HEIGHT, v2x, v2y, v2z);
            hilf::deck2station(x,                       y,     district_radius, deck_radius - DECK_HEIGHT, v3x, v3y, v3z);
            hilf::deck2station(x,                       y + 1, district_radius, deck_radius - DECK_HEIGHT, v4x, v4y, v4z);
            phi = x / district_radius;
            nx = cos(phi);
            ny = sin(phi);
            nz = 0.0;
            break;
            
        case WALL_WEST:
            hilf::deck2station(x - HALF_WALL_THICKNESS, y,     district_radius, deck_radius, v1x, v1y, v1z);
            hilf::deck2station(x - HALF_WALL_THICKNESS, y + 1, district_radius, deck_radius, v2x, v2y, v2z);
            hilf::deck2station(x - HALF_WALL_THICKNESS, y + 1, district_radius, deck_radius - DECK_HEIGHT, v3x, v3y, v3z);
            hilf::deck2station(x - HALF_WALL_THICKNESS, y,     district_radius, deck_radius - DECK_HEIGHT, v4x, v4y, v4z);
            phi = (x - HALF_WALL_THICKNESS) / district_radius;
            nx = -sin(phi);
            ny = cos(phi);
            nz = 0.0;
            break;
            
        case WALL_ROOF_NORTH:
            hilf::deck2station(x,     y - HALF_WALL_THICKNESS, district_radius, deck_radius - DECK_HEIGHT, v1x, v1y, v1z);
            hilf::deck2station(x + 1, y - HALF_WALL_THICKNESS, district_radius, deck_radius - DECK_HEIGHT, v2x, v2y, v2z);
            hilf::deck2station(x + 1, y,                       district_radius, deck_radius - DECK_HEIGHT, v3x, v3y, v3z);
            hilf::deck2station(x,     y,                       district_radius, deck_radius - DECK_HEIGHT, v4x, v4y, v4z);
            phi = x / district_radius;
            nx = cos(phi);
            ny = sin(phi);
            nz = 0.0;
            break;
            
        case WALL_NORTH:
            hilf::deck2station(x + 1, y - HALF_WALL_THICKNESS, district_radius, deck_radius, v1x, v1y, v1z);
            hilf::deck2station(x,     y - HALF_WALL_THICKNESS, district_radius, deck_radius, v2x, v2y, v2z);
            hilf::deck2station(x,     y - HALF_WALL_THICKNESS, district_radius, deck_radius - DECK_HEIGHT, v3x, v3y, v3z);
            hilf::deck2station(x + 1, y - HALF_WALL_THICKNESS, district_radius, deck_radius - DECK_HEIGHT, v4x, v4y, v4z);
            nx = 0.0;
            ny = 0.0;
            nz = 1.0;
            break;
            
        case ROOF:
            hilf::deck2station(x,     y,     district_radius, deck_radius - DECK_HEIGHT, v1x, v1y, v1z);
            hilf::deck2station(x,     y + 1, district_radius, deck_radius - DECK_HEIGHT, v2x, v2y, v2z);
            hilf::deck2station(x + 1, y + 1, district_radius, deck_radius - DECK_HEIGHT, v3x, v3y, v3z);
            hilf::deck2station(x + 1, y,     district_radius, deck_radius - DECK_HEIGHT, v4x, v4y, v4z);
            phi = (x + 0.5) / district_radius;
            nx = cos(phi);
            ny = sin(phi);
            nz = 0.0;
            break;
            
        case FLOOR:
            hilf::deck2station(x,     y,     district_radius, deck_radius, v1x, v1y, v1z);
            hilf::deck2station(x,     y + 1, district_radius, deck_radius, v2x, v2y, v2z);
            hilf::deck2station(x + 1, y + 1, district_radius, deck_radius, v3x, v3y, v3z);
            hilf::deck2station(x + 1, y,     district_radius, deck_radius, v4x, v4y, v4z);
            phi = (x + 0.5) / district_radius;
            nx = cos(phi);
            ny = sin(phi);
            nz = 0.0;
    }
    tx = (v3x - v4x);
    ty = (v3y - v4y);
    tz = (v3z - v4z);
    
    bx = (v1x - v4x);
    by = (v1y - v4y);
    bz = (v1z - v4z);
    
    hilf::normieren(tx, ty, tz);
    hilf::normieren(bx, by, bz);
    
}


void Tile::setLightDirection(float quelle_x, float quelle_y, float quelle_z)
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


void Tile::setLightDirection(bool lighted)
{
    if (lighted)
    {
        Openglwidget::light_inc[0] = 0.5;
        Openglwidget::light_inc[1] = 0.5;
        Openglwidget::light_inc[2] = 1.0;
    }
    else
    {
        Openglwidget::light_inc[0] = 0.5;
        Openglwidget::light_inc[1] = 0.5;
        Openglwidget::light_inc[2] = 0.515;
    }
}


std::string Tile::str()
{
    std::stringstream ss;
    ss << "            Tile" << std::endl;
    return ss.str();
}
