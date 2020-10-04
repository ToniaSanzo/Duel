#pragma once
#include <string>
#include "../Game.h"
#include "SDL.h"
#include "Components.h"
#include "../TextureManager.h"

class ColliderComponent : public Component
{
public:
    // An area that is collidable
    SDL_Rect collider;

    // The tag allows us to find out what collided with what
    std::string tag;

    SDL_Texture *tex;
    SDL_Rect srcR, destR;

    TransformComponent *transform;

    // Constructor for the collider component
    ColliderComponent(std::string t) {
        tag = t;
    }

    // Constructor for the collider component
    ColliderComponent(std::string t, int xpos, int ypos, int size) {
        tag = t;
        collider.x = xpos;
        collider.y = ypos;
        collider.h = collider.w = size;
    }

    void init() override {
        // If this entity does not have the transform component, add
        // it
        if (!entity->hasComponent<TransformComponent>()) {
            entity->addComponent<TransformComponent>();
        }
        // Set the transform component
        transform = &entity->getComponent<TransformComponent>();
        collider.w = transform->width;
        collider.h = transform->height;
        
        
        //// Load the collider texture
        //tex = TextureManager::LoadTexture("Assets/coltex.png");
        //srcR = { 0, 0, 32, 32 };
        //destR = { collider.x, collider.y, collider.w, collider.h };
    }
    

    void update() override
    {
        collider.x = static_cast<int>(transform->position.x);
        collider.y = static_cast<int>(transform->position.y);
    }

    void draw() override
    {
        //TextureManager::Draw(tex, srcR, destR, SDL_FLIP_NONE);
    }

};