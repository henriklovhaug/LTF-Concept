#include "collisionObject.hpp"
#include <raylib.h>


CollisionObject::CollisionObject(Vector3 position, bool isGround, float scale, std::string name)
{
    setPosition(position);
    setIsGround(isGround);
    setScale(scale);
    setOBJname(name);
    this->model = LoadModel(objURL.c_str());
}

void CollisionObject::setPosition(Vector3 position)
{
    this->position = position;
} 

void CollisionObject::setOBJname(std::string name)
{
    this->objURL.append(name);
}

void CollisionObject::setScale(float scale)
{
    this->scale = scale;
}

void CollisionObject::setIsGround(bool isGround)
{
    this->isGround = isGround;
}

Vector3 CollisionObject::getPosition()
{
    return this->position;
}

float CollisionObject::getScale()
{
    return this->scale;
}

std::string CollisionObject::getOBJname()
{
    return this->objURL;
}

bool CollisionObject::getIsGround()
{
    return this->isGround;
}

Model CollisionObject::getModel()
{
    return this->model;
}

BoundingBox CollisionObject::getBox()
{
    return MeshBoundingBox(getModel().meshes[0]);
}