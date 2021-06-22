#include <raylib.h>
#include <string>

class CollisionObject
{
private:
    // Position
    Vector3 position;

    // URL for obj file
    std::string objURL = "resources/";

    // Scale of object
    float scale;

    // ground ? walkable : will collide
    bool isGround;

    //Model loaded from file
    Model model;

    //Bounds around model
    BoundingBox box;

public:
    CollisionObject(Vector3 position, bool isGround, float scale, std::string name = "0");

    void setPosition(Vector3 position);
    void setOBJname(std::string name);
    void setScale(float scale);
    void setIsGround(bool isGround);
    

    Vector3 getPosition();
    std::string getOBJname();
    float getScale();
    bool getIsGround();
    Model getModel();
    BoundingBox getBox();
};
