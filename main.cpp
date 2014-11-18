#include <SFML/Graphics.hpp>
#include "Chunk.h"
#include <iostream>



int main()
{
	sf::RenderWindow window(sf::VideoMode(1000, 600), "SFML works!");
	sf::CircleShape shape(10.f);	
	
	std::vector<Chunk*> chunks;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
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
			{
				window.close();
			}
			// catch the resize events
			if (event.type == sf::Event::Resized)
			{
				// update the view to the new size of the window
				sf::FloatRect visibleArea(0,0, event.size.width, event.size.height);
				view.reset(visibleArea);
				//window.setView(sf::View(visibleArea));
			}
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

		if (sf::Mouse::isButtonPressed(Mouse::Left))
		{
			Vector2f mouseloc(Mouse::getPosition(window).x, Mouse::getPosition(window).y);

			Chunk * chosenchunk = nullptr;
			for (auto chunk : chunks)
			{
				//y axis
				if (chunk->Top() < mouseloc.y && chunk->Bottom() > mouseloc.y)
				{
					// x axis
					if (chunk->Left() < mouseloc.x && chunk->Right() > mouseloc.x)
					{

						chosenchunk = chunk;
						break;
					}
				}
			}


			if (chosenchunk)
			{
				float realx = mouseloc.x - chosenchunk->getLocation().x;
				float realy = mouseloc.y - chosenchunk->getLocation().y;

				int finalx = (realx / TileSize);
				int finaly = (realy / TileSize);
				chosenchunk->setTileType(finalx, finaly, ETileType::Air);
				//std::cout << "x: " << finalx << " y: " << finaly << std::endl;
			}
		}
		else if (sf::Mouse::isButtonPressed(Mouse::Right))
		{
			Vector2f mouseloc(Mouse::getPosition(window).x, Mouse::getPosition(window).y);

			Chunk * chosenchunk = nullptr;
			for (auto chunk : chunks)
			{
				//y axis
				if (chunk->Top() < mouseloc.y && chunk->Bottom() > mouseloc.y)
				{
					// x axis
					if (chunk->Left() < mouseloc.x && chunk->Right() > mouseloc.x)
					{

						chosenchunk = chunk;
						break;
					}
				}
			}


			if (chosenchunk)
			{
				float realx = mouseloc.x - chosenchunk->getLocation().x;
				float realy = mouseloc.y - chosenchunk->getLocation().y;

				int finalx = (realx / TileSize);
				int finaly = (realy / TileSize);
				chosenchunk->setTileType(finalx, finaly, ETileType::Dirt);
				//std::cout << "x: " << finalx << " y: " << finaly << std::endl;
			}
		}
		Vector2f mouseloc(Mouse::getPosition(window).x, Mouse::getPosition(window).y);



		shape.setPosition(Mouse::getPosition(window).x, Mouse::getPosition(window).y);

		window.setView(view);
		window.clear();
		
		for (auto chunk : chunks)
		{
			window.draw(*chunk);
		}
		//window.draw(selectionrect);
		//window.draw(shape);
		window.display();
	}

	return 0;
}