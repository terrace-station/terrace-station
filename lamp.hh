#ifndef LAMP_HH
#define LAMP_HH

#include <math.h>
#include <GL/gl.h>

enum LAMPTYPE {
                  LAMP_STATIC=0,
                  LAMP_PULS,
                  LAMP_FLICKER,
                  LAMP_SPOT
               };

class Lamp
{
public:
   
   LAMPTYPE type;
   GLenum lightinuse;
   
   bool enabled;
   bool working;
   
   GLfloat position[4];
   GLfloat ambient[4];
   GLfloat diffuse[4];
   GLfloat specular[4];
   
   GLfloat spot_direction[3]; // Hierzu bislang nichts weiter implementiert;
   GLfloat spot_cutoff;
   GLfloat spot_exponent;
   
   GLfloat constant_attenuation;
   GLfloat linear_attenuation;
   GLfloat quadratic_attenuation;
   
   void lampbegin(bool alarm=false);
   void lampend();
   
   void set_lamptype(LAMPTYPE type_);
   
   void set_position(GLfloat position_x, GLfloat position_y, GLfloat position_z, GLfloat position_w);
   void set_position(GLfloat position_x, GLfloat position_y, GLfloat position_z);
   
   void set_ambient(GLfloat ambient_r, GLfloat ambient_g, GLfloat ambient_b, GLfloat ambient_a);
   void set_ambient(GLfloat ambient_r, GLfloat ambient_g, GLfloat ambient_b);
   
   void set_diffuse(GLfloat diffuse_r, GLfloat diffuse_g, GLfloat diffuse_b, GLfloat diffuse_a);
   void set_diffuse(GLfloat diffuse_r, GLfloat diffuse_g, GLfloat diffuse_b);
   
   void set_specular(GLfloat specular_r, GLfloat specular_g, GLfloat specular_b, GLfloat specular_a);
   void set_specular(GLfloat specular_r, GLfloat specular_g, GLfloat specular_b);
   
   void set_lightcolor(GLfloat r, GLfloat g, GLfloat b);
   
   void set_attenuation(GLfloat att_const, GLfloat att_linear, GLfloat att_quad);
   
   void set_std();
   
   Lamp();
   Lamp(LAMPTYPE type);
   Lamp(LAMPTYPE type, GLfloat position_x, GLfloat position_y, GLfloat position_z);
};

#endif
