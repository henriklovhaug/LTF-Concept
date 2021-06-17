#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include <cmath>

#define MAX_COLUMNS 20
#define sensitivity 0.003f
#define maxY 89.0f
#define moveSpeed 0.2f;

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

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
    static float mousex = 0;
    static float mousey = 0;

    static Vector2 previousMouse = {0.0f, 0.0f}; //Get the position of the mouse
    SetCameraMode(camera, CAMERA_CUSTOM);

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        DisableCursor();
        Vector2 currentMouse = GetMousePosition();

        Vector3 v1 = camera.position;
        Vector3 v2 = camera.target;

        // Generate planes for camerarotaion, used for movement
        float dx = v2.x - v1.x;
        float dy = v2.y - v1.y;
        float dz = v2.z - v1.z;

        float anglex = atan2f(dx, dz);
        float angley = atan2f(dy, sqrtf(dx * dx + dz * dz));

        if (IsKeyDown('W'))
        {
            camera.position.x += sinf(anglex) * moveSpeed;
            camera.position.z += cosf(anglex) * moveSpeed;
        }
        if (IsKeyDown('S'))
        {
            camera.position.x -= sinf(anglex) * moveSpeed;
            camera.position.z -= cosf(anglex) * moveSpeed;
        }
        // Delta mouseposition
        mousex += (currentMouse.x - previousMouse.x) * -sensitivity;
        mousey += (currentMouse.y - previousMouse.y) * sensitivity;

        previousMouse = currentMouse;

        // Matrix calculation
        Matrix translation = MatrixTranslate(0, 0, 1.0f);
        Matrix rotation = MatrixRotateXYZ({PI * 2 - mousey, PI * 2 - mousex, 0});
        Matrix transform = MatrixMultiply(translation, rotation);

        // Update
        //----------------------------------------------------------------------------------
        UpdateCamera(&camera); // Update camera
        //----------------------------------------------------------------------------------
        camera.target.x = camera.position.x - transform.m12;
        camera.target.y = camera.position.y - transform.m13;
        camera.target.z = camera.position.z - transform.m14;

        if (IsKeyDown('A'))
        {
            camera.target.z += 0.1f;
        }

        if (IsKeyDown('D'))
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