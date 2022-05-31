#pragma once

#ifndef PHRASE_HPP
#define PHRASE_HPP

#include <vector>
#include <ostream>

#include "caractere.hpp"

class Phrase
{
private:
    std::vector<Alphabet*> chaine;
public:
    Phrase();
    Phrase(std::vector<Alphabet*> v_param);

    std::vector<Alphabet*> const& phrase() const;
    std::vector<Alphabet*>& phrase();

    std::vector<Alphabet*> const iteration() const;

    Alphabet& operator()(int pos);
};

std::ostream& operator<<(std::ostream& s, Phrase& p);

#endif