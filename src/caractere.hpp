#pragma once

#ifndef CARACTERE_HPP
#define CARACTERE_HPP

#include <iostream>
#include <list>

class Caractere
{
public:
    Caractere();
};

class Alphabet: public Caractere
{
private:
    char symbole;
public:
    Alphabet(char char_param);
    virtual char get_char();
    virtual std::list<Alphabet*> rule()=0;
};

class A: public Alphabet
{
public:
    A();
    std::list<Alphabet*> rule();
};

class B: public Alphabet
{
public:
    B();
    std::list<Alphabet*> rule();
};

class F: public Alphabet
{
public:
    F();
    std::list<Alphabet*> rule();
};

#endif