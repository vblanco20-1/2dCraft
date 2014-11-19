#pragma once

#include "GameWorld.h"

class PlayerController
{
public:
	virtual void ProcessInput(float DeltaTime);

	virtual void ProcessInputEvent(Event event);

	virtual void ChangeTile(Vector2f Coords, ETileType::Type type);

	PlayerController(GameWorld* world, Window*window, View* view);
private:
	GameWorld* World;
	Window*myWindow;
	View* myView;
};