#include <raylib.h>
#include <raymath.h>
#include <string>


class Gun
{
private:


    // Gun name
    char gunName[256];

    // Gun position
    Vector3 position;

    // Gun Model
    std::string gunModel = "resources/guns";

    // Gun Model Texture
    Texture gunTexture;

    // Gun damage
    float damage;

public:
    Gun(/* args */);

    // Set gun name
    void setName(char* name);

    // Set gun position
    void setPosition(Vector3 position);


<<<<<<< HEAD
=======
    // Set gun model
    void setModel(std::string model);


>>>>>>> 8337529c683315471e2cc5d848140af4abcd446e
    // Set gun texture
    void setTexture(Texture texture);


    // Set gun damage
    void setDamage(float damage);


    // Get gun position
    Vector3 getPosition();

    // Get gun model
    Model getModel();

    // Get gun texture
    Texture getTexture();

    // Get gun damage
    float getDamage();
};
