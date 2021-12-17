#include "GameWindow.h"
#include "FightScene.h"

namespace render {
    GameWindow::GameWindow()
    {
        initScenes();
        zoom = 5.0;
        center.x = 0;
        center.y = 0; 
    };

    void GameWindow::init ()
    {
        initScenes();
        zoom = 5.0;
        center.x = 0;
        center.y = 0; 
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
        setWindow(sf::RenderWindow(sf::VideoMode(2000u, 600u), "TMX Loader"));
        window.setVerticalSyncEnabled(true);

        //adjust the view to centre on map
        sf::View view = window.getView();
        view.zoom(zoom);
        view.setCenter(center.x, center.y);
        window.setView(view);
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
