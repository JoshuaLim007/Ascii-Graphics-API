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