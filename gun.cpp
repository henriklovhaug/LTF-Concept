#include "gun.hpp"
#include <string>

<<<<<<< HEAD
=======

/**
 * @brief This setter is different as C++ pratice
 *
 * @param name name of gun
 */
>>>>>>> 8337529c683315471e2cc5d848140af4abcd446e
void Gun::setName(char *name)
{
    strcpy_s(this->gunName, name);
}

void Gun::setDamage(float damage)
{
    this->damage = damage;
}

<<<<<<< HEAD
=======
void Gun::setModel(std::string model)
{
    this->gunModel.append(model);
}

>>>>>>> 8337529c683315471e2cc5d848140af4abcd446e
void Gun::setPosition(Vector3 position)
{
    this->position = position;
}

void Gun::setTexture(Texture texture)
{
    this->gunTexture = texture;
}