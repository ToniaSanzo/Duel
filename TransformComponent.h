#pragma once
#include "Components.h"
#include "..\Vector2D.h"

class TransformComponent : public Component {
public:
    Vector2D position;
    Vector2D velocity;

    int height = 32;
    int width = 32;
    int scale = 1;

    int score = 0;

    int speed = 3;

    // Default constructor sets the position to (0,0)
    TransformComponent() {
        position.x = position.y = 0.f;
    }

    // Constructor for scale
    TransformComponent(int sc) {
        position.x = 0.f;
        position.y = 0.f;
        scale = sc;
    }

    // Construct the transform component at a given position
    TransformComponent(float x, float y) {
        position.x = x;
        position.y = y;
    }

    // Construct the transform component with 
    // position and dimmension
    TransformComponent(float x, float y, int h, int w, int sc) {
        position.x = x;
        position.y = y;
        height = h;
        width = w;
        scale = sc;
    }

    // Use the init function to confirm that the velocity starts at 0
    void init() override {
        velocity.x = 0;
        velocity.y = 0;
    }

    // How the position component gets updated
    void update() override {
        position.x += velocity.x * speed;
        position.y += velocity.y * speed;
    }

    void setPos(float x, float y) {
        position.x = x;
        position.y = y;
    }
};