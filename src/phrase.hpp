#pragma once

#ifndef PHRASE_HPP
#define PHRASE_HPP

#include <vector>
#include <ostream>

#include "caractere.hpp"

class Phrase
{
private:
    std::vector<Caractere*> chaine;
public:
    Phrase();
    Phrase(std::vector<Caractere*> v_param);

    std::vector<Caractere*> const& phrase() const;
    std::vector<Caractere*>& phrase();
    unsigned int size_phrase() const;
    unsigned int size_phrase();

    std::vector<Caractere*> const iteration() const;

    Caractere& operator()(int pos);
};

std::ostream& operator<<(std::ostream& s, Phrase& p);

#endif