#pragma once
#ifndef RENDERERABLE_H_
#define RENDERERABLE_H_

#include "Quad.h"

class Renderable
{
private:
    void Init();
    unsigned int DrawOrder = 0;
    Quad DrawMaterial;
    Vector2f WorldPosition = Vector2f::ZERO;

protected:
    Renderable(Vector2f, Quad);
    Renderable();
    Renderable(const Renderable &);
    Renderable &operator=(const Renderable &);

public:
    Quad get_material();
    void set_material(Quad);
    void set_draw_order(unsigned int);
    unsigned int get_draw_order();
    Vector2f get_position();
    void set_position(const Vector2f &);
    virtual void on_draw() = 0;
};

#endif