#include "modell.hh"

#define MODELTEXTURES_DIR "models/textures"
Textures* Modell::textures = NULL;

Modell::Modell(bool flat_shading) : flat_shading(flat_shading)
{
   textures_loaded = false;
}


Modell::Modell(std::string dateiname, bool flat_shading) : flat_shading(flat_shading)
{
   lade(dateiname);
   textures_loaded = false;
}


void Modell::lade_textur()
{
   for (int i=0; i<anzahl_materialien; i++)
   {
      if (materialien[i].textur)
      {
         std::string label;
         int delim;
         
         label = materialien[i].textur_datei;
         
         delim = label.find_last_of("."); // Endung abschneiden
         label = label.substr(0, delim);

         delim = label.find_last_of("/"); // Pfad abschneiden
         label = label.substr(delim+1);

         materialien[i].textur_id = textures->get_id(label);
      }
   }
   textures_loaded = true;
}
  
void Modell::zeichne()
{
   if (textures == NULL)
      textures = new Textures(MODELTEXTURES_DIR);
   if (!textures_loaded)
      lade_textur();
   
   if (valid_modell)
   {
      for (int i=0; i<anzahl_objekte; i++)
      {
   //       std::cout << "i " << i << " ,bool-textur " << objekte[i].material->textur << std::endl ;
      if(objekte[i].material->textur)
         glBindTexture(GL_TEXTURE_2D, objekte[i].material->textur_id);
         
      glColor4f(objekte[i].material->Kdr, objekte[i].material->Kdg, objekte[i].material->Kdb, objekte[i].material->alpha);
      
         for(int j=0; j<objekte[i].anzahl_dreiecke; j++)
         {
            if (objekte[i].dreiecke[j].viereck)
               glBegin(GL_QUADS);
            else
               glBegin(GL_TRIANGLES);
            glEdgeFlag(false);
   //       std::cout << objekte[i].dreiecke[j].ecke[0] << "\t" << objekte[i].dreiecke[j].ecke[1] << "\t" << objekte[i].dreiecke[j].ecke[2] << "\n";

            if(flat_shading)
               glNormal3f(objekte[i].dreiecke[j].normal_x, objekte[i].dreiecke[j].normal_y, objekte[i].dreiecke[j].normal_z); // fuer flat shading!

            if(objekte[i].material->textur)
            {
   //             std::cout << "\nTextur Koords: " << texkoords[objekte[i].dreiecke[j].texecke[0]].tx << texkoords[objekte[i].dreiecke[j].texecke[0]].ty;
   //             std::cout << "\n               " << texkoords[objekte[i].dreiecke[j].texecke[1]].tx << texkoords[objekte[i].dreiecke[j].texecke[1]].ty;
   //             std::cout << "\n               " << texkoords[objekte[i].dreiecke[j].texecke[2]].tx << texkoords[objekte[i].dreiecke[j].texecke[2]].ty;
            if(!flat_shading)
               glNormal3f(knoten[objekte[i].dreiecke[j].ecke[0]].n_x, knoten[objekte[i].dreiecke[j].ecke[0]].n_y, knoten[objekte[i].dreiecke[j].ecke[0]].n_z);
                  glTexCoord2f(texkoords[objekte[i].dreiecke[j].texecke[0]].tx, texkoords[objekte[i].dreiecke[j].texecke[0]].ty);
            glVertex3f(knoten[objekte[i].dreiecke[j].ecke[0]].x, knoten[objekte[i].dreiecke[j].ecke[0]].y, knoten[objekte[i].dreiecke[j].ecke[0]].z);
            if(!flat_shading)
               glNormal3f(knoten[objekte[i].dreiecke[j].ecke[1]].n_x, knoten[objekte[i].dreiecke[j].ecke[1]].n_y, knoten[objekte[i].dreiecke[j].ecke[1]].n_z);
                  glTexCoord2f(texkoords[objekte[i].dreiecke[j].texecke[1]].tx, texkoords[objekte[i].dreiecke[j].texecke[1]].ty);
            glVertex3f(knoten[objekte[i].dreiecke[j].ecke[1]].x, knoten[objekte[i].dreiecke[j].ecke[1]].y, knoten[objekte[i].dreiecke[j].ecke[1]].z);
            if(!flat_shading)
               glNormal3f(knoten[objekte[i].dreiecke[j].ecke[2]].n_x, knoten[objekte[i].dreiecke[j].ecke[2]].n_y, knoten[objekte[i].dreiecke[j].ecke[2]].n_z);
                  glTexCoord2f(texkoords[objekte[i].dreiecke[j].texecke[2]].tx, texkoords[objekte[i].dreiecke[j].texecke[2]].ty);
            glVertex3f(knoten[objekte[i].dreiecke[j].ecke[2]].x, knoten[objekte[i].dreiecke[j].ecke[2]].y, knoten[objekte[i].dreiecke[j].ecke[2]].z);
            if (objekte[i].dreiecke[j].viereck)
            {
               if(!flat_shading)
               glNormal3f(knoten[objekte[i].dreiecke[j].ecke[3]].n_x, knoten[objekte[i].dreiecke[j].ecke[3]].n_y, knoten[objekte[i].dreiecke[j].ecke[3]].n_z);
                  glTexCoord2f(texkoords[objekte[i].dreiecke[j].texecke[3]].tx, texkoords[objekte[i].dreiecke[j].texecke[3]].ty);
               glVertex3f(knoten[objekte[i].dreiecke[j].ecke[3]].x, knoten[objekte[i].dreiecke[j].ecke[3]].y, knoten[objekte[i].dreiecke[j].ecke[3]].z);
            }
               
            }
            else
            {
   //             std::cout << knoten[objekte[i].dreiecke[j].ecke[0]].n_x << ", " << knoten[objekte[i].dreiecke[j].ecke[0]].n_y << ", " << knoten[objekte[i].dreiecke[j].ecke[0]].n_z << std::endl;
   //             std::cout << knoten[objekte[i].dreiecke[j].ecke[0]].x << ", " << knoten[objekte[i].dreiecke[j].ecke[0]].y << ", " << knoten[objekte[i].dreiecke[j].ecke[0]].z << std::endl;
            if(!flat_shading)
               glNormal3f(knoten[objekte[i].dreiecke[j].ecke[0]].n_x, knoten[objekte[i].dreiecke[j].ecke[0]].n_y, knoten[objekte[i].dreiecke[j].ecke[0]].n_z); // kein flat shading
            glVertex3f(knoten[objekte[i].dreiecke[j].ecke[0]].x, knoten[objekte[i].dreiecke[j].ecke[0]].y, knoten[objekte[i].dreiecke[j].ecke[0]].z);
            if(!flat_shading)
               glNormal3f(knoten[objekte[i].dreiecke[j].ecke[1]].n_x, knoten[objekte[i].dreiecke[j].ecke[1]].n_y, knoten[objekte[i].dreiecke[j].ecke[1]].n_z);
            glVertex3f(knoten[objekte[i].dreiecke[j].ecke[1]].x, knoten[objekte[i].dreiecke[j].ecke[1]].y, knoten[objekte[i].dreiecke[j].ecke[1]].z);
            if(!flat_shading)
               glNormal3f(knoten[objekte[i].dreiecke[j].ecke[2]].n_x, knoten[objekte[i].dreiecke[j].ecke[2]].n_y, knoten[objekte[i].dreiecke[j].ecke[2]].n_z);
            glVertex3f(knoten[objekte[i].dreiecke[j].ecke[2]].x, knoten[objekte[i].dreiecke[j].ecke[2]].y, knoten[objekte[i].dreiecke[j].ecke[2]].z);
            if (objekte[i].dreiecke[j].viereck)
            {
               if(!flat_shading)
               {
   //                   std::cout << knoten[objekte[i].dreiecke[j].ecke[3]].n_x << ", " << knoten[objekte[i].dreiecke[j].ecke[3]].n_y << ", " << knoten[objekte[i].dreiecke[j].ecke[3]].n_z << std::endl;
                  glNormal3f(knoten[objekte[i].dreiecke[j].ecke[3]].n_x, knoten[objekte[i].dreiecke[j].ecke[3]].n_y, knoten[objekte[i].dreiecke[j].ecke[3]].n_z);
               }
   //                std::cout << knoten[objekte[i].dreiecke[j].ecke[3]].x << ", " << knoten[objekte[i].dreiecke[j].ecke[3]].y << ", " << knoten[objekte[i].dreiecke[j].ecke[3]].z << std::endl;
               glVertex3f(knoten[objekte[i].dreiecke[j].ecke[3]].x, knoten[objekte[i].dreiecke[j].ecke[3]].y, knoten[objekte[i].dreiecke[j].ecke[3]].z);
            }
            }
            glEnd();
         }
      
      if(objekte[i].material->textur)
         glBindTexture(GL_TEXTURE_2D, 0);
      }
   }
}

void lese_material(std::string dateiname, Modell* modell)
{
  std::fstream eingang;
  eingang.open((dateiname+".mtl").c_str(), std::ios::in);

  if (!eingang)
  {
    std::cout << "Fehler beim Laden der Datei!" << std::endl;
    return;
  }
  
  char hc;
  char* buffer = new char[256];  
  
  int n_zaehler = 0;
  
  do
  {
    hc = eingang.get();
    if (hc=='n')
    {
      n_zaehler++;
    }
  } while (eingang.getline(buffer,256));
  
  modell->materialien = new Material[n_zaehler];
  modell->anzahl_materialien = n_zaehler;
  
  std::cout << "\n Materialien n: " << n_zaehler;
  
  for (int i=0; i<n_zaehler; i++)
  {
    std::cout << "\nMaterial " << i; 
    
    eingang.close();
    eingang.open((dateiname+".mtl").c_str(), std::ios::in);
    
    modell->materialien[i].textur = false; // als defaultwerte
    modell->materialien[i].Kar = 0.5;
    modell->materialien[i].Kag = 0.5;
    modell->materialien[i].Kab = 0.5;
    modell->materialien[i].Kdr = 0.5;
    modell->materialien[i].Kdg = 0.5;
    modell->materialien[i].Kdb = 0.5;
    modell->materialien[i].Ksr = 0.5;
    modell->materialien[i].Ksg = 0.5;
    modell->materialien[i].Ksb = 0.5;
    modell->materialien[i].alpha = 1.0;
    
    int j = 0;
    
    do
    {
      hc = eingang.get();
      if (hc == 'n')
      {
        j++;
        if (j > i)
          break;
      }
    } while (eingang.getline(buffer,256));
    
    eingang.get();eingang.get();eingang.get();eingang.get();eingang.get();eingang.get();
    
    eingang >> modell->materialien[i].name;
    
    std::cout << " Name: " << modell->materialien[i].name; 
    
    eingang.getline(buffer,256);
    hc = eingang.get();
    
    while(hc != 'n')
    {
      if (hc == 'K')
      {
        hc = eingang.get();
        if (hc == 'a')
        {
          eingang >> modell->materialien[i].Kar >> modell->materialien[i].Kag >> modell->materialien[i].Kab;
          std::cout << "\nSetze ambient-Parameter : " << modell->materialien[i].Kar << "\t" << modell->materialien[i].Kag << "\t"  <<  modell->materialien[i].Kab;
        }
        else if (hc == 'd')
        {
          eingang >> modell->materialien[i].Kdr >> modell->materialien[i].Kdg >> modell->materialien[i].Kdb;
          std::cout << "\nSetze diffuse-Parameter : " << modell->materialien[i].Kdr << "\t" << modell->materialien[i].Kdg << "\t"  <<  modell->materialien[i].Kdb;
        }
        else if (hc == 's')
        {
          eingang >> modell->materialien[i].Ksr >> modell->materialien[i].Ksg >> modell->materialien[i].Ksb;
          std::cout << "\nSetze specular-Parameter: " << modell->materialien[i].Ksr << "\t" << modell->materialien[i].Ksg << "\t"  <<  modell->materialien[i].Ksb;
        }        
      }
      
      else if (hc == 'N')
      {
        hc = eingang.get();
        if (hc == 's')
        {
          eingang >> modell->materialien[i].Ns;
        }
        if (hc == 'i')
        {
          eingang >> modell->materialien[i].Ni;          
        }        
      }
      
      else if (hc == 'd')
      {
        eingang >> modell->materialien[i].alpha;
        std::cout << "\nSetze alpha-Wert: " << modell->materialien[i].alpha;
      }
      
      else if (hc == 'i')
      {
        eingang.get();eingang.get();eingang.get();eingang.get();
        eingang >> modell->materialien[i].illum;
      }
      
      else if (hc == 'm')
      {
        modell->materialien[i].textur = true;
        eingang.get();eingang.get();eingang.get();eingang.get();eingang.get();eingang.get();
        
        eingang >> modell->materialien[i].textur_datei;
        

      }

      if(!eingang.getline(buffer,256))
        break;
      hc = eingang.get();

    }

/*  
Ns 96.078431 //shiness
Ka 0.000000 0.000000 0.000000 // ambient rgb
Kd 0.640000 0.640000 0.640000 // diffuse rgp
Ks 0.500000 0.500000 0.500000 // specular rgb
Ni 1.000000  // refraction
d 1.000000 // alpha
illum 2  
map_Kd /home/hb/opengl/rdz/modelle/test.bmp
*/
    
    
  }
}


void Modell::lade(std::string dateiname)
{
  std::fstream eingang;
  eingang.open((dateiname+".obj").c_str(), std::ios::in);

  if (!eingang)
  {
    std::cout << "Fehler beim Laden der Datei!" << std::endl;
    return;
    valid_modell = false;
  }
  
  lese_material(dateiname, this);
  
  char hc;
  char* buffer = new char[256];
  
  int v_zaehler = 0;
  int t_zaehler = 0;
  int f_zaehler = 0;
  int o_zaehler = 0;
  
  do
  {
    hc = eingang.get();
    if (hc=='v')
    {
      hc = eingang.get();
      if (hc=='t')
        t_zaehler++;
      else
        v_zaehler++;
    }
    if (hc=='o')
    {
      o_zaehler++;
    }
  } while (eingang.getline(buffer,256));
  
  eingang.close();
  eingang.open((dateiname+".obj").c_str(), std::ios::in);
//   eingang.seekg(0, std::ios::beg);
  
  std::cout << "\n Anzahl Objekte o: " << o_zaehler << "\t Anzahl Knoten v:" << v_zaehler << "\t Anzahl Texturkooridanten t:" << t_zaehler;
  
  
  this->anzahl_knoten    = v_zaehler;
  this->anzahl_texkoords = t_zaehler;
  this->anzahl_objekte   = o_zaehler;
  this->objekte = new Element[o_zaehler];
  this->knoten = new Knoten[v_zaehler];
  if (t_zaehler > 0)
    this->texkoords = new TexKoord[t_zaehler];

  v_zaehler = 0;
  t_zaehler = 0;
  int position;
  
  do
  {
    hc = eingang.get();
    
    if (hc == 'v')
    {
      hc = eingang.get();
      if (hc == ' ')
      {
        eingang >> this->knoten[v_zaehler].x >> this->knoten[v_zaehler].z  >> this->knoten[v_zaehler].y;
        
        float laenge = sqrt(this->knoten[v_zaehler].x*this->knoten[v_zaehler].x
                          + this->knoten[v_zaehler].y*this->knoten[v_zaehler].y
                          + this->knoten[v_zaehler].z*this->knoten[v_zaehler].z);
        
        this->knoten[v_zaehler].n_x = this->knoten[v_zaehler].x/laenge;
        this->knoten[v_zaehler].n_y = this->knoten[v_zaehler].y/laenge;
        this->knoten[v_zaehler].n_z = this->knoten[v_zaehler].z/laenge;
        
        v_zaehler++;
      }
      else if (hc == 't')
      {
        eingang >> this->texkoords[t_zaehler].tx >> this->texkoords[t_zaehler].ty;
        t_zaehler++;
      }
    }
  }
  while (eingang.getline(buffer,256));
  hc = 0;
  
  if (v_zaehler != this->anzahl_knoten)
  {
    std::cout << "\nFehler beim Auslesen der Knoten!";
  }
  if (t_zaehler != this->anzahl_texkoords)
  {
    std::cout << "\nFehler beim Auslesen der Texturkooridanten!";
  }
  
  eingang.close();
  eingang.open((dateiname+".obj").c_str(), std::ios::in);
//   eingang.seekg(0, std::ios::beg);
  
  for (int i=0; i<o_zaehler; i++)
  {
    for(int k=0; k<=i;)
    {
      hc = eingang.get();
      if (hc == 'o')
        k++;
      eingang.getline(buffer,256);
    }
      
    f_zaehler = 0;
    
    do
    {
      hc = eingang.get();
      if (hc == 'f')
        f_zaehler++;
      if (hc == 'o')
        break;
    }
    while (eingang.getline(buffer,256));

    std::cout << "\n\nObjekt " << i << ": Anzahl Flaechen f:" << f_zaehler;
    
    this->objekte[i].dreiecke = new Dreieck[f_zaehler];
    this->objekte[i].anzahl_dreiecke = f_zaehler;
    f_zaehler = 0;
    
    eingang.close();
    eingang.open((dateiname+".obj").c_str(), std::ios::in);
    hc = 0;
    
    for(int k=0; k<=i;)
    {
      hc = eingang.get();
      if (hc == 'o')
        k++;
      eingang.getline(buffer,256);
    }
    
    hc = eingang.get();
    
    float a1,a2,a3,b1,b2,b3,c1,c2,c3,laenge;
    
    while(hc != 'o')
    {
      
      if (hc == 'f')
      {
        bool texturkoordinaten = false;
        
        eingang >> this->objekte[i].dreiecke[f_zaehler].ecke[0];
        this->objekte[i].dreiecke[f_zaehler].ecke[0]--;
        hc = eingang.get();
        std::cout << "\n" << this->objekte[i].dreiecke[f_zaehler].ecke[0];
        if (hc == '/')
        {
          texturkoordinaten = true;
          eingang >> this->objekte[i].dreiecke[f_zaehler].texecke[0];
          this->objekte[i].dreiecke[f_zaehler].texecke[0]--;
          std::cout << "/" << this->objekte[i].dreiecke[f_zaehler].texecke[0];
        }
          
        eingang >> this->objekte[i].dreiecke[f_zaehler].ecke[1];
        this->objekte[i].dreiecke[f_zaehler].ecke[1]--;
        std::cout << "\t" << this->objekte[i].dreiecke[f_zaehler].ecke[1];
        if (texturkoordinaten)
        {
          eingang.get();
          eingang >> this->objekte[i].dreiecke[f_zaehler].texecke[1];
          this->objekte[i].dreiecke[f_zaehler].texecke[1]--;
          std::cout << "/" << this->objekte[i].dreiecke[f_zaehler].texecke[1];
        }
          
        eingang >> this->objekte[i].dreiecke[f_zaehler].ecke[2];
        this->objekte[i].dreiecke[f_zaehler].ecke[2]--;
        std::cout << "\t" << this->objekte[i].dreiecke[f_zaehler].ecke[2];
        if (texturkoordinaten)
        {
          eingang.get();
          eingang >> this->objekte[i].dreiecke[f_zaehler].texecke[2];
          this->objekte[i].dreiecke[f_zaehler].texecke[2]--;
          std::cout << "/" << this->objekte[i].dreiecke[f_zaehler].texecke[2];
        }
        
         if (eingang.get() == '\n')
         {
            eingang.unget();
            this->objekte[i].dreiecke[f_zaehler].viereck = false;
         }
         else
         {
            eingang.unget();
            this->objekte[i].dreiecke[f_zaehler].viereck = true;
            eingang >> this->objekte[i].dreiecke[f_zaehler].ecke[3];
            this->objekte[i].dreiecke[f_zaehler].ecke[3]--;
            std::cout << "\t" << this->objekte[i].dreiecke[f_zaehler].ecke[3];
            if (texturkoordinaten)
            {
               eingang.get();
               eingang >> this->objekte[i].dreiecke[f_zaehler].texecke[3];
               this->objekte[i].dreiecke[f_zaehler].texecke[3]--;
               std::cout << "/" << this->objekte[i].dreiecke[f_zaehler].texecke[3];
            }
         }
        
        
//         std::cout << this->objekte[i].dreiecke[f_zaehler].ecke[0] << "\tx" 
//                   << this->objekte[i].dreiecke[f_zaehler].ecke[1] << "\tx" 
//                   << this->objekte[i].dreiecke[f_zaehler].ecke[2] << "\nx";

        a1 = this->knoten[this->objekte[i].dreiecke[f_zaehler].ecke[0]].x; 
        a2 = this->knoten[this->objekte[i].dreiecke[f_zaehler].ecke[0]].y; 
        a3 = this->knoten[this->objekte[i].dreiecke[f_zaehler].ecke[0]].z;
                  
        b1 = this->knoten[this->objekte[i].dreiecke[f_zaehler].ecke[1]].x; 
        b2 = this->knoten[this->objekte[i].dreiecke[f_zaehler].ecke[1]].y; 
        b3 = this->knoten[this->objekte[i].dreiecke[f_zaehler].ecke[1]].z;
                  
        c1 = this->knoten[this->objekte[i].dreiecke[f_zaehler].ecke[2]].x; 
        c2 = this->knoten[this->objekte[i].dreiecke[f_zaehler].ecke[2]].y; 
        c3 = this->knoten[this->objekte[i].dreiecke[f_zaehler].ecke[2]].z;
                  
        this->objekte[i].dreiecke[f_zaehler].normal_x = ((b3-a3)*(c2-a2) - (b2-a2)*(c3-a3));
        this->objekte[i].dreiecke[f_zaehler].normal_y = ((b1-a1)*(c3-a3) - (b3-a3)*(c1-a1));
        this->objekte[i].dreiecke[f_zaehler].normal_z = ((b2-a2)*(c1-a1) - (b1-a1)*(c2-a2));
        
        hilf::normieren((this->objekte[i].dreiecke[f_zaehler].normal_x), (this->objekte[i].dreiecke[f_zaehler].normal_y), (this->objekte[i].dreiecke[f_zaehler].normal_z));
        
//         laenge = sqrt(this->objekte[i].dreiecke[f_zaehler].normal_x*this->objekte[i].dreiecke[f_zaehler].normal_x
//                     + this->objekte[i].dreiecke[f_zaehler].normal_y*this->objekte[i].dreiecke[f_zaehler].normal_y
//                     + this->objekte[i].dreiecke[f_zaehler].normal_z*this->objekte[i].dreiecke[f_zaehler].normal_z);
//       
//         this->objekte[i].dreiecke[f_zaehler].normal_x /= laenge;
//         this->objekte[i].dreiecke[f_zaehler].normal_y /= laenge;
//         this->objekte[i].dreiecke[f_zaehler].normal_z /= laenge;
        
        f_zaehler++;
      }
      

      if (hc == 'u')
      {
        eingang.get(); eingang.get(); eingang.get(); eingang.get(); eingang.get(); eingang.get();
        
        std::string materialname;
        eingang >> materialname;
        std::cout << "\nSuche Material für " << materialname;
        
        for (int l=0; l<this->anzahl_materialien; l++)
        {
          if (materialname == this->materialien[l].name)
          {
            this->objekte[i].material = &(this->materialien[l]);
            std::cout << "\nWeise Objekt " << i << " das Material " << this->materialien[l].name << " zu";
//             break;
          }
        }
      }
      
      if (!eingang.getline(buffer,256))
        break;
      hc = eingang.get();
    }
    
    
    eingang.close();
    eingang.open((dateiname+".obj").c_str(), std::ios::in);
    
  }
  
  float norm_x;
  float norm_y;
  float norm_z;
  
  std::cout << "\nNormalen berechnen" << std::endl;
  
  for (int j=0; j<this->anzahl_knoten; j++)
  {
    norm_x = 0;
    norm_y = 0;
    norm_z = 0;
    
    for (int k=0; k<this->anzahl_objekte; k++)
    {
      for (int l=0; l<this->objekte[k].anzahl_dreiecke; l++)
      {
        if (this->objekte[k].dreiecke[l].ecke[0] == j ||
            this->objekte[k].dreiecke[l].ecke[1] == j ||
            this->objekte[k].dreiecke[l].ecke[2] == j   )
        {
          norm_x += this->objekte[k].dreiecke[l].normal_x;
          norm_y += this->objekte[k].dreiecke[l].normal_y;
          norm_z += this->objekte[k].dreiecke[l].normal_z;
          
//           std::cout << "\nWeise dem Knoten " << j << " die Normale der Flaeche o:" << k << ", f:" << l; 
        }
      }
    }
    
    if (norm_x != 0 || norm_y != 0 || norm_z != 0)
    {
      hilf::normieren(norm_x, norm_y, norm_z);
      this->knoten[j].n_x = norm_x;
      this->knoten[j].n_y = norm_y;
      this->knoten[j].n_z = norm_z;
    }
  }
  
  

  eingang.close();
  valid_modell = true;
}



Modell* lade_modell(std::string dateiname, bool flat_shading_)
{
  std::fstream eingang;
  eingang.open((dateiname+".obj").c_str(), std::ios::in);

  Modell* modell = new Modell(flat_shading_);
  
  if (!eingang)
  {
    std::cout << "Fehler beim Laden der Datei!" << std::endl;
    modell->valid_modell = false;
    return modell;
  }
  
  lese_material(dateiname, modell);
  
  char hc;
  char* buffer = new char[256];
  
  int v_zaehler = 0;
  int t_zaehler = 0;
  int f_zaehler = 0;
  int o_zaehler = 0;
  
  do
  {
    hc = eingang.get();
    if (hc=='v')
    {
      hc = eingang.get();
      if (hc=='t')
        t_zaehler++;
      else
        v_zaehler++;
    }
    if (hc=='o')
    {
      o_zaehler++;
    }
  } while (eingang.getline(buffer,256));
  
  eingang.close();
  eingang.open((dateiname+".obj").c_str(), std::ios::in);
//   eingang.seekg(0, std::ios::beg);
  
  std::cout << "\n Anzahl Objekte o: " << o_zaehler << "\t Anzahl Knoten v:" << v_zaehler << "\t Anzahl Texturkooridanten t:" << t_zaehler;
  
  
  modell->anzahl_knoten    = v_zaehler;
  modell->anzahl_texkoords = t_zaehler;
  modell->anzahl_objekte   = o_zaehler;
  modell->objekte = new Element[o_zaehler];
  modell->knoten = new Knoten[v_zaehler];
  if (t_zaehler > 0)
    modell->texkoords = new TexKoord[t_zaehler];

  v_zaehler = 0;
  t_zaehler = 0;
  int position;
  
  do
  {
    hc = eingang.get();
    
    if (hc == 'v')
    {
      hc = eingang.get();
      if (hc == ' ')
      {
        eingang >> modell->knoten[v_zaehler].x >> modell->knoten[v_zaehler].z  >> modell->knoten[v_zaehler].y;
        
        float laenge = sqrt(modell->knoten[v_zaehler].x*modell->knoten[v_zaehler].x
                          + modell->knoten[v_zaehler].y*modell->knoten[v_zaehler].y
                          + modell->knoten[v_zaehler].z*modell->knoten[v_zaehler].z);
        
        modell->knoten[v_zaehler].n_x = modell->knoten[v_zaehler].x/laenge;
        modell->knoten[v_zaehler].n_y = modell->knoten[v_zaehler].y/laenge;
        modell->knoten[v_zaehler].n_z = modell->knoten[v_zaehler].z/laenge;
        
        v_zaehler++;
      }
      else if (hc == 't')
      {
        eingang >> modell->texkoords[t_zaehler].tx >> modell->texkoords[t_zaehler].ty;
        t_zaehler++;
      }
    }
  }
  while (eingang.getline(buffer,256));
  hc = 0;
  
  if (v_zaehler != modell->anzahl_knoten)
  {
    std::cout << "\nFehler beim Auslesen der Knoten!";
  }
  if (t_zaehler != modell->anzahl_texkoords)
  {
    std::cout << "\nFehler beim Auslesen der Texturkooridanten!";
  }
  
  eingang.close();
  eingang.open((dateiname+".obj").c_str(), std::ios::in);
//   eingang.seekg(0, std::ios::beg);
  
  for (int i=0; i<o_zaehler; i++)
  {
    for(int k=0; k<=i;)
    {
      hc = eingang.get();
      if (hc == 'o')
        k++;
      eingang.getline(buffer,256);
    }
      
    f_zaehler = 0;
    
    do
    {
      hc = eingang.get();
      if (hc == 'f')
        f_zaehler++;
      if (hc == 'o')
        break;
    }
    while (eingang.getline(buffer,256));

    std::cout << "\n\nObjekt " << i << ": Anzahl Flaechen f:" << f_zaehler;
    
    modell->objekte[i].dreiecke = new Dreieck[f_zaehler];
    modell->objekte[i].anzahl_dreiecke = f_zaehler;
    f_zaehler = 0;
    
    eingang.close();
    eingang.open((dateiname+".obj").c_str(), std::ios::in);
    hc = 0;
    
    for(int k=0; k<=i;)
    {
      hc = eingang.get();
      if (hc == 'o')
        k++;
      eingang.getline(buffer,256);
    }
    
    hc = eingang.get();
    
    float a1,a2,a3,b1,b2,b3,c1,c2,c3,laenge;
    
    while(hc != 'o')
    {
      
      if (hc == 'f')
      {
        bool texturkoordinaten = false;
        
        eingang >> modell->objekte[i].dreiecke[f_zaehler].ecke[0];
        modell->objekte[i].dreiecke[f_zaehler].ecke[0]--;
        hc = eingang.get();
        std::cout << "\n" << modell->objekte[i].dreiecke[f_zaehler].ecke[0];
        if (hc == '/')
        {
          texturkoordinaten = true;
          eingang >> modell->objekte[i].dreiecke[f_zaehler].texecke[0];
          modell->objekte[i].dreiecke[f_zaehler].texecke[0]--;
          std::cout << "/" << modell->objekte[i].dreiecke[f_zaehler].texecke[0];
        }
          
        eingang >> modell->objekte[i].dreiecke[f_zaehler].ecke[1];
        modell->objekte[i].dreiecke[f_zaehler].ecke[1]--;
        std::cout << "\t" << modell->objekte[i].dreiecke[f_zaehler].ecke[1];
        if (texturkoordinaten)
        {
          eingang.get();
          eingang >> modell->objekte[i].dreiecke[f_zaehler].texecke[1];
          modell->objekte[i].dreiecke[f_zaehler].texecke[1]--;
          std::cout << "/" << modell->objekte[i].dreiecke[f_zaehler].texecke[1];
        }
          
        eingang >> modell->objekte[i].dreiecke[f_zaehler].ecke[2];
        modell->objekte[i].dreiecke[f_zaehler].ecke[2]--;
        std::cout << "\t" << modell->objekte[i].dreiecke[f_zaehler].ecke[2];
        if (texturkoordinaten)
        {
          eingang.get();
          eingang >> modell->objekte[i].dreiecke[f_zaehler].texecke[2];
          modell->objekte[i].dreiecke[f_zaehler].texecke[2]--;
          std::cout << "/" << modell->objekte[i].dreiecke[f_zaehler].texecke[2];
        }
        
         if (eingang.get() == '\n')
         {
            eingang.unget();
            modell->objekte[i].dreiecke[f_zaehler].viereck = false;
         }
         else
         {
            eingang.unget();
            modell->objekte[i].dreiecke[f_zaehler].viereck = true;
            eingang >> modell->objekte[i].dreiecke[f_zaehler].ecke[3];
            modell->objekte[i].dreiecke[f_zaehler].ecke[3]--;
            std::cout << "\t" << modell->objekte[i].dreiecke[f_zaehler].ecke[3];
            if (texturkoordinaten)
            {
               eingang.get();
               eingang >> modell->objekte[i].dreiecke[f_zaehler].texecke[3];
               modell->objekte[i].dreiecke[f_zaehler].texecke[3]--;
               std::cout << "/" << modell->objekte[i].dreiecke[f_zaehler].texecke[3];
            }
         }
        
        
//         std::cout << modell->objekte[i].dreiecke[f_zaehler].ecke[0] << "\tx" 
//                   << modell->objekte[i].dreiecke[f_zaehler].ecke[1] << "\tx" 
//                   << modell->objekte[i].dreiecke[f_zaehler].ecke[2] << "\nx";

        a1 = modell->knoten[modell->objekte[i].dreiecke[f_zaehler].ecke[0]].x; 
        a2 = modell->knoten[modell->objekte[i].dreiecke[f_zaehler].ecke[0]].y; 
        a3 = modell->knoten[modell->objekte[i].dreiecke[f_zaehler].ecke[0]].z;
                  
        b1 = modell->knoten[modell->objekte[i].dreiecke[f_zaehler].ecke[1]].x; 
        b2 = modell->knoten[modell->objekte[i].dreiecke[f_zaehler].ecke[1]].y; 
        b3 = modell->knoten[modell->objekte[i].dreiecke[f_zaehler].ecke[1]].z;
                  
        c1 = modell->knoten[modell->objekte[i].dreiecke[f_zaehler].ecke[2]].x; 
        c2 = modell->knoten[modell->objekte[i].dreiecke[f_zaehler].ecke[2]].y; 
        c3 = modell->knoten[modell->objekte[i].dreiecke[f_zaehler].ecke[2]].z;
                  
        modell->objekte[i].dreiecke[f_zaehler].normal_x = ((b3-a3)*(c2-a2) - (b2-a2)*(c3-a3));
        modell->objekte[i].dreiecke[f_zaehler].normal_y = ((b1-a1)*(c3-a3) - (b3-a3)*(c1-a1));
        modell->objekte[i].dreiecke[f_zaehler].normal_z = ((b2-a2)*(c1-a1) - (b1-a1)*(c2-a2));
        
        hilf::normieren((modell->objekte[i].dreiecke[f_zaehler].normal_x), (modell->objekte[i].dreiecke[f_zaehler].normal_y), (modell->objekte[i].dreiecke[f_zaehler].normal_z));
        
//         laenge = sqrt(modell->objekte[i].dreiecke[f_zaehler].normal_x*modell->objekte[i].dreiecke[f_zaehler].normal_x
//                     + modell->objekte[i].dreiecke[f_zaehler].normal_y*modell->objekte[i].dreiecke[f_zaehler].normal_y
//                     + modell->objekte[i].dreiecke[f_zaehler].normal_z*modell->objekte[i].dreiecke[f_zaehler].normal_z);
//       
//         modell->objekte[i].dreiecke[f_zaehler].normal_x /= laenge;
//         modell->objekte[i].dreiecke[f_zaehler].normal_y /= laenge;
//         modell->objekte[i].dreiecke[f_zaehler].normal_z /= laenge;
        
        f_zaehler++;
      }
      

      if (hc == 'u')
      {
        eingang.get(); eingang.get(); eingang.get(); eingang.get(); eingang.get(); eingang.get();
        
        std::string materialname;
        eingang >> materialname;
        std::cout << "\nSuche Material für " << materialname;
        
        for (int l=0; l<modell->anzahl_materialien; l++)
        {
          if (materialname == modell->materialien[l].name)
          {
            modell->objekte[i].material = &(modell->materialien[l]);
            std::cout << "\nWeise Objekt " << i << " das Material " << modell->materialien[l].name << " zu";
//             break;
          }
        }
      }
      
      if (!eingang.getline(buffer,256))
        break;
      hc = eingang.get();
    }
    
    
    eingang.close();
    eingang.open((dateiname+".obj").c_str(), std::ios::in);
    
  }
  
  float norm_x;
  float norm_y;
  float norm_z;
  
  std::cout << "\nNormalen berechnen" << std::endl;
  
  for (int j=0; j<modell->anzahl_knoten; j++)
  {
    norm_x = 0;
    norm_y = 0;
    norm_z = 0;
    
    for (int k=0; k<modell->anzahl_objekte; k++)
    {
      for (int l=0; l<modell->objekte[k].anzahl_dreiecke; l++)
      {
        if (modell->objekte[k].dreiecke[l].ecke[0] == j ||
            modell->objekte[k].dreiecke[l].ecke[1] == j ||
            modell->objekte[k].dreiecke[l].ecke[2] == j   )
        {
          norm_x += modell->objekte[k].dreiecke[l].normal_x;
          norm_y += modell->objekte[k].dreiecke[l].normal_y;
          norm_z += modell->objekte[k].dreiecke[l].normal_z;
          
//           std::cout << "\nWeise dem Knoten " << j << " die Normale der Flaeche o:" << k << ", f:" << l; 
        }
      }
    }
    
    if (norm_x != 0 || norm_y != 0 || norm_z != 0)
    {
      hilf::normieren(norm_x, norm_y, norm_z);
      modell->knoten[j].n_x = norm_x;
      modell->knoten[j].n_y = norm_y;
      modell->knoten[j].n_z = norm_z;
    }
  }
  
  

  eingang.close();
  modell->valid_modell = true;
  return modell;
}


