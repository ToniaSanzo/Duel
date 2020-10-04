#pragma once
#include <iostream>

class Vector2D
{
public:
    // Vectors x coordinate
    float x;
    // Vectors y coordinate
    float y;

    // Default constructor
    Vector2D();
    // Vector2D constructor
    Vector2D(float x, float y);

    // Function to add 2 vectors
    Vector2D &add(const Vector2D &vec);
    // Function to subtract 2 vectors
    Vector2D &subtract(const Vector2D &vec);
    // Function to mutiply 2 vectors
    Vector2D &mutiply(const Vector2D &vec);
    // Function to divide 2 vectors
    Vector2D &divide(const Vector2D &vec);

    // Operator overload +
    friend Vector2D &operator+(Vector2D &v1, const Vector2D &v2);
    // Operator overload -
    friend Vector2D &operator-(Vector2D &v1, const Vector2D &v2);
    // Operator overload *
    friend Vector2D &operator*(Vector2D &v1, const Vector2D &v2);
    // Operator overload /
    friend Vector2D &operator/(Vector2D &v1, const Vector2D &v2);

    // Operator overload +=
    Vector2D &operator+=(const Vector2D &vec);
    // Operator overload -=
    Vector2D &operator-=(const Vector2D &vec);
    // Operator overload *=
    Vector2D &operator*=(const Vector2D &vec);
    // Operator overload /=
    Vector2D &operator/=(const Vector2D &vec);

    // Operator overload << (output stream)
    friend std::ostream &operator<<(std::ostream &stream, const Vector2D &vec);
};