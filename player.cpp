#include "Player.hpp"

void Player::setX(float x)
{
    this->xPosition = x;
}
void Player::setY(float y)
{
    this->yPosition = y;
}
void Player::setZ(float z)
{
    this->zPosition = z;
}

float Player::getX()
{
    return this->xPosition;
}
float Player::getY()
{
    return this->yPosition;
}
float Player::getZ()
{
    return this->zPosition;
}
void Player::moveForward()
{
    this->xPosition -= 0.2f;
}
void Player::moveBackward()
{
    this->xPosition += 0.2f;
}
void Player::moveLeft()
{
    this->zPosition += 0.2f;
}
void Player::moveRight()
{
    this->zPosition -= 0.2f;
}
Player::Player(float x, float y, float z)
{
    setX(x);
    setY(y);
    setZ(z);
}