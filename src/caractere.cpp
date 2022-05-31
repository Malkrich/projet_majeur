#include "caractere.hpp"

caractere::caractere()
    {}

alphabet::alphabet(char char_param):symbole(char_param)
    {}

char alphabet::get_char(){return symbole;}

std::list<alphabet*> A::rule()
{
    std::list<alphabet*> ret;
    ret.push_back(new A);
    return ret;
}

A::A():alphabet('A')
    {}

B::B():alphabet('B')
    {}

F::F():alphabet('F')
    {}