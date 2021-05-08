#include<iostream>
#include"raylib.h"
int main(void)
{

    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "The_big_hen");

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