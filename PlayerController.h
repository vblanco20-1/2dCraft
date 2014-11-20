#pragma once

#include "GameWorld.h"
#include "Creature.h"

class PlayerController
{
public:
	virtual void ProcessInput(float DeltaTime);

	virtual void ProcessInputEvent(Event event);

	virtual void ChangeTile(Vector2f Coords, ETileType::Type type);

	PlayerController(GameWorld* world, Window*window, View* view);

	Creature * myCreature;

private:
	Vector2f linestart;
	Vector2f lineend;
	bool start;

	GameWorld* World;
	Window*myWindow;
	View* myView;
};