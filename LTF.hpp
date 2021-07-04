/*TODO: Create collision take takes in (object,object) and (object,player)
these two can be the same, but could be beneficial to keep them seperate*/

/* TODO: need collision for infinitely thin walls*/

#pragma once
#include <raylib.h>
#include <raymath.h>
#include "collisionObject.hpp"
#include <vector>
#include "player.hpp"
/**
 * @brief Only use LTF in main
 * 
 */
namespace LTF
{
#pragma region collision
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
        return object.getBox().min.x < player.getPositionX() &&
               object.getBox().min.y < player.getPositionY() &&
               object.getBox().min.z < player.getPositionZ() &&
               player.getPositionX() < object.getBox().max.x &&
               player.getPositionY() < object.getBox().max.y &&
               player.getPositionZ() < object.getBox().max.z;
    }

    bool collision(CollisionObject object, Vector3 player)
    {
        return object.getBox().min.x < player.x &&
               object.getBox().min.y < player.y &&
               object.getBox().min.z < player.z &&
               player.x < object.getBox().max.x &&
               player.y < object.getBox().max.y &&
               player.z < object.getBox().max.z;
    }

    bool collision(std::vector<CollisionObject> list, Player player, int direction)
    {
        for (CollisionObject obj : list)
        {
            if (collision(obj, player.getNextPosition(direction)))
                return true;
        }
        return false;
    }
    bool collision(std::vector<CollisionObject> list, Player player, float deltatime)
    {
        for (CollisionObject obj : list)
        {
            if (collision(obj, player.getNextGravityVector(deltatime)))
                return true;
        }
        return false;
    }
#pragma endregion

    /**
     * @brief Projects vector one onto plane created by vector two and three
     * 
     * @param v1 Vector one
     * @param v2b Vector two
     * @param v3b Vector three
     * @return Projected vector
     */
    Vector3 projection(Vector3 v1, Vector3 v2b, Vector3 v3b)
    {
        if (Vector3DotProduct(v2b, v3b) == 0)
        {
            return Vector3Add(Vector3Scale(v2b, Vector3DotProduct(v1, v2b) / Vector3DotProduct(v2b, v2b)),
                              Vector3Scale(v3b, Vector3DotProduct(v1, v3b) / Vector3DotProduct(v3b, v3b)));
        }
        else
        {
            return {0, 0, 0};
        }
    }
    /**
     * @brief Calculates angle between two vectors
     * 
     * @param v1 Vector one
     * @param v2 Vector two
     * @return Angle in degrees. Use DEG2RAD to convert back
     */
    float Vector3Angle(Vector3 v1, Vector3 v2)
    {
        return acosf(Vector3DotProduct(v1, v2) / (Vector3Length(v1) * Vector3Length(v2))) * RAD2DEG;
    }

}