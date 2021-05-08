#include <iostream>
#include "raylib.h"
#include "Player.h"
#include <string>
int main(void)
{

    const int screenWidth = 800;
    const int screenHeight = 450;
    Player myPlayer(5,5,5);
    InitWindow(screenWidth, screenHeight, "The_big_hen");

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {

        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("test", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }
    std::cout << myPlayer.getX() << std::endl;

    CloseWindow();

    return 0;
}