#include <iostream>
#include <vector>
#include "Player.h"

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
    this->xPosition--;
}
void Player::moveBackward()
{
    this->xPosition++;
}
void Player::moveLeft(){
    this->yPosition++;
}
void Player::moveRight(){
    this->yPosition--;
}
Player::Player(float x, float y, float z)
{
    setX(x);
    setY(y);
    setZ(z);
}