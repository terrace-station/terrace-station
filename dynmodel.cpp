#include "dynmodel.hh"

#include "openglwidget.hh"

// Transformation::Transformation(TRANSFORM type) : type(type)
// {}

Transformation::Transformation(int target, TRANSFORM type, float time_delay, GLfloat arg1_, GLfloat arg2_, GLfloat arg3_, GLfloat arg4_) : type(type), target(target), time_delay(time_delay)
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


void Transformation::transform(float& time_lastchange)
{
    float fortschritt = (Openglwidget::laufzeit-time_lastchange)/time_delay;
    GLfloat arg1_, arg2_, arg3_;
    
    switch(type)
    {
        case TRA_TRANSLATE:
        arg1_ = arg1*fortschritt;
        arg2_ = arg2*fortschritt;
        arg3_ = arg3*fortschritt;
        glTranslatef(arg1_, arg2_, arg3_);
        break;
        
        case TRA_ROTATE:
        arg1_ = arg1*fortschritt;
        glRotatef(arg1_, arg2_, arg3_, arg4); // arg4 ist die 3.Koordinate der Drehachse und muss nie geändert werden
        break;
        
        case TRA_SCALE:
        arg1_ = arg1*fortschritt+(1-fortschritt);
        arg2_ = arg2*fortschritt+(1-fortschritt);
        arg3_ = arg3*fortschritt+(1-fortschritt);
        glScalef(arg1_, arg2_, arg3_);
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

void State::add_transformation(int target, TRANSFORM type, float time_delay, GLfloat arg1_, GLfloat arg2_, GLfloat arg3_, GLfloat arg4_)
{
    transformations.emplace_back(target, type, time_delay, arg1_, arg2_, arg3_, arg4_);
}

State::State(std::string name) : name(name)
{}

// // // // // // // // // // // // // // // // // // // // // // // // Dynmodel // // // // // // // // // // // // // // // //


Dynmodel::Dynmodel(DYNMODELNAME modelltyp) : state(0)
{
    set_dynmodel(modelltyp);
}


Dynmodel::Dynmodel() : state(0)
{
}


void Dynmodel::zeichne()
{
    int transf=0;
    
    for (int i=0; i < models.size(); i++)
    {
        glPushMatrix();
        while(transf < states[state].transformations.size() && states[state].transformations[transf].target == i)
        {
            if (states[state].transformations[transf].time_delay == 0.0 || Openglwidget::laufzeit>(time_lastchange+states[state].transformations[transf].time_delay))
                states[state].transformations[transf].transform();
            else
                states[state].transformations[transf].transform(time_lastchange);
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


void Dynmodel::set_state(int state_)
{
    if (state_ < 0 || state_ >= states.size())
        LOG(WARNING) << "State existiert nicht!";
    else
    {
        state = state;
        time_lastchange = Openglwidget::laufzeit;
    }

}


void Dynmodel::set_state(std::string state_)
{
    int i;
    for (i=0; i<states.size(); i++)
    {
        if (states[i].name == state_)
        {
            state = i;
            time_lastchange = Openglwidget::laufzeit;
            break;
        }
    }
    if (i == states.size())
        LOG(WARNING) << "State existiert nicht!";
    
}


std::string Dynmodel::get_state()
{
    return states[state].name;
}


void Dynmodel::set_dynmodel(DYNMODELNAME modelltyp)
{
    switch(modelltyp)
    {
        case DYN_door1:
            add_model("door1frame");
            add_model("door1leaf");
            add_state("closed");
                states[0].add_transformation(1, TRA_TRANSLATE, 0.0, 0.0, 0.0, -1.7);
                states[0].add_transformation(1, TRA_TRANSLATE, 2.0, 0.0, 0.0, 1.7);
            add_state("open");
                states[1].add_transformation(1, TRA_TRANSLATE, 2.0, 0.0, 0.0, -1.7);  // target, type, timedelay, arg1, arg2, arg3
                break;
            
        case DYN_door2:
            add_model("door1frame");
            add_model("door2leaf");
            add_model("door2leaf");
            add_state("closed");
                states[0].add_transformation(1, TRA_TRANSLATE, 0.0, 0.0, 0.35, 0.0);
                states[0].add_transformation(1, TRA_SCALE,     0.0, 1.0, 0.2, 1.0);
                states[0].add_transformation(1, TRA_SCALE,     1.0, 1.0, 5.0, 1.0);
                states[0].add_transformation(2, TRA_TRANSLATE, 0.0, 0.0,-0.35, 0.0);
                states[0].add_transformation(2, TRA_SCALE,     0.0, 1.0,-1.0, 1.0);
                states[0].add_transformation(2, TRA_SCALE,     0.0, 1.0, 0.2, 1.0);
                states[0].add_transformation(2, TRA_SCALE,     1.0, 1.0, 5.0, 1.0);
            add_state("open");
                states[1].add_transformation(1, TRA_TRANSLATE, 0.0, 0.0, 0.35, 0.0);
                states[1].add_transformation(1, TRA_SCALE,     1.0, 1.0, 0.2, 1.0);
                states[1].add_transformation(2, TRA_TRANSLATE, 0.0, 0.0,-0.35, 0.0);
                states[1].add_transformation(2, TRA_SCALE,     0.0, 1.0,-1.0, 1.0);
                states[1].add_transformation(2, TRA_SCALE,     1.0, 1.0, 0.2, 1.0);
                break;
            
        default:
            break;
        
    }
}



