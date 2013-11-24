

enum TRANSFORM {
                  TRA_TRANSLATION=0,
                  TRA_ROTATION,
                  TRA_SCALING
               };

class Transformation
{
   TRANSFORM type;
   
   GLfloat arg1;
   GLfloat arg2;
   GLfloat arg3;
   GLfloat arg4;
   
   Transformation(TRANSFORM type) : type(type)
   {}
   
   void set_type(TRANSFORM type_)
   {
      type = type_;
   }
   
   void set_arguments(GLfloat arg1, GLfloat arg2, GLfloat arg3, GLfloat arg4=1.0){}
   
   void transform()
   {
      switch(type)
      {
         case TRA_TRANSLATION:
            glTranslatef(arg1, arg2, arg3);
            break;
            
         case TRA_ROTATION:
            glTranslatef(arg1, arg2, arg3, arg4);
            break;
            
         case TRA_SCALING:
            glScalef(arg1, arg2, arg3);
            break;
            
         default: 
            ;
      }
   }
   
   void transform(GLfloat arg1_, GLfloat arg2_, GLfloat arg3_, GLfloat arg4_=1.0)
   {
      switch(type)
      {
         case TRA_TRANSLATION:
            glTranslatef(arg1_, arg2_, arg3_);
            break;
            
         case TRA_ROTATION:
            glTranslatef(arg1_, arg2_, arg3_, arg4_);
            break;
            
         case TRA_SCALING:
            glScalef(arg1_, arg2_, arg3_);
            break;
            
         default: 
            ;
      }
   }
};

class Animation
{
   
};

class State
{
   list<std::string> models;
   
   list<Transformation> transformations;
   
   bool animated;
   
   
};


class Dynmodel
{
   vector<State> states;

   
};