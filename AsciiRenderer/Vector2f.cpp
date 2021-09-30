#include "Vector2f.h"
#include <math.h>

const Vector2f Vector2f::ZERO = Vector2f(0, 0);
const Vector2f Vector2f::IDENTITY = Vector2f(1, 1);
const Vector2f Vector2f::RIGHT = Vector2f(1, 0);
const Vector2f Vector2f::LEFT = Vector2f(-1, 0);
const Vector2f Vector2f::UP = Vector2f(0, 1);
const Vector2f Vector2f::DOWN = Vector2f(0, -1);

Vector2f::Vector2f()
{
    x = 0;
    y = 0;
}
Vector2f::Vector2f(const Vector2f &other)
{
    x = other.x;
    y = other.y;
}
Vector2f::Vector2f(float x, float y)
{
    this->x = x;
    this->y = y;
}
Vector2f Vector2f::lerp(const Vector2f &initial, const Vector2f &target, float time)
{
    if (time > 1)
    {
        time = 1;
    }
    else if (time < 0)
    {
        time = 0;
    }
    float x = target.x * time - initial.x * (1 - time);
    float y = target.y * time - initial.y * (1 - time);

    return Vector2f(x, y);
}
float Vector2f::magnitude(const Vector2f &value)
{
    return sqrtf(powf(value.x, 2) + powf(value.y, 2));
}
Vector2f Vector2f::normalize(const Vector2f &value)
{
    float mag = magnitude(value);
    return Vector2f(value.x / mag, value.y / mag);
}
float Vector2f::dot(const Vector2f& lhs, const Vector2f& rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y;
}
Vector2f Vector2f::reflect(const Vector2f& o, const Vector2f& normal) {
    return o - normal * 2 * dot(o, normal);
}