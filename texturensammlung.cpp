#include "texturensammlung.hh"


Texturensammlung::Texturensammlung()
{
   tex_stars = new Textur("pics/sterne.bmp", 3);
   tex_sonne = new Textur("pics/sonne.bmp", 3);
   tex_district = new Textur("pics/district.bmp", 3);
   
   tex_flare[0] = new Textur("pics/flares/flare1.bmp", 3);
   tex_flare[1] = new Textur("pics/flares/flare2.bmp", 3);
   tex_flare[2] = new Textur("pics/flares/flare3.bmp", 3);
   tex_flare[3] = new Textur("pics/flares/flare4.bmp", 3);
   tex_flare[4] = new Textur("pics/flares/flare5.bmp", 3);
   
   tex_planet[0] = new Textur("pics/planeten/rock/rock1.bmp", 3);
   tex_planet[1] = new Textur("pics/planeten/rock/rock2.bmp", 3);
   tex_planet[2] = new Textur("pics/planeten/rock/rock3.bmp", 3);
   tex_planet[3] = new Textur("pics/planeten/rock/rock4.bmp", 3);
   tex_planet[4] = new Textur("pics/planeten/rock/rock5.bmp", 3);
   tex_planet[5] = new Textur("pics/planeten/rock/rock6.bmp", 3);
   tex_planet[6] = new Textur("pics/planeten/gas/gas1.bmp", 3);
   tex_planet[7] = new Textur("pics/planeten/gas/gas2.bmp", 3);
   tex_planet[8] = new Textur("pics/planeten/gas/gas3.bmp", 3);
   tex_planet[9] = new Textur("pics/planeten/gas/gas4.bmp", 3);
}

Texturensammlung::~Texturensammlung()
{
   delete tex_stars;
   delete tex_sonne;
   delete tex_district;
   
   for(int i=0; i<5; i++)
      delete tex_flare[i];
   
   for(int i=0; i<10; i++)
      delete tex_planet[i];
}


void bind_texture(Textur* textur)
{
   glGenTextures(1, &(textur->id));
   glBindTexture(GL_TEXTURE_2D, textur->id);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
   glTexImage2D(GL_TEXTURE_2D, 0, 3, textur->groesse_x, textur->groesse_y, 0, GL_RGB, GL_UNSIGNED_BYTE, textur->daten);
   glBindTexture(GL_TEXTURE_2D, 0);
}


void Texturensammlung::texturen_laden()
{
   bind_texture(tex_stars);
   bind_texture(tex_sonne);
   bind_texture(tex_district);
   
   for(int i=0; i<5; i++)
      bind_texture(tex_flare[i]);
   
   for(int i=0; i<10; i++)
      bind_texture(tex_planet[i]);
   
}

