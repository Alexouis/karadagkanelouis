

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <tmx/MapLoader.hpp>

#include <sstream>
#include <cassert>

void AddObject(tmx::MapLayer& layer, const sf::Vector2f& coords)
{
	const float width = 32.f;
	const float height = 64.f;
	
	tmx::MapObject mo;
	mo.setPosition(coords);
	mo.addPoint(sf::Vector2f());
	mo.addPoint(sf::Vector2f(width, 0.f));
	mo.addPoint(sf::Vector2f(width, height));
	mo.addPoint(sf::Vector2f(0.f, height));
	mo.createDebugShape(sf::Color::Magenta); //must always call this after adding points
											//to properly create bounding properties.

	layer.objects.push_back(mo);
}


int main()
{
	sf::RenderWindow renderWindow(sf::VideoMode(800u, 600u), "TMX Loader");
	renderWindow.setVerticalSyncEnabled(true);

	//create map loader and load map
	tmx::MapLoader ml("res/maps/");
	ml.load("addRemove.tmx");

	sf::Clock deltaClock, frameClock;

	assert(ml.getLayers().size() > 1);
	auto& objectLayer = ml.getLayers()[1];


	//-----------------------------------//

	while(renderWindow.isOpen())
	{
		//poll input
		sf::Event event;
		while(renderWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				renderWindow.close();

			if(event.type == sf::Event::KeyReleased)
			{
				switch(event.key.code)
				{
				case sf::Keyboard::Escape:
					renderWindow.close();
					break;
				case sf::Keyboard::D:
					if(objectLayer.objects.size())
					{
						//objectLayer.objects.pop_back();
						objectLayer.objects.erase(objectLayer.objects.end() - 1);
					}
					break;
				default: break;
				}
			}

			if(event.type == sf::Event::MouseButtonReleased)
			{
				switch(event.mouseButton.button)
				{
				case sf::Mouse::Left:
					{
					sf::Vector2f mousePos = renderWindow.mapPixelToCoords(sf::Mouse::getPosition(renderWindow));
					AddObject(objectLayer, mousePos);
					}
					break;
				default: break;
				}
			}
        }

		frameClock.restart();

		//draw
		renderWindow.clear();
		renderWindow.draw(ml);
		ml.drawLayer(renderWindow, tmx::MapLayer::Debug);
		renderWindow.display();

		const float time = 1.f / frameClock.getElapsedTime().asSeconds();
		std::stringstream stream;
		stream << "Click mouse to add or D to remove. Current fps: " << time << std::endl;
		renderWindow.setTitle(stream.str());
	}

	return 0;
}