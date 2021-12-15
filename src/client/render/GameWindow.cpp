#include "GameWindow.h"

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
        Scene menu;
        // Scene *endGame = new Scene();
        // FightScene *fs = new FightScene();
        // sceneStack.push_back(menu);
        // sceneStack.push_back(fs);
        // sceneStack.push_back(endGame);
        // Scene c();
        //unique_ptr u : make_unique(c);
        
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