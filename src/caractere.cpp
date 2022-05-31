#include "caractere.hpp"

/*================CARACTERE========================*/
Caractere::Caractere(char char_param):symbole(char_param)
    {}

char Caractere::get_char() {return symbole;}



/*================ALPHABET========================*/
Alphabet::Alphabet(char char_param):Caractere(char_param)
    {}



/*================LETTRES========================*/
A::A():Alphabet('A')
    {}



std::vector<Alphabet*> A::rule()
{
    std::vector<Alphabet*> ret({new A, new B});
    return ret;
}

B::B():Alphabet('B')
    {}

std::vector<Alphabet*> B::rule()
{
    std::vector<Alphabet*> ret({new A});
    return ret;
}

F::F():Alphabet('F')
    {}

std::vector<Alphabet*> F::rule()
{
    std::vector<Alphabet*> ret({new F});
    return ret;
}

std::ostream& operator<<(std::ostream& s, Caractere& c)
{
    s << c.get_char();
    return s;
}