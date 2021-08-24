#include <string>
#include <raylib.h>
#include <raymath.h>

#pragma once

class Colliders
{
private:
    //name
    std::string name;

    //position
    Vector3 position;


public:
    Colliders(std::string name, Vector3 position);

};

