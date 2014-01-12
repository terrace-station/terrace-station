#ifndef DYNMODEL_HH
#define DYNMODEL_HH

#include<vector>
#include<string>
#include <GL/gl.h>
// #include <GL/glu.h>

#include "log.hh"

enum TRANSFORM {
                  TRA_TRANSLATE=0,
                  TRA_ROTATE,
                  TRA_SCALE,
                  TRA_VANISH
               };

class Transformation
{
public:
    TRANSFORM type;
    
    GLfloat arg1;
    GLfloat arg2;
    GLfloat arg3;
    GLfloat arg4;
    
    int target;
    float time_delay;
    
    //    void set_type(TRANSFORM type_);
    void set_arguments(GLfloat arg1_, GLfloat arg2_, GLfloat arg3_, GLfloat arg4_=0.0);
    void transform();
    void transform(float& start_zeit);
    //    void transform(GLfloat arg1_, GLfloat arg2_, GLfloat arg3_, GLfloat arg4_=0.0);
    
    //    Transformation(TRANSFORM type);
    Transformation(int target, TRANSFORM type, float time_delay, GLfloat arg1_, GLfloat arg2_, GLfloat arg3_, GLfloat arg4_=0.0);
};

// class Animation
// {
//    
// };

class State
{
public:
    std::vector<Transformation> transformations;
    std::string name;
    
    void add_transformation(int target, TRANSFORM type, float time_delay, GLfloat arg1_, GLfloat arg2_, GLfloat arg3_, GLfloat arg4_=0.0);
    
    State(std::string name);
};


enum DYNMODELNAME {
                DYN_door1 = 0
              };


class Dynmodel
{
public:
    std::vector<std::string> models;
    std::vector<State> states;
    
    int state;
    float time_lastchange;
   
    void set_state(std::string);
    void set_state(int);
    std::string get_state();
    void zeichne();
    void add_state(std::string);
    void add_model(std::string);
    Dynmodel(DYNMODELNAME modelltyp);
};



#endif