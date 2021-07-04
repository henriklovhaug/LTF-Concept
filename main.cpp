#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include <cmath>
#include <ctime>
#include <string>
#include "player.hpp"
#include "LTF.hpp"
#include "collisionObject.hpp"
#include <list>
#include <vector>

#define MAX_COLUMNS 20

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800 * 2;
    const int screenHeight = 450 * 2;

    InitWindow(screenWidth, screenHeight, "LTF");

    //test new class
    CollisionObject myObj({0, 0, 0}, false, 1, "arch.obj");

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

    //Objects in play area
    std::vector<CollisionObject> objectList;
    for (int i = 0; i < MAX_COLUMNS; i++)
    {
        objectList.push_back(CollisionObject({float(GetRandomValue(-15, 15)), 2, float(GetRandomValue(-15, 15))}, false, 2, "cone.obj"));
    }
    CollisionObject testFloor({0, -2, 0}, false, 2, "floor.obj");

    static float mousex = 0;
    static float mousey = 0;

    static Vector2 previousMouse = GetMousePosition(); //Get the position of the mouse

    SetCameraMode(camera, CAMERA_CUSTOM);

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    /*--------------------------------------------------------------------------------------
    Console sysout area for properties not needed to be repeated during playing
    ---------------------------------------------------------------------------------------*/
    std::cout << "max x: " << myObj.getBox().max.x << std::endl;
    std::cout << "min x: " << myObj.getBox().min.x << std::endl;

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        start = clock();
        DisableCursor(); // Mouse can move freely without worrying about screenborders
        Vector2 currentMouse = GetMousePosition();

// Movement
#pragma region movement

        if (IsKeyDown('W') && !LTF::collision(objectList, player, 1))
        {
            player.moveForward();
        }
        if (IsKeyDown('S') && !LTF::collision(objectList, player, 2))
        {
            player.moveBackward();
        }
        if (IsKeyDown('A') && !LTF::collision(objectList, player, 3))
        {
            player.moveLeft();
        }

        if (IsKeyDown('D') && !LTF::collision(objectList, player, 4))
        {
            player.moveRight();
        }
        if (IsKeyPressed(KEY_SPACE))
        {
            player.jump();
        }

        // Delta mouseposition
        mousex += (currentMouse.x - previousMouse.x) * -SENSITIVITY; //SENSITIVITY is found in player.hpp
        mousey += (currentMouse.y - previousMouse.y) * -SENSITIVITY;

        previousMouse = currentMouse;

#pragma endregion
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

        if(!LTF::collision(objectList,player,deltaTime)) player.updateGravity(deltaTime);
        
        player.updateTarget(mousex, mousey);

        camera.position = player.getPosition();
        camera.target = player.getTarget();
        camera.up = player.getUp();

        if (IsKeyPressed('F'))
        {
            player.setUp({1.0f, 0, 0});
            player.updateBases();
        }
        if (IsKeyPressed('G'))
        {
            player.setUp({0, 1.0f, 0});
            player.updateBases();
        }

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        BeginMode3D(camera);

        DrawModel(testFloor.getModel(), testFloor.getPosition(), testFloor.getScale(), GRAY);
        //DrawPlane({0.0f, 0.0f, 0.0f}, {32.0f, 32.0f}, LIGHTGRAY); // Draw ground
        DrawCube({-16.0f, 2.5f, 0.0f}, 1.0f, 5.0f, 32.0f, BLUE); // Draw a blue wall
        DrawCube({16.0f, 2.5f, 0.0f}, 1.0f, 5.0f, 32.0f, LIME);  // Draw a green wall
        DrawCube({0.0f, 2.5f, 16.0f}, 32.0f, 5.0f, 1.0f, GOLD);  // Draw a yellow wall

        //Testdraw models
        if (!LTF::collision(myObj, player))
        {
            DrawModel(myObj.getModel(), myObj.getPosition(), myObj.getScale(), BLUE);
        }
        else
        {
            DrawModel(myObj.getModel(), myObj.getPosition(), myObj.getScale(), RED);
        }
        DrawBoundingBox(myObj.getBox(), GREEN);

        // Draw some cubes around
        /*for (int i = 0; i < MAX_COLUMNS; i++)
        {
            DrawCube(positions[i], 2.0f, heights[i], 2.0f, colors[i]);
            DrawCubeWires(positions[i], 2.0f, heights[i], 2.0f, MAROON);
        }*/
        for (CollisionObject obj : objectList)
        {
            if (!LTF::collision(obj, player))
            {
                DrawModel(obj.getModel(), obj.getPosition(), obj.getScale(), BLUE);
            }
            else
            {
                DrawModel(obj.getModel(), obj.getPosition(), obj.getScale(), RED);
            }
        }

        EndMode3D();
        EndDrawing();
        //----------------------------------------------------------------------------------
        /*                               Console out place
        ----------------------------------------------------------------------------------*/
        //std::cout << LTF::collision(bounds,{0,0,20},player.getPosition(),player.getRadius()) << std::endl;
        //std::cout << player.getPositionY() << std::endl;
        std::cout << player.getPositionY() << std::endl;

        // Stop clock and calulate deltaTimme
        finish = clock();
        deltaTime = (float(finish) - float(start)) / CLOCKS_PER_SEC;
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    //TODO: write desctructor for collisionObject
    // UnloadModel(model);
    std::cout << LTF::Vector3Angle({1, 0, 0}, {1, 1, 0}) << std::endl;
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}