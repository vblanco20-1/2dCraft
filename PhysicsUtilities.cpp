#include "PhysicsUtilities.h"
#include "GameWorld.h"
#include "DebugDraw.h"
bool PhysicsUtilities::isPointBlocked(const GameWorld* World, Vector2f point)
{
	Chunk * chosenchunk = World->getChunk(point);

	if (chosenchunk)
	{
		float realx = point.x - chosenchunk->getLocation().x;
		float realy = point.y - chosenchunk->getLocation().y;

		int finalx = (realx / TileSize);
		int finaly = (realy / TileSize);
		if (chosenchunk->getTileType(finalx, finaly) != ETileType::Air)
		{
			return true;
		}	
	
	}
	return false;
}

sf::Vector2f PhysicsUtilities::simpleRaycast(const GameWorld* World, Vector2f start, Vector2f end)
{
	//for the love of god, do this right, this is lame as hell
	DebugDraw::GetInstance()->DrawDebugCircle(start, 5, Color::Red);
	DebugDraw::GetInstance()->DrawDebugCircle(end, 5, Color::Red);
	for (int i = 0; i < 40; i++)
	{
		Vector2f toend = start - end;
		float Alpha =float(i) /40.f;
		toend *= Alpha;
		Vector2f finalpos = start - toend;
		

		if (isPointBlocked(World, finalpos))
		{
			DebugDraw::GetInstance()->DrawDebugCircle(finalpos, 5, Color::White);
			return finalpos;
		}
		else
		{
			DebugDraw::GetInstance()->DrawDebugCircle(finalpos, 5, Color::Black);
		}
	}

	return Vector2f(0, 0);
}
