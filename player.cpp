#include "player.hpp"
#include <iostream>

/**
 * @brief Turns mouse movement into rotation of player
 *
 * @param deltaX
 * @param deltaY MouseDelta y has to be handled before it's passed into method i.e. cap how far up the player can see etc.
 */
void Player::updateTarget(float deltaX, float deltaY)
{
    Matrix translation = MatrixTranslate(0, 0, 1.0f);
    Matrix rotation = MatrixRotateXYZ({PI * 2 - deltaY, PI * 2 - deltaX, 0});
    Matrix transform = MatrixMultiply(translation, rotation);
    setTarget({getPositionX() - transform.m12, getPositionY() - transform.m13, getPositionZ() - transform.m14});
}

void Player::updateBases()
{
    if (up.x == 1)
    {
        bases.first = {0, 0, 1};
        bases.second = {0, 1, 0};
    }
    else if (up.z == 1)
    {
        bases.first = {1, 0, 0};
        bases.second = {0, 1, 0};
    }
    else
    {
        bases.first = {1, 0, 0};
        bases.second = {0, 0, 1};
    }
}

void Player::moveForward(float scalar)
{
    setPosition(Vector3Add(getPosition(), Vector3Scale(getMovement(bases.first, bases.second), MOVESPEED * scalar)));
}
void Player::moveBackward(float scalar)
{
    setPosition(Vector3Add(getPosition(), Vector3Negate(Vector3Scale(getMovement(bases.first, bases.second), MOVESPEED * scalar))));
}
void Player::moveLeft(float scalar)
{
    setPosition(Vector3Add(getPosition(), Vector3Negate(Vector3Perpendicular(Vector3Scale(getMovement(bases.first, bases.second), MOVESPEED*scalar)))));
}
void Player::moveRight(float scalar)
{
    setPosition(Vector3Add(getPosition(), Vector3Perpendicular(Vector3Scale(getMovement(bases.first, bases.second), MOVESPEED*scalar))));
}

void Player::crouch()
{
    if (!canJump() && !isCrouched)
    {
        this->position = Vector3Subtract(this->position, this->up);
    }
}
/**
 * @brief Get normalized vector projected onto plane
 *
 * @param v1 basis one
 * @param v2 basis two
 * @return Vector3 projected
 */
Vector3 Player::getMovement(Vector3 v1, Vector3 v2)
{
    return Vector3Normalize(project(Vector3Subtract(getTarget(), getPosition()), v1, v2));
}

/**
 * @brief calculates where player whould be next tick. Used for preemptive crash detection
 *
 * @param direction 1: forward, 2: backwards, 3: left, 4: right
 * @return Vector3 where player would be
 */
Vector3 Player::getNextPosition(int direction)
{
    switch (direction)
    {
    case 1:
        return Vector3Add(getPosition(), Vector3Scale(getMovement({1, 0, 0}, {0, 0, 1}), MOVESPEED));
        break;
    case 2:
        return Vector3Add(getPosition(), Vector3Negate(Vector3Scale(getMovement({1, 0, 0}, {0, 0, 1}), MOVESPEED)));
        break;
    case 3:
        return Vector3Add(getPosition(), Vector3Negate(Vector3Perpendicular(Vector3Scale(getMovement({1, 0, 0}, {0, 0, 1}), MOVESPEED))));
        break;
    case 4:
        return Vector3Add(getPosition(), Vector3Perpendicular(Vector3Scale(getMovement({1, 0, 0}, {0, 0, 1}), MOVESPEED)));
        break;
    case 5:
    default:
        return {0, 0, 0};
        break;
    }
}
/**
 * @brief Le jump
 *
 */
void Player::jump()
{
    speed = Vector3Scale(this->up, jumpConstant);
}

bool Player::canJump()
{
    Vector3 temp = Vector3Add(this->up, this->speed);
    return this->up.x == temp.x &&
           this->up.y == temp.y &&
           this->up.z == temp.z;
}

//TODO: this needs testing, can clip through ground somtimes
/**
 * @brief Makes player fall
 *
 * @param deltaTime makes method independent from framerate
 *
 */
void Player::updateGravity(float deltaTime)
{
    position = getNextGravityVector(deltaTime);
}

/**
 * @brief gives where the player will be next tick
 *
 * @param deltaTime makes it independent from framerate
 * @return Vector3
 */
Vector3 Player::getNextGravityVector(float deltaTime)
{
    Vector3 temp = Vector3Add(Vector3Scale(speed, deltaTime),
                              Vector3Scale(getGravityVector(), powf(deltaTime, 2) * gravityconstant));
    speed = Vector3Add(speed, Vector3Scale(getGravityVector(), deltaTime * 75));
    return Vector3Add(position, temp);
}

void Player::resetSpeed()
{
    this->speed = {0, 0, 0};
}

// Setters and constructor
#pragma region Setters and constructor
void Player::setPosition(Vector3 position)
{
    this->position = position;
}

void Player::setTarget(Vector3 target)
{
    this->target = target;
}

void Player::setUp(Vector3 up)
{
    this->up = up;
}

/**
 * @brief Construct a new Player object
 *
 * @param position
 * @param target
 * @param up Defines up and gravity vector
 *
 */
Player::Player(Vector3 position, Vector3 target, Vector3 up)
{
    setPosition(position);
    setTarget(target);
    setUp(up);
}
#pragma endregion

// Getters
#pragma region getters

Vector3 Player::getPosition()
{
    return this->position;
}
float Player::getPositionX()
{
    return this->position.x;
}
float Player::getPositionY()
{
    return this->position.y;
}
float Player::getPositionZ()
{
    return this->position.z;
}

Vector3 Player::getTarget()
{
    return this->target;
}
float Player::getTargetX()
{
    return this->target.x;
}
float Player::getTargetY()
{
    return this->target.y;
}
float Player::getTargetZ()
{
    return this->target.z;
}

Vector3 Player::getUp()
{
    return this->up;
}
Vector3 Player::getGravityVector()
{
    return Vector3Negate(Vector3Scale(this->up, 2));
}
float Player::getUpX()
{
    return this->up.x;
}
float Player::getUpY()
{
    return this->up.y;
}
float Player::getUpZ()
{
    return this->up.z;
}

float Player::getSpeedY()
{
    return this->speed.y;
}

float Player::getRadius()
{
    return this->radius;
}

float Player::getHeight()
{
    return this->height;
}

Ray Player::getRay()
{
    this->ray.position = this->position;
    this->ray.direction = Vector3Normalize(project(Vector3Subtract(this->target, this->position), bases.first, bases.second));
    return ray;
}

Ray Player::getDownRay()
{
    this->downRay.position = this->position;
    this->downRay.direction = getGravityVector();
    return downRay;
}

Ray Player::getDownRayFromNextPosition(float deltaTime)
{
    this->downRay.position = getNextGravityVector(deltaTime);
    this->downRay.direction = getGravityVector();
    return downRay;
}

Ray Player::getFeetRay()
{
    this->feetRay.position = getFeet();
    this->feetRay.direction = Vector3Normalize(project(Vector3Subtract(this->target, getFeet()), bases.first, bases.second));
    return feetRay;
}

Ray Player::getShootingRay()
{
    this->shootingRay.position = this->position;
    this->shootingRay.direction =Vector3Normalize(Vector3Subtract(this->target, this->position));
    return shootingRay;
}

Vector3 Player::getFeet()
{
    return Vector3Add(this->position, Vector3Scale(this->up,-this->height));
}


#pragma endregion

Vector3 Player::project(Vector3 v1, Vector3 v2b, Vector3 v3b)
{
    if (Vector3DotProduct(v2b, v3b) == 0)
    {
        return Vector3Add(Vector3Scale(v2b, Vector3DotProduct(v1, v2b) / Vector3DotProduct(v2b, v2b)),
                          Vector3Scale(v3b, Vector3DotProduct(v1, v3b) / Vector3DotProduct(v3b, v3b)));
    }
    else
    {
        //TODO: Handle not orthogonal basis
        return {0, 0, 0};
    }
}