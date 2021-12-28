/*
 * File             view_zoom.cpp
 * Directory        examples
 * Created Date     Monday, December 27th 2021, 11:18:05 am
 * Author           Nouhou KANE
 * Email            nouhou.kane@ensea.fr
 * 
 * Copyright (c) 2021  ENSEA(FR)
 * __________________________________________________________________________
 */

#include <SFML/Graphics.hpp>
#include <iostream>

 void renderMap(void){

    sf::RenderWindow gamewindow(sf::VideoMode(2000u, 600u), "TMX Loader");
    sf::View view = gamewindow.getView();
    sf::Vector2f center0 = view.getCenter();
    view.setCenter(sf::Vector2f(1000,300));
    sf::Vector2f center = view.getCenter();
    std::cout << "view center : x = " << center.x <<" y= "<< center.y << std::endl;
    sf::Vector2i center2 = gamewindow.mapCoordsToPixel(center);
    std::cout << "view center : x = " << center2.x <<" y= "<< center2.y << std::endl;
    sf::Vector2f center3 = gamewindow.mapPixelToCoords(center2);
    std::cout << "view center : x = " << center3.x <<" y= "<< center3.y << std::endl;
    float zoom = 0.8;
    float deux = 2.0;

    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(100, 50));
    rectangle.setOutlineColor(sf::Color::Red);
    rectangle.setOutlineThickness(5);
    sf::Vector2f position(gamewindow.mapPixelToCoords(sf::Vector2i(0,0)));
    rectangle.setPosition(position);
    sf::Vector2f scale = rectangle.getScale();
    //rectangle.setScale(scale/zoom);       
    

    sf::Event event;

    while(gamewindow.isOpen()){

        sf::Vector2i mousePosScreen = (sf::Vector2i)gamewindow.mapPixelToCoords(sf::Mouse::getPosition(gamewindow));

        while(gamewindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                gamewindow.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::D)
            if (event.type == sf::Event::MouseButtonPressed){
            }
            if(event.type == sf::Event::MouseWheelMoved)
            {
                if(event.mouseWheel.delta != 0)
                {
                    if(event.mouseWheel.delta == 1)
                    {
                        zoom = 0.8; 
                    }
                    else
                    {
                        zoom = 1.25; 
                    } 
                    scale *= zoom;
                    view.zoom(zoom);
                    gamewindow.setView(view); 
                    center2 = gamewindow.mapCoordsToPixel(position);
                    std::cout << "view center : x = " << position.x <<" y= "<< position.y << std::endl;
                    rectangle.setScale(scale);    
                    rectangle.setPosition(gamewindow.mapPixelToCoords(sf::Vector2i(0,0)));   
                }
                
            }
        }


        gamewindow.clear();
        gamewindow.draw(rectangle);

        gamewindow.display();

    }

    
} 



int main(){

    renderMap();
}