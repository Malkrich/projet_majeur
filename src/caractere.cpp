#include "caractere.hpp"

caractere::caractere()
    {}

alphabet::alphabet(char char_param):symbole(char_param)
    {}

char alphabet::get_char(){return symbole;}

A::A():alphabet('A')
    {}

std::list<alphabet*> A::rule()
{
    std::list<alphabet*> ret;
    ret.push_back(new A);
    ret.push_back(new B);
    return ret;
}

B::B():alphabet('B')
    {}

std::list<alphabet*> B::rule()
{
    std::list<alphabet*> ret;
    ret.push_back(new A);
    return ret;
}

F::F():alphabet('F')
    {}

std::list<alphabet*> F::rule()
{
    std::list<alphabet*> ret;
    ret.push_back(new F);
    return ret;
}