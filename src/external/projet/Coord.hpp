#pragma once

#ifndef COORD_HPP
#define COORD_HPP

#include <ostream>
#include <cmath>
#include <queue>

#include "../../lib/3d/vec2.hpp"
#include "../../lib/3d/mat3.hpp"
#include "../../lib/3d/vec3.hpp"

class Coord{
    float x;
    float y;
    float z;
    float theta;
    float phi;
    float beta;
    std::queue<cpe::vec2> file_rotation; //new ugo

    cpe::vec3 sens;

    public:
        Coord();
        Coord(float x,float y,float z,float theta,float phi);

        float get_x() const;
        float& get_x();
        float get_y() const;
        float& get_y();
        float get_z() const;
        float& get_z();
        float get_theta() const;
        float& get_theta();
        float get_phi() const;
        float& get_phi();
        std::queue<cpe::vec2> get_file_rotation() const;
        std::queue<cpe::vec2>& get_file_rotation();
        void translation(float r);
        void rotation_theta(float angle);
        void rotation_phi(float angle);
        void teleportation(float new_x,float new_y,float new_z,float new_theta,float new_phi);
        void remplir_file_rotation(cpe::vec2 new_rot); //new ugo

        cpe::vec3& orientation();
        cpe::vec3 const orientation() const;

};

std::ostream& operator<<(std::ostream& s,Coord const& c);

#endif
