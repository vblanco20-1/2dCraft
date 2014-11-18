#include "GameWorld.h"

void GameWorld::draw(RenderTarget& target, RenderStates states) const
{
	//draw the tiles
	for (auto chunk : chunks)
	{
		target.draw(*chunk);
	}
}
