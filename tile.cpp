#include "tile.hh"
#include "hilfsfunktionen.h"

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
}

std::string Tile::str()
{
    std::stringstream ss;
    ss << "            Tile" << std::endl;
    return ss.str();
}
