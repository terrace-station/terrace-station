#ifndef TILE_HH
#define TILE_HH

#include "hilfsfunktionen.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <math.h>
#include <GL/gl.h>

class Tile
{
public:
    GLfloat v1x; // Vertexkoordinaten zu jedem Eckpunkt
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
    
    GLfloat tx; // tangent
    GLfloat ty;
    GLfloat tz;
    
    GLfloat bx; // bitangent
    GLfloat by;
    GLfloat bz;
    
    GLfloat nx; // normal
    GLfloat ny;
    GLfloat nz;
    
    GLfloat cr; // Lichteinfallsrichtung
    GLfloat cg;
    GLfloat cb;
    
    Tile(int x, int y, float district_radius, float deck_radius);
    Tile(int x, int y, float district_radius, float deck_radius, int orientation, bool top);
    
    void setLightColor(float quelle_x, float quelle_y, float quelle_z);
    std::string str();
};

#endif
