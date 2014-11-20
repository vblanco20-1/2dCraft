#pragma once
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/VertexArray.hpp"
using namespace sf;

const int ChunkSize = 16;
const float TileSize = 20;
namespace ETileType
{
	enum Type
	{
		Air, Stone, Dirt,Grass, null
	};
}

struct Tile
{
	ETileType::Type Type;
};


class Chunk : public Drawable
{
public:

	virtual void draw(RenderTarget& target, RenderStates states) const;

	//use random generation to create the tiles
	virtual void generateTiles();
	// reload the vertex array for drawing
	virtual void regenerateVertexArray();
	
	
	//try to load from a file
	virtual bool load(int x, int y, bool bForceRebuild);

	//save the chunk to a file
	virtual void save();

	//clear the chunk
	virtual void clear();


	//virtual void setLocation(Vector2f loc);
	virtual Vector2f getLocation(){ return Location; }
	virtual void setTileType(int x, int y, ETileType::Type type);
	virtual ETileType::Type getTileType(int x, int y);


	virtual void setChunkLoc(int x, int y);;
	virtual Vector2i getChunkLoc(){ return ChunkLoc; };

	//for physics
	float Top()   { return Location.y;                       }
	float Bottom(){ return Location.y + ChunkSize *TileSize; }
	float Left()  { return Location.x;                       }
	float Right() { return Location.x + ChunkSize *TileSize; }
private:

	Texture *TileMap;
	//coordinate in the chunk array(for save and load)
	Vector2i ChunkLoc;
	//coordinate in world space for rendering
	Vector2f Location;
	
	Tile Tiles[ChunkSize][ChunkSize];

	VertexArray Vertices;

};

