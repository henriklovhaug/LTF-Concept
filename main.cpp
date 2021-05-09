#include "raylib.h"
#include "player.h"
#include <iostream>

#define MAX_COLUMNS 20

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800 * 3;
    const int screenHeight = 450 * 3;

    InitWindow(screenWidth, screenHeight, "Henrik & Stefan");

    Player player(4.0f, 2.0f, 4.0f);
    // Define the camera to look into our 3d world (position, target, up vector)
    Camera camera = {0};
    camera.position = {4.0f, 2.0f, 4.0f};
    camera.target = {0.0f, 1.8f, 0.0f};
    camera.up = {0.0f, 1.0f, 0.0f};
    camera.fovy = 60.0f;

    // Generates some random columns
    float heights[MAX_COLUMNS] = {0};
    Vector3 positions[MAX_COLUMNS] = {0};
    Color colors[MAX_COLUMNS] = {0};

    for (int i = 0; i < MAX_COLUMNS; i++)
    {
        heights[i] = (float)GetRandomValue(1, 12);
        positions[i] = {(float)GetRandomValue(-15, 15), heights[i] / 2.0f, (float)GetRandomValue(-15, 15)};
        colors[i] = RED;
    }

    SetCameraMode(camera, CAMERA_FREE); // Set a first person camera mode

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        UpdateCamera(&camera); // Update camera
        if (IsKeyDown('W'))
        {
            player.moveForward();
            camera.position = {player.getX(), player.getZ(), player.getY()};
        }
        if (IsKeyDown('S'))
        {
            player.setX(player.getX() + 1.0f);
            camera.position = {player.getX(), player.getZ(), player.getY()};
        }
        if (IsKeyDown('A'))
        {
            player.moveLeft();
            camera.position = {player.getX(), player.getZ(), player.getY()};
        }
        if (IsKeyDown('D'))
        {
            player.moveRight();
            camera.position = {player.getX(), player.getZ(), player.getY()};
        }
        /*if(IsKeyDown('W')) {
            player.setX(player.getX()+1.0f);
            camera.position = {player.getX(),player.getZ(),player.getY()};
            }*/

        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        BeginMode3D(camera);

        DrawPlane({0.0f, 0.0f, 0.0f}, {32.0f, 32.0f}, LIGHTGRAY); // Draw ground
        DrawCube({-16.0f, 2.5f, 0.0f}, 1.0f, 5.0f, 32.0f, BLUE);  // Draw a blue wall
        DrawCube({16.0f, 2.5f, 0.0f}, 1.0f, 5.0f, 32.0f, LIME);   // Draw a green wall
        DrawCube({0.0f, 2.5f, 16.0f}, 32.0f, 5.0f, 1.0f, GOLD);   // Draw a yellow wall

        // Draw some cubes around
        for (int i = 0; i < MAX_COLUMNS; i++)
        {
            DrawCube(positions[i], 2.0f, heights[i], 2.0f, colors[i]);
            DrawCubeWires(positions[i], 2.0f, heights[i], 2.0f, MAROON);
        }

        EndMode3D();
        /*
        DrawRectangle(10, 10, 220, 70, Fade(SKYBLUE, 0.5f));
        DrawRectangleLines(10, 10, 220, 70, BLUE);

        DrawText("First person camera default controls:", 20, 20, 10, BLACK);
        DrawText("- Move with keys: W, A, S, D", 40, 40, 10, DARKGRAY);
        DrawText("- Mouse move to look around", 40, 60, 10, DARKGRAY);
    std::cout << player.getX() << std::endl;
*/
        EndDrawing();
        //----------------------------------------------------------------------------------
    }
    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}