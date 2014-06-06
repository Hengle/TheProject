#ifndef SG_DEFAULT_RENDER_QUEUE_H
#define SG_DEFAULT_RENDER_QUEUE_H

#include "isg_render_queue.h"

namespace sg
{
class sg_light_object; typedef std::shared_ptr<sg_light_object> sg_light_object_ptr;
class sg_skybox_object;
class scenegraph;
class sg_default_render_queue: public isg_render_queue
{
    public:
        sg_default_render_queue(scenegraph * sg);
        virtual ~sg_default_render_queue();

        virtual void add_object(isg_object *  obj);
        virtual void clear();

        inline void pre_render();
        virtual void set_material(isg_object * obj, sg_material_ptr material);
        virtual void render_all();
        inline void post_render();

    protected:
        scenegraph * m_scenegraph;
        std::vector<isg_object * > m_objects;
        std::vector<sg_light_object*> m_lights;
        sg_skybox_object * m_skybox;

        sg_material_ptr m_current_material;
};

}

#endif // SG_DEFAULT_RENDER_QUEUE_H