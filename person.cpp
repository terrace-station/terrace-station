#include "person.hh"


Person::Person()
{
    objekt_typ = "Person";
}


void Person::set_dynmodel()
{
    add_model("door1leaf");
    add_state("standing");
}