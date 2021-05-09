class Player
{
private:
    float xPosition = 0.0f;
    float *ptrX = &xPosition;
    float yPosition = 0.0f;
    float *ptrY = &yPosition;
    float zPosition = 0.0f;
    float *ptrZ = &zPosition;

public:
    Player(float x, float y, float z);
    void setX(float x);
    void setY(float y);
    void setZ(float z);
    void moveForward();
    void moveBackward();
    void moveLeft();
    void moveRight();
    float getX();
    float getY();
    float getZ();
};
