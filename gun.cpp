#include "gun.hpp"
#include <string>

void Gun::setName(char* name)
{
    strcpy_s(this->gunName, name);
}

void Gun::setDamage(float damage)
{
    this->damage = damage;
}



