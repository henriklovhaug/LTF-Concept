#include<iostream>
#include"raylib.h"
#include"player.h"
int main(void)
{

    const int screenWidth = 800;
    const int screenHeight = 450;
<<<<<<< HEAD
    Player myPlayer(5);
    InitWindow(screenWidth, screenHeight, "The_big_hen");
=======

    InitWindow(screenWidth, screenHeight, "LTF");
>>>>>>> 0c18ab9ba0ee461de8ebc72f2ef0ab5149243edf

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {

        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("Ababot", 190, 200, 20, LIGHTGRAY);

        EndDrawing();
        
    }

    CloseWindow(); 

    return 0;
}