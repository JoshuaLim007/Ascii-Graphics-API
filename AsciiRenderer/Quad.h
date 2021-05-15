#pragma once
#ifndef QUAD_H_
#define QUAD_H_

#include "Vector2f.h"

struct Quad
{
public:
    Vector2f LocalSpacePosition = Vector2f::ZERO;
    Vector2f Scale = Vector2f::IDENTITY;
    Vector2f HalfExtents = Vector2f::IDENTITY;

    int OutlineSize = 0;
    char BorderStyle = '#';
    char FillStyle = '*';
    char BaseColor;
    char OutlineColor;

    Quad();

    /*
        Vector2f LocalSpacePosition,
        Vector2f HalfExtents,
        Vector2f Scale,
        char FillStyle,
        int OutlineSize,
        char BorderStyle)
    */
    Quad(Vector2f, Vector2f, Vector2f, char, int, char);
};

#endif