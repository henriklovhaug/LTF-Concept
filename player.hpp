#include <raylib.h>
#include <raymath.h>

#define sensitivity 0.003f
#define maxY 89.0f
#define moveSpeed 0.2f

class Player
{
private:
    // Position
    Vector3 position;

    // Current way the player is facing
    Vector3 target;

    // Up
    Vector3 up;

    // Mouse delta
    float mousex = 0;
    float mousey = 0;

    // Planes used for movement
    Vector3 v1 = getPosition();
    Vector3 v2 = getTarget();

    // Generate planes for movement
    float dx = v2.x - v1.x;
    float dy = v2.y - v1.y;
    float dz = v2.z - v1.z;

    float anglex = atan2f(dx, dz);
    float angley = atan2f(dy, sqrtf(dx *dx + dz * dz));

public:
    Player(Vector3 position, Vector3 target, Vector3 up);
    void setPosition(Vector3 position);
    void setTarget(Vector3 target);
    void setUp(Vector3 up);

    //Movement methods and helpers
    void updatePlaneXZ();
    
    void moveForward();
    void moveBackward();
    void moveLeft();
    void moveRight();

    //Update target while playing
    void updateTarget(float deltaX, float deltaY);

    // Getters for position, target, up.
    Vector3 getPosition();
    float getPositionX();
    float getPositionY();
    float getPositionZ();

    Vector3 getTarget();
    float getTargetX();
    float getTargetY();
    float getTargetZ();

    float getUpX();
    float getUpY();
    float getUpZ();
};
