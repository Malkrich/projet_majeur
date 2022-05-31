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
    virtual std::vector<Caractere*> rule()=0;
    virtual bool hasRule()=0;
};

class Constante: public Caractere
{
public:
    Constante(char char_param);
    virtual std::vector<Caractere*> rule()=0;
    bool hasRule();
};

class CrochetOpen: public Constante
{
public:
    CrochetOpen();
    std::vector<Caractere*> rule();
};

class CrochetClose: public Constante
{
public:
    CrochetClose();
    std::vector<Caractere*> rule();
};

class Alphabet: public Caractere
{
public:
    Alphabet(char char_param);
    virtual std::vector<Caractere*> rule()=0;
    bool hasRule();
};

class A: public Alphabet
{
public:
    A();
    std::vector<Caractere*> rule();
};

class B: public Alphabet
{
public:
    B();
    std::vector<Caractere*> rule();
};

class F: public Alphabet
{
public:
    F();
    std::vector<Caractere*> rule();
};

std::ostream& operator<<(std::ostream& s, Caractere& c);

#endif