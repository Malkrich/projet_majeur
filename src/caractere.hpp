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
    virtual std::list<alphabet*> rule();
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
};

class F: public alphabet
{
public:
    F();
};

#endif