#ifndef PERSON_HH
#define PERSON_HH


class Person: public Mausobjekt, public Dynmodel
{
    int x;
    int y;
    
public:
    
    void set_dynmodel();

};


#endif
