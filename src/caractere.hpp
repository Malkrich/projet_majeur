#pragma once

#ifndef CARACTERE_HPP
#define CARACTERE_HPP

#include <iostream>
#include <vector>
#include <ostream>

class Caractere
{
private:
    char symbole;
public:
    Caractere(char char_param);
    char get_char();
};

class Alphabet: public Caractere
{
public:
    Alphabet(char char_param);
    virtual std::vector<Alphabet*> rule()=0;
};

class A: public Alphabet
{
public:
    A();
    std::vector<Alphabet*> rule();
};

class B: public Alphabet
{
public:
    B();
    std::vector<Alphabet*> rule();
};

class F: public Alphabet
{
public:
    F();
    std::vector<Alphabet*> rule();
};

std::ostream& operator<<(std::ostream& s, Caractere& c);

#endif