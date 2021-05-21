#pragma once
#ifndef QUAD_H_
#define QUAD_H_

#include "Vector2f.h"
#include <vector>
#include <istream>
#include <fstream>

struct color {
    float r;
    float g;
    float b;
};
class Sprite
{
private:
    color* texture = NULL;
    unsigned int m_width = 0, m_height = 0;
public:

    Vector2f LocalSpacePosition = Vector2f::ZERO;
    Vector2f AABB = Vector2f::ZERO;

    bool set_texture(char*);
    void flush_texture();
    color* get_texture() const;
    unsigned int width() const;
    unsigned int height() const;
};

#endif