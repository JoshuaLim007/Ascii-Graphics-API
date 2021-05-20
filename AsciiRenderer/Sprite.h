#pragma once
#ifndef QUAD_H_
#define QUAD_H_

#include "Vector2f.h"
#include <vector>
#include <istream>

struct Sprite
{
public:
    Vector2f LocalSpacePosition = Vector2f::ZERO;
    Vector2f AABB = Vector2f::ZERO;
    Vector2f Scale = Vector2f::IDENTITY;
    std::vector<char> sprite_array;

    Sprite();
    Sprite(Vector2f, Vector2f, std::istream);
};

#endif