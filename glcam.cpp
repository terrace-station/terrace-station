#include "glcam.hh"


Glcam::Glcam()
{
    set_start(100, 0, 0, 10, 45, 0);
    set_boundaries(100, 100, 
                   0, 360, 
                   -100, 100, 
                   1, 100, 
                   0, 180, 
                   0, 360);
    set_upside(3);
}


void Glcam::set_upside(int upside_)
{
   upside = upside_;
}


void Glcam::set_start(float radius_, float phi_, float z_, float zoom_, float theta_, float psi_)
{
   radius = radius_;
   phi    = phi_;
   z      = z_;
   zoom   = zoom_;
   theta  = theta_;
   psi    = psi_;
}


void Glcam::set_boundaries(float radius_min_, float radius_max_,
                           float phi_min_, float phi_max_,
                           float z_min_, float z_max_,
                           float zoom_min_, float zoom_max_,
                           float theta_min_, float theta_max_,
                           float psi_min_, float psi_max_)
{
   radius_min = radius_min_; radius_max = radius_max_;
   phi_min    = phi_min_   ; phi_max    = phi_max_   ;
   z_min      = z_min_     ; z_max      = z_max_     ;
   zoom_min   = zoom_min_  ; zoom_max   = zoom_max_  ;
   theta_min  = theta_min_ ; theta_max  = theta_max_ ;
   psi_min    = psi_min_   ; psi_max    = psi_max_   ;
}

void Glcam::calc_position()
{
    pos_x = radius*cos(phi*RAD);
    pos_y = radius*sin(phi*RAD);
    pos_z = z;
    
    kamera_x = (radius - zoom*cos(theta*RAD)) * cos(phi*RAD + zoom/radius*sin(theta*RAD)*cos(psi*RAD));
    kamera_y = (radius - zoom*cos(theta*RAD)) * sin(phi*RAD + zoom/radius*sin(theta*RAD)*cos(psi*RAD));
    kamera_z = pos_z + zoom*sin(theta*RAD)*sin(psi*RAD);
    
    switch(upside)
    {
        case -1:
            oben_x = -cos(phi*RAD);
            oben_y = -sin(phi*RAD);
            oben_z = 0;
            break;
            
        case 3:
            oben_x = 0;
            oben_y = 0;
            oben_z = 1;
            break;
            
        case 1:
            oben_x = cos(phi*RAD);
            oben_y = sin(phi*RAD);
            oben_z = 0;
            break;
            
        default:
            oben_x = 0;
            oben_y = 0;
            oben_z = 1;
    }
}









