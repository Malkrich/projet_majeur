#include "caractere.hpp"

Caractere::Caractere()
    {}

Alphabet::Alphabet(char char_param):symbole(char_param)
    {}

char Alphabet::get_char(){return symbole;}

A::A():Alphabet('A')
    {}

std::list<Alphabet*> A::rule()
{
    std::list<Alphabet*> ret({new A, new B});
    return ret;
}

B::B():Alphabet('B')
    {}

std::list<Alphabet*> B::rule()
{
    std::list<Alphabet*> ret({new A});
    return ret;
}

F::F():Alphabet('F')
    {}

std::list<Alphabet*> F::rule()
{
    std::list<Alphabet*> ret({new F});
    return ret;
}