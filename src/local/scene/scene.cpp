

#include <GL/glew.h>

#include "scene.hpp"

#include "../../lib/opengl/glutils.hpp"

#include "../../lib/perlin/perlin.hpp"
#include "../../lib/interface/camera_matrices.hpp"

#include "../interface/myWidgetGL.hpp"

#include <cmath>

#include <string>
#include <sstream>
#include "../../lib/mesh/mesh_io.hpp"

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
//        std::cout << "u0=" << u0 << ", u1=" << u1 << ", u2=" << u2 << std::endl;
        triangle_index connec = {u0,u1,u2};
        g2.add_triangle_index(connec);
    }
    g2.fill_empty_field_by_default();
}

void scene::transform_branche(cpe::vec3 old_pos, cpe::vec3 new_pos, cpe::vec2 old_rot, cpe::vec2 new_rot)
{
    cpe::vec3 translation = new_pos - old_pos;
    cpe::vec2 rotation = new_rot - old_rot;

    branche.transform_apply_translation(translation);
    branche.transform_apply_rotation({1.0f,0.0f,0.0f},rotation.x());
    branche.transform_apply_rotation({0.0f,1.0f,0.0f},rotation.y());
    std::cout << translation << std::endl;
}

void scene::build_surface()
{
    int Nx = 200;
    int Ny = 200;
    float xmin = -1.0f;
    float xmax = 1.0f;
    float ymin = -1.0f;
    float ymax = 1.0f;

    cylindre = create_plan(xmin,xmax,ymin,ymax,Nx,Ny);
    set_cylindre(cylindre,Nx,Ny);

    // on ajoute le cylindre dans l'objet branche, qui sera manipulé dans la suite du programme
    add_geometry(cylindre, branche);

    // iterations sur la phrase
    for(unsigned int i = 0; i < 2; i++)
    {
        p.phrase() = p.iteration();
    }
    std::cout << p << std::endl;

    cpe::vec3 new_pos;
    cpe::vec3 old_pos;
    cpe::vec3 translation;
    cpe::vec2 old_rot;
    cpe::vec2 new_rot;

    for(unsigned int i = 0; i < p.size_phrase(); i++)
    {
        old_pos = t.get_pos();
        old_rot = t.get_rot();
        p(i).action(t);
        new_pos = t.get_pos();
        new_rot = t.get_rot();
        transform_branche(old_pos,new_pos, old_rot, new_rot);


        if(p(i).is_adding_geometry())
            add_geometry(branche, arbre);
    }
}

void scene::set_cylindre(cpe::mesh& m, int Nu, int Nv)
{
    float const u_min = 0.0f;
    float const u_max = 2*M_PI;
    float const v_min = 0.0f;
    float const v_max = 1.0f;

    float const r = 0.1f;

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
//    surface_opengl.draw();
    final_mesh.draw();


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
    shader_program_id = read_shader("shaders/shader_mesh.vert",
                                    "shaders/shader_mesh.frag"); PRINT_OPENGL_ERROR();
}

