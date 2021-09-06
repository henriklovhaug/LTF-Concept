#include "colliders.hpp"
#include <raylib.h>
#include <raymath.h>

Colliders::Colliders(std::string name, Vector3 position)
{
    this->name = name;
    this->position = position;
}

std::string Colliders::getName()
{
    return this->name;
}

Vector3 Colliders::getPosition()
{
    return this->position;
}
