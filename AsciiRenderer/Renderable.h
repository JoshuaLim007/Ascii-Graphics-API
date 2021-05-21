#pragma once
#ifndef RENDERERABLE_H_
#define RENDERERABLE_H_

#include "Sprite.h"
#include <vector>
#include "InputManager.h"

class Renderable
{
private:
    void Init();
    void Dump();
    unsigned int DrawOrder = 0;
    Sprite DrawMaterial;


protected:
    Renderable(Vector2f, Sprite);
    Renderable();
    ~Renderable();

public:
    Vector2f Scale = Vector2f::IDENTITY;
    Vector2f WorldPosition = Vector2f::ZERO;

    Sprite get_material() const;
    void set_material(Sprite);
    void set_draw_order(unsigned int) ;
    unsigned int get_draw_order() const;
    //Vector2f get_position();
    //void set_position(const Vector2f &);
    virtual void on_preRender(double) = 0;
};

#endif