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
            if (collision(obj, Vector3Subtract(player.getNextGravityVector(deltatime),player.getUp())))
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


//gathered from https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm and raylib's src/models.c
    RayHitInfo GetRayCollisionTriangle(Ray ray, Vector3 p1, Vector3 p2, Vector3 p3)
    {
#define EPSILON 0.000001 // A small number

        RayHitInfo collision = {0};
        Vector3 edge1 = {0};
        Vector3 edge2 = {0};
        Vector3 p, q, tv;
        float det, invDet, u, v, t;

        // Find vectors for two edges sharing V1
        edge1 = Vector3Subtract(p2, p1);
        edge2 = Vector3Subtract(p3, p1);

        // Begin calculating determinant - also used to calculate u parameter
        p = Vector3CrossProduct(ray.direction, edge2);

        // If determinant is near zero, ray lies in plane of triangle or ray is parallel to plane of triangle
        det = Vector3DotProduct(edge1, p);

        // Avoid culling!
        if ((det > -EPSILON) && (det < EPSILON))
            return collision;

        invDet = 1.0f / det;

        // Calculate distance from V1 to ray origin
        tv = Vector3Subtract(ray.position, p1);

        // Calculate u parameter and test bound
        u = Vector3DotProduct(tv, p) * invDet;

        // The intersection lies outside of the triangle
        if ((u < 0.0f) || (u > 1.0f))
            return collision;

        // Prepare to test v parameter
        q = Vector3CrossProduct(tv, edge1);

        // Calculate V parameter and test bound
        v = Vector3DotProduct(ray.direction, q) * invDet;

        // The intersection lies outside of the triangle
        if ((v < 0.0f) || ((u + v) > 1.0f))
            return collision;

        t = Vector3DotProduct(edge2, q) * invDet;

        if (t > EPSILON)
        {
            // Ray hit, get hit point and normal
            collision.hit = true;
            collision.distance = t;
            collision.normal = Vector3Normalize(Vector3CrossProduct(edge1, edge2));
            collision.position = Vector3Add(ray.position, Vector3Scale(ray.direction, t));
        }

        return collision;
    }

    RayHitInfo GetRayCollisionMesh(Ray ray, Mesh mesh, Matrix transform, Vector3 position)
    {
        RayHitInfo collision = {0};


        if (mesh.vertices != NULL)
        {
            int triangleCount = mesh.triangleCount;

            // Test against all triangles in mesh
            for (int i = 0; i < triangleCount; i++)
            {
                Vector3 a, b, c;
                Vector3 *vertdata = (Vector3 *)mesh.vertices;

                if (mesh.indices)
                {
                    a = vertdata[mesh.indices[i * 3 + 0]];
                    b = vertdata[mesh.indices[i * 3 + 1]];
                    c = vertdata[mesh.indices[i * 3 + 2]];
                }
                else
                {
                    a = vertdata[i * 3 + 0];
                    b = vertdata[i * 3 + 1];
                    c = vertdata[i * 3 + 2];
                }

                a = Vector3Add(Vector3Transform(a, transform),position);
                b = Vector3Add(Vector3Transform(b, transform),position);
                c = Vector3Add(Vector3Transform(c, transform),position);

                RayHitInfo triHitInfo = GetRayCollisionTriangle(ray, a, b, c);

                if (triHitInfo.hit)
                {
                    // Save the closest hit triangle
                    if ((!collision.hit) || (collision.distance > triHitInfo.distance))
                        collision = triHitInfo;
                }
            }
        }

        return collision;
    }


    RayHitInfo GetRayCollisionModel(Ray ray, Model model, Vector3 position)
    {
        RayHitInfo collision = {0};

        for (int m = 0; m < model.meshCount; m++)
        {
            RayHitInfo meshHitInfo = GetRayCollisionMesh(ray, model.meshes[m], model.transform, position);

            if (meshHitInfo.hit)
            {
                // Save the closest hit mesh
                if ((!collision.hit) || (collision.distance > meshHitInfo.distance))
                    collision = meshHitInfo;
            }
        }

        return collision;
    }

    Ray rayTransform(Ray ray, int direction)
    {
        switch (direction)
        {
        case 1:
            return ray;
            break;
        case 2:
            ray.direction = Vector3Negate(ray.direction);
            return ray;
            break;
        case 3:
            ray.direction = Vector3Negate(Vector3Perpendicular(ray.direction));
            return ray;
            break;
        case 4:
            ray.direction = Vector3Perpendicular(ray.direction);
            return ray;
            break;
        default:
            return ray;
            break;
        }
    }

}