#pragma once
#include "Components.h"
#include "SDL.h"
#include "../TextureManager.h"
#include "Animation.h"
#include <map>
#include "../AssetManager.h"

class SpriteComponent : public Component {
private:
    TransformComponent *transform;
    SDL_Texture *texture;
    SDL_Rect srcRect, destRect;

    // True this is animated, false not animated
    bool animated = false;

    // Frames in the animation
    int frames = 0;

    // Speed is the delay in between frames in milliseconds
    int speed = 100;

public:
    // Identifies the sprite
    std::string texID;

    // The index needs to be at 0, because If we don't 
    // animate this is where we will start
    int animIndex = 0;

    // We have a map of all the animations mapped to there
    // name
    std::map<const char *, Animation> animations;

    SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

    SpriteComponent() = default;
    
    // Constructor with the path to the tecture to be used
    SpriteComponent(const char *path) {
        setTex(path);
    }

    // Constructor with the path to the texture to be used,
    // and whether the sprite is animated
    SpriteComponent(std::string tID, bool isAnimated) {
        texID = tID;
        animated = isAnimated;

        // Animation
        Animation idle = Animation(0, 3, 200);
        Animation walk = Animation(1, 2, 200);
        Animation attack = Animation(2, 3, 100);
        Animation death = Animation(3, 5, 100);

        animations.emplace("idle", idle);
        animations.emplace("walk", walk);
        animations.emplace("attack", attack);
        animations.emplace("death", death);

        play("idle");
        setTex(tID);
    }

    // SpriteComponent destructor, destroys the texture
    ~SpriteComponent() {}

    // Change the texture
    void setTex(std::string tID) {
        texture = Game::assets->getTexture(tID);
    }

    // Initialize the position component, srcRect and destRect
    void init() override {
        transform = &entity->getComponent<TransformComponent>();

        srcRect.x = srcRect.y = 0;
        srcRect.w = transform->width;
        srcRect.h = transform->height;
        
    }

    // Update where to draw the components based on the position 
    // component
    void update() override {

        if (animated) {
            // The srcRect moves between the different frames
            // based on the time
            srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);

        }

        srcRect.y = animIndex * transform->height;

        // Casted these from floats to ints, because the
        // rectangle is expecting ints
        destRect.x = (int)transform->position.x;
        destRect.y = (int)transform->position.y;
        destRect.w = transform->width * transform->scale;
        destRect.h = transform->height * transform->scale;
    }

    void draw() override {
        TextureManager::Draw(texture, srcRect, destRect, spriteFlip);
    }

    // Used to update the frames and index for playing the
    // specific animation
    void play(const char *animName) {
        frames = animations[animName].frames;
        speed = animations[animName].speed;
        animIndex = animations[animName].index;
    }
};