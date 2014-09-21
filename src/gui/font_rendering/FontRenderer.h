#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H

class GUIEnvironment;
class Shader;
struct font;

typedef vector<font*> font_vector;
typedef font_vector::iterator fvi; //font_vector_iterator

struct SubStrInfo
{
    std::wstring text;
    glm::vec4 col;
    bool bold;
};

class font_renderer
{
private:
    FT_Library ft;
    FT_Face ff;

    GUIEnvironment* m_env;

    font* default_font;
    font* current_font;

    font_vector fonts;

    Shader* font_shader;

    void set_font_color(glm::vec4 color);

    GLuint vao;
    GLuint vbo;
public:
    font_renderer(GUIEnvironment* env);

    ~font_renderer();

    font* create_font(std::string name, std::string filename, int32_t size=12);

    bool remove_font(std::string font_to_remove);

    void use_font(std::string font_name="default");

    font* get_font(std::string name);

    font* get_default_font();

    void set_default_font(font* new_font);

    void render_string(std::string font_name, std::wstring text, glm::vec2 pos, glm::vec4 color=glm::vec4(1,1,1,1));

    void render_string(std::wstring text, glm::vec2 pos,glm::vec4 color,bool drawshadow);

    void render_string(std::wstring text, glm::vec2 pos,bool drawshadow);

    void render_string_formatted(std::wstring text, glm::vec2 pos,float linewidth,bool drawshadow);

    glm::vec2 get_text_dimensions(const std::wstring & text,const std::string &font_name="default");
};
