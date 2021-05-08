#include <iostream>
#include <vector>
#include "Player.h"

void Player::setX(int x)
{
    this->x = x;
}

int Player::getX()
{
    return this->x;
}
Player::Player(int x)
{
    setX(x);
}