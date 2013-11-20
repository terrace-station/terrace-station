#ifndef TILE_HH
#define TILE_HH

#include <sstream>
#include <string>
#include <vector>
#include <math.h>
#include <GL/gl.h>

class Tile
{
    GLfloat vertex1x;
    GLfloat vertex1y;
    GLfloat vertex1z;
    GLfloat vertex2x;
    GLfloat vertex2y;
    GLfloat vertex2z;
    GLfloat vertex3x;
    GLfloat vertex3y;
    GLfloat vertex3z;
    GLfloat vertex4x;
    GLfloat vertex4y;
    GLfloat vertex4z;
    GLfloat normalx;
    GLfloat normaly;
    GLfloat normalz;
    
public:
    Tile(int x, int y, float district_radius, float deck_radius);
    Tile(int x, int y, float district_radius, float deck_radius, int orientation, bool top);
    
    GLfloat& get_vertex1x();
    GLfloat& get_vertex1y();
    GLfloat& get_vertex1z();
    GLfloat& get_vertex2x();
    GLfloat& get_vertex2y();
    GLfloat& get_vertex2z();
    GLfloat& get_vertex3x();
    GLfloat& get_vertex3y();
    GLfloat& get_vertex3z();
    GLfloat& get_vertex4x();
    GLfloat& get_vertex4y();
    GLfloat& get_vertex4z();
    GLfloat& get_normalx();
    GLfloat& get_normaly();
    GLfloat& get_normalz();
    
    std::string str();
};

#endif
