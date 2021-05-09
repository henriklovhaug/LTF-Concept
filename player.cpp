#include <iostream>
#include <vector>
#include "Player.h"

void Player::setX(float x)
{
    this->x = x;
}
void Player::setY(float y)
{
    this->y = y;
}
void Player::setZ(float z)
{
    this->z = z;
}

float Player::getX()
{
    return this->x;
}
float Player::getY()
{
    return this->y;
}
float Player::getZ()
{
    return this->z;
}
Player::Player(float x, float y, float z)
{
    setX(x);
    setY(y);
    setZ(z);
}