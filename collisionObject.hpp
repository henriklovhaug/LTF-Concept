#include <raylib.h>
#include <string>

#pragma once

class CollisionObject
{
private:
    // Position
    Vector3 position;

    // URL for obj file
    std::string objURL = "resources/";

    // Scale of object
    float scale;

    //Model loaded from file
    Model model;

    Color color;

    //Bounds around model
    BoundingBox box;
    void scaleBox(float scale);

public:
    CollisionObject(Vector3 position, float scale, Color color, std::string name = "0");

    void setPosition(Vector3 position);
    void setOBJname(std::string name);
    void setScale(float scale);
    void boundingBoxCorrection();
    void setColor(Color color);

    Vector3 getPosition();
    std::string getOBJname();
    float getScale();
    Model getModel();
    BoundingBox getBox();
    Color getColor();
};
