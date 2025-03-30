#include "entrypoint.h"
#include <raylib.h>
#include "Classes.h"

//Creer votre class Engin ici et appeler une fonction start que vous définisser à la classe dans la fonction raylib_start plus bas.
void raylib_start(void){

    InitWindow(Width, Height, "Breakout");

    Paddle paddle = Paddle(Width/2, Height - 100);

    while (!WindowShouldClose() & !IsKeyPressed(KEY_ESCAPE))
    {
        BeginDrawing();
        ClearBackground(WHITE);

        paddle.Update(1);
        paddle.Draw();

        EndDrawing();
    }
    

}