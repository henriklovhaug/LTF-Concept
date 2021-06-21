#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include <cmath>
#include <ctime>
#include <string>
#include "player.hpp"
#include "LTF.hpp"

#define MAX_COLUMNS 20

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800 * 2;
    const int screenHeight = 450 * 2;

    InitWindow(screenWidth, screenHeight, "LTF");

    // Blender models
    // TODO: find out if path has to be absolute or resource path can be specified in CMake
    Model model = LoadModel("Resources/wierdBox.obj");
    BoundingBox bounds = MeshBoundingBox(model.meshes[0]);

    // Get delta time for force-sensitive physics
    clock_t start, finish;
    static float deltaTime = 0;

    // Initialize player
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

    /*--------------------------------------------------------------------------------------
    Console sysout area for properties not needed to be repeated during playing
    ---------------------------------------------------------------------------------------*/
    std::cout << "max x: " << bounds.max.x << std::endl;
    std::cout << "min x: " << bounds.min.x << std::endl;

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        start = clock();
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
        if (IsKeyPressed(KEY_SPACE))
        {
            player.jump();
        }
#pragma endregion

        // Delta mouseposition
        mousex += (currentMouse.x - previousMouse.x) * -sensitivity; //Sensitivity is found in player.hpp
        mousey += (currentMouse.y - previousMouse.y) * -sensitivity;

        previousMouse = currentMouse;

        // Update
        //----------------------------------------------------------------------------------
        UpdateCamera(&camera); // Update camera
        //----------------------------------------------------------------------------------

        // Makes sure player can't turn camera over on it's head
        if (mousey > 85.0f * DEG2RAD)
        {
            mousey = 85.0f * DEG2RAD;
        }
        else if (mousey < -85.0f * DEG2RAD)
        {
            mousey = -85.0f * DEG2RAD;
        }

        player.updateGravity(deltaTime);
        player.updateTarget(mousex, mousey);

        camera.position = player.getPosition();
        camera.target = player.getTarget();

        if (IsKeyDown('F'))
        {
            player.setUp({1.0f, 0, 0});
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

        //Testdraw models
        DrawModel(model, {0, 0, 20}, 1, RED);

        // Draw some cubes around
        for (int i = 0; i < MAX_COLUMNS; i++)
        {
            DrawCube(positions[i], 2.0f, heights[i], 2.0f, colors[i]);
            DrawCubeWires(positions[i], 2.0f, heights[i], 2.0f, MAROON);
        }

        EndMode3D();
        EndDrawing();
        //----------------------------------------------------------------------------------
        //std::cout << LTF::collision(bounds,{0,0,20},player.getPosition(),player.getRadius()) << std::endl;
        std::cout << player.getPositionY() << std::endl;


        // Stop clock and calulate deltaTimme
        finish = clock();
        deltaTime = (float(finish) - float(start)) / CLOCKS_PER_SEC;
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadModel(model);
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}