#ifndef TILE_HH
#define TILE_HH

#include <sstream>
#include <string>
#include <vector>
#include <math.h>
#include <GL/gl.h>

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
    
    Tile(int x, int y, float district_radius, float deck_radius);
    Tile(int x, int y, float district_radius, float deck_radius, int orientation, bool top);
    
    std::string str();
};

#endif
