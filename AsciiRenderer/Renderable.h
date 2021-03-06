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
    Sprite Sprites;


protected:
    Renderable(Vector2f, Sprite);
    Renderable();
    ~Renderable();

public:
    Vector2f Scale = Vector2f::IDENTITY;
    Vector2f WorldPosition = Vector2f::ZERO;

    Sprite get_material() const;
    void set_material(Sprite);

    Vector2f get_screen_position();


    void set_draw_order(unsigned int) ;
    unsigned int get_draw_order() const;
    virtual void on_preRender(double) = 0;
};

#endif