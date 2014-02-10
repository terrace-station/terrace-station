#ifndef GLCAM_HH
#define GLCAM_HH

#include <GL/gl.h>
// #include <GL/glu.h>

class Glcam
{
public:
   
   float theta, phi, psi;
   float theta_soll, phi_soll, psi_soll;
   
   float zoom;
   float zoom_soll;
   
   GLfloat pos_x;
   GLfloat pos_y;
   GLfloat pos_z;
   
   GLfloat oben_x;
   GLfloat oben_y;
   GLfloat oben_z;
   
   GLfloat dir_x;
   GLfloat dir_y;
   GLfloat dir_z;
   
//    Glcam();
    
};

#endif
