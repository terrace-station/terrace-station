#ifndef TILE_HH
#define TILE_HH

#include <sstream>
#include <string>
#include <vector>
#include <math.h>

class Tile
{
    std::vector<float> vertex1;
    std::vector<float> vertex2;
    std::vector<float> vertex3;
    std::vector<float> vertex4;
    std::vector<float> normal;
    
public:
    Tile(int x, int y, float radius);
    Tile(int x, int y, float radius, int orientation, bool top);
    
    std::vector<float>& get_vertex1();
    std::vector<float>& get_vertex2();
    std::vector<float>& get_vertex3();
    std::vector<float>& get_vertex4();
    std::vector<float>& get_normal();
    
    std::string str();
};

#endif
