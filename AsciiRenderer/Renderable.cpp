#include "Renderable.h"
#include "Renderer.h"

Renderable::Renderable(Vector2f worldPosition, Sprite drawMaterial) : WorldPosition(worldPosition), Sprites(drawMaterial)
{
    Init();
}
Renderable::Renderable()
{
    Init();
}
Renderable::~Renderable()
{
    Dump();
}

Sprite Renderable::get_material() const
{
    return Sprites;
}
void Renderable::set_material(Sprite mat)
{
    Sprites = mat;
}
void Renderable::set_draw_order(unsigned int value)
{
    DrawOrder = value;
}
unsigned int Renderable::get_draw_order() const
{
    return DrawOrder;
}
void Renderable::Init()
{
    Renderer::get_instance()->add_renderable_to_render_stack(this);
}
void Renderable::Dump() {
    Renderer::get_instance()->remove_renderable_to_render_stack(this);
}
Vector2f Renderable::get_screen_position() {
    auto renderer = Renderer::get_instance();
    auto camPos = renderer->get_camera_position();
    auto worldCamPos = camPos - WorldPosition;

    Vector2f wp(WorldPosition.x, -WorldPosition.y);
    Vector2f cp(camPos.x, -camPos.y);

    auto position = wp - cp + Vector2f(renderer->get_screen_width() * 0.5, renderer->get_screen_height() * 0.5);
    return position;
}