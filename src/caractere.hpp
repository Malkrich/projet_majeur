#pragma once

#ifndef CARACTERE_HPP
#define CARACTERE_HPP

#include <iostream>
#include <list>

class caractere
{
public:
    caractere();
};

class alphabet: public caractere
{
private:
    char symbole;
public:
    alphabet(char char_param);
    virtual char get_char();
    virtual std::list<alphabet*> rule()=0;
};

class A: public alphabet
{
public:
    A();
    std::list<alphabet*> rule();
};

class B: public alphabet
{
public:
    B();
    std::list<alphabet*> rule();
};

class F: public alphabet
{
public:
    F();
    std::list<alphabet*> rule();
};

#endif