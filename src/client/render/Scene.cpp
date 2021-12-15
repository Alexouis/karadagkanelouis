#include "Scene.h"

namespace render {
    Scene::Scene ()
    {
        init();
        setId(1);
        loadTextures();

    };

    
    void Scene::draw (sf::RenderTarget& target, sf::RenderStates& states) const{

    };

    

    void Scene::loadImages (){

    };

    void Scene::loadTextures (){
        if (this->id = 1)this->t.loadFromFile("res/frames.png"); // load texture de personnage si scene de combat
    };

    void Scene::init (){
        this->id=0;
        
    };

    void Scene::update (){

    };

    // Setters and Getters
    const std::vector<std::unique_ptr<Box>>& Scene::getBoxes() const{
        return this->boxes;
    };

    void Scene::setBoxes(const std::vector<std::unique_ptr<Box>>& boxes){

    };

    int Scene::getId() const{

    };

    void Scene::setId(int id){

    };

    void Scene::draw (sf::RenderTarget& target, sf::RenderStates states) const{
        target.draw(this->sprite);
    }

};