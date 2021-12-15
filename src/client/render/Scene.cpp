#include "Scene.h"

namespace render {
    Scene::Scene ()
    {
        
    };
    
    // void Scene::draw (){

    // };

    // void Scene::clear (){

    // };

    void Scene::loadImages (){

    };

    void Scene::loadTextures (){

    };

    void Scene::init (){

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