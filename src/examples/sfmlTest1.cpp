/*
 * File             sfmlTest1.cpp
 * Directory        examples
 * Created Date     Monday, November 15th 2021, 10:55:29 pm
 * Author           Nouhou KANE
 * Email            nouhou.kane@ensea.fr
 * 
 * Copyright (c) 2021  ENSEA(FR)
 * __________________________________________________________________________
 */

#include <iostream>

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string.h>


#include <json/json.h>
#include <dirent.h>
#include <iostream>         

#include <tmx/MapLoader.h>
#include <sstream>


#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include <fstream>

#include <map>


// Fin test SFML


using namespace std;


float tileWidth = 519;
float tileHeight = 519;
float mapxy = 20;

sf::Vector2f orthoIso(float x, float y){
    float isox = (x - y*(tileWidth/tileHeight))/2.0;
    float isoy = (x*(tileHeight/tileWidth) + y)/2.0;
    return sf::Vector2f(isox, isoy);
}



void test1(){
    
    sf::VertexArray quad(sf::Quads, 4);

    // on le définit comme un rectangle, placé en (10, 10) et de taille 100x100
    quad[0].position = sf::Vector2f(100, 100);
    quad[1].position = orthoIso(100,0) + sf::Vector2f(100, 100);
    quad[2].position = orthoIso(100,100) + sf::Vector2f(100, 100);
    quad[3].position = orthoIso(0,100) + sf::Vector2f(100, 100);

    // et on définit la zone de texture à lui appliquer comme étant le rectangle de 25x50 démarrant en (0, 0)
    quad[0].texCoords = sf::Vector2f(0, 0);
    quad[1].texCoords = sf::Vector2f(25, 0);
    quad[2].texCoords = sf::Vector2f(25, 50);
    quad[3].texCoords = sf::Vector2f(0, 50);
    
    sf::RenderWindow renderWindow(sf::VideoMode(2000u, 600u), "TMX Loader");
	renderWindow.setVerticalSyncEnabled(true);

    bool show = false;

    while(renderWindow.isOpen())
	{
		//poll input
		sf::Event event;
		while(renderWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				renderWindow.close();
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::D)
				show = !show;
        }


		//draw map
		renderWindow.clear();
        renderWindow.draw(quad);
        renderWindow.display();
		


		//print mouse coords to orthographic (screen) coords and world (isometric) coords
		sf::Vector2f mousePosScreen = renderWindow.mapPixelToCoords(sf::Mouse::getPosition(renderWindow));

		std::stringstream stream;
		stream << "Mouse Position: "<< mousePosScreen.x << ", " << mousePosScreen.y ;

		renderWindow.setTitle(stream.str());
		
	}


}



void testSFML() {
    sf::Texture texture;
    if (!texture.loadFromFile("/home/mkas/ENSEA/karadagkanelouis/res/map/map_1.png"))
    {
        // error...
		std::cout << texture.getMaximumSize() << endl;
    }

    sf::Sprite sprite;
    sprite.setTexture(texture);
	//sprite.setPosition(0,0);
	sf::Rect<float> rect =  sprite.getLocalBounds();

	std::cout << "left = " << rect.left << ", top = " << rect.top << ", width = " << rect.width << ", height = " << rect.height << std::endl;

	sf::RenderWindow renderWindow(sf::VideoMode(2000u, 600u), "TMX Loader");
	renderWindow.setVerticalSyncEnabled(true);

	//adjust the view to centre on map
	sf::View view = renderWindow.getView();
	view.zoom(5.0f);
	view.setCenter(rect.width/2, rect.height/2);
	renderWindow.setView(view);


	//to toggle show output
	bool show = true;

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
				show = !show;
        }


		//draw map
		if(show){
			renderWindow.clear();
			renderWindow.draw(sprite);
			renderWindow.display();
		}
		


		//print mouse coords to orthographic (screen) coords and world (isometric) coords
		sf::Vector2f mousePosScreen = renderWindow.mapPixelToCoords(sf::Mouse::getPosition(renderWindow));

		std::stringstream stream;
		stream << "Mouse Position: "<< mousePosScreen.x << ", " << mousePosScreen.y ;

		renderWindow.setTitle(stream.str());
		
	}
}




void renderRenderRealMap(void){
    //create map loader and load map
	tmx::MapLoader ml("res/map/");
	ml.load("map_1.tmx");
	bool collision;
	bool visible = false;
	sf::VertexArray m_gridVertices;
	uint m_tileWidth = 519;
	uint m_tileHeight = 268;
	uint m_width = 22;
	uint m_height = 22;
	float m_tileRatio = static_cast<float>(m_tileWidth) / static_cast<float>(m_tileHeight);
	
	sf::Color debugColour(120u, 120u, 120u, 120u);
	float mapHeight = static_cast<float>(m_tileHeight * m_height);
	for(int x = 0; x <= m_width; x += 2)
	{
		float posX = static_cast<float>(x * (m_tileWidth / m_tileRatio));
		m_gridVertices.append(sf::Vertex(ml.isometricToOrthogonal(sf::Vector2f(posX, 0.f)), debugColour));
		m_gridVertices.append(sf::Vertex(ml.isometricToOrthogonal(sf::Vector2f(posX, mapHeight)), debugColour));
		posX += static_cast<float>(m_tileWidth) / m_tileRatio;
		m_gridVertices.append(sf::Vertex(ml.isometricToOrthogonal(sf::Vector2f(posX, mapHeight)), debugColour));
		m_gridVertices.append(sf::Vertex(ml.isometricToOrthogonal(sf::Vector2f(posX, 0.f)), debugColour));
		posX += static_cast<float>(m_tileWidth) / m_tileRatio;
		m_gridVertices.append(sf::Vertex(ml.isometricToOrthogonal(sf::Vector2f(posX, 0.f)), debugColour));
	}
	float mapWidth = static_cast<float>(m_tileWidth * (m_width / m_tileRatio));
	// for(int y = 0; y <= m_height; y += 2)
	// {
	// 	float posY = static_cast<float>(y *m_tileHeight);
	// 	m_gridVertices.append(sf::Vertex(ml.isometricToOrthogonal(sf::Vector2f(0.f, posY)), debugColour));
	// 	posY += static_cast<float>(m_tileHeight);
	// 	m_gridVertices.append(sf::Vertex(ml.isometricToOrthogonal(sf::Vector2f(0.f, posY)), debugColour));
	// 	m_gridVertices.append(sf::Vertex(ml.isometricToOrthogonal(sf::Vector2f(mapWidth, posY)), debugColour));
	// 	posY += static_cast<float>(m_tileHeight);
	// 	m_gridVertices.append(sf::Vertex(ml.isometricToOrthogonal(sf::Vector2f(mapWidth, posY)), debugColour));
	// }

	m_gridVertices.setPrimitiveType(sf::LinesStrip);
	// auto& layers = ml.getLayers();
	// for(auto& layer : layers)
	// {
	// 	std::cout<< layer.name << std::endl;
	// 	std::cout << "ok" << std::endl;
	// 	std::cout<<  " : " << layer.objects.size()<< std::endl;
		
	// 	for(auto& object : layer.objects)
	// 	{
	// 		std::cout<<  " : " << layer.objects.size()<< std::endl;
	// 	}
	// }

	auto& layers = ml.getLayers();
	for(auto& layer : layers)
	{
		if(layer.name == "Trees"| layer.name == "Trees_front"){
			for(const auto& object : layer.objects)
			{
				std::cout << "ok\n";
			}
		}
	}
	
	sf::RenderWindow renderWindow(sf::VideoMode(2000u, 600u), "TMX Loader");
	renderWindow.setVerticalSyncEnabled(true);

	//adjust the view to centre on map
	sf::View view = renderWindow.getView();
	view.zoom(10.0f);
	view.setCenter(1024.0f, 2000.0f);
	renderWindow.setView(view);
	


	//to toggle show output
	bool show = false;

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
				show = !show;
			
			// if(event.type == sf::Event::MouseButtonReleased)
			// {
			// 	switch(event.mouseButton.button)
			// 	{
			// 	case sf::Mouse::Left:
			// 	{
			// 		sf::Vector2f mousePos = renderWindow.mapPixelToCoords(sf::Mouse::getPosition(renderWindow));
			// 		auto& layers = ml.getLayers();
			// 		for(auto& layer : layers)
			// 		{
			// 			if(layer.name == "Trees"){
			// 				renderWindow.draw(layer);
			// 			}
			// 		}
			// 	}
			// 		break;
			// 	default: break;
			// 	}
			// }
        }


		//draw map
		renderWindow.clear();
		//renderWindow.draw(ml);
		auto& layers = ml.getLayers();
		for(auto& layer : layers)
		{
			std::cout<<layer.name << " type = " << layer.type << std::endl;
			if(layer.name == "ground"){
				
				for(auto tile = layer.tiles.begin(); tile != layer.tiles.end(); ++tile){
					renderWindow.draw(tile->sprite);
					std::cout << "ok\n";
				}
			}
		}
		renderWindow.draw(m_gridVertices);
		
		if(show)ml.drawLayer(renderWindow, 0,tmx::MapLayer::Debug);
		renderWindow.display();


		//print mouse coords to orthographic (screen) coords and world (isometric) coords
		sf::Vector2f mousePosScreen = renderWindow.mapPixelToCoords(sf::Mouse::getPosition(renderWindow));
		sf::Vector2f mousePosWorld = ml.orthogonalToIsometric(mousePosScreen);

		std::stringstream stream;
		stream << "Mouse Position: "<< mousePosScreen.x << ", " << mousePosScreen.y << " World Position: " << mousePosWorld.x << ", " << mousePosWorld.y;

		renderWindow.setTitle(stream.str());
		
	}
}




void randomMap(void){
    vector<string> mapLoc; 
    srand (time(NULL));
    int randomNb = rand() % 6;
    switch (randomNb)
    {
    case 0:
        renderRenderRealMap();
        break; 
    case 1:
        system("./bin/Isometric ");
        break;
    case 2:
        system("./bin/ShaderEffects");
        break;
    case 3:
        system("./bin/MapWithQuadTree");
        break;
    case 4:
        system("./bin/BenchMark");
        break;
    case 5:
        system("./bin/AddRemoveObjects");
        break;
    
    default:
        renderRenderRealMap();
        break;
    }

}

#include <json/json.h>
#include <dirent.h>
#include <iostream>               // for std::cout


/*

int main(int argc,char* argv[])
{
    //test1();

	//DIR *dir;
	//struct dirent *ent;
	//if ((dir = opendir ("res/demon/demon")) != NULL) {
	///* print all the files and directories within directory */
	//while ((ent = readdir (dir)) != NULL) {
	//	printf ("%s\n", ent->d_name);
	//}
	//closedir (dir);
	//} else {
	///* could not open directory */
	//perror ("");
	//return EXIT_FAILURE;
	//}

	

	
/*	
    return 0;

}
*/




int main(){
    bool alive = true;
    while (alive){
		Json::Value root;   // will contains the root value after parsing.
		Json::Reader reader;
		std::ifstream test("data/frames_info.json", std::ifstream::binary);
		bool parsingSuccessful = reader.parse( test, root, false );
		if ( !parsingSuccessful )
		{
			// report to the user the failure and their locations in the document.
			std::cout  << reader.getFormatedErrorMessages()
				<< "\n";
		}

		std::string encoding = root.get("encoding", "UTF-8" ).asString();
		std::cout << encoding << "\n";
		const Json::Value mynames = root["b"];
		cout << mynames << "\n";
		alive = false;
		std::map<std::string, Json::Value > m;
		m["root"] = root;
		std::cout << m["root"] << "\n";
    }

	//testSFML();
	renderRenderRealMap();
    return 0;
}
