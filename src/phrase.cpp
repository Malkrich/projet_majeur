#include "phrase.hpp"

Phrase::Phrase():chaine({new A})
    {}

Phrase::Phrase(std::vector<Caractere*> v_param):chaine(v_param)
    {}

std::vector<Caractere*> const& Phrase::phrase() const
{
    return chaine;
}

std::vector<Caractere*>& Phrase::phrase()
{
    return chaine;
}

unsigned int Phrase::size_phrase() const {return chaine.size();}

unsigned int Phrase::size_phrase() {return chaine.size();}

std::vector<Caractere*> const Phrase::iteration() const
{
    std::vector<Caractere*> ret;
    for(auto it = chaine.begin(); it != chaine.end(); it++)
    {
        auto r = (*it)->rule();
        ret.insert(ret.end(),r.begin(),r.end());
    }

    return ret;
}

Caractere& Phrase::operator()(int pos){return *chaine[pos];}

std::ostream& operator<<(std::ostream& s, Phrase& p)
{
    for(auto it = p.phrase().begin(); it != p.phrase().end(); it++)
    {
        s << *(*it);
    }
    return s;
}