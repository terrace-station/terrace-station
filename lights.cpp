#include "lights.hh"


Lights::Lights(float& laufzeit): laufzeit(laufzeit)
{
//    spot_pos[0]  = 0  ; spot_pos[1]  = 0  ; spot_pos[2]  = 4  ; spot_pos[3]  = 0  ;
//    spot_dir[0]  = 1  ; spot_dir[1]  = 1  ; spot_dir[2]  = 0  ;
//    spot_ambi[0] = 1.0; spot_ambi[1] = 0.8; spot_ambi[2] = 0.0; spot_ambi[3] = 1.0;
//    spot_diff[0] = 1.0; spot_diff[1] = 0.5; spot_diff[2] = 0.5; spot_diff[3] = 1.0;
//    spot_spec[0] = 1.0; spot_spec[1] = 0.5; spot_spec[2] = 0.5; spot_spec[3] = 1.0;
}

void Lights::init_lights()
{
   init_kamera();
   init_sonne();
   init_warn1();
   init_warn2();
}


void Lights::init_sonne()
{
   sonne_pos[0]  = 100000; sonne_pos[1]= 0  ;sonne_pos[2]  = 0  ; sonne_pos[3]  = 1.0;
   sonne_ambi[0] = 0.1; sonne_ambi[1] = 0.1; sonne_ambi[2] = 0.1; sonne_ambi[3] = 1.0;
   sonne_diff[0] = 1.0; sonne_diff[1] = 1.0; sonne_diff[2] = 1.0; sonne_diff[3] = 1.0;
   sonne_spec[0] = 1.0; sonne_spec[1] = 1.0; sonne_spec[2] = 1.0; sonne_spec[3] = 1.0;
   
   glLightfv(GL_LIGHT1, GL_POSITION, sonne_pos);
   glLightfv(GL_LIGHT1, GL_AMBIENT,  sonne_ambi);
   glLightfv(GL_LIGHT1, GL_DIFFUSE,  sonne_diff);
   glLightfv(GL_LIGHT1, GL_SPECULAR, sonne_spec);
}


void Lights::init_kamera()
{
   kamera_pos[0]  = 0  ; kamera_pos[1]  = 0  ; kamera_pos[2]  = 0  ; kamera_pos[3]  = 1.0;
   kamera_ambi[0] = 0.5; kamera_ambi[1] = 0.5; kamera_ambi[2] = 0.5; kamera_ambi[3] = 1.0;
   kamera_diff[0] = 1.0; kamera_diff[1] = 1.0; kamera_diff[2] = 1.0; kamera_diff[3] = 1.0;
   kamera_spec[0] = 1.0; kamera_spec[1] = 1.0; kamera_spec[2] = 1.0; kamera_spec[3] = 1.0;
   
   glLightfv(GL_LIGHT0, GL_POSITION, kamera_pos);
   glLightfv(GL_LIGHT0, GL_AMBIENT,  kamera_ambi);
   glLightfv(GL_LIGHT0, GL_DIFFUSE,  kamera_diff);
   glLightfv(GL_LIGHT0, GL_SPECULAR, kamera_spec);
   
   kamera_att_const = 1.0; kamera_att_linear = 0.01; kamera_att_quad = 0.0;
   
   glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION,  kamera_att_const);
   glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION,    kamera_att_linear);
   glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, kamera_att_quad);
}


void Lights::init_warn1()
{
   warn1_pos[0]  = 0  ; warn1_pos[1]  = 0  ; warn1_pos[2]  = 0  ; warn1_pos[3]  = 1.0;
   warn1_ambi[0] = 0.8; warn1_ambi[1] = 0.0; warn1_ambi[2] = 0.0; warn1_ambi[3] = 1.0;
   warn1_diff[0] = 0.8; warn1_diff[1] = 0.0; warn1_diff[2] = 0.0; warn1_diff[3] = 1.0;
   warn1_spec[0] = 0.8; warn1_spec[1] = 0.0; warn1_spec[2] = 0.0; warn1_spec[3] = 1.0;
   
   glLightfv(GL_LIGHT2, GL_POSITION, warn1_pos);
   glLightfv(GL_LIGHT2, GL_AMBIENT,  warn1_ambi);
   glLightfv(GL_LIGHT2, GL_DIFFUSE,  warn1_diff);
   glLightfv(GL_LIGHT2, GL_SPECULAR, warn1_spec);
   
   warn1_att_const = 1.0; warn1_att_linear = 0.1; warn1_att_quad = 0.0;
   
   glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION,  warn1_att_const);
   glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION,    warn1_att_linear);
   glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, warn1_att_quad);
}


void Lights::init_warn2()
{
   warn2_pos[0]  = 0  ; warn2_pos[1]  = 0  ; warn2_pos[2]  = 0  ; warn2_pos[3]  = 1.0;
   warn2_ambi[0] = 0.8; warn2_ambi[1] = 0.8; warn2_ambi[2] = 1.0; warn2_ambi[3] = 1.0;
   warn2_diff[0] = 0.8; warn2_diff[1] = 0.8; warn2_diff[2] = 1.0; warn2_diff[3] = 1.0;
   warn2_spec[0] = 0.8; warn2_spec[1] = 0.8; warn2_spec[2] = 1.0; warn2_spec[3] = 1.0;
   
   glLightfv(GL_LIGHT3, GL_POSITION, warn2_pos);
   glLightfv(GL_LIGHT3, GL_AMBIENT,  warn2_ambi);
   glLightfv(GL_LIGHT3, GL_DIFFUSE,  warn2_diff);
   glLightfv(GL_LIGHT3, GL_SPECULAR, warn2_spec);
   
   warn2_att_const = 0.1; warn2_att_linear = 0.5; warn2_att_quad = 0.0;
   warn2_ein = true;
   
   glLightf(GL_LIGHT3, GL_CONSTANT_ATTENUATION,  warn2_att_const);
   glLightf(GL_LIGHT3, GL_LINEAR_ATTENUATION,    warn2_att_linear);
   glLightf(GL_LIGHT3, GL_QUADRATIC_ATTENUATION, warn2_att_quad);
}


void Lights::set_kamera_pos(GLfloat x, GLfloat y, GLfloat z, GLfloat a)
{
   kamera_pos[0] = x; kamera_pos[1] = y; kamera_pos[2] = z; kamera_pos[3] = a;
   glLightfv(GL_LIGHT0, GL_POSITION, kamera_pos);
}


void Lights::set_kamera_pos(GLfloat x, GLfloat y, GLfloat z)
{
   kamera_pos[0] = x; kamera_pos[1] = y; kamera_pos[2] = z;
   glLightfv(GL_LIGHT0, GL_POSITION, kamera_pos);
}


void Lights::set_sonne_pos(GLfloat x, GLfloat y, GLfloat z, GLfloat a)
{
   sonne_pos[0] = x; sonne_pos[1] = y; sonne_pos[2] = z; sonne_pos[3] = a;
   glLightfv(GL_LIGHT1, GL_POSITION, sonne_pos);
}


void Lights::set_sonne_pos()
{
   glLightfv(GL_LIGHT1, GL_POSITION, sonne_pos);
}


void Lights::set_warn1_pos(GLfloat x, GLfloat y, GLfloat z, GLfloat a)
{
   warn1_pos[0] = x; warn1_pos[1] = y; warn1_pos[2] = z; warn1_pos[3] = a;
   glLightfv(GL_LIGHT2, GL_POSITION, warn1_pos);
}


void Lights::set_warn1_pos(GLfloat x, GLfloat y, GLfloat z)
{
   warn1_pos[0] = x; warn1_pos[1] = y; warn1_pos[2] = z;
   glLightfv(GL_LIGHT2, GL_POSITION, warn1_pos);
}


void Lights::set_warn2_pos(GLfloat x, GLfloat y, GLfloat z, GLfloat a)
{
   warn2_pos[0] = x; warn2_pos[1] = y; warn2_pos[2] = z; warn2_pos[3] = a;
   glLightfv(GL_LIGHT3, GL_POSITION, warn2_pos);
}


void Lights::set_warn2_pos(GLfloat x, GLfloat y, GLfloat z)
{
   warn2_pos[0] = x; warn2_pos[1] = y; warn2_pos[2] = z;
   glLightfv(GL_LIGHT3, GL_POSITION, warn2_pos);
}


void Lights::set_kamera_ambi(GLfloat x, GLfloat y, GLfloat z, GLfloat a)
{
   kamera_ambi[0] = x; kamera_ambi[1] = y; kamera_ambi[2] = z; kamera_ambi[3] = a;
   glLightfv(GL_LIGHT0, GL_AMBIENT, kamera_ambi);
}


void Lights::set_kamera_diff(GLfloat x, GLfloat y, GLfloat z, GLfloat a)
{
   kamera_diff[0] = x; kamera_diff[1] = y; kamera_diff[2] = z; kamera_diff[3] = a;
   glLightfv(GL_LIGHT0, GL_DIFFUSE, kamera_diff);
}


void Lights::set_kamera_spec(GLfloat x, GLfloat y, GLfloat z, GLfloat a)
{
   kamera_spec[0] = x; kamera_spec[1] = y; kamera_spec[2] = z; kamera_spec[3] = a;
   glLightfv(GL_LIGHT0, GL_SPECULAR, kamera_spec);
}


void Lights::set_kamera_att(GLfloat att_const, GLfloat att_linear, GLfloat att_quad)
{
   kamera_att_const = att_const; kamera_att_linear = att_linear; kamera_att_quad = att_quad;
   
   glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION,  kamera_att_const);
   glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION,    kamera_att_linear);
   glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, kamera_att_quad);
}


void Lights::set_warn1_att(GLfloat att_const, GLfloat att_linear, GLfloat att_quad)
{
   warn1_att_const = att_const; warn1_att_linear = att_linear; warn1_att_quad = att_quad;
   
   glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION,  warn1_att_const);
   glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION,    warn1_att_linear);
   glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, warn1_att_quad);
}


void Lights::set_warn1_att(GLfloat att_const)
{
   warn1_att_const = att_const;
   
   glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION,  warn1_att_const);
}


void Lights::set_warn2_att(GLfloat att_const, GLfloat att_linear, GLfloat att_quad)
{
   warn2_att_const = att_const; warn2_att_linear = att_linear; warn2_att_quad = att_quad;
   
   glLightf(GL_LIGHT3, GL_CONSTANT_ATTENUATION,  warn2_att_const);
   glLightf(GL_LIGHT3, GL_LINEAR_ATTENUATION,    warn2_att_linear);
   glLightf(GL_LIGHT3, GL_QUADRATIC_ATTENUATION, warn2_att_quad);
}


void Lights::set_warn2_att(GLfloat att_const)
{
   warn2_att_const = att_const;
   
   glLightf(GL_LIGHT3, GL_CONSTANT_ATTENUATION,  warn2_att_const);
}


#define WARN1_AMP  1
#define WARN1_FREQ 2

void Lights::update_warn1()
{
   set_warn1_att(WARN1_AMP+WARN1_AMP*sin(laufzeit*WARN1_FREQ));
}

void Lights::update_warn2()
{
   if (warn2_ein)
   {
      if ((rand()%100) < 40)
      {
         warn2_ein = false;
         set_warn2_att(3.0);
//          std::cout << "licht aus" << std::endl;
      }
   }
   else
   {
      if ((rand()%100) < 40)
      {
         warn2_ein = true;
         set_warn2_att(0.1);
//          std::cout << "licht ein" << std::endl;
      }
   }
}

void Lights::kamera_on()
{
   glEnable(GL_LIGHT0);
}

void Lights::kamera_off()
{
   glDisable(GL_LIGHT0);
}

void Lights::sonne_on()
{
   glEnable(GL_LIGHT1);
}

void Lights::sonne_off()
{
   glDisable(GL_LIGHT1);
}

void Lights::warn1_on()
{
   glEnable(GL_LIGHT2);
}

void Lights::warn1_off()
{
   glDisable(GL_LIGHT2);
}

void Lights::warn2_on()
{
   glEnable(GL_LIGHT3);
}

void Lights::warn2_off()
{
   glDisable(GL_LIGHT3);
}


