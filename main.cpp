#include <SFML/Graphics.hpp>
#include "Chunk.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1000, 600), "SFML works!");
	sf::CircleShape shape(100.f);
	

	std::vector<Chunk*> chunks;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			Chunk *newChunk = new Chunk();
			newChunk->setLocation(sf::Vector2f(i*ChunkSize*TileSize, j*ChunkSize*TileSize));
			newChunk->generateTiles();
			chunks.push_back(newChunk);
		}
	}
	
	
	shape.setFillColor(sf::Color::Green);

	sf::View view(sf::FloatRect(0, 0, 1000, 600));
	
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Left)
				{
					view.move(30.f, 0.f);
				}
				else if (event.key.code == sf::Keyboard::Right)
				{
					view.move(-30.f, 0.f);
				}
			}
		}

		window.setView(view);
		window.clear();
		//window.draw(shape);
		for (auto chunk : chunks)
		{
			window.draw(*chunk);
		}
		window.display();
	}

	return 0;
}