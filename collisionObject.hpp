#include <raylib.h>
#include <string>
#include <vector>
#include "colliders.hpp"

#pragma once

class CollisionObject
{
private:
    // Position
    Vector3 position;

    // URL for obj file
    std::string objURL = "resources/";

    // URL for collision file
    std::string collisionURL = "resources/";

    // Scale of object
    float scale;

    //Model loaded from file
    Model model;

    //Collision Model
    Model collisionModel;

    //Colliders list
    std::vector<Colliders> colliders;

    Color color;

    //Bounds around model
    BoundingBox box;
    void scaleBox(float scale);


public:
    CollisionObject(Vector3 position, float scale, Color color, std::string name);
    //Second constructor for collisionObject
    CollisionObject(Vector3 position, float scale, Color color, std::string name, std::string collisionModelURL);
    //Third constructor for collisionObject
    CollisionObject(Vector3 position, float scale, Color color, std::string name, std::vector<Colliders> colliders);

    void setPosition(Vector3 position);
    void setOBJname(std::string name);
    void setCollisionModel(std::string name);
    void setScale(float scale);
    void boundingBoxCorrection();
    void setColor(Color color);
    void addColliders(Colliders colliders);

    Vector3 getPosition();
    std::string getOBJname();
    float getScale();
    Model getModel();
    Model getCollisionModel();
    BoundingBox getBox();
    Color getColor();
    std::vector<Colliders> getColliders();
};
