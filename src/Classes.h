#pragma once

#include "entrypoint.h"
#include <raylib.h>

#define Width 1920
#define Height 1080

class GameObject {
    protected:
    float x;
    float y;
    float width;
    float height;
    float speed;
    Color color;
    public:

    GameObject() {
        x = 0;
        y = 0;
        width = 0;
        height = 0;
        speed = 0;
        color = WHITE;
    }
    
    GameObject(float new_x, float new_y, float new_width, float new_height, float new_speed, Color new_color) {
        x = new_x;
        y = new_y;
        width = new_width;
        height = new_height;
        speed = new_speed;
        color = new_color;
    }


    void Update(float dt);
    void Draw();
};

class Paddle : public GameObject {
    public:

    Paddle() : GameObject(Width/2, Height - 100, 100, 20, 5, GREEN) {}

    // Constructeur personnalisé
    Paddle(float x, float y) : GameObject(x, y, 100, 20, 5, GREEN) {}

    void Update(float dt) {
        if (IsKeyDown(KEY_A)) {
            if (x - speed > 0) {
                x -= speed;
            }
        } else if (IsKeyDown(KEY_D)) {
            if ((x + width) + speed < Width) {
                x += speed;
            }
        }
        Draw();
    }
    void Draw() {
        Rectangle rect = {0};
        rect.x = x;
        rect.y = y;
        rect.width = width;
        rect.height = height;

        DrawRectangleRec(rect, color);
    }
};

class Brick : public GameObject {

};

class Ball : public GameObject {

};