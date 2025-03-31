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
            int w = 150;
            int h = 75;
            int SpacingX = Width / Brick_columns;
            int SpacingY = 400 / Brick_rows;
            int x = SpacingX * col + SpacingX/2 - w/2;
            int y = SpacingY * row + 25;
            bricks[row][col] = Brick(x, y, w, h, RED);
        }
    }

    while (!WindowShouldClose() & !IsKeyPressed(KEY_ESCAPE))
    {
        BeginDrawing();
        ClearBackground(BLACK);

        paddle.Update(GetFrameTime());
        paddle.Draw();

        ball.Draw();
        ball.Update(GetFrameTime(), bricks, paddle);

        for (int row = 0; row < Brick_rows; row++) {
            for (int col = 0; col < Brick_columns; col++) {
                if (bricks[row][col].CheckIfActive())bricks[row][col].Draw();
            }
        }

        ball.WaitForStart();

        EndDrawing();
    }
    

}