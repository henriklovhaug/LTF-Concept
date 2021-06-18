#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include <cmath>
#include "player.hpp"

#define MAX_COLUMNS 20

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800 * 2;
    const int screenHeight = 450 * 2;

    InitWindow(screenWidth, screenHeight, "LTF");

    // Initialise player
    Player player({4.0f, 2.0f, 4.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 0.0f});

    // Define the camera to look into our 3d world (position, target, up vector)
    Camera camera = {0};
    camera.position = player.getPosition();
    camera.target = player.getTarget();
    camera.up = player.getUp();
    camera.fovy = 60.0f;
    //camera.projection = CAMERA_PERSPECTIVE;

    // Generates some random columns
    float heights[MAX_COLUMNS] = {0};
    Vector3 positions[MAX_COLUMNS] = {0};
    Color colors[MAX_COLUMNS] = {0};

    for (int i = 0; i < MAX_COLUMNS; i++)
    {
        heights[i] = (float)GetRandomValue(1, 12);
        positions[i] = {(float)GetRandomValue(-15, 15), heights[i] / 2.0f, (float)GetRandomValue(-15, 15)};
        colors[i] = BLUE;
    }

    static float mousex = 0;
    static float mousey = 0;

    static Vector2 previousMouse = {0.0f, 0.0f}; //Get the position of the mouse

    SetCameraMode(camera, CAMERA_CUSTOM);

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        DisableCursor(); // Mouse can move freely without worrying about screenborders
        Vector2 currentMouse = GetMousePosition();

// Movement
#pragma region movement

        if (IsKeyDown('W'))
        {
            player.moveForward();
        }
        if (IsKeyDown('S'))
        {
            player.moveBackward();
        }
        if (IsKeyDown('A'))
        {
            player.moveLeft();
        }

        if (IsKeyDown('D'))
        {
            player.moveRight();
        }
#pragma endregion

        // Delta mouseposition
        mousex += (currentMouse.x - previousMouse.x) * -sensitivity;
        mousey += (currentMouse.y - previousMouse.y) * sensitivity;

        previousMouse = currentMouse;

        // Update
        //----------------------------------------------------------------------------------
        UpdateCamera(&camera); // Update camera
        //----------------------------------------------------------------------------------
        player.updateTarget(mousex, mousey);

        camera.position = player.getPosition();
        camera.target = player.getTarget();

        if (IsKeyDown('F'))
        {
            camera.up.y = 0;
            camera.up.x = 1;
        }

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
        EndDrawing();
        //----------------------------------------------------------------------------------
        std::cout << Vector3Length(Vector3Subtract(camera.position, camera.target)) << std::endl;

        /*std::cout << "Camera up x: " << camera.up.x << std::endl;
        std::cout << "Camera up y: " << camera.up.y << std::endl;
        std::cout << "Camera up z: " << camera.up.z << std::endl;*/
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}