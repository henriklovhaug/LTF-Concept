/*TODO: Create collision take takes in (object,object) and (object,player)
these two can be the same, but could be beneficial to keep them seperate*/
#pragma once
#include <raylib.h>
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
}