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

    //Height of player
    float height = 1.5f;

    // Mouse delta
    float mouseX = 0;
    float mouseY = 0;

    // Planes used for movement
    Vector3 movement;
    Ray ray;
    Ray feetRay;
    Ray downRay;
    Ray shootingRay;

    std::pair<Vector3, Vector3> bases = {{1, 0, 0}, {0, 0, 1}};

    // Boolean var

    // Radius     used for testing
    float radius = 1;

public:
    bool isCrouched = false;
    // Player will controll camera (Position, Target, Up)

    Player(Vector3 position, Vector3 target, Vector3 up);

    void setPosition(Vector3 position);
    void setTarget(Vector3 target);
    void setUp(Vector3 up);
    void setHeight(float height);

    //Movement methods and helpers
    void updateBases();

    Vector3 project(Vector3 v1, Vector3 v2b, Vector3 v3b);
    Vector3 getMovement(Vector3 v1, Vector3 v2);

    void moveForward(float scalar);
    void moveBackward(float scalar);
    void moveLeft(float scalar);
    void moveRight(float scalar);

    void crouch();

    void jump();
    void updateGravity(float deltaTime);
    Vector3 getNextGravityVector(float deltaTime);
    void resetSpeed();

    Ray getDownRay();
    Ray getDownRayFromNextPosition(float deltaTime);
    Ray getFeetRay();
    Ray getRay();
    Ray getShootingRay();

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
    bool canJump();

    float getRadius();
    float getHeight();
    Vector3 getFeet();
};
