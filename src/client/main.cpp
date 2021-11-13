#include <iostream>

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string.h>



#include <tmx/MapLoader.hpp>
#include <sstream>


// Fin test SFML

#include  <state.h>

using namespace std;
using namespace state;


void clientTest(void){
    Exemple exemple;
    exemple.setX(53);
    //MapLoader::MapLoader("res/map");
    cout << "It works !" << endl;
}



void testSFML() {
    sf::Texture texture;
    if (!texture.loadFromFile("../../res/synthetic grass/ground_grass_gen_07.png"))
    {
        // error...
    }

    sf::Sprite sprite;
    sprite.setTexture(texture);
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    window.draw(sprite);
}





void renderTest(void){
    //create map loader and load map
	tmx::MapLoader ml("/home/mkas/ENSEA/test/karadagkanelouis/res/map/");
	ml.load("map_1.tmx");
	
	sf::RenderWindow renderWindow(sf::VideoMode(2000u, 600u), "TMX Loader");
	renderWindow.setVerticalSyncEnabled(true);

	//adjust the view to centre on map
	sf::View view = renderWindow.getView();
	view.zoom(3.0f);
	view.setCenter(1024.0f, 2000.0f);
	renderWindow.setView(view);


	//to toggle debug output
	bool debug = false;

	//-----------------------------------//

	while(renderWindow.isOpen())
	{
		//poll input
		sf::Event event;
		while(renderWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				renderWindow.close();
			if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::D)
				debug = !debug;
        }


		//draw map
		renderWindow.clear();
		renderWindow.draw(ml);
		if(debug)ml.drawLayer(renderWindow, tmx::MapLayer::Debug);
		renderWindow.display();


		//print mouse coords to orthographic (screen) coords and world (isometric) coords
		sf::Vector2f mousePosScreen = renderWindow.mapPixelToCoords(sf::Mouse::getPosition(renderWindow));
		sf::Vector2f mousePosWorld = ml.orthogonalToIsometric(mousePosScreen);

		std::stringstream stream;
		stream << "Mouse Position: "<< mousePosScreen.x << ", " << mousePosScreen.y << " World Position: " << mousePosWorld.x << ", " << mousePosWorld.y;

		renderWindow.setTitle(stream.str());
		
	}
}





int main(int argc,char* argv[])
{
    if(argc < 2){
        std::cout << "It works ! " << std::endl;
        return 0;
    }

    if(strcmp(argv[1], "client") == 0){
        clientTest();
    }else if(strcmp(argv[1], "render") == 0){
        renderTest();
    }
    else{
        std::cout << "Expected one argument like 'client' or 'render'" << std::endl;
    }

    return 0;

}
