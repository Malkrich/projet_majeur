

#include <GL/glew.h>

#include "scene.hpp"

#include "../../lib/opengl/glutils.hpp"

#include "../../lib/perlin/perlin.hpp"
#include "../../lib/interface/camera_matrices.hpp"

#include "../interface/myWidgetGL.hpp"

#include <cmath>
#include <queue>

#include <string>
#include <sstream>
#include "../../lib/mesh/mesh_io.hpp"

#include "../../lib/3d/vec2.hpp"

using namespace cpe;

void scene::add_geometry(cpe::mesh& g1, cpe::mesh& g2)
{
    unsigned const int size_to_add = g2.size_vertex();

    for(int i = 0; i < g1.size_vertex(); i++)
    {
        g2.add_vertex(g1.vertex(i));
    }

    for(int i = 0; i < g1.size_connectivity(); i++)
    {
        int u0 = g1.connectivity(i)[0]+size_to_add;
        int u1 = g1.connectivity(i)[1]+size_to_add;
        int u2 = g1.connectivity(i)[2]+size_to_add;
        triangle_index connec = {u0,u1,u2};
        g2.add_triangle_index(connec);
    }

    for(int i = 0; i < g1.size_color(); i++)
    {
        g2.add_color(g1.color(i));
    }
    g2.fill_empty_field_by_default();
}

void scene::copy_geometry(mesh &g1, mesh &g2)
{
    for(int i = 0; i < g1.size_vertex(); i++)
    {
        g2.vertex(i) = g1.vertex(i);
    }

    for(int i = 0; i < g1.size_connectivity(); i++)
    {
        g2.connectivity(i) = g1.connectivity(i);
    }

    for(int i = 0; i < g1.size_color(); i++)
    {
        g2.color(i) = g1.color(i);
    }
    g2.fill_empty_field_by_default();
}

void scene::build_feuille()
{
    add_geometry(cylindre,feuille);
    feuille.transform_apply_scale(0.3f,0.3f,0.5f);

    std::vector<vec3> vertices = {{0.0f,0.0f,0.04f},
                           {-0.015f,0.0f,0.06f},
                           {0.015f,0.0f,0.06},
                           {-0.015f,0.0f,0.08f},
                           {0.015f,0.0f,0.08f},
                           {0.0f,0.0f,0.1f}};

    std::vector<triangle_index> connec = {triangle_index(0,1,2),
                                         triangle_index(1,3,2),
                                         triangle_index(2,4,3),
                                         triangle_index(3,4,5)};

    cpe::mesh m;
    for(auto v : vertices)
        m.add_vertex(v);

    for(auto c : connec)
        m.add_triangle_index(c);

    add_geometry(m,feuille);

    add_geometry(feuille,bush);
    feuille.transform_apply_rotation({0.0f,1.0f,0.0f},M_PI/5);
    add_geometry(feuille,bush);
    feuille.transform_apply_rotation({0.0f,1.0f,0.0f},-2*M_PI/5);
    add_geometry(feuille,bush);
    feuille.transform_apply_rotation({0.0f,0.0f,1.0f},M_PI/2);
    add_geometry(feuille,bush);
    feuille.transform_apply_rotation({0.0f,0.0f,1.0f},M_PI);
    add_geometry(feuille,bush);
    feuille.transform_apply_rotation({1.0f,0.0f,0.0f},M_PI/5);
    add_geometry(feuille,bush);

    bush.fill_empty_field_by_default();

    for(int i = 0; i < bush.size_color(); i++)
    {
        bush.color(i) = {0.2f,0.8f,0.2f};
    }
}

std::stack<cpe::vec2> scene::all_rotation(cpe::mesh& m) {
    std::stack<cpe::vec2> pile_rotation;
     std::queue<cpe::vec2> file_rotation = t.get_file_rotation();
     int taille = file_rotation.size();
     for (int i =0; i < taille; ++i) {
         cpe::vec2 new_rot = file_rotation.front();
         file_rotation.pop();
         rotation(m, new_rot);
         pile_rotation.push(new_rot);
     }
     return pile_rotation;
}

void scene::all_rotation_inverse(cpe::mesh& m, std::stack<cpe::vec2> pile_rotation) {
     int taille = pile_rotation.size();
     for (int i =0; i < taille; ++i) {
         cpe::vec2 new_rot = pile_rotation.top();
         pile_rotation.pop();
         rotation_inverse(m, -1.0f*new_rot);
     }
}

void scene::rotation(cpe::mesh& m, cpe::vec2 rotation)
{
    m.transform_apply_rotation({1.0f,0.0f,0.0f},rotation.x());
    m.transform_apply_rotation({0.0f,1.0f,0.0f},rotation.y());
}

void scene::rotation_inverse(cpe::mesh& m, cpe::vec2 rotation)
{
    m.transform_apply_rotation({0.0f,1.0f,0.0f},rotation.y());
    m.transform_apply_rotation({1.0f,0.0f,0.0f},rotation.x());
}


void scene::translation(cpe::mesh& m, cpe::vec3 translation, const float h)
{
    translation = h*translation;
    m.transform_apply_translation(translation);
}

void scene::build_surface()
{
    srand(time(NULL));

    int Nx = 20;
    int Ny = 20;
    float xmin = -1.0f;
    float xmax = 1.0f;
    float ymin = -1.0f;
    float ymax = 1.0f;

    const float h = 0.1f;
    const float r = 0.01f;

    cpe::vec3 dir_cylindre = {0.0f,0.0f,1.0f};

    cylindre = create_plan(xmin,xmax,ymin,ymax,Nx,Ny);
    set_cylindre(cylindre,Nx,Ny,h,r);

    // on ajoute le cylindre dans l'objet branche, qui sera manipulé dans la suite du programme
    add_geometry(cylindre, branche);
    add_geometry(branche, branche_copy);
    build_feuille();
    add_geometry(bush,bush_copy);

    t.set_orientation(dir_cylindre);

    p.phrase() = {new F};

    // iterations sur la phrase
    for(unsigned int i = 0; i < 3; i++)
    {
        p.phrase() = p.iteration();
    }
    std::cout << "Phrase finale :" << p << std::endl;

    cpe::vec3 pos;
    //cpe::vec2 old_rot = {0.0f,0.0f};
    cpe::vec2 old_rot;
    cpe::vec2 new_rot;

    unsigned int ordre = 0;
    float s_param = 1.0f;

    for(unsigned int i = 0; i < p.size_phrase(); i++)
    {
        pos = t.get_pos();
        old_rot = t.get_rot();
        p(i).action(t);
        new_rot = t.get_rot();

        ordre += p(i).get_incr_ordre();
        s_param = 1.0f/(ordre+1);

        std::cout << "Progression : " << ((float)i*100/(float)p.size_phrase()) << "%" << std::endl;
        if(p(i).is_adding_geometry())
        {
            if(p(i).get_char() == 'F')
            {
                branche.transform_apply_scale(s_param,s_param,1.0f);
                std::stack<cpe::vec2> pile_rotation = all_rotation(branche);
                copy_geometry(branche,branche_copy);
                translation(branche_copy, pos, h);
                add_geometry(branche_copy, arbre);
                all_rotation_inverse(branche, pile_rotation);
                branche.transform_apply_scale(1.0f/s_param,1.0f/s_param,1.0f);
            }
            if(p(i).get_char() == 'L')
            {
                bush.transform_apply_rotation({0.0f,0.0f,1.0f},rand()*M_PI/2);
                bush.transform_apply_scale(s_param,s_param,s_param);
                std::stack<cpe::vec2> pile_rotation = all_rotation(bush);
                copy_geometry(bush,bush_copy);
                translation(bush_copy, pos, h);
                add_geometry(bush_copy, arbre);
                all_rotation_inverse(bush, pile_rotation);
                bush.transform_apply_scale(1.0f/s_param,1.0f/s_param,1/s_param);
            }
        }
    }

    ground = create_plan(xmin,xmax,ymin,ymax,Nx,Ny);
    ground.transform_apply_rotation({1.0f,0.0f,0.0f},M_PI/2);
    ground.fill_empty_field_by_default();
    ground_opengl.fill_vbo(ground);
}

void scene::set_cylindre(cpe::mesh& m, int Nu, int Nv, float const h, float const r)
{
    float const u_min = 0.0f;
    float const u_max = 2*M_PI;
    float const v_min = 0.0f;
    float const v_max = h;

    for(int ku = 0; ku < Nu; ku++)
    {
        for(int kv = 0; kv < Nv; kv++)
        {
            float const u_n = static_cast<float>(ku)/(Nu-1);
            float const v_n = static_cast<float>(kv)/(Nv-1);

            float const u = u_min + u_n * (u_max-u_min);
            float const v = v_min + v_n * (v_max-v_min);

            float const x = r*cos(u);
            float const y = r*sin(u);
            float const z = v;

            m.vertex(ku*Nu+kv) = {x,y,z};
        }
    }
    m.fill_empty_field_by_default();
    for(int i = 0; i < m.size_color(); i++)
    {
        m.color(i) = {0.42f,0.23f,0.13f};
    }
}

cpe::mesh scene::create_plan(float xmin, float xmax, float ymin, float ymax, int Nx, int Ny)
{
    cpe::mesh ret;

    const float dx = xmax-xmin;
    const float dy = ymax-ymin;
    const float step_x = dx/(float)(Nx-1);
    const float step_y = dy/(float)(Ny-1);

    // vertex
    for(int kv = 0; kv < Ny; kv++)
    {
        for(int ku = 0; ku < Nx; ku++)
        {
            ret.add_vertex({xmin+ku*step_x, 0., ymin+kv*step_y});
            ret.add_texture_coord({step_x,step_y});
            ret.add_normal({0.,1.0,0.});
        }
    }

    // connectivity
    for(int kv = 0; kv < Ny-1; kv++)
    {
        for(int ku = 0; ku < Nx-1; ku++)
        {
            ret.add_triangle_index({Nx*ku+kv,Nx*(ku+1)+kv+1,Nx*(ku+1)+kv});
            ret.add_triangle_index({Nx*ku+kv,Nx*ku+kv+1,Nx*(ku+1)+kv+1});
        }
    }

    return ret;
}

void scene::load_scene()
{
    load_common_data();


    build_surface();


    arbre.fill_normal();
    arbre.fill_empty_field_by_default();

    final_mesh.fill_vbo(arbre);

}

void scene::draw_scene()
{
    //Setup uniform parameters
    glUseProgram(shader_program_id);                                                                           PRINT_OPENGL_ERROR();

    //Get cameras parameters (modelview,projection,normal).
    camera_matrices const& cam=pwidget->camera();

    //Set Uniform data to GPU
    glUniformMatrix4fv(get_uni_loc(shader_program_id,"camera_modelview"),1,false,cam.modelview.pointer());     PRINT_OPENGL_ERROR();
    glUniformMatrix4fv(get_uni_loc(shader_program_id,"camera_projection"),1,false,cam.projection.pointer());   PRINT_OPENGL_ERROR();
    glUniformMatrix4fv(get_uni_loc(shader_program_id,"normal_matrix"),1,false,cam.normal.pointer());           PRINT_OPENGL_ERROR();


    glBindTexture(GL_TEXTURE_2D,texture_default);  PRINT_OPENGL_ERROR();
    final_mesh.draw();

    glBindTexture(GL_TEXTURE_2D, texture_ground); PRINT_OPENGL_ERROR();
    ground_opengl.draw();
}


scene::scene()
    :shader_program_id(0)
{}


GLuint scene::load_texture_file(std::string const& filename)
{
    return pwidget->load_texture_file(filename);
}

void scene::set_widget(myWidgetGL* widget_param)
{
    pwidget=widget_param;
}


void scene::load_common_data()
{
    texture_default=load_texture_file("data/white.jpg");
    texture_ground=load_texture_file("data/ground.jpg");
    shader_program_id = read_shader("shaders/shader_mesh.vert",
                                    "shaders/shader_mesh.frag"); PRINT_OPENGL_ERROR();
}

