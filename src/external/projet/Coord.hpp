#pragma once

#ifndef COORD_HPP
#define COORD_HPP

#include <ostream>
#include <cmath>

class Coord{
    float x;
    float y;
    float z;
    float theta;
    float phi;

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
        void translation(float r);
        void rotation_theta(float angle);
        void rotation_phi(float angle);
        void teleportation(float new_x,float new_y,float new_z,float new_theta,float new_phi);

};

std::ostream& operator<<(std::ostream& s,Coord const& c);

#endif