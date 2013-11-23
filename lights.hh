#ifndef LIGHTS_HH
#define LIGHTS_HH


#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <GL/gl.h>

class Lights
{
public:
   
   float& laufzeit;
   
   GLfloat kamera_pos[4], kamera_ambi[4], kamera_diff[4], kamera_spec[4];
   GLfloat kamera_att_const, kamera_att_linear, kamera_att_quad;
   
   GLfloat sonne_pos[4],  sonne_ambi[4],  sonne_diff[4],  sonne_spec[4];
   GLfloat sonne_att_const, sonne_att_linear, sonne_att_quad;
   
   GLfloat warn1_pos[4],  warn1_ambi[4],  warn1_diff[4],  warn1_spec[4];
   GLfloat warn1_att_const, warn1_att_linear, warn1_att_quad;
   GLfloat warn1_dir[3];

   GLfloat warn2_pos[4],  warn2_ambi[4],  warn2_diff[4],  warn2_spec[4];
   GLfloat warn2_att_const, warn2_att_linear, warn2_att_quad;
   bool warn2_ein;
   
   void init_lights();
   void init_kamera();
   void init_sonne();
   void init_warn1();
   void init_warn2();
   
   void set_kamera_pos (GLfloat, GLfloat, GLfloat, GLfloat);
   void set_kamera_pos (GLfloat, GLfloat, GLfloat);
   void set_sonne_pos (GLfloat, GLfloat, GLfloat, GLfloat);
   void set_sonne_pos ();
   void set_warn1_pos (GLfloat, GLfloat, GLfloat, GLfloat);
   void set_warn1_pos (GLfloat, GLfloat, GLfloat);
   void set_warn2_pos (GLfloat, GLfloat, GLfloat, GLfloat);
   void set_warn2_pos (GLfloat, GLfloat, GLfloat);
   
   void set_kamera_ambi(GLfloat, GLfloat, GLfloat, GLfloat);
   
   void set_kamera_diff(GLfloat, GLfloat, GLfloat, GLfloat);
   
   void set_kamera_spec(GLfloat, GLfloat, GLfloat, GLfloat);
   
   void set_kamera_att (GLfloat, GLfloat, GLfloat);
   void set_warn1_att  (GLfloat, GLfloat, GLfloat);
   void set_warn1_att  (GLfloat);
   void set_warn2_att  (GLfloat, GLfloat, GLfloat);
   void set_warn2_att  (GLfloat);
   
   void update_warn1();
   void update_warn2();
   
   void kamera_on();
   void kamera_off();
   void sonne_on();
   void sonne_off();
   void warn1_on();
   void warn1_off();
   void warn2_on();
   void warn2_off();
   
   
   Lights(float& laufzeit);
};

#endif