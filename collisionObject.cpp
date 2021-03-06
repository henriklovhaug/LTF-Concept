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
 *
 * @note Position in Blender need to be {0,0,0} for ease of use
 */
CollisionObject::CollisionObject(Vector3 position, float scale, Color color, std::string name = "0")
{
    setPosition(position);
    setScale(scale);
    setOBJname(name);
    setColor(color);
    this->model = LoadModel(objURL.c_str());
    this->collisionModel = LoadModel(objURL.c_str());
    this->box = GetMeshBoundingBox(this->collisionModel.meshes[0]);
    scaleBox(scale);
    boundingBoxCorrection();
}

CollisionObject::CollisionObject(Vector3 position, float scale, Color color, std::string name, std::string collisionModelURL)
{
    setPosition(position);
    setScale(scale);
    setOBJname(name);
    setColor(color);
    this->model = LoadModel(objURL.c_str());
    this->collisionModel = LoadModel(collisionModelURL.c_str());
    this->box = GetMeshBoundingBox(this->collisionModel.meshes[0]);
    scaleBox(scale);
    boundingBoxCorrection();
}

CollisionObject::CollisionObject(Vector3 position, float scale, Color color, std::string name, std::vector<Colliders> colliders)
{
    setPosition(position);
    setScale(scale);
    setOBJname(name);
    setColor(color);
    this->model = LoadModel(objURL.c_str());
    this->collisionModel = LoadModel(objURL.c_str());
    this->box = GetMeshBoundingBox(this->collisionModel.meshes[0]);
    scaleBox(scale);
    boundingBoxCorrection();
    this->colliders = colliders;

}

void CollisionObject::boundingBoxCorrection()
{
    this->box.max = Vector3Add(this->box.max, this->position);
    this->box.min = Vector3Add(this->box.min, this->position);
}

void CollisionObject::setPosition(Vector3 position)
{
    this->position = position;
}

void CollisionObject::setOBJname(std::string name)
{
    this->objURL.append(name);
}

void CollisionObject::setCollisionModel(std::string name)
{
    this->collisionURL.append(name);
}

void CollisionObject::setScale(float scale)
{
    this->scale = scale;
}

void CollisionObject::setColor(Color color)
{
    this->color = color;
}

void CollisionObject::addColliders(Colliders colliders)
{
    this->colliders.push_back(colliders);
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

Color CollisionObject::getColor()
{
    return this->color;
}

Model CollisionObject::getModel()
{
    return this->model;
}

Model CollisionObject::getCollisionModel()
{
    return this->collisionModel;
}

BoundingBox CollisionObject::getBox()
{
    return this->box;
}

std::vector<Colliders> CollisionObject::getColliders()
{
    return this->colliders;
}

void CollisionObject::scaleBox(float scale)
{
    Vector3 diff = Vector3Subtract(Vector3Scale(this->box.max, scale), this->box.max);
    this->box.max = Vector3Scale(this->box.max, scale);
    this->box.min = Vector3Subtract(this->box.min, diff);
}