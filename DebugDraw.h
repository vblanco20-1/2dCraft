#pragma once
#include "SFML/Graphics.hpp"
#include <vector>
using namespace sf;

const unsigned int MAX_DEBUG_OBJECTS = 200;
class DebugDraw : public Drawable
{
public:
	virtual void DrawDebugCircle(Vector2f Center, float radius, Color color);
	virtual void DrawDebugLine(Vector2f Start, Vector2f end, Color color);

	virtual void draw(RenderTarget& target, RenderStates states) const;
	virtual void clearArray();
	static  DebugDraw * GetInstance();

private:
	DebugDraw();

	static DebugDraw * Instance;
	Drawable* DrawObjects[MAX_DEBUG_OBJECTS];
	int DrawObjectsNum;
};