#include "caractere.hpp"

/*================CARACTERE========================*/
Caractere::Caractere(char char_param):symbole(char_param)
    {}

char Caractere::get_char() {return symbole;}



/*================ALPHABET========================*/
Alphabet::Alphabet(char char_param):Caractere(char_param)
    {}

bool Alphabet::is_adding_geometry() const {return true;}

/*================CONSTANTES========================*/

Constante::Constante(char char_param):Caractere(char_param)
    {}

/*================CARACTERES CONSTANTES========================*/
CrochetOpen::CrochetOpen():Constante('[')
    {}

bool Constante::is_adding_geometry() const {return false;}

std::vector<Caractere*> CrochetOpen::rule()
{
    std::vector<Caractere*> ret({new CrochetOpen});
    return ret;
}

void CrochetOpen::action(Turtle& tortue) {
    tortue.sauvegarder_etat();
}  

CrochetClose::CrochetClose():Constante(']')
    {}


std::vector<Caractere*> CrochetClose::rule()
{
    std::vector<Caractere*> ret({new CrochetClose});
    return ret;
}

void CrochetClose::action(Turtle& tortue) {
    tortue.telecharger_etat();
}

Plus::Plus():Constante('+')
    {}


std::vector<Caractere*> Plus::rule()
{
    std::vector<Caractere*> ret({new Plus});
    return ret;
}

void Plus::action(Turtle& tortue) {
    float theta = M_PI / 2;
    tortue.rotation_theta(theta);
}

Moins::Moins():Constante('-')
    {}

std::vector<Caractere*> Moins::rule()
{
    std::vector<Caractere*> ret({new Moins});
    return ret;
}

void Moins::action(Turtle& tortue) {
    float theta = -1 * M_PI / 2;
    tortue.rotation_theta(theta);
}

RollR::RollR():Constante('/')
    {}

std::vector<Caractere*> RollR::rule()
{
    std::vector<Caractere*> ret({new RollR});
    return ret;
}

void RollR::action(Turtle& tortue) {
    float phi = M_PI / 2;
    tortue.rotation_phi(phi);
}

RollL::RollL():Constante('\\')
    {}

std::vector<Caractere*> RollL::rule()
{
    std::vector<Caractere*> ret({new RollL});
    return ret;
}

void RollL::action(Turtle& tortue) {
    float phi = -1 *  M_PI / 2;
    tortue.rotation_phi(phi);
}

/*================LETTRES========================*/
A::A():Alphabet('A')
    {}

std::vector<Caractere*> A::rule()
{
    std::vector<Caractere*> ret({new A, new B});
    return ret;
}

void A::action(Turtle& tortue) {
    tortue.translation(1.0f);
}

B::B():Alphabet('B')
    {}

void B::action(Turtle& tortue) {
    tortue.translation(1.0f);
}    

std::vector<Caractere*> B::rule()
{
    std::vector<Caractere*> ret({new A});
    return ret;
}

F::F():Alphabet('F')
    {}

void F::action(Turtle& tortue) {
    tortue.translation(1.0f);
}  

std::vector<Caractere*> F::rule()
{
//    std::vector<Caractere*> ret({new F, new CrochetOpen, new Plus, new F, new CrochetClose});
    std::vector<Caractere*> ret({new F, new F, new Plus});
    return ret;
}

std::ostream& operator<<(std::ostream& s, Caractere& c)
{
    s << c.get_char();
    return s;
}
