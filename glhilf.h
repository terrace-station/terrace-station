#ifndef glhilf_H
#define glhilf_H

#include <math.h>
#include "hilfsfunktionen.h"


namespace glhilf
{
    static float farbpalette(double farbe_, char rgb_) // Diese Funktion errechnet aus einem Parameter zwischen -1 und 1 einen r, g oder b Wert und gibt ihn zurueck. Die Farbpalette ist Rot-Gruen-Blau.
    {
    //   farbe_/=2*(max_farbwert);
    //   farbe_+=0.5;

    // Farbpalette mit (dunkelblau, blau, cyan, gruen, gelb, rot, dunkelrot)
    if (rgb_=='r')
    {
        if(farbe_ < 1./6.)
            farbe_ =  0;
        else if(farbe_ < 1./3.)
            farbe_ =  0;
        else if(farbe_ < 0.5)
            farbe_ =  0;
        else if(farbe_ < 2./3.)
            farbe_ =  6*farbe_ - 3;
        else if(farbe_ < 5./6.)
            farbe_ =  1;
        else if(farbe_ < 1.0)
            farbe_ = -3*farbe_ + 3.5;
        else
            farbe_ = 0.5;
    }
    else if (rgb_=='g')
    {
        if(farbe_ < 1./6.)
        farbe_ =  0;
        else if(farbe_ < 1./3.)
        farbe_ =  6*farbe_ - 1;
        else if(farbe_ < 0.5)
        farbe_ =  1;
        else if(farbe_ < 2./3.)
        farbe_ =  1;
        else if(farbe_ < 5./6.)
        farbe_ = -6*farbe_ + 5;
        else
        farbe_ = 0;
    }
    if (rgb_=='b')
    {
        if(farbe_ < 0.)
            farbe_ =  0.5;
        else if(farbe_ < 1./6.)
            farbe_ =  3*farbe_ + 0.5;
        else if(farbe_ < 1./3.)
            farbe_ = 1;
        else if(farbe_ < 0.5)
            farbe_ = -6*farbe_ + 3;
        else if(farbe_ < 2./3.)
            farbe_ = 0;
        else if(farbe_ < 5./6.)
            farbe_ = 0;
        else
            farbe_ = 0;
    }

    return farbe_;
    }

    static void normieren(double& normal_x_, double& normal_y_, double& normal_z_)
    {
        double laenge = sqrt((normal_x_)*(normal_x_)
                            + (normal_y_)*(normal_y_)
                            + (normal_z_)*(normal_z_));

        normal_x_ /= laenge;
        normal_y_ /= laenge;
        normal_z_ /= laenge;
    }

    static void normieren(float& normal_x_, float& normal_y_, float& normal_z_)
    {
        float laenge = sqrt((normal_x_)*(normal_x_)
                            + (normal_y_)*(normal_y_)
                            + (normal_z_)*(normal_z_));

        normal_x_ /= laenge;
        normal_y_ /= laenge;
        normal_z_ /= laenge;
    }

static void draw_cone(float bx, float by, float bz, float tx, float ty, float tz, float radius, int detail)
{
    float hoehe   = sqrt((tx-bx)*(tx-bx) + (ty-by)*(ty-by) + (tz-bz)*(tz-bz));
    float winkel  = acos((tz-bz)/hoehe)/RAD;
    float winkel2 = atan(radius/hoehe); // halber Oeffungswinkel des Kegels;
    float x1_ = 0;
    float y1_ = 0;

    glEnable(GL_LIGHTING);
    glPushMatrix();
    glTranslatef(bx, by, bz);
    if (by-ty != 0 || tx-bx != 0)
        glRotatef(winkel, -ty+by, tx-bx, 0);
    else
        glRotatef(winkel, 1, 0, 0);

    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    for (int j=0; j<detail+1; ++j)
    {
        x1_ = radius*cos(2*PI*j/detail);
        y1_ = radius*sin(2*PI*j/detail);
        glVertex3f(x1_, y1_, 0);
    }
    glEnd();

    glBegin(GL_QUAD_STRIP);
    glNormal3f(0, 0, 1);
//     glVertex3f(0, 0, hoehe);
    for (int j=0; j<detail+1; ++j)
    {
        x1_ = radius*cos(2*PI*j/detail);
        y1_ = radius*sin(2*PI*j/detail);
        glNormal3f(cos(winkel2)*x1_/radius, cos(winkel2)*y1_/radius, sin(winkel2));
        glVertex3f(0, 0, hoehe);
        glVertex3f(x1_, y1_, 0);
    }
    glEnd();

    glPopMatrix();
    glDisable(GL_LIGHTING);
}


static void draw_pickdummy()
{
    glBegin(GL_QUAD_STRIP);
        glVertex3f(-0.5, -0.5, 1.0);
        glVertex3f(-0.5, -0.5, 0.0);
        glVertex3f( 0.5, -0.5, 1.0);
        glVertex3f( 0.5, -0.5, 0.0);
        glVertex3f( 0.5,  0.5, 1.0);
        glVertex3f( 0.5,  0.5, 0.0);
        glVertex3f(-0.5,  0.5, 1.0);
        glVertex3f(-0.5,  0.5, 0.0);
        glVertex3f(-0.5, -0.5, 1.0);
        glVertex3f(-0.5, -0.5, 0.0);
    glEnd();
}


static void draw_torus(float radiust, float radiusp, int detailt, int detailp)
{
   float x1, x2, x3, x4;
   float y1, y2, y3, y4;
   float z1, z2, z3, z4;
   
   float normal_x1, normal_x2;
   float normal_y1, normal_y2;
   float normal_z1, normal_z2;
   
   float winkelt, winkelp;
   
   for (int t=0; t<detailt; t++)
   {
      glBegin(GL_QUAD_STRIP);
      for (int p=0; p<detailp+1; p++)
      {
         winkelt = 2.0*PI*t/detailt;
         winkelp = 2.0*PI*p/detailp;
         
         x1 = (radiust + radiusp*cos(winkelp))*cos(winkelt);
         y1 = (radiust + radiusp*cos(winkelp))*sin(winkelt);
         z1 = radiusp*sin(winkelp);
         
         normal_x1 = x1 - radiust*cos(winkelt);
         normal_y1 = y1 - radiust*sin(winkelt);
         normal_z1 = z1;
         normieren(normal_x1, normal_y1, normal_z1);
         
         winkelt = 2.0*PI*(t+1)/detailt;
         
         x2 = (radiust + radiusp*cos(winkelp))*cos(winkelt);
         y2 = (radiust + radiusp*cos(winkelp))*sin(winkelt);
         z2 = radiusp*sin(winkelp);
         
         normal_x2 = x2 - radiust*cos(winkelt);
         normal_y2 = y2 - radiust*sin(winkelt);
         normal_z2 = z2;
         normieren(normal_x2, normal_y2, normal_z2);
         
         glNormal3f(normal_x2, normal_y2, normal_z2);
         glVertex3f(x2,y2,z2);
         glNormal3f(normal_x1, normal_y1, normal_z1);
         glVertex3f(x1,y1,z1);
      }
      glEnd();
   }
   
}

static void draw_cylinder(float bx, float by, float bz, float tx, float ty, float tz, float radius, int detail)
{
   float hoehe = sqrt((tx-bx)*(tx-bx) + (ty-by)*(ty-by) + (tz-bz)*(tz-bz));
   float winkel = acos((tz-bz)/hoehe)*180/PI;
   float x1_ = 0;
   float y1_ = 0;

   glEnable(GL_LIGHTING);
   glPushMatrix();
   glTranslatef(bx, by, bz);
   glRotatef(winkel, -ty+by, tx-bx, 0);

   glBegin(GL_TRIANGLE_FAN);
   glNormal3f(0, 0, 1);
   glVertex3f(0, 0, 0);
   for (int j=0; j<detail+1; j++)
   {
      x1_ = radius*cos(2*PI*j/detail);
      y1_ = radius*sin(2*PI*j/detail);
      glVertex3f(x1_, y1_, 0);
   }
   glEnd();

   glBegin(GL_TRIANGLE_FAN);
   glNormal3f(0, 0, 1);
   glVertex3f(0, 0, hoehe);
   for (int j=0; j<detail+1; j++)
   {
      x1_ = radius*cos(2*PI*j/detail);
      y1_ = radius*sin(2*PI*j/detail);
      glVertex3f(x1_, y1_, hoehe);
   }
   glEnd();

   glBegin(GL_QUAD_STRIP);
   for (int j=0; j<detail+1; j++)
   {
      x1_ = radius*cos(2*PI*j/detail);
      y1_ = radius*sin(2*PI*j/detail);
      glNormal3f(-x1_/radius, -y1_/radius, 0);
      glVertex3f(x1_, y1_, 0);
      glVertex3f(x1_, y1_, hoehe);
   }
   glEnd();

   glPopMatrix();
   glDisable(GL_LIGHTING);
}

static void draw_tube(float bx, float by, float bz, float tx, float ty, float tz, float radius, int detail)
{
   float hoehe = sqrt((tx-bx)*(tx-bx) + (ty-by)*(ty-by) + (tz-bz)*(tz-bz));
   float winkel = acos((tz-bz)/hoehe)*180/PI;
   float x1_ = 0;
   float y1_ = 0;

   glEnable(GL_LIGHTING);
   glPushMatrix();
   glTranslatef(bx, by, bz);
   glRotatef(winkel, -ty+by, tx-bx, 0);

   glBegin(GL_QUAD_STRIP);
   for (int j=0; j<detail+1; j++)
   {
      x1_ = radius*cos(2*PI*j/detail);
      y1_ = radius*sin(2*PI*j/detail);
      glNormal3f(x1_/radius, y1_/radius, 0);
      glVertex3f(x1_, y1_, 0);
      glVertex3f(x1_, y1_, hoehe);
   }
   glEnd();

   glPopMatrix();
   glDisable(GL_LIGHTING);
}


static void draw_tube_mesh(float bx, float by, float bz, float tx, float ty, float tz, float radius, int detail)
{
   float hoehe = sqrt((tx-bx)*(tx-bx) + (ty-by)*(ty-by) + (tz-bz)*(tz-bz));
   float winkel = acos((tz-bz)/hoehe)*180/PI;
   float x1_ = 0;
   float y1_ = 0;

   glEnable(GL_LIGHTING);
   glPushMatrix();
   glTranslatef(bx, by, bz);
   glRotatef(winkel, -ty+by, tx-bx, 0);

   glBegin(GL_LINE_STRIP);
   for (int j=0; j<detail+1; j++)
   {
      x1_ = radius*cos(2*PI*j/detail);
      y1_ = radius*sin(2*PI*j/detail);
      glVertex3f(x1_, y1_, 0);
      glVertex3f(x1_, y1_, hoehe);
   }
   glEnd();

   glBegin(GL_LINE_LOOP);
   for (int j=0; j<detail+1; j++)
   {
      x1_ = radius*cos(2*PI*j/detail);
      y1_ = radius*sin(2*PI*j/detail);
      glVertex3f(x1_, y1_, 0);
   }
   glEnd();

   glBegin(GL_LINE_LOOP);
   for (int j=0; j<detail+1; j++)
   {
      x1_ = radius*cos(2*PI*j/detail);
      y1_ = radius*sin(2*PI*j/detail);
      glVertex3f(x1_, y1_, hoehe);
   }
   glEnd();

   glPopMatrix();
   glDisable(GL_LIGHTING);
}


static void draw_texture_sphere(float radius_, int laengen_grade, int breiten_grade)
{
  
  float x1_ = 0;
  float y1_ = 0;
  float z1_ = 0;
  
  float x2_ = 0;
  float y2_ = 0;
  float z2_ = 0;
  
  for(int i=0; i<breiten_grade; i++)
  {
    glBegin(GL_QUAD_STRIP);
    
    z1_ = -radius_*cos(PI*i/breiten_grade);
    z2_ = -radius_*cos(PI*(i+1)/breiten_grade);
    
    for(int j=0; j<=laengen_grade; j++)
    {
      x1_ = radius_*cos(2*PI*j/laengen_grade)*sin(PI*i/breiten_grade);
      y1_ = radius_*sin(2*PI*j/laengen_grade)*sin(PI*i/breiten_grade);
      
      x2_ = radius_*cos(2*PI*j/laengen_grade)*sin(PI*(i+1)/breiten_grade);
      y2_ = radius_*sin(2*PI*j/laengen_grade)*sin(PI*(i+1)/breiten_grade);
      
      
      glNormal3f(x1_/radius_, y1_/radius_, z1_/radius_);
      glTexCoord2f(float(j)/float(laengen_grade), float(i)/float(breiten_grade));     glVertex3f(x1_, y1_, z1_);
      glNormal3f(x2_/radius_, y2_/radius_, z2_/radius_);
      glTexCoord2f(float(j)/float(laengen_grade), float((i+1))/float(breiten_grade)); glVertex3f(x2_, y2_, z2_);
    }
    
    glEnd();
  }
}


static void draw_star_map(float x_, float dex, float dey)
{
   float y_ = x_*1.4142136;
   
   glBegin(GL_QUADS);
      glTexCoord2f(0.0, 0.0); glVertex3f(-x_, -x_, -x_); glTexCoord2f(0.0, dey); glVertex3f(-x_, 0.0, -x_); glTexCoord2f(dex, dey); glVertex3f(0.0, 0.0, -y_); glTexCoord2f(dex, 0.0); glVertex3f(0.0, -x_, -x_);
      glTexCoord2f(0.0, 0.0); glVertex3f(-x_, 0.0, -x_); glTexCoord2f(0.0, dey); glVertex3f(-x_,  x_, -x_); glTexCoord2f(dex, dey); glVertex3f(0.0,  x_, -x_); glTexCoord2f(dex, 0.0); glVertex3f(0.0, 0.0, -y_);
      glTexCoord2f(0.0, 0.0); glVertex3f(0.0, 0.0, -y_); glTexCoord2f(0.0, dey); glVertex3f(0.0,  x_, -x_); glTexCoord2f(dex, dey); glVertex3f( x_,  x_, -x_); glTexCoord2f(dex, 0.0); glVertex3f( x_, 0.0, -x_);
      glTexCoord2f(0.0, 0.0); glVertex3f(0.0, -x_, -x_); glTexCoord2f(0.0, dey); glVertex3f(0.0, 0.0, -y_); glTexCoord2f(dex, dey); glVertex3f( x_, 0.0, -x_); glTexCoord2f(dex, 0.0); glVertex3f( x_, -x_, -x_);
      glTexCoord2f(0.0, 0.0); glVertex3f(-x_, -x_,  x_); glTexCoord2f(0.0, dey); glVertex3f(-x_, 0.0,  x_); glTexCoord2f(dex, dey); glVertex3f(0.0, 0.0,  y_); glTexCoord2f(dex, 0.0); glVertex3f(0.0, -x_,  x_);
      glTexCoord2f(0.0, 0.0); glVertex3f(-x_, 0.0,  x_); glTexCoord2f(0.0, dey); glVertex3f(-x_,  x_,  x_); glTexCoord2f(dex, dey); glVertex3f(0.0,  x_,  x_); glTexCoord2f(dex, 0.0); glVertex3f(0.0, 0.0,  y_);
      glTexCoord2f(0.0, 0.0); glVertex3f(0.0, 0.0,  y_); glTexCoord2f(0.0, dey); glVertex3f(0.0,  x_,  x_); glTexCoord2f(dex, dey); glVertex3f( x_,  x_,  x_); glTexCoord2f(dex, 0.0); glVertex3f( x_, 0.0,  x_);
      glTexCoord2f(0.0, 0.0); glVertex3f(0.0, -x_,  x_); glTexCoord2f(0.0, dey); glVertex3f(0.0, 0.0,  y_); glTexCoord2f(dex, dey); glVertex3f( x_, 0.0,  x_); glTexCoord2f(dex, 0.0); glVertex3f( x_, -x_,  x_);
   
      glTexCoord2f(0.0, 0.0); glVertex3f(-x_, -x_, -x_); glTexCoord2f(0.0, dey); glVertex3f(-x_, -x_, 0.0); glTexCoord2f(dex, dey); glVertex3f(0.0, -y_, 0.0); glTexCoord2f(dex, 0.0); glVertex3f(0.0, -x_, -x_);
      glTexCoord2f(0.0, 0.0); glVertex3f(-x_, -x_, 0.0); glTexCoord2f(0.0, dey); glVertex3f(-x_, -x_,  x_); glTexCoord2f(dex, dey); glVertex3f(0.0, -x_,  x_); glTexCoord2f(dex, 0.0); glVertex3f(0.0, -y_, 0.0);
      glTexCoord2f(0.0, 0.0); glVertex3f(0.0, -y_, 0.0); glTexCoord2f(0.0, dey); glVertex3f(0.0, -x_,  x_); glTexCoord2f(dex, dey); glVertex3f( x_, -x_,  x_); glTexCoord2f(dex, 0.0); glVertex3f( x_, -x_, 0.0);
      glTexCoord2f(0.0, 0.0); glVertex3f(0.0, -x_, -x_); glTexCoord2f(0.0, dey); glVertex3f(0.0, -y_, 0.0); glTexCoord2f(dex, dey); glVertex3f( x_, -x_, 0.0); glTexCoord2f(dex, 0.0); glVertex3f( x_, -x_, -x_);
      glTexCoord2f(0.0, 0.0); glVertex3f(-x_,  x_, -x_); glTexCoord2f(0.0, dey); glVertex3f(-x_,  x_, 0.0); glTexCoord2f(dex, dey); glVertex3f(0.0,  y_, 0.0); glTexCoord2f(dex, 0.0); glVertex3f(0.0,  x_, -x_);
      glTexCoord2f(0.0, 0.0); glVertex3f(-x_,  x_, 0.0); glTexCoord2f(0.0, dey); glVertex3f(-x_,  x_,  x_); glTexCoord2f(dex, dey); glVertex3f(0.0,  x_,  x_); glTexCoord2f(dex, 0.0); glVertex3f(0.0,  y_, 0.0);
      glTexCoord2f(0.0, 0.0); glVertex3f(0.0,  y_, 0.0); glTexCoord2f(0.0, dey); glVertex3f(0.0,  x_,  x_); glTexCoord2f(dex, dey); glVertex3f( x_,  x_,  x_); glTexCoord2f(dex, 0.0); glVertex3f( x_,  x_, 0.0);
      glTexCoord2f(0.0, 0.0); glVertex3f(0.0,  x_, -x_); glTexCoord2f(0.0, dey); glVertex3f(0.0,  y_, 0.0); glTexCoord2f(dex, dey); glVertex3f( x_,  x_, 0.0); glTexCoord2f(dex, 0.0); glVertex3f( x_,  x_, -x_);
      
      glTexCoord2f(0.0, 0.0); glVertex3f(-x_, -x_, -x_); glTexCoord2f(0.0, dey); glVertex3f(-x_, -x_, 0.0); glTexCoord2f(dex, dey); glVertex3f(-y_, 0.0, 0.0); glTexCoord2f(dex, 0.0); glVertex3f(-x_, 0.0, -x_);
      glTexCoord2f(0.0, 0.0); glVertex3f(-x_, -x_, 0.0); glTexCoord2f(0.0, dey); glVertex3f(-x_, -x_,  x_); glTexCoord2f(dex, dey); glVertex3f(-x_, 0.0,  x_); glTexCoord2f(dex, 0.0); glVertex3f(-y_, 0.0, 0.0);
      glTexCoord2f(0.0, 0.0); glVertex3f(-y_, 0.0, 0.0); glTexCoord2f(0.0, dey); glVertex3f(-x_, 0.0,  x_); glTexCoord2f(dex, dey); glVertex3f(-x_,  x_,  x_); glTexCoord2f(dex, 0.0); glVertex3f(-x_,  x_, 0.0);
      glTexCoord2f(0.0, 0.0); glVertex3f(-x_, 0.0, -x_); glTexCoord2f(0.0, dey); glVertex3f(-y_, 0.0, 0.0); glTexCoord2f(dex, dey); glVertex3f(-x_,  x_, 0.0); glTexCoord2f(dex, 0.0); glVertex3f(-x_,  x_, -x_);
      glTexCoord2f(0.0, 0.0); glVertex3f( x_, -x_, -x_); glTexCoord2f(0.0, dey); glVertex3f( x_, -x_, 0.0); glTexCoord2f(dex, dey); glVertex3f( y_, 0.0, 0.0); glTexCoord2f(dex, 0.0); glVertex3f( x_, 0.0, -x_);
      glTexCoord2f(0.0, 0.0); glVertex3f( x_, -x_, 0.0); glTexCoord2f(0.0, dey); glVertex3f( x_, -x_,  x_); glTexCoord2f(dex, dey); glVertex3f( x_, 0.0,  x_); glTexCoord2f(dex, 0.0); glVertex3f( y_, 0.0, 0.0);
      glTexCoord2f(0.0, 0.0); glVertex3f( y_, 0.0, 0.0); glTexCoord2f(0.0, dey); glVertex3f( x_, 0.0,  x_); glTexCoord2f(dex, dey); glVertex3f( x_,  x_,  x_); glTexCoord2f(dex, 0.0); glVertex3f( x_,  x_, 0.0);
      glTexCoord2f(0.0, 0.0); glVertex3f( x_, 0.0, -x_); glTexCoord2f(0.0, dey); glVertex3f( y_, 0.0, 0.0); glTexCoord2f(dex, dey); glVertex3f( x_,  x_, 0.0); glTexCoord2f(dex, 0.0); glVertex3f( x_,  x_, -x_);
   glEnd();
}


static void zeichne_ring(float radius_, float breite_, int unterteilungen_)
{  
  float x1_ = radius_;
  float y1_ = 0;
  
  float x2_ = radius_ + breite_;
  float y2_ = 0;
  
  glBegin(GL_QUAD_STRIP);
  
  glVertex3f(x1_, y1_, 0);
  glVertex3f(x2_, y2_, 0);
  
  for (int i=0; i<=unterteilungen_; i++)
  {
    x1_ = radius_*cos(2*PI*i/unterteilungen_);
    y1_ = radius_*sin(2*PI*i/unterteilungen_);
    
    x2_ = (breite_+radius_)*cos(2*PI*i/unterteilungen_);
    y2_ = (breite_+radius_)*sin(2*PI*i/unterteilungen_);
   
    glNormal3f(0.0, 0.0, -1.0);
    glVertex3f(x1_, y1_, 0);
    glVertex3f(x2_, y2_, 0);
  }
  
  glEnd();
}


static void zeichne_kreis(float radius_, int unterteilungen_)
{  
  float x_=radius_;
  float y_=0;
  glBegin(GL_LINE_LOOP);
  glVertex3f(x_, y_, 0);
  for (int i=0; i<unterteilungen_; i++)
  {
    x_ = radius_*cos(2*PI*i/unterteilungen_);
    y_ = radius_*sin(2*PI*i/unterteilungen_);
    glVertex3f(x_, y_, 0);    
  }
  
  glEnd();
}


static void draw_dummy_floor()
{
    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_QUADS);
        glNormal3f( 0.0,  1.0, 0.0); glVertex3f(-0.5, -0.5, 0.0); glVertex3f(-0.5, -0.5, 1.0);
                                     glVertex3f( 0.5, -0.5, 1.0); glVertex3f( 0.5, -0.5, 0.0);
        glNormal3f(-1.0,  0.0, 0.0); glVertex3f( 0.5, -0.5, 0.0); glVertex3f( 0.5, -0.5, 1.0);
                                     glVertex3f( 0.5,  0.5, 1.0); glVertex3f( 0.5,  0.5, 0.0);
        glNormal3f( 0.0, -1.0, 0.0); glVertex3f( 0.5,  0.5, 0.0); glVertex3f( 0.5,  0.5, 1.0);
                                     glVertex3f(-0.5,  0.5, 1.0); glVertex3f(-0.5,  0.5, 0.0);
        glNormal3f( 1.0,  0.0, 0.0); glVertex3f(-0.5,  0.5, 0.0); glVertex3f(-0.5,  0.5, 1.0);
                                     glVertex3f(-0.5, -0.5, 1.0); glVertex3f(-0.5, -0.5, 0.0);
    glEnd();
}

}



#endif
