#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include <cmath>
#include <ctime>
#include <string>
#include "player.hpp"
#include "LTF.hpp"
#include "collisionObject.hpp"
#include "gun.hpp"
#include <list>
#include <vector>
//#include <simdjson.h>

#define MAX_COLUMNS 5

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800 * 3;
    const int screenHeight = 450 * 3;

    InitWindow(screenWidth, screenHeight, "LTF");

    //test new class

    // Get delta time for force-sensitive physics
    double new_time, old_time;
    static double deltaTime = 0;

    // Initialize player
    Player player({4.0f, 20.0f, 4.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 0.0f});
    float speedScalar = 1;

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
        objectList.push_back(CollisionObject({float(GetRandomValue(-15, 15)), 0, float(GetRandomValue(-15, 15))}, 2, BLUE, "cone.obj"));
    }
    //Other collision stuff
    CollisionObject box({-10.5f, 0, 0}, 1, BLUE, "box.obj");
    objectList.push_back(box);
    CollisionObject arch2({0, 0, 0}, 1, ORANGE, "arch2.obj");
    objectList.push_back(arch2);
    CollisionObject testFloor({0, -2, 0}, 2, GREEN, "floor.obj");
    objectList.push_back(testFloor);
    CollisionObject testWall({0, 0, 10}, 1, BROWN, "wall.obj");
    objectList.push_back(testWall);
    CollisionObject rWall({20, 0, 0}, 1, YELLOW, "Rwall.obj");
    objectList.push_back(rWall);
    CollisionObject testFloor2({40, -6, 0}, 2, LIME, "floor.obj");
    objectList.push_back(testFloor2);
    CollisionObject stair({15, 2, -10}, 3, Color({0, 32, 132, 255}), "stair.obj");
    objectList.push_back(stair);

    //Stuff that only needs to be drawn
    CollisionObject gun({30, 0, 0}, 1, WHITE, "gun.obj");
    objectList.push_back(gun);

    static float mouseX = 0;
    static float mouseY = 0;

    static Vector2 previousMouse = GetMousePosition(); //Get the position of the mouse

    SetCameraMode(camera, CAMERA_CUSTOM);

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    /*--------------------------------------------------------------------------------------
    Console sysout area for properties not needed to be repeated during playing
    ---------------------------------------------------------------------------------------*/
    //std::cout << objectList.size() << std::endl;

    old_time = LTF::clock();

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        new_time = LTF::clock();
        deltaTime = (double(new_time) - double(old_time)) / 1000000000.0f;
        std::cout << deltaTime << std::endl;
        old_time = new_time;

        DisableCursor(); // Mouse can move freely without worrying about screenborders
        Vector2 currentMouse = GetMousePosition();

// Movement
#pragma region movement

        if (IsKeyDown('W') &&
            LTF::collisionInfo(player.getRay(), objectList, 1).distance > 1.5f &&
            LTF::collisionInfo(player.getFeetRay(), objectList, 1).distance > 1.5f)
        {
            player.moveForward(speedScalar);
        }
        if (IsKeyDown('S') &&
            LTF::collisionInfo(player.getRay(), objectList, 2).distance > 1.5f &&
            LTF::collisionInfo(player.getFeetRay(), objectList, 2).distance > 1.5f)
        {
            player.moveBackward(speedScalar);
        }
        if (IsKeyDown('A') &&
            LTF::collisionInfo(player.getRay(), objectList, 3).distance > 1.5f &&
            LTF::collisionInfo(player.getFeetRay(), objectList, 3).distance > 1.5f)
        {
            player.moveLeft(speedScalar);
        }

        if (IsKeyDown('D') &&
            LTF::collisionInfo(player.getRay(), objectList, 4).distance > 1.5f &&
            LTF::collisionInfo(player.getFeetRay(), objectList, 4).distance > 1.5f)
        {
            player.moveRight(speedScalar);
        }

        if (IsKeyPressed(KEY_SPACE))
        {
            player.jump();
        }

        if (IsKeyDown(KEY_LEFT_SHIFT))
        {
            speedScalar = 2;
        }
        if (IsKeyReleased(KEY_LEFT_SHIFT))
        {
            speedScalar = 1;
        }

        if (IsKeyDown(KEY_LEFT_CONTROL))
        {
            speedScalar = 0.5;
        }
        if (IsKeyReleased(KEY_LEFT_CONTROL))
        {
            speedScalar = 1;
        }
        if (IsKeyPressed(KEY_NINE))
        {
            camera.fovy -= 10;
        }
        if (IsKeyPressed(KEY_ZERO))
        {
            camera.fovy += 10;
        }
        // Delta mouseposition
        mouseX += (currentMouse.x - previousMouse.x) * -SENSITIVITY; //SENSITIVITY is found in player.hpp
        mouseY += (currentMouse.y - previousMouse.y) * -SENSITIVITY;

        previousMouse = currentMouse;

        if (LTF::nextFallingInfo(player, objectList, 1, deltaTime).distance > player.getHeight())
        {
            player.updateGravity(deltaTime);
        }
        else if (LTF::nextFallingInfo(player, objectList, 1, deltaTime).distance < player.getHeight() - 0.5f &&
                 player.getSpeedY() == 0)
        {
            player.setPosition(Vector3Add(player.getPosition(), player.getUp()));
        }
        else
        {
            player.resetSpeed();
        }
#pragma endregion
        // Update
        //----------------------------------------------------------------------------------
        UpdateCamera(&camera); // Update camera
                               //----------------------------------------------------------------------------------

#pragma region forces and limits
        // Makes sure player can't turn camera over on it's head
        if (mouseY > 85.0f * DEG2RAD)
        {
            mouseY = 85.0f * DEG2RAD;
        }
        else if (mouseY < -85.0f * DEG2RAD)
        {
            mouseY = -85.0f * DEG2RAD;
        }

        //Moves camera around based on mouse movement
        player.updateTarget(mouseX, mouseY);

#pragma endregion

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
        if (IsKeyPressed('Z'))
        {
            player.resetSpeed();
            player.setPosition({4.0f, 4.0f, 4.0f});
        }

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        BeginMode3D(camera);

        DrawModel(gun.getModel(), gun.getPosition(), gun.getScale(), gun.getColor());
        DrawModel(testFloor.getModel(), testFloor.getPosition(), testFloor.getScale(), GRAY);
        DrawCube({-16.0f, 2.5f, 0.0f}, 1.0f, 5.0f, 32.0f, BLUE); // Draw a blue wall
        //DrawCube({16.0f, 2.5f, 0.0f}, 1.0f, 5.0f, 32.0f, LIME);  // Draw a green wall
        DrawCube({0.0f, 2.5f, 16.0f}, 32.0f, 5.0f, 1.0f, GOLD); // Draw a yellow wall
        DrawRay({{1, 1, 0}, {0, 0, 0}}, PINK);

        //Testdraw models

        if (!LTF::collision(arch2, player))
        {
            DrawModel(arch2.getModel(), arch2.getPosition(), arch2.getScale(), arch2.getColor());
        }
        else
        {
            if (GetRayCollisionModel(player.getRay(), arch2.getModel()).hit &&
                GetRayCollisionModel(player.getRay(), arch2.getModel()).distance < 1)
            {
                DrawModel(arch2.getModel(), arch2.getPosition(), arch2.getScale(), RED);
            }
            else
                DrawModel(arch2.getModel(), arch2.getPosition(), arch2.getScale(), arch2.getColor());
        }
        DrawBoundingBox(arch2.getBox(), GREEN);

        for (CollisionObject obj : objectList)
        {
            if (!LTF::collision(obj, player))
            {
                DrawModel(obj.getModel(), obj.getPosition(), obj.getScale(), obj.getColor());
                DrawBoundingBox(obj.getBox(), GREEN);
            }
            else
            {
                DrawModel(obj.getModel(), obj.getPosition(), obj.getScale(), RED);
            }
        }

        EndMode3D();

        // Debug Drawing
        LTF::debugToScreen("dT: %f ms", deltaTime*1000, 60, 60);

        EndDrawing();
        //----------------------------------------------------------------------------------
        /*                               Console out place
        ----------------------------------------------------------------------------------*/
        //std::cout << LTF::collisionInfo(player.getRay(), arch2,2).hit << std::endl;
        //std::cout << player.getSpeedY() << std::endl;
        //std::cout << LTF::collisionInfo(player.getFeetRay(), objectList, 1).distance << std::endl;

    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    //TODO: write desctructor for collisionObject
    // UnloadModel(model);
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}