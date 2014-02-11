#ifndef GLCAM_HH
#define GLCAM_HH

#include "hilfsfunktionen.h"

#include <GL/gl.h>
// #include <GL/glu.h>

class Glcam
{
public:
   
    float radius;
    float phi;
    float z;
    float zoom;
    float theta;
    float psi;
    
    float radius_min, radius_max;
    float phi_min, phi_max;
    float z_min, z_max;
    float zoom_min, zoom_max;
    float theta_min, theta_max;
    float psi_min, psi_max;
    
    int upside; // 1: e_r ist oben, -1: -e_r ist oben, 2: e_phi ist oben (unbenutzt), 3: e_z ist oben
    
    GLfloat kamera_x;
    GLfloat kamera_y;
    GLfloat kamera_z;
    
    GLfloat pos_x;
    GLfloat pos_y;
    GLfloat pos_z;
    
    GLfloat oben_x;
    GLfloat oben_y;
    GLfloat oben_z;
    
    void set_upside(int upside_);
    void set_start(float radius_, float phi_, float z_, float zoom_, float theta_, float psi_);
    void set_boundaries(float radius_min_, float radius_max_,
                        float phi_min_, float phi_max_,
                        float z_min_, float z_max_,
                        float zoom_min_, float zoom_max_,
                        float theta_min_, float theta_max_,
                        float psi_min_, float psi_max_);
    void calc_position();
    
    Glcam();
};

#endif
