#pragma once

#include "entrypoint.h"
#include <raylib.h>
#include <math.h>

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

    float GetX() { return x; }
    float GetY() { return y; }
    float GetWidth() { return width; }
    float GetHeight() { return height; }

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

    bool CheckIfActive() {
        if (isActive) {
            return true;
        } else {
            return false;
        }
    }

    void Deactivate() {
        isActive = false;
    }

};

class Ball : public GameObject {
    private:
    float dirX;
    float dirY;
    bool isInPlay;

    public:
    //Pour le constructeur, le width est considéré comme le radius
    Ball() : GameObject(Width/2, Height - 200, 50, 50, 500, GREEN) {
        dirX = -1.0f;
        dirY = -1.0f;
        isInPlay = false;
    };

    void Draw() {
        DrawCircle(x, y, width, YELLOW);
    }

    void WaitForStart() {
        if (!isInPlay & IsKeyPressed(KEY_SPACE)) {isInPlay = true;} else if (!isInPlay) {DrawText("PRESS SPACE TO START", Width/2 - 300, Height/2, 50, BLUE);}
    }

    void Update(float dt, Brick bricks[Brick_rows][Brick_columns], Paddle paddle) {

        if (x + width > Width) {x = Width - width; dirX *= -1;}
        if (x - width < 0) {x = 0 + width; dirX *= -1;}
        if (y - height < 0) {y = 0 + height; dirY *= -1;}

        if (isInPlay == true) {

            Vector2 ballCenter = {x, y};

            for (int row = 0; row < Brick_rows; row++) {
                for (int col = 0; col < Brick_columns; col++) {
                    if (!bricks[row][col].CheckIfActive()) continue;
                    Rectangle brickRect = {
                        bricks[row][col].GetX(),
                        bricks[row][col].GetY(),
                        bricks[row][col].GetWidth(),
                        bricks[row][col].GetHeight()
                    };

                    if (CheckCollisionCircleRec(ballCenter, width, brickRect)) {
                        float brickCenterX = bricks[row][col].GetX() + bricks[row][col].GetWidth() / 2;
                        float brickCenterY = bricks[row][col].GetY() + bricks[row][col].GetHeight() / 2;
                        
                        float dx = ballCenter.x - brickCenterX;
                        float dy = ballCenter.y - brickCenterY;
                        
                        //J'ai fait mes recherches sur cette formule
                        if (abs(dx) > abs(dy)) {
                            dirX *= -1;
                        } else {
                            dirY *= -1;
                        }
                        
                        bricks[row][col].Deactivate();
                    }
                }
            }

            Rectangle PaddleRect = {
                paddle.GetX(),
                paddle.GetY(),
                paddle.GetWidth(),
                paddle.GetHeight()
            };

            if (CheckCollisionCircleRec(ballCenter, width, PaddleRect)) dirY = -1;

            x += dirX * speed * dt;
            y += dirY * speed * dt;
        }
    }

};