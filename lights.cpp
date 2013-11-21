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
}


void Lights::init_sonne()
{
   sonne_pos[0]  = 100000; sonne_pos[1]= 0  ;sonne_pos[2]  = 0  ; sonne_pos[3]  = 0  ;
   sonne_ambi[0] = 0.0; sonne_ambi[1] = 0.0; sonne_ambi[2] = 0.0; sonne_ambi[3] = 1.0;
   sonne_diff[0] = 1.0; sonne_diff[1] = 1.0; sonne_diff[2] = 1.0; sonne_diff[3] = 1.0;
   sonne_spec[0] = 1.0; sonne_spec[1] = 1.0; sonne_spec[2] = 1.0; sonne_spec[3] = 1.0;
   
   glLightfv(GL_LIGHT1, GL_POSITION, sonne_pos);
   glLightfv(GL_LIGHT1, GL_AMBIENT,  sonne_ambi);
   glLightfv(GL_LIGHT1, GL_DIFFUSE,  sonne_diff);
   glLightfv(GL_LIGHT1, GL_SPECULAR, sonne_spec);
}


void Lights::init_kamera()
{
   kamera_pos[0]  = 0  ; kamera_pos[1]  = 0  ; kamera_pos[2]  = 0  ; kamera_pos[3]  = 0  ;
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


