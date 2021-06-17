<<<<<<< HEAD
#include <raylib.h>
#include <iostream>
#include <cmath>

#define MAX_COLUMNS 20

=======
#include "raylib.h"
#include "player.h"
#include <iostream>
#include <string>

#define MAX_COLUMNS 20

Player player(4.0f, 2.0f, 4.0f);
>>>>>>> 2f0ace6345e1499813a0f0df8636912bd862132b
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
<<<<<<< HEAD
    const int screenWidth = 800;
    const int screenHeight = 450;
=======
    const int screenWidth = 800 * 3;
    const int screenHeight = 450 * 3;
>>>>>>> 2f0ace6345e1499813a0f0df8636912bd862132b

    InitWindow(screenWidth, screenHeight, "LTF");

    // Define the camera to look into our 3d world (position, target, up vector)
    Camera camera = {0};
    camera.position = {4.0f, 2.0f, 4.0f};
    camera.target = {0.0f, 1.0f, 0.0f};
    camera.up = {0.0f, 1.0f, 0.0f};
    camera.fovy = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;

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

    SetCameraMode(camera, CAMERA_CUSTOM);

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        DisableCursor();
        Vector2 previousMouse = GetMousePosition(); //Get the position of the mouse

        Vector3 v1 = camera.position;
        Vector3 v2 = camera.target;

        // Generate planes for camerarotaion
        float dx = v2.x - v1.x;
        float dy = v2.y - v1.y;
        float dz = v2.z - v1.z;

        float anglex = atan2f(dx, dz);
        float angley = atan2f(dy, sqrtf(dx * dx + dz * dz));

        // Delta mouseposition
        float mousex = GetMousePosition().x - previousMouse.x;
        float mousey = GetMousePosition().y - previousMouse.y;
        // Update
        //----------------------------------------------------------------------------------
        UpdateCamera(&camera); // Update camera
        //----------------------------------------------------------------------------------
        camera.target.x = sin(anglex)*cos(angley)
        if (IsKeyDown('W'))
        {
            camera.target.y += 0.1f;
        }

        if (IsKeyDown('S'))
        {
            camera.target.y -= 0.1f;
        }
        if(IsKeyDown('A'))
        {
            camera.target.z += 0.1f;
        }

        if(IsKeyDown('D'))
        {
            camera.target.z -= 0.1f;
        }

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
<<<<<<< HEAD
        EndDrawing();
        Vector2 currentMouse = GetMousePosition();
=======
        /*
        DrawRectangle(10, 10, 220, 70, Fade(SKYBLUE, 0.5f));
        DrawRectangleLines(10, 10, 220, 70, BLUE);

        DrawText("First person camera default controls:", 20, 20, 10, BLACK);
        DrawText("- Move with keys: W, A, S, D", 40, 40, 10, DARKGRAY);
        DrawText("- Mouse move to look around", 40, 60, 10, DARKGRAY);
        std::cout << player.getX() << std::endl;
        */
        /*std::string mystring = std::to_string(camera.target.x);
        std::cout << "target x: " << mystring << std::endl;
       std::string mystriny = std::to_string(camera.target.y);
        std::cout << "target y: " << mystriny << std::endl;
       std::string mystrinz = std::to_string(camera.target.z);
        std::cout << "target z: " << mystrinz << std::endl;
        EndDrawing();*/
>>>>>>> 2f0ace6345e1499813a0f0df8636912bd862132b
        //----------------------------------------------------------------------------------
        std::cout << currentMouse.x << std::endl;
        std::cout << currentMouse.y << std::endl;

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