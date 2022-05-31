#include "phrase.hpp"

Phrase::Phrase():chaine({new A})
    {}

Phrase::Phrase(std::vector<Alphabet*> v_param):chaine(v_param)
    {}

std::vector<Alphabet*> const& Phrase::phrase() const
{
    return chaine;
}

std::vector<Alphabet*>& Phrase::phrase()
{
    return chaine;
}

std::vector<Alphabet*> const Phrase::iteration() const
{
    std::vector<Alphabet*> ret;
    for(auto it = chaine.begin(); it != chaine.end(); it++)
    {
        ret.insert(ret.end(),(*it)->rule().begin(),(*it)->rule().end());
    }

    return ret;
}

std::ostream& operator<<(std::ostream& s, Phrase& p)
{
    for(auto it = p.phrase().begin(); it != p.phrase().end(); it++)
    {
        s << *(*it);
    }
    return s;
}