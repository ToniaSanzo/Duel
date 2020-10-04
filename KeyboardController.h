#pragma once
#include "../Game.h"
#include "ECS.h"
#include "Components.h"

class KeyboardController : public Component {
public:
    TransformComponent *transform;
    SpriteComponent *sprite;
    bool attacking = false;
    bool dead = false;

    void init() override {
        transform = &entity->getComponent<TransformComponent>();
        sprite = &entity->getComponent<SpriteComponent>();
    }

    void update() override {

        // What we do when a key is pressed
        if (Game::event.type == SDL_KEYDOWN) {
            if (sprite->texID == "warrior") {
                switch (Game::event.key.keysym.sym) {
                case SDLK_w:
                    transform->velocity.y = -1;
                    sprite->play("walk");
                    dead = false;
                    break;
                case SDLK_a:
                    transform->velocity.x = -1;
                    sprite->play("walk");
                    dead = false;
                    sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
                    break;
                case SDLK_d:
                    transform->velocity.x = 1;
                    sprite->play("walk");
                    dead = false;
                    sprite->spriteFlip = SDL_FLIP_NONE;
                    break;
                case SDLK_s:
                    transform->velocity.y = 1;
                    sprite->play("walk");
                    dead = false;
                    break;
                case SDLK_SPACE:
                    sprite->play("attack");
                    dead = false;
                    attacking = true;
                    break;
                default:
                    break;
                }
            }

            if (sprite->texID == "ranger") {
                switch (Game::event.key.keysym.sym) {
                case SDLK_UP:
                    transform->velocity.y = -1;
                    sprite->play("walk");
                    dead = false;
                    break;
                case SDLK_LEFT:
                    transform->velocity.x = -1;
                    sprite->play("walk");
                    dead = false;
                    sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
                    break;
                case SDLK_RIGHT:
                    transform->velocity.x = 1;
                    sprite->play("walk");
                    dead = false;
                    sprite->spriteFlip = SDL_FLIP_NONE;
                    break;
                case SDLK_DOWN:
                    transform->velocity.y = 1;
                    sprite->play("walk");
                    dead = false;
                    break;
                case SDLK_RSHIFT:
                    sprite->play("attack");
                    dead = false;
                    attacking = true;
                    break;
                default:
                    break;
                }
            }

            if (sprite->texID == "wizard") {
                switch (Game::event.key.keysym.sym) {
                case SDLK_i:
                    transform->velocity.y = -1;
                    sprite->play("walk");
                    dead = false;
                    break;
                case SDLK_j:
                    transform->velocity.x = -1;
                    sprite->play("walk");
                    dead = false;
                    sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
                    break;
                case SDLK_l:
                    transform->velocity.x = 1;
                    sprite->play("walk");
                    dead = false;
                    sprite->spriteFlip = SDL_FLIP_NONE;
                    break;
                case SDLK_k:
                    transform->velocity.y = 1;
                    sprite->play("walk");
                    dead = false;
                    break;
                case SDLK_b:
                    sprite->play("attack");
                    attacking = true;
                    dead = false;
                    break;
                default:
                    break;
                }
            }
        }

        // What we do when a key is released
        if (Game::event.type == SDL_KEYUP) {
            if (sprite->texID == "warrior") {
                switch (Game::event.key.keysym.sym) {
                case SDLK_w:
                    transform->velocity.y = 0;
                    sprite->play("idle");
                    break;
                case SDLK_a:
                    transform->velocity.x = 0;
                    sprite->play("idle");
                    break;
                case SDLK_d:
                    transform->velocity.x = 0;
                    sprite->play("idle");
                    break;
                case SDLK_s:
                    transform->velocity.y = 0;
                    sprite->play("idle");
                    break;
                case SDLK_SPACE:
                    sprite->play("idle");
                    attacking = false;
                    break;
                default:
                    break;
                }
            }

            if (sprite->texID == "ranger") {
                switch (Game::event.key.keysym.sym) {
                case SDLK_UP:
                    transform->velocity.y = 0;
                    sprite->play("idle");
                    break;
                case SDLK_LEFT:
                    transform->velocity.x = 0;
                    sprite->play("idle");
                    break;
                case SDLK_RIGHT:
                    transform->velocity.x = 0;
                    sprite->play("idle");
                    break;
                case SDLK_DOWN:
                    transform->velocity.y = 0;
                    sprite->play("idle");
                    break;
                case SDLK_RSHIFT:
                    sprite->play("idle");
                    attacking = false;
                    break;
                default:
                    break;
                }
            }


            if (sprite->texID == "wizard") {
                switch (Game::event.key.keysym.sym) {
                case SDLK_i:
                    transform->velocity.y = 0;
                    sprite->play("idle");
                    break;
                case SDLK_j:
                    transform->velocity.x = 0;
                    sprite->play("idle");
                    break;
                case SDLK_l:
                    transform->velocity.x = 0;
                    sprite->play("idle");
                    break;
                case SDLK_k:
                    transform->velocity.y = 0;
                    sprite->play("idle");
                    break;
                case SDLK_b:
                    sprite->play("idle");
                    attacking = false;
                    break;
                default:
                    break;
                }
            }
        }
    }
};