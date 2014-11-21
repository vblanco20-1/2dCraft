#include "PlayerController.h"
#include "DebugDraw.h"
#include "PhysicsUtilities.h"
#include "Creature.h"
void PlayerController::ProcessInput(float DeltaTime)
{
	sf::Vector2i Mousepos = sf::Mouse::getPosition(*myWindow);
	Vector2f mouseloc(Mousepos.x, Mousepos.y);
	mouseloc += myView->getCenter() - myView->getSize() / 2.f;

	if (PhysicsUtilities::isPointBlocked(World, mouseloc))
	{
		DebugDraw::GetInstance()->DrawDebugCircle(mouseloc, 5, sf::Color::Red);
	}
	else
	{
		DebugDraw::GetInstance()->DrawDebugCircle(mouseloc, 5, sf::Color::Blue);
	}

	
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
	

	if (linestart.x != 0 && lineend.x != 0)
	{
		PhysicsUtilities::simpleRaycast(World, linestart, lineend);

		DebugDraw::GetInstance()->DrawDebugCircle(linestart, 5, sf::Color::Green);
		DebugDraw::GetInstance()->DrawDebugCircle(lineend, 5, sf::Color::Cyan);
	}

	if (myCreature != nullptr)
	{

		Vector2f newVel = myCreature->getVelocity();
		if (sf::Keyboard::isKeyPressed(Keyboard::W))
		{
			newVel.y = -100;
		}
		if (sf::Keyboard::isKeyPressed(Keyboard::S))
		{
			newVel.y = 100;
		}
		if (sf::Keyboard::isKeyPressed(Keyboard::A))
		{
			newVel.x = -100;
		}
		if (sf::Keyboard::isKeyPressed(Keyboard::D))
		{
			newVel.x = 100;
		}
		myCreature->setVelocity(newVel);



		myCreature->update(DeltaTime);

	
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
	sf::Vector2i Mousepos = sf::Mouse::getPosition(*myWindow);
	Vector2f mouseloc(Mousepos.x, Mousepos.y);
	mouseloc += myView->getCenter() - myView->getSize() / 2.f;
	if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Button::Right)
	{
		

		if (!start)
		{
			lineend = mouseloc;
			start = !start;
		}
		else
		{
			start = !start;
			linestart = mouseloc;
		}
	}

	if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Button::Middle)
	{
		if (!PhysicsUtilities::isPointBlocked(World,mouseloc))
		{
			if (myCreature != nullptr)
			{
				delete myCreature;
			}

			myCreature = new Creature(mouseloc, World);

		}
	}
}

PlayerController::PlayerController(GameWorld* world, Window*window, View* view)
{
	myCreature = nullptr;
	start = false;
	World = world;
	myWindow = window;
	myView = view;
}
