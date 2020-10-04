#include "Vector2D.h"

// Default constructor
Vector2D::Vector2D()
{
    x = 0.f;
    y = 0.f;
}

// Vector2D constructor
Vector2D::Vector2D(float x, float y)
{
    this->x = x;
    this->y = y;
}

// Function to add 2 vectors
Vector2D &Vector2D::add(const Vector2D &vec)
{
    this->x += vec.x;
    this->y += vec.y;
    return *this;
}

// Function to subtract 2 vectors
Vector2D &Vector2D::subtract(const Vector2D &vec)
{
    this->x -= vec.x;
    this->y -= vec.y;
    return *this;
}

// Function to mutiply 2 vectors
Vector2D &Vector2D::mutiply(const Vector2D &vec)
{
    this->x *= vec.x;
    this->y *= vec.y;
    return *this;
}

// Function to divide 2 vectors
Vector2D &Vector2D::divide(const Vector2D &vec)
{
    this->x /= vec.x;
    this->y /= vec.y;
    return *this;
}

// Operator overload +
Vector2D &operator+(Vector2D &v1, const Vector2D &v2)
{
    return v1.add(v2);
}

// Operator overload -
Vector2D &operator-(Vector2D &v1, const Vector2D &v2)
{
    return v1.subtract(v2);
}

// Operator overload *
Vector2D &operator*(Vector2D &v1, const Vector2D &v2)
{
    return v1.mutiply(v2);
}

// Operator overload /
Vector2D &operator/(Vector2D &v1, const Vector2D &v2)
{
    return v1.divide(v2);
}

// Operator overload << (output stream)
std::ostream &operator<<(std::ostream &stream, const Vector2D &vec)
{
    stream << "(" << vec.x << ", " << vec.y << ")";
    return stream;
}

// Operator overload +=
Vector2D &Vector2D::operator+=(const Vector2D &vec)
{
    return this->add(vec);
}

// Operator overload -=
Vector2D &Vector2D::operator-=(const Vector2D &vec)
{
    return this->subtract(vec);
}

// Operator overload *=
Vector2D &Vector2D::operator*=(const Vector2D &vec)
{
    return this->mutiply(vec);
}

// Operator overload /=
Vector2D &Vector2D::operator/=(const Vector2D &vec)
{
    return this->divide(vec);
}