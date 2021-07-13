#include "gun.hpp"
#include <string>


/**
 * @brief This setter is different as C++ pratice
 *
 * @param name name of gun
 */
void Gun::setName(char *name)
{
    strcpy_s(this->gunName, name);
}

void Gun::setDamage(float damage)
{
    this->damage = damage;
}

void Gun::setModel(std::string model)
{
    this->gunModel.append(model);
}

void Gun::setPosition(Vector3 position)
{
    this->position = position;
}

void Gun::setTexture(Texture texture)
{
    this->gunTexture = texture;
}