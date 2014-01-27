#include "precomp.h"
#include "sg_aabb_wireframe_object.h"

#include "scenegraph.h"
#include "sg_mesh_object.h"
#include "opengl/mesh.h"
#include "opengl/buffer_object.h"

namespace sg
{

sg_aabb_wireframe_object::sg_aabb_wireframe_object(sg_mesh_object_ptr mobj)
{
    m_obj = mobj;
    m_mesh = mesh_ptr(new mesh());
    m_mesh->buffers[mesh::POSITION] = new buffer_object<glm::vec3>();
    m_mesh->buffers[mesh::INDICES] = new index_buffer_object<uint32_t>();

    buffer_object<glm::vec3> * bo = static_cast<buffer_object<glm::vec3> *>(m_mesh->buffers[mesh::POSITION]);
    index_buffer_object<uint32_t> * ibo = static_cast<index_buffer_object<uint32_t> *>(m_mesh->buffers[mesh::INDICES]);

    glm::vec3 minp = m_obj->get_aabb().get_min();
    glm::vec3 maxp = m_obj->get_aabb().get_max();

    bo->data.push_back(glm::vec3(minp.x,minp.y,minp.z));
    bo->data.push_back(glm::vec3(maxp.x,minp.y,minp.z));
    bo->data.push_back(glm::vec3(maxp.x,minp.y,maxp.z));
    bo->data.push_back(glm::vec3(minp.x,minp.y,maxp.z));

    bo->data.push_back(glm::vec3(minp.x,maxp.y,minp.z));
    bo->data.push_back(glm::vec3(maxp.x,maxp.y,minp.z));
    bo->data.push_back(glm::vec3(maxp.x,maxp.y,maxp.z));
    bo->data.push_back(glm::vec3(minp.x,maxp.y,maxp.z));

    ibo->data.push_back(0); ibo->data.push_back(1);
    ibo->data.push_back(1); ibo->data.push_back(2);
    ibo->data.push_back(2); ibo->data.push_back(3);
    ibo->data.push_back(3); ibo->data.push_back(0);

    ibo->data.push_back(4); ibo->data.push_back(5);
    ibo->data.push_back(5); ibo->data.push_back(6);
    ibo->data.push_back(6); ibo->data.push_back(7);
    ibo->data.push_back(7); ibo->data.push_back(4);

    ibo->data.push_back(4); ibo->data.push_back(0);
    ibo->data.push_back(5); ibo->data.push_back(1);
    ibo->data.push_back(6); ibo->data.push_back(2);
    ibo->data.push_back(7); ibo->data.push_back(3);

    m_mesh->init();

    m_materials.resize(1);
}

sg_aabb_wireframe_object::~sg_aabb_wireframe_object()
{
    //dtor
}

uint32_t sg_aabb_wireframe_object::get_type()
{
    return SGO_AABB_WIREFRAME_OBJECT;
}

void sg_aabb_wireframe_object::render(scenegraph * sg)
{
    sg->on_set_material(this->get_material(0));
    on_set_shader_constants(this->get_material(0).mat_shader);
    m_mesh->render_lines();
}

void sg_aabb_wireframe_object::on_set_shader_constants(shader_ptr shader)
{
    glm::vec4 col(1,1,1,1);
    glUniform4fv(shader->getparam("color"),1,glm::value_ptr(col));
}

glm::mat4x4 & sg_aabb_wireframe_object::get_transform()
{
    return m_obj->get_transform();
}

sg_material & sg_aabb_wireframe_object::get_material(uint32_t index)
{
    return m_materials[index];
}

uint32_t sg_aabb_wireframe_object::get_material_count()
{
    return m_materials.size();
}

}
