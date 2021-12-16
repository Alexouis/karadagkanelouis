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
        sceneQueue.push(std::move(holder));
        holder = std::unique_ptr<Scene>(new FightScene());
        sceneQueue.push(std::move(holder));
        holder = std::unique_ptr<Scene>(new Scene());
        sceneQueue.push(std::move(holder));
    };

    void GameWindow::draw()
    {   
        sf::RenderWindow renderWindow(sf::VideoMode(2000u, 600u), "TMX Loader");
        renderWindow.setVerticalSyncEnabled(true);

        //adjust the view to centre on map
        sf::View view = renderWindow.getView();
        view.zoom(zoom);
        view.setCenter(center.x, center.y);
        renderWindow.setView(view);
    };

    void GameWindow::update()
    {

    };

    
    void GameWindow::clearBackground()
    {

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
