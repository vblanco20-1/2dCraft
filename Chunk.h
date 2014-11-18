#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/VertexArray.hpp"
using namespace sf;

const int ChunkSize = 16;
const float TileSize = 20;
namespace ETileType
{
	enum Type
	{
		Air, Stone, Dirt
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
	virtual void generateTiles();
	virtual void regenerateVertexArray();
	virtual void setLocation(Vector2f loc);
private:

	Vector2f Location;
	
	Tile Tiles[ChunkSize][ChunkSize];

	VertexArray Vertices;

};

