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
    const std::vector<Box*>& Scene::getBoxes() const{
        return this->boxes;
    };

    void Scene::setBoxes(const std::vector<Box*>& boxes)
    {
        this->boxes = boxes;
    }

    int Scene::getId() const{
        return this->id;
    };

    void Scene::setId(int id){
        this->id = id;
    };

    const sf::Texture& Scene::getT() const{
        return this->t;
    };

    void Scene::setT(const sf::Texture& t){
        this->t = t;
    };

    Scene::~Scene (){

    };

};