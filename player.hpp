#include <raylib.h>
#include <raymath.h>
#include <utility>

#define SENSITIVITY 0.003f
#define maxY 89.0f
#define MOVESPEED 0.2f
#define gravityconstant 150.0f
#define jumpConstant 50.0f

#pragma once

class Player
{
private:
    // Position
    Vector3 position;

    // Current way the player is facing
    Vector3 target;

    // Up
    Vector3 up;

    //Speed vector
    Vector3 speed = {0, 0, 0};

    // Mouse delta
    float mousex = 0;
    float mousey = 0;

    // Planes used for movement
    Vector3 movement;

    // Generate planes for movement
    float dx;
    float dy;
    float dz;

    float anglex;
    float angley = atan2f(dy, sqrtf(dx *dx + dz * dz));

    std::pair<Vector3, Vector3> bases = {{1, 0, 0}, {0, 0, 1}};

    // Boolean var
    bool canJump = true;

    // Radius     used for testing
    float radius = 1;

public:
    // Player will controll camera (Position, Target, Up)

    Player(Vector3 position, Vector3 target, Vector3 up);

    void setPosition(Vector3 position);
    void setTarget(Vector3 target);
    void setUp(Vector3 up);

    //Movement methods and helpers
    void updatePlaneXZ();
    void updateBases();

    Vector3 projection(Vector3 v1, Vector3 v2b, Vector3 v3b);
    Vector3 getMovement(Vector3 v1, Vector3 v2);
    
    void moveForward();
    void moveBackward();
    void moveLeft();
    void moveRight();

    void jump();
    void updateGravity(float deltaTime);
    Vector3 getNextGravity(float deltaTime);

    //Update target while playing

    void updateTarget(float deltaX, float deltaY);

    // Getters for position, target, up.
    Vector3 getPosition();
    float getPositionX();
    float getPositionY();
    float getPositionZ();
    Vector3 getNextPosition(int direction);

    Vector3 getTarget();
    float getTargetX();
    float getTargetY();
    float getTargetZ();

    Vector3 getUp();
    Vector3 getGravityVector();
    float getUpX();
    float getUpY();
    float getUpZ();

    float getSpeedY();

    float getRadius();
};
