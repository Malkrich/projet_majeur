
/** TP 4ETI - CPE Lyon - 2013/2014 */

#pragma once

#ifndef SCENE_HPP
#define SCENE_HPP

//#include <GL/gl.h>
#include <GL/glew.h>

#include "../../lib/3d/mat2.hpp"
#include "../../lib/3d/mat3.hpp"
#include "../../lib/3d/vec2.hpp"
#include "../../lib/3d/vec3.hpp"
#include "../../lib/mesh/mesh_parametric.hpp"
#include "../../lib/opengl/mesh_opengl.hpp"
#include "../../lib/mesh/mesh.hpp"
#include "../../lib/interface/camera_matrices.hpp"

// Doc projet
#include "../../external/projet/phrase.hpp"
#include "../../external/projet/Turtle.hpp"
#include "../../external/projet/Coord.hpp"

#include <vector>
#include <cmath>
#include <limits>
#include <stack>
#include <queue>
#include <time.h>

class myWidgetGL;

class scene
{
public:

    scene();


    void build_surface();


    /** \brief Method called only once at the beginning (load off files ...) */
    void load_scene();

    /** \brief Method called at every frame */
    void draw_scene();

    /** Set the pointer to the parent Widget */
    void set_widget(myWidgetGL* widget_param);

    /** Load basic data for the scene */
    void load_common_data();

    void set_cylindre(cpe::mesh& m, int Nx, int Ny, float const h, float const r);

    cpe::mesh create_plan(float xmin, float xmax, float ymin, float ymax, int Nx, int Ny);

    void add_geometry(cpe::mesh& g1, cpe::mesh& g2);
    void copy_geometry(cpe::mesh& g1, cpe::mesh& g2);

    void build_feuille();


    std::stack<cpe::vec2> all_rotation(cpe::mesh& m);
    void all_rotation_inverse(cpe::mesh& m, std::stack<cpe::vec2> pile_rotation);
    void rotation(cpe::mesh& m, cpe::vec2 rotation);
    void rotation_inverse(cpe::mesh& m, cpe::vec2 rotation);
    void translation(cpe::mesh& m, cpe::vec3 translation, const float h);

private:

    /** Load a texture from a given file and returns its id */
    GLuint load_texture_file(std::string const& filename);

    /** Access to the parent object */
    myWidgetGL* pwidget;

    /** Default id for the texture (white texture) */
    GLuint texture_default;
    GLuint texture_ground;

    /** The id of the shader do draw meshes */
    GLuint shader_program_id;

    Turtle t;
    Phrase p;

    cpe::mesh cylindre;
    cpe::mesh branche;
    cpe::mesh branche_copy;
    cpe::mesh arbre;

    cpe::mesh feuille;
    cpe::mesh bush;
    cpe::mesh bush_copy;

    cpe::mesh ground;
    cpe::mesh_opengl ground_opengl;
    GLuint ground_texture;

    cpe::mesh_opengl final_mesh;
};

#endif
