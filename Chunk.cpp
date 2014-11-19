#include "Chunk.h"
#include "SFML/Graphics/RenderTarget.hpp"
#include <iostream>

#include <fstream>
#include <string>
#include <sstream>
#include "ResourceManager.h"
#include "noise/noise.h"
#include <cmath>
using namespace std;
void Chunk::draw(RenderTarget& target, RenderStates states) const
{
	states.texture = TileMap;
	target.draw(Vertices, states);
}

void Chunk::generateTiles()
{
	//uwotm8
	noise::module::Perlin PerlinNoise = noise::module::Perlin::Perlin();

	//PerlinNoise.SetSeed(0);
	PerlinNoise.SetOctaveCount(2);
	//PerlinNoise.SetFrequency(10);
	double value = PerlinNoise.GetValue(1.25, 0.75, 0.50);
	
	for (int x = 0; x< ChunkSize; x++)
	{
		bool TopLayer = false;
		for (int y = 0; y < ChunkSize; y++)
		{
			float Xnoise = x + Location.x/TileSize;
			float Ynoise = y + Location.y/TileSize;

			//this shit creates mountains
			float Density = PerlinNoise.GetValue(Xnoise/10, Ynoise/10, 0);			
			Density += (Ynoise/5)-1.5;
		
			if (Density > 1)
			{
				Density = 1;
				//add holes as caves

				float val = PerlinNoise.GetValue(Xnoise / 10, Ynoise / 10, 3.4);
				//val -= Density/10;
				if (val > 0.5)
				{
				Density = 0;
				}
				else
				{
					Density -= val;
				}
			//	Density -= val*1.2;
			}
			


			//std::cout << Density << "-" << Xnoise << "-" << Ynoise << std::endl;
			if (Density> 0.7)
			{
				Tiles[x][y].Type = ETileType::Stone;
			}
			else if (Density > 0.1)
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

	TileMap = ResourceManager::GetInstance()->GetTexture( "Resources/Tiles.png");

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

			//texture coords
			Vector2f tA, tB, tC, tD;

			switch (Tiles[x][y].Type)
			{
			case ETileType::Air:
				//VertColor = Color::Cyan;
				tA = Vector2f(0, 32);
				tB = Vector2f(32, 32);
				tC = Vector2f(32, 64);
				tD = Vector2f(0, 64);

				break;
			case ETileType::Dirt:
				//VertColor.r = 133;
				//VertColor.g = 65;
				//VertColor.b = 35;

				tA = Vector2f(0, 0);
				tB = Vector2f(32, 0);
				tC = Vector2f(32, 32);
				tD = Vector2f(0, 32);
				break;
			case ETileType::Stone:
				//VertColor.r = 100;
				//VertColor.g = 100;
				//VertColor.b = 100;

				tA = Vector2f(32, 0);
				tB = Vector2f(64, 0);
				tC = Vector2f(64, 32);
				tD = Vector2f(32, 32);
				break;


			case ETileType::Grass:
				tA = Vector2f(32, 32);
				tB = Vector2f(64, 32);
				tC = Vector2f(64, 64);
				tD = Vector2f(32, 64);
				break;
			default:
				VertColor = Color::Red;
			}
		//	VertColor = Color::White;
			sf::Vertex* quad = &Vertices[(y + x * ChunkSize) * 4];

			quad[0] = Vertex(A,tA);
			quad[1] = Vertex(B,tB);
			quad[2] = Vertex(D, tC);
			quad[3] = Vertex(C,tD);
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

bool Chunk::load(int x, int y, bool bForceRebuild)
{

	setChunkLoc(x, y);

	if (!bForceRebuild)
	{
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
	}
	else
	{
		generateTiles();
	}

	//setChunkLoc(x, y);
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
