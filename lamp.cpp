#include "lamp.hh"

#include "openglwidget.hh"

Lamp::Lamp()
{
   working = true;
   enabled = true;
   set_std();
}

Lamp::Lamp(LAMPTYPE type): type(type)
{
   working = true;
   enabled = true;
   set_std();
}

Lamp::Lamp(LAMPTYPE type, GLfloat position_x, GLfloat position_y, GLfloat position_z): type(type)
{
   working = true;
   enabled = true;
   set_std();
   set_position(position_x, position_y, position_z);
}

void Lamp::lampbegin()
{
   lightinuse = GL_LIGHT7;

   while(glIsEnabled(lightinuse)) // freies Licht suchen
   {
      if (lightinuse == GL_LIGHT4)
      {
         std::cout << "Mehr als 4 Lichter in Benutzung!" << std::endl;
         break;
      }
      lightinuse = lightinuse-1;
   }
      
   if (!enabled)
      return;
   
   glEnable(lightinuse);
   
   switch(type)
   {
      case LAMP_STATIC:
         glLightfv(lightinuse, GL_POSITION, position);
         glLightfv(lightinuse, GL_AMBIENT,  ambient);
         glLightfv(lightinuse, GL_DIFFUSE,  diffuse);
         glLightfv(lightinuse, GL_SPECULAR, specular);
         
         glLightf(lightinuse, GL_CONSTANT_ATTENUATION,  constant_attenuation);
         glLightf(lightinuse, GL_LINEAR_ATTENUATION,    linear_attenuation);
         glLightf(lightinuse, GL_QUADRATIC_ATTENUATION, quadratic_attenuation);
         break;
   
      case LAMP_PULS:
         
#define PULS_AMP  1
#define PULS_FREQ 2

         constant_attenuation = PULS_AMP+PULS_AMP*sin(Openglwidget::laufzeit*PULS_FREQ);
         
         glLightfv(lightinuse, GL_POSITION, position);
         glLightfv(lightinuse, GL_AMBIENT,  ambient);
         glLightfv(lightinuse, GL_DIFFUSE,  diffuse);
         glLightfv(lightinuse, GL_SPECULAR, specular);
         
         glLightf(lightinuse, GL_CONSTANT_ATTENUATION,  constant_attenuation);
         glLightf(lightinuse, GL_LINEAR_ATTENUATION,    linear_attenuation);
         glLightf(lightinuse, GL_QUADRATIC_ATTENUATION, quadratic_attenuation);
         break;
   
      case LAMP_FLICKER:
         
#define FLICKER_ON_PROB  2
#define FLICKER_OFF_PROB 4

         if (working)
         {
            if (constant_attenuation < 0.3)
               constant_attenuation = 0.7;
            
            if ((rand()%(int(Openglwidget::fps_average)+1)) < FLICKER_OFF_PROB)
            {
               working = false;
               constant_attenuation = 10.0;
            }
         }
         else
         {

            if ((rand()%(int(Openglwidget::fps_average)+1)) < FLICKER_ON_PROB)
            {
               working = true;
               constant_attenuation = 0.1;
            }
         }
         
         glLightfv(lightinuse, GL_POSITION, position);
         glLightfv(lightinuse, GL_AMBIENT,  ambient);
         glLightfv(lightinuse, GL_DIFFUSE,  diffuse);
         glLightfv(lightinuse, GL_SPECULAR, specular);
         
         glLightf(lightinuse, GL_CONSTANT_ATTENUATION,  constant_attenuation);
         glLightf(lightinuse, GL_LINEAR_ATTENUATION,    linear_attenuation);
         glLightf(lightinuse, GL_QUADRATIC_ATTENUATION, quadratic_attenuation);
         break;
         
      case LAMP_SPOT:
            // TODO
         break;
   
   }
}

void Lamp::lampend()
{
   glDisable(lightinuse);
}

void Lamp::set_std()
{
   
   switch(type)
   {
      case LAMP_STATIC:
         set_position(0.0, 0.0, 0.0);
         set_lightcolor(1.0, 1.0, 1.0);
         set_attenuation(0.5, 0.1, 0.0);
         break;
      case LAMP_PULS:
         set_position(0.0, 0.0, 0.0);
         set_lightcolor(1.0, 0.0, 0.0);
         set_attenuation(0.3, 0.3, 0.0);
         break;
      case LAMP_FLICKER:
         set_position(0.0, 0.0, 0.0);
         set_lightcolor(0.8, 0.8, 1.0);
         set_attenuation(0.3, 0.3, 0.0);
         break;
      case LAMP_SPOT:    // TODO
         set_position(0.0, 0.0, 0.0);
         set_lightcolor(1.0, 1.0, 1.0);
         set_attenuation(0.5, 0.5, 0.0);
         break;
      default:
         set_position(0.0, 0.0, 0.0);
         set_lightcolor(1.0, 1.0, 1.0);
         set_attenuation(0.5, 0.5, 0.0);
   }
}

void Lamp::set_lamptype(LAMPTYPE type_)
{
   type = type_;
   set_std();
}

void Lamp::set_position(GLfloat position_x, GLfloat position_y, GLfloat position_z, GLfloat position_w)
{
   position[0] = position_x;
   position[1] = position_y;
   position[2] = position_z;
   position[3] = position_w;
}

void Lamp::set_position(GLfloat position_x, GLfloat position_y, GLfloat position_z)
{
   position[0] = position_x;
   position[1] = position_y;
   position[2] = position_z;
   position[3] = 1.0;
}

void Lamp::set_ambient(GLfloat ambient_r, GLfloat ambient_g, GLfloat ambient_b, GLfloat ambient_a)
{
   ambient[0] = ambient_r;
   ambient[1] = ambient_g;
   ambient[2] = ambient_b;
   ambient[3] = ambient_a;
}

void Lamp::set_ambient(GLfloat ambient_r, GLfloat ambient_g, GLfloat ambient_b)
{
   ambient[0] = ambient_r;
   ambient[1] = ambient_g;
   ambient[2] = ambient_b;
   ambient[3] = 1.0;
}

void Lamp::set_diffuse(GLfloat diffuse_r, GLfloat diffuse_g, GLfloat diffuse_b, GLfloat diffuse_a)
{
   diffuse[0] = diffuse_r;
   diffuse[1] = diffuse_g;
   diffuse[2] = diffuse_b;
   diffuse[3] = diffuse_a;
}

void Lamp::set_diffuse(GLfloat diffuse_r, GLfloat diffuse_g, GLfloat diffuse_b)
{
   diffuse[0] = diffuse_r;
   diffuse[1] = diffuse_g;
   diffuse[2] = diffuse_b;
   diffuse[3] = 1.0;
}

void Lamp::set_specular(GLfloat specular_r, GLfloat specular_g, GLfloat specular_b, GLfloat specular_a)
{
   specular[0] = specular_r;
   specular[1] = specular_g;
   specular[2] = specular_b;
   specular[3] = specular_a;
}

void Lamp::set_specular(GLfloat specular_r, GLfloat specular_g, GLfloat specular_b)
{
   specular[0] = specular_r;
   specular[1] = specular_g;
   specular[2] = specular_b;
   specular[3] = 1.0;
}

void Lamp::set_lightcolor(GLfloat r, GLfloat g, GLfloat b)
{
   ambient[0] = r;
   ambient[1] = g;
   ambient[2] = b;
   ambient[3] = 1.0;
   diffuse[0] = r;
   diffuse[1] = g;
   diffuse[2] = b;
   diffuse[3] = 1.0;
   specular[0] = r;
   specular[1] = g;
   specular[2] = b;
   specular[3] = 1.0;
}

void Lamp::set_attenuation(GLfloat att_const, GLfloat att_linear, GLfloat att_quad)
{
   constant_attenuation  = att_const;
   linear_attenuation    = att_linear;
   quadratic_attenuation = att_quad;
}

   


   


