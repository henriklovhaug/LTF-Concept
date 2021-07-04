#include "Player.hpp"

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

void Player::updatePlaneXZ()
{
    Vector3 v1 = getPosition();
    Vector3 v2 = getTarget();

    dx = v2.x - v1.x;
    dz = v2.z - v1.z;

    anglex = atan2f(dx, dz);
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

void Player::moveForward()
{
    setPosition(Vector3Add(getPosition(), Vector3Scale(getMovement(bases.first, bases.second), MOVESPEED)));
}
void Player::moveBackward()
{
    setPosition(Vector3Add(getPosition(), Vector3Negate(Vector3Scale(getMovement(bases.first, bases.second), MOVESPEED))));
}
void Player::moveLeft()
{

    setPosition(Vector3Add(getPosition(), Vector3Negate(Vector3Perpendicular(Vector3Scale(getMovement(bases.first, bases.second), MOVESPEED)))));
}
void Player::moveRight()
{
    setPosition(Vector3Add(getPosition(), Vector3Perpendicular(Vector3Scale(getMovement(bases.first, bases.second), MOVESPEED))));
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
    return Vector3Normalize(projection(Vector3Subtract(getTarget(), getPosition()), v1, v2));
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
    if (canJump)
    {
        speed.y = jumpConstant;
    }
}

//TODO: this needs testing
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
 * @param deltaTime makes it independent from framrate
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
    this->speed = {0,0,0};
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
#pragma endregion

Vector3 Player::projection(Vector3 v1, Vector3 v2b, Vector3 v3b)
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