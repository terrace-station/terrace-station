void Openglwidget::set_material_std()
{
   set_material_ambi(0.05, 0.05, 0.05, 1.0);
   set_material_diff(0.8, 0.8, 0.8, 1.0);
   set_material_spec(0.0, 0.0, 0.0, 1.0);
   set_material_shin(0);
}


void Openglwidget::set_material(MATERIAL material)
{
   switch(material)
   {
      case MAT_KUPFER:
         set_material_ambi(0.23, 0.09, 0.03, 1.0);
         set_material_diff(0.55, 0.21, 0.07, 1.0);
         set_material_spec(0.58, 0.22, 0.07, 1.0);
         set_material_shin(51.2);
      break;
      
      case MAT_GUMMI:
         set_material_ambi(0.02, 0.02, 0.02, 1.0);
         set_material_diff(0.01, 0.01, 0.01, 1.0);
         set_material_spec(0.40, 0.40, 0.40, 1.0);
         set_material_shin(10.0);
      break;
      
      case MAT_PLASTIK:
         set_material_ambi(0.00, 0.00, 0.00, 1.0);
         set_material_diff(0.01, 0.01, 0.01, 1.0);
         set_material_spec(0.50, 0.50, 0.50, 1.0);
         set_material_shin(32.0);
      break;
      
      case MAT_MESSING:
         set_material_ambi(0.33, 0.22, 0.03, 1.0);
         set_material_diff(0.78, 0.57, 0.11, 1.0);
         set_material_spec(0.99, 0.94, 0.81, 1.0);
         set_material_shin(27.9);
      break;
      
      case MAT_SILBER:
         set_material_ambi(0.23, 0.23, 0.23, 1.0);
         set_material_diff(0.28, 0.28, 0.28, 1.0);
         set_material_spec(0.77, 0.77, 0.77, 1.0);
         set_material_shin(89.6);
      break;
      
      case MAT_GOLD:
         set_material_ambi(0.25, 0.22, 0.06, 1.0);
         set_material_diff(0.35, 0.31, 0.09, 1.0);
         set_material_spec(0.90, 0.72, 0.21, 1.0);
         set_material_shin(83.2);
      break;
      
      default:
         set_material_std();
   }
}


void Openglwidget::set_material_ambi(float ambi1, float ambi2, float ambi3, float ambi4)
{
   mat_ambi[0] = ambi1;
   mat_ambi[1] = ambi2;
   mat_ambi[2] = ambi3;
   mat_ambi[3] = ambi4;
   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambi);
}


void Openglwidget::set_material_diff(float diff1, float diff2, float diff3, float diff4)
{
   mat_diff[0] = diff1;
   mat_diff[1] = diff2;
   mat_diff[2] = diff3;
   mat_diff[3] = diff4;
   glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diff);
}


void Openglwidget::set_material_spec(float spec1, float spec2, float spec3, float spec4)
{
   mat_spec[0] = spec1;
   mat_spec[1] = spec2;
   mat_spec[2] = spec3;
   mat_spec[3] = spec4;
   glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_spec);
}


void Openglwidget::set_material_shin(float shin1)
{
   mat_shin = shin1;
   glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shin1);
}
