#include "caractere.hpp"

/*================CARACTERE========================*/
Caractere::Caractere(char char_param):symbole(char_param)
    {}

char Caractere::get_char() {return symbole;}



/*================ALPHABET========================*/
Alphabet::Alphabet(char char_param):Caractere(char_param)
    {}

bool Alphabet::hasRule() {return true;}

/*================CONSTANTES========================*/

Constante::Constante(char char_param):Caractere(char_param)
    {}

bool Constante::hasRule() {return false;}

/*================CARACTERES CONSTANTES========================*/
CrochetOpen::CrochetOpen():Constante('[')
    {}

std::vector<Caractere*> CrochetOpen::rule()
{
    std::vector<Caractere*> ret({new CrochetOpen});
    return ret;
}

CrochetClose::CrochetClose():Constante(']')
    {}

std::vector<Caractere*> CrochetClose::rule()
{
    std::vector<Caractere*> ret({new CrochetClose});
    return ret;
}

/*================LETTRES========================*/
A::A():Alphabet('A')
    {}

std::vector<Caractere*> A::rule()
{
    std::vector<Caractere*> ret({new A, new B});
    return ret;
}

B::B():Alphabet('B')
    {}

std::vector<Caractere*> B::rule()
{
    std::vector<Caractere*> ret({new A});
    return ret;
}

F::F():Alphabet('F')
    {}

std::vector<Caractere*> F::rule()
{
    std::vector<Caractere*> ret({new F});
    return ret;
}

std::ostream& operator<<(std::ostream& s, Caractere& c)
{
    s << c.get_char();
    return s;
}