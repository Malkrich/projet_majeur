#include "caractere.hpp"

/*================CARACTERE========================*/
Caractere::Caractere(char char_param, int ordre_param):symbole(char_param),incr_ordre(ordre_param)
    {}

char Caractere::get_char() {return symbole;}
int Caractere::get_incr_ordre() const {return incr_ordre;}


/*================ALPHABET========================*/
Alphabet::Alphabet(char char_param):Caractere(char_param,0)
    {}

bool Alphabet::is_adding_geometry() const {return true;}

/*================CONSTANTES========================*/

Constante::Constante(char char_param, int ordre_param):Caractere(char_param,ordre_param),angle_x(M_PI/5),angle_y(M_PI/5),angle_z(M_PI/18)
{}

/*================CARACTERES CONSTANTES========================*/
CrochetOpen::CrochetOpen():Constante('[',1)
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

CrochetClose::CrochetClose():Constante(']',-1)
    {}


std::vector<Caractere*> CrochetClose::rule()
{
    std::vector<Caractere*> ret({new CrochetClose});
    return ret;
}

void CrochetClose::action(Turtle& tortue) {
    tortue.telecharger_etat();
}

Plus::Plus():Constante('+',0)
    {}


std::vector<Caractere*> Plus::rule()
{
    std::vector<Caractere*> ret({new Plus});
    return ret;
}

void Plus::action(Turtle& tortue) {
    float theta = angle_x;
    tortue.rotation_theta(theta);
}

Moins::Moins():Constante('-',0)
    {}

std::vector<Caractere*> Moins::rule()
{
    std::vector<Caractere*> ret({new Moins});
    return ret;
}

void Moins::action(Turtle& tortue) {
    float theta = -angle_x;
    tortue.rotation_theta(theta);
}

RollR::RollR():Constante('/',0)
    {}

std::vector<Caractere*> RollR::rule()
{
    std::vector<Caractere*> ret({new RollR});
    return ret;
}

void RollR::action(Turtle& tortue) {
    float phi = angle_y;
    tortue.rotation_phi(phi);
}

RollL::RollL():Constante('\\',0)
    {}

std::vector<Caractere*> RollL::rule()
{
    std::vector<Caractere*> ret({new RollL});
    return ret;
}

void RollL::action(Turtle& tortue) {
    float phi = -angle_y;
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
    /*ARBRE 2D*/
//    std::vector<Caractere*> ret({new F, new CrochetOpen, new Plus, new F, new CrochetClose,
//                                 new F, new CrochetOpen, new Moins, new F, new CrochetClose,
//                                 new F});


    /*ARBRE 3D*/
//    std::vector<Caractere*> ret({new F, new CrochetOpen, new Plus, new F, new L, new CrochetClose,
//                                 new CrochetOpen, new RollL, new F, new L, new CrochetClose,
//                                 new F, new CrochetOpen, new Moins, new F, new L, new CrochetClose,
//                                 new F, new CrochetOpen, new RollR, new F, new L, new CrochetClose,
//                                 new F});

    /*ARBRE ENCHANTE*/
//    std::vector<Caractere*> ret({new F, new CrochetOpen, new CrochetOpen, new RollR, new F, new L, new CrochetClose, new F, new L, new CrochetClose, new Plus, new RollL, new F,new Moins,new F});
//    std::vector<Caractere*> ret({new F, new CrochetOpen, new CrochetOpen, new RollR, new F, new CrochetClose, new F, new CrochetClose, new Plus, new RollL, new F,new Moins,new F});

    /*ARBRE 3D WIDE*/
//    std::vector<Caractere*> ret({new F, new CrochetOpen, new Plus, new F, new L, new CrochetClose,
//                                 new CrochetOpen, new RollL, new F, new L, new CrochetClose,
//                                 new CrochetOpen, new Moins, new F, new L, new CrochetClose,
//                                 new CrochetOpen, new RollR, new F, new L, new CrochetClose,
//                                 new F});

    std::vector<Caractere*> ret({new F,new CrochetOpen,new RollL,new F,new CrochetClose,new Plus,new RollL,new F,new RollR,new CrochetOpen,new F,new CrochetOpen,new Plus, new Plus, new F,new L,new CrochetClose,new F,new L,new CrochetClose,new Moins,new Moins});

    return ret;
}

L::L():Alphabet('L')
    {}

void L::action(Turtle& tortue){
}

std::vector<Caractere*> L::rule()
{
    std::vector<Caractere*> ret = {new L};

    return ret;
}

std::ostream& operator<<(std::ostream& s, Caractere& c)
{
    s << c.get_char();
    return s;
}
