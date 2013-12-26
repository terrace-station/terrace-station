#ifndef TILE_HH
#define TILE_HH

#include <sstream>
#include <string>
#include <vector>
#include <math.h>
#include <GL/gl.h>

enum TileType {
                WALL_EAST       = 0,
                WALL_SOUTH      = 1,
                WALL_WEST       = 2,
                WALL_NORTH      = 3,
                WALL_ROOF_EAST  = 4,
                WALL_ROOF_SOUTH = 5,
                WALL_ROOF_WEST  = 6,
                WALL_ROOF_NORTH = 7,
                FLOOR           = 8,
                ROOF            = 9
            };

class Tile
{
public:
    GLfloat v1x;
    GLfloat v1y;
    GLfloat v1z;
    GLfloat v2x;
    GLfloat v2y;
    GLfloat v2z;
    GLfloat v3x;
    GLfloat v3y;
    GLfloat v3z;
    GLfloat v4x;
    GLfloat v4y;
    GLfloat v4z;
    GLfloat nx;
    GLfloat ny;
    GLfloat nz;
    
    Tile(int x, int y, float district_radius, float deck_radius, TileType type);
    
    std::string str();
};

#endif
