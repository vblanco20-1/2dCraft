#include "PlayerController.h"

void PlayerController::ProcessInput(float DeltaTime)
{
	sf::Vector2i Mousepos = sf::Mouse::getPosition(*myWindow);
	Vector2f mouseloc(Mousepos.x, Mousepos.y);
	mouseloc += myView->getCenter() - myView->getSize() / 2.f;


	//std::cout << "x: " << mouseloc.x << " y: " << mouseloc.y << std::endl;
	if (sf::Mouse::isButtonPressed(Mouse::Left))
	{
		Chunk * chosenchunk = World->getChunk(mouseloc);

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
}

void PlayerController::ChangeTile(Vector2f Coords, ETileType::Type type)
{

}

void PlayerController::ProcessInputEvent(Event event)
{
	
	if (event.type == sf::Event::Closed)
	{
		myWindow->close();
	}
	// catch the resize events
	if (event.type == sf::Event::Resized)
	{
		// update the view to the new size of the window
		sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
		myView->reset(visibleArea);
		//window.setView(sf::View(visibleArea));
	}
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Left)
		{
			myView->move(30.f, 0.f);
		}
		else if (event.key.code == sf::Keyboard::Right)
		{
			myView->move(-30.f, 0.f);
		}
		else if (event.key.code == sf::Keyboard::Space)
		{
			World->saveChunks();
		}
		else if (event.key.code == sf::Keyboard::LControl)
		{
			//World->checkChunkBounds(myView->getCenter() - Vector2f(500, 300), myView->getCenter() + Vector2f(500, 300));
		}
	}
}

PlayerController::PlayerController(GameWorld* world, Window*window, View* view)
{
	World = world;
	myWindow = window;
	myView = view;
}
