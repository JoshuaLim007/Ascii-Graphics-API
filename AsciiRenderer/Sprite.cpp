#include "Sprite.h"
#include <math.h>

Sprite::Sprite()
{
}
Sprite::Sprite(Vector2f LocalSpacePosition, Vector2f Scale, std::istream sprite_file)
{
    this->LocalSpacePosition = LocalSpacePosition;
    this->Scale = Scale;
}
