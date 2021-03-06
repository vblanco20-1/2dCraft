#include <SFML/Graphics.hpp>
#include "Chunk.h"
#include <iostream>

#include "GameWorld.h"
#include "PlayerController.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1000, 600), "SFML works!");

	
	GameWorld World;
	World.createChunks(6, 2);

	
	
	

	sf::View view(sf::FloatRect(0, 0, 1000, 600));
	sf::View zoomedview(sf::FloatRect( 0,-0, 1000, 600));

	PlayerController Controller = PlayerController(&World, &window, &view);
	window.setFramerateLimit(60);
	double frametime = 1.f / 60.f;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			Controller.ProcessInputEvent(event);
		}

		Controller.ProcessInput(frametime);		
		
		World.checkChunkBounds(view.getCenter() - Vector2f(500, 300), view.getCenter() + Vector2f(500, 300));
		window.setView(view);
		window.clear(Color(95, 184, 213));
		
		window.draw(World);
		if (Controller.myCreature != nullptr)
		{
			window.draw(*Controller.myCreature);
		}
		
		window.display();
	}

	return 0;
}