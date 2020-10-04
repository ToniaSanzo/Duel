#pragma once

struct Animation
{
    int index;
    int frames;
    int speed;

    // Default constructor we do not use
    Animation() { index = 0; frames = 0; speed = 0; }

    // Constructor sets the index, frames, and speed
    Animation(int i, int f, int s) {
        index = i;
        frames = f;
        speed = s;
    }


};