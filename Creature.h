#pragma  once
#include "GameObject.h"
#include "SFML/Graphics.hpp"
#include "GameWorld.h"
using namespace sf;
class Creature : public GameObject, public Drawable
{
public:
	virtual void update(float DeltaTime);
	virtual void draw(RenderTarget& target, RenderStates states) const;
	Creature(Vector2f startLocation, GameWorld *theWorld);


	virtual void setVelocity(Vector2f newVel){ velocity = newVel; };
	virtual Vector2f getVelocity(){ return velocity; };
	virtual void setPosition(Vector2f newPos){ position = newPos; };
	virtual Vector2f getPosition(){ return position; };

private:
	Vector2f velocity;
	Vector2f position;
	GameWorld *World;
	CircleShape myCircle;
};