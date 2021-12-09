#include "Background.h"

namespace render{
    Background::Background (){

    }

    void Background::update(){
        
    };

    void Background::draw (){

    };
    void Background::clear (){

    };
    // Setters and Getters
    const std::vector<int>& Background::getGameMap() const{
        return Background::gameMap;
    };

    void Background::setGameMap(const std::vector<int>& gameMap){
       /*  //create map loader and load map
        
        gameMap.load("res/map/map_1.tmx");
        
        sf::RenderWindow renderWindow(sf::VideoMode(2000u, 900u), "TMX Loader");
        renderWindow.setVerticalSyncEnabled(true);

        //adjust the view to centre on map
        sf::View view = renderWindow.getView();
        view.zoom(7.0f);
        view.setCenter(1024.0f, 2000.0f);
        renderWindow.setView(view);


        //to toggle debug output
        bool debug = false;
        bool anim = false;
        int num_anim=0;
        //-----------------------------------//
        static float posx = 500;
        static float posy = 1500;

        static float move_posx = 500;
        static float move_posy = 1500;

        Player Mustafa ;
        Mustafa.setPosition(Position());
                    
        int i_x;
        int i_y;
        sf::Font font;
        if (!font.loadFromFile("arial.ttf"))
        {
            // error...
        }
        sf::Text text;
        text.setFont(font);
        text.setString("Hello world");
        text.setCharacterSize(250);

        while(renderWindow.isOpen())
        {
            //poll input
            sf::Event event;
            
        //	Json::Value root;
        //    Json::Reader reader;
        //    std::ifstream img("frames_info.json", );

            
            //draw map
            renderWindow.clear();
            
        // root["demon"]["demon_idle_w"]["n"]        
            sf::Texture heroTexture;
            if (!heroTexture.loadFromFile("res/frames.png"))
            {
                // error...
            }
            sf::Sprite heroSprite;
            heroSprite.setTexture(heroTexture);
            heroSprite.setTextureRect(sf::IntRect(300,300,100,70));
            heroSprite.setPosition(sf::Vector2f(500.f, 200.f));
            heroSprite.scale(sf::Vector2f(20.f,20.f));
            sf::Sprite heroSprite2;
            heroSprite2.setTexture(heroTexture);
            heroSprite2.setTextureRect(sf::IntRect(0, 0, 100, 80));
            heroSprite2.setPosition(sf::Vector2f(-500.f, 200.f));
            heroSprite2.scale(sf::Vector2f(20.f,20.f));
            sf::Sprite heroSprite3;
            heroSprite3.setTexture(heroTexture);
            heroSprite3.setTextureRect(sf::IntRect(435, 520, 50, 60));
        //    heroSprite3.setPosition(sf::Vector2f(posx, posy));
        heroSprite3.setPosition(sf::Vector2f(move_posx, move_posy)); //TESTER ANIMATION ICI
            heroSprite3.scale(sf::Vector2f(20.f,20.f));
            renderWindow.draw(gameMap);
            renderWindow.draw(heroSprite);
            renderWindow.draw(heroSprite2);
            renderWindow.draw(heroSprite3);
            renderWindow.draw(text);
            if(debug)gameMap.drawLayer(renderWindow, tmx::MapLayer::Debug);
            renderWindow.display();
            //TEST POUR ANIMATION
            if (move_posx != posx or move_posy!= posy){
                if (abs(move_posx-posx)<30) move_posx=posx;
                else if (move_posx < posx) move_posx=move_posx+30;
                else move_posx= move_posx -30;
                if (abs(move_posy-posy)<30) move_posy=posy;
                else if(move_posy < posy) move_posy=move_posy+30;
                else move_posy= move_posy -30;
        }
    //
    //
            //print mouse coords to orthographic (screen) coords and world (isometric) coords
            sf::Vector2f mousePosScreen = renderWindow.mapPixelToCoords(sf::Mouse::getPosition(renderWindow));
            sf::Vector2f mousePosWorld = gameMap.orthogonalToIsometric(mousePosScreen);
            sf::Vector2f mousePos(floor(mousePosWorld.x/278),floor(mousePosWorld.y/278));
            std::stringstream stream;
            stream << "Mouse Position: "<< mousePosScreen.x << ", " << mousePosScreen.y << " World Position: " << mousePosWorld.x << ", " << mousePosWorld.y << " Cell: " << mousePos.x << ", " << mousePos.y;

            renderWindow.setTitle(stream.str());
            
            while(renderWindow.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    renderWindow.close();
                if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::D)
                    debug = !debug;
                if(event.type == sf::Event::MouseButtonPressed){
                    //Mustafa.setPosition(Position(floor(mousePosWorld.x/278),floor(mousePosWorld.y/278)));
                    Mustafa.move(mousePos.x,mousePos.y);
                    mousePosWorld.x=mousePos.x*270+270/2;
                    mousePosWorld.y=mousePos.y*270+270/2;
                    
                    mousePosScreen = gameMap.isometricToOrthogonal(mousePosWorld);
                    i_x = Mustafa.getPosition().getX();
                    i_y = Mustafa.getPosition().getY();
                    //i_x++ ;
                    posx = mousePosScreen.x - 40*20/2;
                    posy = mousePosScreen.y - 60*20;

                    std::stringstream ss;
                    ss<<"Position : ("<< i_x <<","<< i_y <<")";
                    text.setString(ss.str());
                }
                
            }
        } */
    };


}