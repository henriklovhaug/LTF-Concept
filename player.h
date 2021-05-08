class Player
{
private:
    float x;
    float *ptrX = &x;
    float y;
    float *ptrY = &y;
    float z;
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
