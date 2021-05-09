class Player
{
private:
    float x = 0.0f;
    float *ptrX = &x;
    float y = 0.0f;
    float *ptrY = &y;
    float z = 0.0f;
    float *ptrZ = &z;

public:
    Player(float x, float y, float z);
    void setX(float x);
    void setY(float y);
    void setZ(float z);
    float getX();
    float getY();
    float getZ();
};
