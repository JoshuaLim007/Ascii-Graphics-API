#include "Renderable.h"
#include "Renderer.h"

Renderable::Renderable(Vector2f worldPosition, Quad drawMaterial) : WorldPosition(worldPosition), DrawMaterial(drawMaterial)
{
    Init();
}

Renderable::Renderable(const Renderable &other) : DrawMaterial(other.DrawMaterial), WorldPosition(other.WorldPosition)
{
    Init();
}
Renderable::Renderable()
{
    Init();
}
Renderable &Renderable::operator=(const Renderable &other)
{

    DrawMaterial = other.DrawMaterial;
    WorldPosition = other.WorldPosition;
    return *this;
}
Vector2f Renderable::get_position()
{
    return WorldPosition;
}
void Renderable::set_position(const Vector2f &pos)
{
    WorldPosition = pos;
}
Quad Renderable::get_material()
{
    return DrawMaterial;
}
void Renderable::set_material(Quad mat)
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
    Renderer::get_instance()->add_rendereable_to_render_stack(this);
}