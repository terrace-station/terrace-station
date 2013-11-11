#ifndef DECK_HH
#define DECK_HH


class District;


class Deck
{
public:
   
   District* district;
   
   int size_x, size_y;
   
   
   Deck();
   ~Deck();
};


#endif