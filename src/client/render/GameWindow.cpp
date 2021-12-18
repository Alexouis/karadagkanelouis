#include "GameWindow.h"
#include "FightScene.h"

namespace render {
    GameWindow::GameWindow(std::unique_ptr<tmx::MapLoader>& gameMap)
    {
       // tmx::MapLoader ml("res/map/");
        gameMap= std::move(gameMap);
        //gameMap.load("map_1.tmx");
        window.create(sf::VideoMode(2000u, 600u), "TMX Loader");
        // = sf::RenderWindow(sf::VideoMode(2000u, 600u), "TMX Loader");
        window.setVerticalSyncEnabled(true);

        //adjust the view to centre on map
        sf::View view = window.getView();
        view.zoom(zoom);
        view.setCenter(center.x, center.y);
        window.setView(view);

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
        this->backGround.clear();
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
