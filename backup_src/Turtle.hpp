#pragma once

#ifndef TURTLE_HPP
#define TURTLE_HPP


#include <vector>
#include <stack>

#include "Coord.hpp"

class Turtle{
    Coord etat;
    std::stack<Coord> pile_etat;


    public:
        Turtle();
        void translation(float r);
        void rotation_theta(float angle);
        void rotation_phi(float angle);
        void sauvegarder_etat();
        void telecharger_etat();

        Coord get_etat() const;
        Coord& get_etat();
        


};

std::ostream& operator<<(std::ostream& s,Turtle const& t);

#endif