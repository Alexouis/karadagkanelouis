#include "GameWindow.h"
#include "FightScene.h"

namespace render {
    GameWindow::GameWindow()
    {
        this->zoom = 4;
        this->currentScene = SceneId::FIGHTSCENE;        
        this->initScenes();
        this->window.create(sf::VideoMode(this->width, this->height), "TMX Loader");
        this->window.setVerticalSyncEnabled(true);
        sf::View view = this->window.getView();
        view.zoom(this->zoom);
        view.setCenter(this->center.x, this->center.y);
        this->window.setView(view); 
    };

    void GameWindow::init ()
    {
        initScenes();
    };

    void GameWindow::initScenes ()
    {   
        std::unique_ptr<Scene> holder = std::unique_ptr<Scene>(new Scene); 
        this->scenes.push_back(std::move(holder));
        holder = std::unique_ptr<FightScene>(new FightScene);
        this->scenes.push_back(std::move(holder));
        holder.reset(new Scene);
        this->scenes.push_back(std::move(holder));
    };

    void GameWindow::draw()
    {   
        this->window.draw(*(this->scenes[this->currentScene]));  
    };

    void GameWindow::update()
    {
        this->scenes[this->currentScene]->update();
    };

    
    void GameWindow::clearBackground()
    {
        this->bgTex.clear();
    };

    // Setters and Getters

    const uint& GameWindow::getHeight() const
    {
        return this->height;
    };

    const std::vector<std::unique_ptr<Scene>>& GameWindow::getScenes() const
    {
        return this->scenes;
    };

    void setScenes(const std::vector<std::unique_ptr<Scene>>& scenes){

    };

    float GameWindow::getZoom() const
    {
        return zoom;
    };

    void GameWindow::setZoom(float zoom)
    {
        this->zoom = zoom;
        sf::View view = this->window.getView();
        view.zoom(this->zoom);
        this->window.setView(view); 
    };

    const sf::Vector2<float>& GameWindow::getCenter() const
    {
        return center;
    };

    void GameWindow::setCenter(const sf::Vector2<float>& center)
    {
        this->center = center;
        sf::View view = this->window.getView();
        view.setCenter(this->center.x, this->center.y);
        this->window.setView(view); 
    };


    void GameWindow::shareStateWith(engine::Engine& ngine){
        (this->scenes[SceneId::FIGHTSCENE])->bindState(ngine);
    }

    
    sf::Vector2f GameWindow::screenToWorld (sf::Vector2f position){
        return (this->scenes[SceneId::FIGHTSCENE])->screenToWorld(position);
    }
    

    sf::Vector2f GameWindow::worldToScreen (sf::Vector2f position){
        return (this->scenes[SceneId::FIGHTSCENE])->worldToScreen(state::Position((int)(position.x), (int)(position.y)));
    }
    

    GameWindow::~GameWindow ()
    {

    };
}
