/*TODO: Create collision take takes in (object,object) and (object,player)
these two can be the same, but could be beneficial to keep them seperate*/

/* TODO: need collision for infinitely thin walls*/

#include <raylib.h>
#include "collisionObject.hpp"

#pragma once
namespace LTF
{

    bool collision(BoundingBox box, Vector3 positionBox, Vector3 center, float radius)
    {
        bool collision = false;

        float dmin = 0;

        if (positionBox.x - center.x < box.min.x)
            dmin += powf(center.x - box.min.x, 2);
        else if (positionBox.x - center.x > box.max.x)
            dmin += powf(center.x - box.max.x, 2);

        if (positionBox.y - center.y < box.min.y)
            dmin += powf(center.y - box.min.y, 2);
        else if (positionBox.y - center.y > box.max.y)
            dmin += powf(center.y - box.max.y, 2);

        if (positionBox.z - center.z < box.min.z)
            dmin += powf(center.z - box.min.z, 2);
        else if (positionBox.z - center.z > box.max.z)
            dmin += powf(center.z - box.max.z, 2);

        if (dmin <= (radius * radius))
            collision = true;

        return collision;
    }
    //TODO: handle player mesh instead of player point
    bool collision(CollisionObject object, Player player)
    {
        return object.getBox().min.x + object.getPosition().x < player.getPositionX() &&
               object.getBox().min.y + object.getPosition().y < player.getPositionY() &&
               object.getBox().min.z + object.getPosition().z < player.getPositionZ() &&
               player.getPositionX() < object.getBox().max.x + object.getPosition().x &&
               player.getPositionY() < object.getBox().max.y + object.getPosition().y &&
               player.getPositionZ() < object.getBox().max.z + object.getPosition().z;
    }
}