#include "DebugDraw.h"


DebugDraw * DebugDraw::Instance = nullptr;

DebugDraw * DebugDraw::GetInstance()
{
	if (Instance == nullptr)
	{
		Instance = new DebugDraw();
	}

	return Instance;
}

void DebugDraw::draw(RenderTarget& target, RenderStates states) const
{
	Drawable* obj = nullptr;
	for (int i = 0; i < MAX_DEBUG_OBJECTS; i++)
	{
		obj = DrawObjects[i];
		if (obj != nullptr)
		{
			target.draw(*obj, states);
			//DrawObjects[i] = nullptr;
			//delete obj;
			
		}
	}	
	
}

void DebugDraw::DrawDebugLine(Vector2f Start, Vector2f end, Color color)
{
	
}

void DebugDraw::DrawDebugCircle(Vector2f Center, float radius, Color color)
{
	CircleShape * shape = new CircleShape(radius);
	shape->setOrigin(Vector2f(radius, radius));
	shape->setPosition(Center);
	shape->setFillColor(color); 
	if (DrawObjectsNum < MAX_DEBUG_OBJECTS)
	{
		DrawObjects[DrawObjectsNum] = shape;
		DrawObjectsNum++;
	}
	
}

DebugDraw::DebugDraw()
{
	for (int i = 0; i < MAX_DEBUG_OBJECTS; i++)
	{
		DrawObjects[i] = nullptr;
	}
	DrawObjectsNum = 0;
}

void DebugDraw::clearArray()
{
	Drawable* obj = nullptr;
	for (int i = 0; i < MAX_DEBUG_OBJECTS; i++)
	{
		obj = DrawObjects[i];
		if (obj != nullptr)
		{
			//target.draw(*obj, states);
			DrawObjects[i] = nullptr;
			delete obj;
			obj = nullptr;

		}
	}

	DrawObjectsNum = 0;
}
