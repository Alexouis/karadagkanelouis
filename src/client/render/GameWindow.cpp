#include "GameWindow.h"
#include "FightScene.h"

namespace render {
    GameWindow::GameWindow()
    {
       // tmx::MapLoader ml("res/map/");
        this->gameMap->load("map_1.tmx");
        //uint bgw = this->gameMap->getMapSize().x;
        //uint bgh = this->gameMap->getMapSize().y;
        //this->bgTex.create(bgw, bgh);
        
        
        //this->bgTex.draw(*(this->gameMap));
        
        //this->bgTex.setView(view);
        //this->bgTex.display();
        //this->background.setTexture(this->bgTex.getTexture());
        //gameMap.load("map_1.tmx");
        this->window.create(sf::VideoMode(this->width, this->height), "TMX Loader");
        // = sf::RenderWindow(sf::VideoMode(2000u, 600u), "TMX Loader");
        this->window.setVerticalSyncEnabled(true);
        sf::View view = this->window.getView();
        view.zoom(5.709);
        view.setCenter(this->center.x, this->center.y);
        this->window.setView(view);
        //this->window.clear();
        //this->window.draw(this->background);
        //this->window.display();

        //adjust the view to centre on map
        

        initScenes();
        
    };

    void GameWindow::init ()
    {
        initScenes();
    };

    void GameWindow::initScenes ()
    {   
        std::unique_ptr<Scene> holder = std::unique_ptr<Scene>(new Scene()); 
        sceneQueue.push(std::move(holder));//first is menu
        holder = std::unique_ptr<Scene>(new FightScene());//2nd is Fight scenne
        sceneQueue.push(std::move(holder));
        holder = std::unique_ptr<Scene>(new Scene());//last is ending scene 
        sceneQueue.push(std::move(holder));
    };

    void GameWindow::draw()
    {   
        this->window.draw(*(this->gameMap));
        this->window.draw(*(this->sceneQueue.front()));  

    };

    void GameWindow::update()
    {
        this->sceneQueue.front()->update();
    };

    
    void GameWindow::clearBackground()
    {
        this->bgTex.clear();
    };

    // Setters and Getters

    const std::queue<std::unique_ptr<Scene>>& GameWindow::getSceneQueue() const
    {
        return this->sceneQueue;
    };

    void setSceneQueue(const std::queue<std::unique_ptr<Scene>>& sceneQueue){

    };

    float GameWindow::getZoom() const
    {
        return zoom;
    };

    void GameWindow::setZoom(float zoom)
    {
        this->zoom = zoom;
    };

    const sf::Vector2<float>& GameWindow::getCenter() const
    {
        return center;
    };

    void GameWindow::setCenter(const sf::Vector2<float>& center)
    {
        this->center = center;
    };

    
    
    

    GameWindow::~GameWindow ()
    {

    };
}
