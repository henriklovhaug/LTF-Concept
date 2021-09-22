#include "gun.hpp"
#include <string>

void Gun::setName(char *name)
{
    strcpy_s(this->gunName, name);
}

void Gun::setDamage(float damage)
{
    this->damage = damage;
}

void Gun::setPosition(Vector3 position)
{
    this->position = position;
}

void Gun::setTexture(Texture texture)
{
    this->gunTexture = texture;
}

Gun::Gun(char *name, Vector3 position, float damage) {
    this->setName(name);
    this->setDamage(damage);
    this->setPosition(position);
}