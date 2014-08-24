#include "Precomp.h"

#include "opengl/Texture.h"

#include "GUIEnvironment.h"

#include "GUIImage.h"

gui_image::gui_image(GUIEnvironment* env, Rect2D<int> dimensions, std::shared_ptr<Texture> tex):GUIElement(env,dimensions)
{
    this->Type=GUIET_ELEMENT;
    environment=env;

    absolute_rect=dimensions;
    relative_rect=absolute_rect;

    m_tex=tex;

    //it's an image...
    this->SetListening(false);

    this->SetParent(env);
}

gui_image::~gui_image()
{
}

void gui_image::Render()
{
    environment->draw_gui_quad(absolute_rect,m_tex,true);

    this->RenderChildren();
}
