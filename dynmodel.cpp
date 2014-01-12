#include "dynmodel.hh"

#include "openglwidget.hh"

// Transformation::Transformation(TRANSFORM type) : type(type)
// {}

Transformation::Transformation(int target, TRANSFORM type, float timedelay, GLfloat arg1_, GLfloat arg2_, GLfloat arg3_, GLfloat arg4_) : type(type), target(target), timedelay(timedelay)
{
    set_arguments(arg1_, arg2_, arg3_, arg4_);
}


// void Transformation::set_type(TRANSFORM type_)
// {
//     type = type_;
// }


void Transformation::set_arguments(GLfloat arg1_, GLfloat arg2_, GLfloat arg3_, GLfloat arg4_)
{
    arg1 = arg1_;
    arg2 = arg2_;
    arg3 = arg3_;
    arg4 = arg4_;
}


void Transformation::transform()
{
    switch(type)
    {
        case TRA_TRANSLATE:
        glTranslatef(arg1, arg2, arg3);
        break;
        
        case TRA_ROTATE:
        glRotatef(arg1, arg2, arg3, arg4);
        break;
        
        case TRA_SCALE:
        glScalef(arg1, arg2, arg3);
        break;
        
        default: 
        ;
    }
}


// void Transformation::transform(GLfloat arg1_, GLfloat arg2_, GLfloat arg3_, GLfloat arg4_=0.0);
// {
//     switch(type)
//     {
//         case TRA_TRANSLATE:
//         glTranslatef(arg1_, arg2_, arg3_);
//         break;
//         
//         case TRA_ROTATE:
//         glTranslatef(arg1_, arg2_, arg3_, arg4_);
//         break;
//         
//         case TRA_SCALE:
//         glScalef(arg1_, arg2_, arg3_);
//         break;
//         
//         default: 
//         ;
//     }
// }

// // // // // // // // // // // // // // // // // // // // // // // // States   // // // // // // // // // // // // // // // //

void State::add_transformation(int target, TRANSFORM type, float timedelay, GLfloat arg1_, GLfloat arg2_, GLfloat arg3_, GLfloat arg4_)
{
    transformations.emplace_back(target, type, timedelay, arg1_, arg2_, arg3_, arg4_);
}

State::State(std::string name) : name(name)
{}

// // // // // // // // // // // // // // // // // // // // // // // // Dynmodel // // // // // // // // // // // // // // // //

void Dynmodel::zeichne()
{
    int transf=0;
    
    for (int i=0; i < models.size(); i++)
    {
        glPushMatrix();
        while(transf < states[state].transformations.size() && states[state].transformations[transf].target == i)
        {
            states[state].transformations[transf].transform();
            ++transf;
            
        }
        
        Openglwidget::models->get(models[i])->zeichne();
        glPopMatrix();
    }
}


void Dynmodel::add_model(std::string modelname)
{
    models.push_back(modelname);
}


void Dynmodel::add_state(std::string statename)
{
    states.emplace_back(statename);
}


Dynmodel::Dynmodel(DYNMODELNAME modelltyp)
{
    state = 0;
    
    switch(modelltyp)
    {
        case DYN_door1:
            add_model("door1frame");
            add_model("door1leaf");
            add_state("closed");
                states[0].add_transformation(1, TRA_TRANSLATE, 0.0, 0.0, 0.0, -2.0);
                states[0].add_transformation(1, TRA_TRANSLATE, 1.0, 0.0, 0.0, 2.0);
            add_state("open");
                states[1].add_transformation(1, TRA_TRANSLATE, 1.0, 0.0, 0.0, -2.0);  // target, type, arg1, arg2, arg3
                break;
            
        default:
            break;
        
    }
}




