#include "Chunk.h"
#include "SFML/Graphics/RenderTarget.hpp"
#include <iostream>
#include "simplex.hpp"
#include <fstream>
#include <string>
#include <sstream>

using namespace std;
void Chunk::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(Vertices, states);
}

void Chunk::generateTiles()
{
	Simplex simplex;
	simplex.init();
	for (int x = 0; x< ChunkSize; x++)
	{
		for (int y = 0; y < ChunkSize; y++)
		{
			float Xnoise = x + Location.x/10;// / (TileSize*ChunkSize);
			float Ynoise = y + Location.y/10;// / (TileSize*ChunkSize);
			float Density = simplex.noise(Xnoise, Ynoise);//+ Location.x/(TileSize*ChunkSize), y*TileSize + Location.y);
			//std::cout << Density << "-" << Xnoise << "-" << Ynoise << std::endl;
			Density += (Ynoise*0.2)-2;

			if (Density> 0.7)
			{
				Tiles[x][y].Type = ETileType::Stone;
			}
			else if (Density > 0.3)
			{
				Tiles[x][y].Type = ETileType::Dirt;
			}
			else
			{
				Tiles[x][y].Type = ETileType::Air;
			}
			//Tiles[x][y].Type = ETileType::Type((x*y) % 3);
		}
	}
	regenerateVertexArray();
}

void Chunk::regenerateVertexArray()
{
	Vertices.resize(ChunkSize*ChunkSize * 4);
	Vertices.setPrimitiveType(PrimitiveType::Quads);
	
	for (int x = 0; x < ChunkSize; x++)
	{
		for (int y = 0; y < ChunkSize; y++)
		{
			Vector2f A, B, C, D;

			A.x = x*TileSize;
			A.y = y*TileSize;
			A += Location;

			B.x = (x+1)*TileSize;
			B.y = y*TileSize;
			B += Location;

			C.x = x*TileSize;
			C.y = (y + 1)*TileSize;
			C += Location;

			D.x = (x + 1)*TileSize;
			D.y = (y+1)*TileSize;
			D += Location;

			Color VertColor;
			switch (Tiles[x][y].Type)
			{
			case ETileType::Air:
				VertColor = Color::Cyan;
				break;
			case ETileType::Dirt:
				VertColor.r = 133;
				VertColor.g = 65;
				VertColor.b = 35;
				break;
			case ETileType::Stone:
				VertColor.r = 100;
				VertColor.g = 100;
				VertColor.b = 100;
				break;
			default:
				VertColor = Color::Red;
			}

			sf::Vertex* quad = &Vertices[(y + x * ChunkSize) * 4];

			quad[0] = Vertex(A, VertColor);
			quad[1] = Vertex(B, VertColor);
			quad[2] = Vertex(D, VertColor);
			quad[3] = Vertex(C, VertColor);			
		}
	}	
}

//void Chunk::setLocation(Vector2f loc)
//{
//	Location = loc;
//	regenerateVertexArray();
//}

void Chunk::setTileType(int x, int y, ETileType::Type type)
{
	if (x < ChunkSize && y < ChunkSize && x >= 0 && y >= 0)
	{
		if (Tiles[x][y].Type != type)
		{
			Tiles[x][y].Type = type;
			regenerateVertexArray();
		}
	}
	else
	{
		std::cout << " invalid coordinates "<< std::endl;
	}
}

bool Chunk::load(int x, int y)
{

	setChunkLoc(x, y);
	stringstream ss;

	ss << "Saves/chunk" << x << "-" << y << ".cnk";
	string filename = ss.str();

	ifstream file;
	file.open(filename);

	if (file.is_open())
	{
		for (int x = 0; x < ChunkSize; x++)
		{
			for (int y = 0; y < ChunkSize; y++)
			{
				int type;
				file >> type;
				Tiles[x][y].Type = ETileType::Type(type);
			}
			//file << endl;
		}

		regenerateVertexArray();
	}
	else
	{
		generateTiles();
	}

	setChunkLoc(x, y);
	return true;
}

void Chunk::save()
{
	stringstream ss;

	ss << "Saves/chunk" << ChunkLoc.x << "-" << ChunkLoc.y << ".cnk";
	string filename = ss.str();

	ofstream file;
	file.open(filename);
	if (file.is_open())
	{
		for (int x = 0; x < ChunkSize; x++)
		{
			for (int y = 0; y < ChunkSize; y++)
			{
				file << Tiles[x][y].Type << " ";
			}
			file << endl;
		}
	}
	file.close();
}

void Chunk::clear()
{
	for (int x = 0; x < ChunkSize; x++)
	{
		for (int y = 0; y < ChunkSize; y++)
		{
			Tiles[x][y].Type = ETileType::Air;
		}
	}

	setChunkLoc(0, 0);
}

void Chunk::setChunkLoc(int x, int y)
{
	ChunkLoc.x = x; ChunkLoc.y = y;

	Location.x = x*ChunkSize*TileSize;
	Location.y = y*ChunkSize*TileSize;

	regenerateVertexArray();
}
