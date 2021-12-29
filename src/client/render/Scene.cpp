#include "Scene.h"
#include "GameWindow.h"
#include <iostream>

namespace render {
    Scene::Scene ()
    {
        init();
        setId(1);
        loadTextures("res/frames.png");

    };

    

    void Scene::loadImages (){

    };

    void Scene::loadTextures (std::string textures_paths){
        this->texture.loadFromFile(textures_paths); // load texture de personnage si scene de combat
    };

    void Scene::init (){
        
    };

    void Scene::update(){
    };
    
    void Scene::update(sf::Event& e, sf::Vector2i m_mousePosition, GameWindow* gameWindow){        
        for(auto &boxe : this->boxes){
            (*boxe).update(e,m_mousePosition, gameWindow);
        }
    };

    // Setters and Getters
    const std::vector<std::unique_ptr<Box>>& Scene::getBoxes() const{
        return this->boxes;
    };

    void Scene::setBoxes(const std::vector<std::unique_ptr<Box>>& boxes){
    };

    char Scene::getId() const{
        return this->id;
    };

    void Scene::setId(char id){
        this->id = id;
    };

    void Scene::draw (sf::RenderTarget& target, sf::RenderStates states) const{
        target.draw(this->sprite, states);
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