
#pragma once
#include "SFML/Graphics.hpp"
#include "Chunk.h"

using namespace sf;
class GameObject;
class GameWorld :public Drawable
{
public:
	virtual void draw(RenderTarget& target, RenderStates states) const;

	virtual void update(float DeltaTime);

	virtual void checkChunkBounds(Vector2f topleft, Vector2f botright);

	virtual void createChunks(int sizex, int sizey);

	virtual Chunk* getChunk(Vector2f position) const ;
	virtual Chunk* getChunkFromCoords(int x, int y) const;
	virtual bool saveChunks();


	

private:

	int leftChunk;
	int rightChunk;
	int topChunk;
	int botChunk;

	Vector2f TerrainCenter;


	std::vector<Chunk*> Chunks;
	std::vector<GameObject*> GameObjects;
};

