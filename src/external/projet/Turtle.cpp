#include <iostream>

#include "Turtle.hpp"

Turtle::Turtle()  {
//    Coord etat = Coord();
}

void Turtle::translation(float r) {
    /*
    float old_x = etat.get_x();
    float old_y = etat.get_y();
    */
    etat.translation(r);
    /*
    float new_x = etat.get_x();
    float new_y = etat.get_y();
    draw_segment(old_x,old_y,new_x,new_y);
    */
}

void Turtle::rotation_theta(float angle) {
    etat.rotation_theta(angle);
}

void Turtle::rotation_phi(float angle) {
    etat.rotation_phi(angle);
}


Coord Turtle::get_etat() const {
    return etat;
}

Coord& Turtle::get_etat() {
    return etat;
}

cpe::vec3 Turtle::get_pos() const
{
    float const x = etat.get_x();
    float const y = etat.get_y();
    float const z = etat.get_z();
    cpe::vec3 ret = {x,y,z};
    return ret;
}

cpe::vec2 Turtle::get_rot() const
{
    float const theta = etat.get_theta();
    float const phi = etat.get_phi();
    cpe::vec2 ret = {theta,phi};
    return ret;
}

void Turtle::sauvegarder_etat() {
    pile_etat.push(etat);
}

void Turtle::telecharger_etat() {
    etat = pile_etat.top();
    pile_etat.pop();
}

std::ostream& operator<<(std::ostream& s,Turtle const& t) {
    Coord etat = t.get_etat();
    s<<"Etat de la tortue : "<<etat;
    return s;
} 
