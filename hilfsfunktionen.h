#ifndef HILF_H
#define HILF_H

#include <math.h>
#include <GL/gl.h>

#define PI   3.14159265358979323846264338327950288419716939937510582097494459230781640628620899862803482534211
#define RAD  0.0174532930056254069010416666666666677
#define GRAD 57.2957779186820467344297304465919085

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


    static void station2deck(float& station_x, float& station_y, float& station_z, float& deck_x, float& deck_y)
    {
        float district_radius = sqrt(station_x*station_x + station_y*station_y);
        float phi = atan2(station_y, station_x);
        
        deck_x = district_radius * phi;
        deck_y = station_z;
    }


    static void station2deck(double& station_x, double& station_y, double& station_z, float& deck_x, float& deck_y)
    {
        float district_radius = sqrt(station_x*station_x + station_y*station_y);
        float phi = atan2(station_y, station_x);
        
        deck_x = district_radius * phi;
        deck_y = station_z;
    }


    static void transform_to_station(GLfloat tmp_r, GLfloat tmp_phi, GLfloat tmp_z)
    {
        glRotatef(-90, 1.0, 0.0, 0.0);
        glRotatef(-90-tmp_phi/RAD, 0.0, 1.0, 0.0);
        glTranslatef(0.0, 0.0, -tmp_r);
        glTranslatef(0.0, -tmp_z, 0.0);
    }

}

#endif
