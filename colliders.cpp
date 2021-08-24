#include "colliders.hpp"
#include <raylib.h>
#include <raymath.h>

Colliders::Colliders(std::string name, Vector3 position)
{
    this->name = name;
    this->position = position;
}