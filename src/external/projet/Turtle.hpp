#pragma once

#ifndef TURTLE_HPP
#define TURTLE_HPP


#include <vector>
#include <stack>

#include "Coord.hpp"
#include "../../lib/3d/vec3.hpp"
#include "../../lib/3d/vec2.hpp"

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
        void set_orientation(cpe::vec3& v_param);

        Coord get_etat() const;
        Coord& get_etat();
        cpe::vec3 get_pos() const;
        cpe::vec2 get_rot() const;
        std::queue<cpe::vec2> get_file_rotation() const;
        std::queue<cpe::vec2>& get_file_rotation();

};

std::ostream& operator<<(std::ostream& s,Turtle const& t);

#endif
