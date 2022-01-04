#include "Scene.h"
#include "GameWindow.h"
#include "Button.h"
#include "Info.h"
#include <iostream>

#define START 0x30  //[code value] =  [0011 0000]

namespace render {

    Scene::Scene ()
    {


    };

    Scene::Scene (char id, std::string type, GameWindow* gameWindow)
    {
        setId(id);
        init(type, gameWindow);

    };

    

    void Scene::loadImages (){

    };

    void Scene::loadTextures (std::string textures_paths){
        this->texture.loadFromFile(textures_paths); // load texture de personnage si scene de combat
    };

    void Scene::init (std::string type, GameWindow* gameWindow){
        sf::Vector2f size;
        sf::Vector2i pos;
        unsigned int fontSize;
        sf::Font myfont;
        if(!myfont.loadFromFile("./extern/tmx-loader/fonts/Ubuntu-M.ttf"))
        {
            std::cerr<<"Could not find contb.ttf font."<<std::endl;
        }
        
        if(type == "start")
        {
            if (!(this->texture).loadFromFile("res/utiles/bgMenu.png"))
            {
                std::cerr<<"Could not find the image for the background"<<std::endl;
            }
            else
            {
                this->sprite.setTexture(this->texture);
            }

            size = sf::Vector2f(100.f,50.f);
            pos = sf::Vector2i(1000,450);
            fontSize = 15;
            std::unique_ptr<Box> holder = std::unique_ptr<Button>(new Button("JOUER", fontSize, myfont, size, pos , SAVE, START, gameWindow)); 
            boxes["JOUER"]=std::move(holder);
            pos = sf::Vector2i(10,10);
            holder = std::unique_ptr<Info>(new Info("PLT - Nouhou KANE, Alexandre LOUIS & Mustafa KARADAG",myfont,fontSize, pos, gameWindow));
            boxes["TITLE"]=std::move(holder);
        }

        else if(type == "end")
        {
            if (!(this->texture).loadFromFile("res/utiles/bgEndDefeat.png"))
            {
                std::cerr<<"Could not find the image for the background"<<std::endl;
            }
            else
            {
                this->sprite.setTexture(this->texture);
            }
        }
        
    };

    void Scene::update(){
    };
    
    void Scene::update(sf::Event& e, sf::Vector2i m_mousePosition, GameWindow* gameWindow){        
        for(const auto& [key, value] : this->boxes){
            (*value).update(e,m_mousePosition, gameWindow);
        }
    };

    // Setters and Getters
    const std::map<std::string,std::unique_ptr<Box>>& Scene::getBoxes() const{
        return this->boxes;
    };

    void Scene::setBoxes(const std::map<std::string,std::unique_ptr<Box>>& boxes){
    };

    char Scene::getId() const{
        return this->id;
    };

    void Scene::setId(char id){
        this->id = id;
    };

    bool Scene::isGameOver()
    {
          return this->gameOver;
    }


    void Scene::draw (sf::RenderTarget& target, sf::RenderStates states) const{
        target.draw(this->sprite, states);
        for (const auto& [key, value] : boxes){
            target.draw(*value,states);
        }
    }

    void Scene::bindState (engine::Engine& ngine){

    }

    sf::Vector2f Scene::screenToWorld (sf::Vector2f position){

    }

    sf::Vector2f Scene::worldToScreen (state::Position position){

    }

    Scene::~Scene(){

    }

};