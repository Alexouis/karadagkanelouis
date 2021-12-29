#include "GameWindow.h"
#include "FightScene.h"

#define DEFAULTZOOM 4
#define DEFAULTXCENTER 1024
#define DEFAULTYCENTER 2000

namespace render {
    GameWindow::GameWindow()
    {
        this->isZoomed = 0;
        this->initScenes();        
        this->zoom = DEFAULTZOOM;
        std::cout << "view: " << this->view.getSize ().x << " " << this->view.getSize().y << std::endl;
        this->isZoomed = (this->zoom != 1);
        std::cout << "isZoomed: " << this->isZoomed << std::endl;
        this->currentScene = SceneId::FIGHTSCENE;        
        this->window.create(sf::VideoMode(this->width, this->height), "TMX Loader");
        this->window.setVerticalSyncEnabled(true);
        this->view = this->window.getView();
        this->view.zoom(this->zoom);
        this->view.setCenter(DEFAULTXCENTER, DEFAULTYCENTER);
        this->window.setView(this->view); 
        std::cout << "view: " << this->view.getSize ().x << " " << this->view.getSize().y << std::endl;

    };

    void GameWindow::init ()
    {
        initScenes();
    };

    void GameWindow::initScenes ()
    {   
        std::unique_ptr<Scene> holder = std::unique_ptr<Scene>(new Scene()); 
        this->scenes.push_back(std::move(holder));
        holder = std::unique_ptr<FightScene>(new FightScene(this));
        this->scenes.push_back(std::move(holder));
        holder.reset(new Scene());
        this->scenes.push_back(std::move(holder));
    };

    void GameWindow::draw()
    {   
        this->window.draw(*(this->scenes[this->currentScene]));
    };

    //void GameWindow::update()
    void GameWindow::update (){
        this->scenes[this->currentScene]->update();
    };
    
    void GameWindow::update (sf::Event& e, sf::Vector2i m_mousePosition)
    {
        this->scenes[this->currentScene]->update(e, m_mousePosition,this);
        this->isZoomed = 0;
    };

    
    void GameWindow::clearBackground()
    {
        this->bgTex.clear();
    };

    // Setters and Getters


    SceneId GameWindow::getCurrentScene() const
    {
        return this->currentScene;
    };

    void GameWindow::setCurrentScene(SceneId currentScene){

    };


    const std::vector<std::unique_ptr<Scene>>& GameWindow::getScenes() const
    {
        return this->scenes;
    };

    void setScenes(const std::vector<std::unique_ptr<Scene>>& scenes){

    };

    void GameWindow::setZoom(float zoom)
    {
        if(this->zoom*zoom > 0)
        {
            this->zoom = zoom;
            this->view.zoom(this->zoom);
            this->window.setView(this->view); 
        }
    };

    void GameWindow::setCenter(sf::Vector2f center)
    {
        this->view.setCenter(center.x,center.y);
        this->window.setView(this->view); 
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
