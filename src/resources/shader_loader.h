#ifndef SHADER_LOADER_H
#define SHADER_LOADER_H

#include "opengl/shader.h"
#include "resource_cache.h"

class logger;
class shader_loader: public resource_cache<shader>
{
    public:
        shader_loader(logger * l);
        virtual ~shader_loader();

        shader_ptr load(const std::string & file);
        shader_ptr get_shader_by_name(const std::string & name);
    protected:
        logger * m_logger;
};

#endif // SHADER_LOADER_H