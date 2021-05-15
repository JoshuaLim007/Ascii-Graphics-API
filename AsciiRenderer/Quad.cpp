#include "Quad.h"
#include <math.h>

Quad::Quad()
{
}
Quad::Quad(Vector2f LocalSpacePosition,
           Vector2f HalfExtents,
           Vector2f Scale,
           char FillStyle,
           int OutlineSize,
           char BorderStyle)
{
    this->LocalSpacePosition = LocalSpacePosition;
    this->HalfExtents = HalfExtents;
    this->FillStyle = FillStyle;
    this->Scale = Scale;
    this->BorderStyle = BorderStyle;
    this->OutlineSize = OutlineSize;
}
