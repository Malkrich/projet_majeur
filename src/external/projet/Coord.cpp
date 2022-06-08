#include "Coord.hpp"

Coord::Coord() : x(0.0f),y(0.0f),z(0.0f),theta(0.0f),phi(0.0f),beta(0.0f){

}

Coord::Coord(float x_init,float y_init,float z_init,float theta_init,float phi_init) : x(x_init),y(y_init),z(z_init),theta(theta_init),phi(phi_init){

}

float Coord::get_x() const {
    return x;
}

float& Coord::get_x() {
    return x;
}

float Coord::get_y() const {
    return y;
}

float& Coord::get_y() {
    return y;
}

float Coord::get_z() const {
    return z;
}

float& Coord::get_z() {
    return z;
}

float Coord::get_theta() const {
    return theta;
}

float& Coord::get_theta() {
    return theta;
}

float Coord::get_phi() const {
    return phi;
}

float& Coord::get_phi() {
    return phi;
}

std::queue<cpe::vec2> Coord::get_file_rotation() const {
    return file_rotation;
}

std::queue<cpe::vec2>& Coord::get_file_rotation() {
    return file_rotation;
}

void Coord::translation(float r) {
//    x = x + r*sin(theta)*cos(phi);
//    y = y + r*sin(theta)*sin(phi);
//    z = z + r*cos(theta);

//    cpe::mat3 Rx  = {1.0f, 0.0f, 0.0f,
//                    0.0f, cos(theta), -sin(theta),
//                    0.0f, sin(theta), cos(theta)};

//    cpe::mat3 Ry  = {cos(phi), 0.0f, sin(phi),
//                    0.0f, 1.0f, 0.0f,
//                    -sin(phi), 0.0f, cos(phi)};

//    cpe::mat3 Rz  = {cos(beta), -sin(beta), 0.0f,
//                    sin(beta), cos(beta), 0.0f,
//                    0.0f, 0.0f, 1.0f};

    x += sens.x();
    y += sens.y();
    z += sens.z();
}


void Coord::rotation_theta(float angle){
    theta = theta + angle;

//    cpe::mat3 Rx  = {1.0f, 0.0f, 0.0f,
//                    0.0f, cos(theta), -sin(theta),
//                    0.0f, sin(theta), cos(theta)};
    cpe::mat3 Rx  = {1.0f, 0.0f, 0.0f,
                    0.0f, cos(angle), -sin(angle),
                    0.0f, sin(angle), cos(angle)};
    sens = Rx*sens;
}

void Coord::rotation_phi(float angle){
    phi = phi + angle;

//    cpe::mat3 Ry  = {cos(phi), 0.0f, sin(phi),
//                    0.0f, 1.0f, 0.0f,
//                    -sin(phi), 0.0f, cos(phi)};
    cpe::mat3 Ry  = {cos(angle), 0.0f, sin(angle),
                    0.0f, 1.0f, 0.0f,
                    -sin(angle), 0.0f, cos(angle)};

    sens = Ry*sens;
}

void Coord::teleportation(float new_x,float new_y,float new_z,float new_theta,float new_phi){
    x = new_x;
    y = new_y;
    z = new_z;
    theta = new_theta;
    phi = new_phi;
}

cpe::vec3& Coord::orientation(){return sens;}
cpe::vec3 const Coord::orientation() const {return sens;}

void Coord::remplir_file_rotation(cpe::vec2 new_rot) { //new ugo
    file_rotation.push(new_rot);
}

std::ostream& operator<<(std::ostream& s,Coord const& c) {
    float x = c.get_x();
    float y = c.get_y();
    float z = c.get_z();
    float theta = c.get_theta();
    float phi = c.get_phi();
    s<<" x = "<<x<<", y = "<<y<<", z = "<<z<<", theta = "<<theta<<", phi = "<<phi;
    return s;
}
