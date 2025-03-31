#include "entrypoint.h"
#include <raylib.h>
#include "Classes.h"

//Creer votre class Engin ici et appeler une fonction start que vous définisser à la classe dans la fonction raylib_start plus bas.
void raylib_start(void){

    InitWindow(Width, Height, "Breakout");

    Paddle paddle = Paddle();
    Ball ball = Ball();
    Brick bricks[Brick_rows][Brick_columns];

    for (int row = 0; row < Brick_rows; row++) {
        for (int col = 0; col < Brick_columns; col++) {
            int x = (Width / Brick_columns) * col + 50;
            int y = (400 / Brick_rows) * row + 50;
            bricks[row][col] = Brick(x, y, 50, 50, RED);
        }
    }

    while (!WindowShouldClose() & !IsKeyPressed(KEY_ESCAPE))
    {
        BeginDrawing();
        ClearBackground(WHITE);

        paddle.Update(GetFrameTime());
        paddle.Draw();

        //ball.Draw();

        for (int row = 0; row < Brick_columns; row++) {
            for (int col = 0; col < Brick_rows; col++) {
               
                bricks[row][col].Draw();
            }
        }

        EndDrawing();
    }
    

}