#include "collisionObject.hpp"
#include <raylib.h>
#include <raymath.h>

/**
 * @brief Construct a new Collision Object:: Collision Object object
 * 
 * @param position Vector3 position
 * @param isGround is it ground? soon to be removed
 * @param scale Scale of object. Will be scaled in all directions
 * @param name name of object file. i.e. "floor.obj"
 */
CollisionObject::CollisionObject(Vector3 position, bool isGround, float scale, std::string name)
{
    setPosition(position);
    setIsGround(isGround);
    setScale(scale);
    setOBJname(name);
    this->model = LoadModel(objURL.c_str());
    this->box = MeshBoundingBox(this->model.meshes[0]);
    scaleBox(scale);
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
    return this->box;
}

void CollisionObject::scaleBox(float scale)
{
    Vector3 diff = Vector3Subtract(Vector3Scale(this->box.max,scale),this->box.max);
    this->box.max = Vector3Scale(this->box.max,scale);
    this->box.min = Vector3Subtract(this->box.min,diff);
}