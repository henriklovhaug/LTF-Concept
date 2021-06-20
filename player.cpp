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
    v1 = getPosition();
    v2 = getTarget();

    dx = v2.x - v1.x;
    dz = v2.z - v1.z;

    anglex = atan2f(dx, dz);
}
void Player::moveForward()
{
    updatePlaneXZ();
    position.x += sinf(anglex) * moveSpeed;
    position.z += cosf(anglex) * moveSpeed;
}
void Player::moveBackward()
{
    updatePlaneXZ();
    position.x -= sinf(anglex) * moveSpeed;
    position.z -= cosf(anglex) * moveSpeed;
}
void Player::moveLeft()
{
    updatePlaneXZ();
    position.x += cosf(anglex) * moveSpeed;
    position.z -= sinf(anglex) * moveSpeed;
}
void Player::moveRight()
{
    updatePlaneXZ();
    position.x -= cosf(anglex) * moveSpeed;
    position.z += sinf(anglex) * moveSpeed;
}

void Player::updateGravity(double deltaTime)
{
    
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
 * @param up 
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
    return Vector3Negate(this->up);
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
#pragma endregion