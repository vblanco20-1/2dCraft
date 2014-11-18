
#pragma once
#include "SFML/Graphics.hpp"
#include "Chunk.h"

using namespace sf;

class GameWorld :public Drawable
{
public:
	virtual void draw(RenderTarget& target, RenderStates states) const;

	virtual Chunk* getChunk(Vector2f position);

private:
	std::vector<Chunk*> chunks;
};

