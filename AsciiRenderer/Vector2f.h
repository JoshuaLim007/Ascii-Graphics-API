#pragma once

#ifndef VECTOR2F_H_
#define VECTOR2F_H_

struct Vector2f
{
    float x, y;
    Vector2f();
    Vector2f(const Vector2f &);
    Vector2f(float, float);
    Vector2f operator+(const Vector2f& o) const{
        return Vector2f(x + o.x, y + o.y);
    }
    Vector2f operator-(const Vector2f& o) const{
        return Vector2f(x - o.x, y - o.y);
    }
    Vector2f operator*(const double& rhs) const {
        return Vector2f(x * rhs, y * rhs);
    }
    Vector2f operator-() {
        this->x *= -1;
        this->y *= -1;
        return *this;
    }
    void operator+=(const Vector2f& rhs) {
        this->x += rhs.x;
        this->y += rhs.y;
    }
    void operator-=(const Vector2f& rhs) {
        this->x -= rhs.x;
        this->y -= rhs.y;
    }
    

    static float dot(const Vector2f& lhs, const Vector2f& rhs);
    static Vector2f reflect(const Vector2f&, const Vector2f&);
    static Vector2f lerp(const Vector2f &, const Vector2f &, float);
    static float magnitude(const Vector2f &);
    static Vector2f normalize(const Vector2f &);

    const static Vector2f ZERO;
    const static Vector2f IDENTITY;
    const static Vector2f RIGHT;
    const static Vector2f LEFT;
    const static Vector2f UP;
    const static Vector2f DOWN;
};

#endif