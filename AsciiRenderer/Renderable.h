#pragma once
#ifndef RENDERERABLE_H_
#define RENDERERABLE_H_

#include "Sprite.h"
#include <vector>

class Renderable
{
private:
    void Init();
    void Dump();
    unsigned int DrawOrder = 0;
    std::vector<Renderable*>::iterator m_itrRef;
    Sprite DrawMaterial;
    Vector2f WorldPosition = Vector2f::ZERO;

protected:
    Renderable(Vector2f, Sprite);
    Renderable();
    ~Renderable();

public:
    Sprite get_material();
    void set_material(Sprite);
    void set_draw_order(unsigned int);
    unsigned int get_draw_order();
    Vector2f get_position();
    void set_position(const Vector2f &);
    virtual void on_draw() {};
};

#endif