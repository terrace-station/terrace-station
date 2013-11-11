#include "district.hh"

District::District()
{
    Deck deck;
    decks.push_back(deck);
}

std::string District::str()
{
    return "District";
}
