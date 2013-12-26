#ifndef HILF_H
#define HILF_H

#include <math.h>

#define PI    3.14159265358979323846
#define RAD 0.01745329252

namespace hilf
{

    static void normieren(double& normal_x_, double& normal_y_, double& normal_z_)
    {
        double laenge = sqrt((normal_x_)*(normal_x_)
                            + (normal_y_)*(normal_y_)
                            + (normal_z_)*(normal_z_));
        if (laenge != 0.0)
        {
            normal_x_ /= laenge;
            normal_y_ /= laenge;
            normal_z_ /= laenge;
        }
    }


    static void normieren(float& normal_x_, float& normal_y_, float& normal_z_)
    {
        double laenge = sqrt((normal_x_)*(normal_x_)
                            + (normal_y_)*(normal_y_)
                            + (normal_z_)*(normal_z_));
        if (laenge != 0.0)
        {
            normal_x_ /= laenge;
            normal_y_ /= laenge;
            normal_z_ /= laenge;
        }
    }

    /**
     * Transform from 2D deck coordinates to 3D station coordinates
     */
    static void deck2station(float deck_x, float deck_y, float district_radius, float deck_radius, float& station_x, float& station_y, float& station_z)
    {
        float phi = deck_x / district_radius;
        
        station_x = deck_radius * cos(phi);
        station_y = deck_radius * sin(phi);
        station_z = deck_y;
    }

}

#endif
