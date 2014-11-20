#include "Creature.h"
#include "PhysicsUtilities.h"
#include <iostream>
using namespace std;
void Creature::update(float DeltaTime)
{
	velocity.y += 98*DeltaTime;
	Vector2f newPos = position + velocity*DeltaTime;
	
	Vector2f rayCast = PhysicsUtilities::simpleRaycast(World, position, newPos);
	if (rayCast.x != 0)
	{
		setVelocity(Vector2f(0, 0));
		return; newPos = rayCast;
	}
	

	position = newPos;
	cout << "creaturepos = " << position.x << "--"<< position.y << endl;


	myCircle.setPosition(position);
}

void Creature::draw(RenderTarget& target, RenderStates states) const
{
	

	target.draw(myCircle);
}

Creature::Creature(Vector2f startLocation, GameWorld *theWorld)
{
	myCircle = CircleShape(10);
	myCircle.setOrigin(Vector2f(10, 10));
	myCircle.setPosition(startLocation);
	position = startLocation;
	velocity.x = 0;
	velocity.y = 0;
	World = theWorld;
}
