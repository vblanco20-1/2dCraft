
#pragma once

#include "SFML/System/Vector2.hpp"

using namespace sf;
struct AABB
{
	Vector2f Center;
	Vector2f Size;

	AABB(Vector2f center, Vector2f size) : Center(center), Size(size){};
};

struct SimpleCircle
{
	Vector2f Center;
	float Radius;

	SimpleCircle(Vector2f center, float radius) : Center(center), Radius(radius){};
};

class GameWorld;
//class made of helper static methods for physics detection, all static so they can accesed from anywhere, C style, a few will be reusable for later projects
class PhysicsUtilities
{
public:
	

	// check a line beetween 2 points, return hit point or nothing
	static Vector2f simpleRaycast(const GameWorld* World ,Vector2f start, Vector2f end);

	// check if that point is inside a solid surface or not, return true if the point is inside a solid tile
	static bool isPointBlocked(const GameWorld* World,Vector2f point);

	//check if a box is blocked by a solid surface, the box is defined by the center and the size
	static bool isBoxBlocked(const GameWorld* World,Vector2f center, Vector2f size);
	static bool isBoxBlocked(const GameWorld* World,AABB box);

	//check a circle moving alone a line, capsule raycast, returns the hit point
	static Vector2f circleSweep(const GameWorld* World,Vector2f start, Vector2f end, float radius);
	static Vector2f circleSweep(const GameWorld* World, Vector2f start, SimpleCircle circle);

	//check a box moving along a line, returns the hit point
	static Vector2f boxSweep(const GameWorld* World,Vector2f start, Vector2f end, Vector2f size);
	static Vector2f boxSweep(const GameWorld* World, Vector2f start, Vector2f end, AABB box);


	//check a box to other box, return true if the boxes overlap
	static bool boxIntersection(Vector2f centerA, Vector2f sizeA, Vector2f centerB, Vector2f sizeB);
	static bool boxIntersection(AABB boxA, AABB boxB);

	//check a circle to other circle, return true if they overlap
	static bool circleIntersection(Vector2f centerA, Vector2f centerB, float radiusA, float radiusB);
	static bool circleIntersection(SimpleCircle circleA, SimpleCircle circleB);
	
};