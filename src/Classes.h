#pragma once

#include "entrypoint.h"
#include <raylib.h>

#define Width 1920
#define Height 1080

#define Brick_rows 4
#define Brick_columns 10

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
    
    void Draw() {
        Rectangle rect = {0};
        rect.x = x;
        rect.y = y;
        rect.width = width;
        rect.height = height;
        DrawRectangleRec(rect, color);
    }
};

class Paddle : public GameObject {
    public:

    Paddle() : GameObject(Width/2 - 50, Height - 100, 100, 20, Width/2, GREEN) {}
    //Paddle(float x, float y) : GameObject(x, y, 100, 20, Width/2, GREEN) {}

    void Update(float dt) {
        if (IsKeyDown(KEY_A)) {
            if (x - speed*dt > 0) {
                x -= speed*dt;
            }
        } else if (IsKeyDown(KEY_D)) {
            if ((x + width) + speed*dt < Width) {
                x += speed*dt;
            }
        }
    }
};

class Brick : public GameObject {
    private:
    bool isActive;
    public:
    Brick() : GameObject(0, 0, 0, 0, 0, BLUE) {
        isActive = false;
    }

    Brick(float x, float y, float width, float height, Color color) : GameObject(x, y, width, height, 0, color) {
    isActive = true;
    }

    void Update(float dt) {
        Rectangle rect = {0};
        rect.x = x;
        rect.y = y;
        rect.width = width;
        rect.height = height;
        //CheckCollisionCircleRec()
    }

};

class Ball : public GameObject {
    private:
    float dirX;
    float dirY;
    bool isInPlay;

    public:
    //Pour le constructeur, le width est considéré comme le radius
    Ball() : GameObject(Width/2, Height - 200, 10, 10, 500, GREEN) {
        dirX = 1.0f;
        dirY = 1.0f;
        isInPlay = false;
    };

    void Draw() {
        DrawCircle(x, y, width, YELLOW);
    }

    void Update(float dt) {
        if (!isInPlay & IsKeyPressed(KEY_SPACE)) isInPlay = true;
        if (isInPlay == true) {
            
        }
    }

};