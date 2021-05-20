#include "Renderable.h"
#include "Renderer.h"

Renderable::Renderable(Vector2f worldPosition, Sprite drawMaterial) : WorldPosition(worldPosition), DrawMaterial(drawMaterial)
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
Vector2f Renderable::get_position()
{
    return WorldPosition;
}
void Renderable::set_position(const Vector2f &pos)
{
    WorldPosition = pos;
}
Sprite Renderable::get_material()
{
    return DrawMaterial;
}
void Renderable::set_material(Sprite mat)
{
    DrawMaterial = mat;
}
void Renderable::set_draw_order(unsigned int value)
{
    DrawOrder = value;
}
unsigned int Renderable::get_draw_order()
{
    return DrawOrder;
}
void Renderable::Init()
{
    this->m_itrRef = Renderer::get_instance()->add_renderable_to_render_stack(this);
}
void Renderable::Dump() {
    Renderer::get_instance()->remove_renderable_to_render_stack(this->m_itrRef);
}