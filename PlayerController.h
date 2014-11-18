#pragma once
#include "Chunk.h"


class PlayerController
{
public:
	virtual void ProcessInput();

	virtual void ChangeTile(Vector2f Coords, ETileType::Type type);
};