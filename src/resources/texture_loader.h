#ifndef TEXTURE_LOADER_H
#define TEXTURE_LOADER_H

#include "itexture_loader.h"

class texture_loader
{
protected:
    std::vector<itexture_loader*> m_loaders;
public:
    texture_loader();
    virtual ~texture_loader();

    virtual void add_loader(itexture_loader * loader);
    virtual texture * load(const std::string & file);
};

#endif // TEXTURE_LOADER_H