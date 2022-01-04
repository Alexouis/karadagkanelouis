#include "GameWindow.h"
#include "FightScene.h"

#define MENU_DEFAULTZOOM 1
#define FIGHTSCENE_DEFAULTZOOM 4
#define DEFAULTXCENTER 1024
#define DEFAULTYCENTER 2000

#define MOVE 0x90 //[targetCode code value] =  [1 001 0000]


namespace render {
    GameWindow::GameWindow()
    {
        this->zoom = MENU_DEFAULTZOOM;
        this->zoomTot = this->zoom;
        this->isZoomed = (this->zoom != 1);
        this->currentScene = SceneId::MENU;        
        this->window.create(sf::VideoMode(this->width, this->height), "TMX Loader");
        this->window.setVerticalSyncEnabled(true);
        this->view = this->window.getView();
        this->view.zoom(this->zoom);
        this->window.setView(this->view);
        this->initScenes(); 
               

    };

    void GameWindow::init ()
    {
        initScenes();
    };

    void GameWindow::initScenes ()
    {   
        std::unique_ptr<Scene> holder = std::unique_ptr<Scene>(new Scene(0,"start",this)); 
        this->scenes.push_back(std::move(holder));
        holder = std::unique_ptr<FightScene>(new FightScene(1,this));
        this->scenes.push_back(std::move(holder));
        holder.reset(new Scene(2,"end",this));
        this->scenes.push_back(std::move(holder));
    };

    void GameWindow::draw()
    {   
        this->window.draw(*(this->scenes[this->currentScene]));
    };

    //void GameWindow::update()
    void GameWindow::update (){
        this->scenes[this->currentScene]->update();
        if(this->currentScene == FIGHTSCENE && this->scenes[this->currentScene]->isGameOver())
        {
            this->nextScene();
        }
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
        this->currentScene = currentScene;
    };

    void GameWindow::nextScene()
    {
        sf::Event event;
        sf::Vector2i mousePosScreen = (sf::Vector2i)(this->window).mapPixelToCoords(sf::Vector2i(0,0));
                
        switch (this->currentScene)
        {
            case SceneId::MENU:
            {
                this->setCurrentScene(FIGHTSCENE);
                this->zoom = FIGHTSCENE_DEFAULTZOOM;
                this->zoomTot =this->zoom;
                this->isZoomed = (this->zoom != 1);
                this->view.zoom(this->zoom);
                this->view.setCenter(DEFAULTXCENTER, DEFAULTYCENTER);
                this->window.setView(this->view); 
                break; 
            }

            case SceneId::FIGHTSCENE:
            {
                state::playerClass winner = this->scenes[this->currentScene]->whosWinner();

                this->setCurrentScene(END);

                switch(winner)
                {
                    case state::playerClass::HERO:
                    {
                        this->scenes[this->currentScene]->setTexture("res/utiles/bgEndHero.png");
                        break;
                    }

                    case state::playerClass::DEMON:
                    {
                        this->scenes[this->currentScene]->setTexture("res/utiles/bgEndDemon.png");
                        break;
                    }
                }

                
                this->zoom = (float)(1/this->zoomTot);
                this->isZoomed = (this->zoom != 1);
                this->view.zoom(this->zoom);
                this->view.setCenter(960,300);
                this->window.setView(this->view); 
                break; 
            }

            default:
                break;
        }
        
        this->update(event,mousePosScreen);
        this->isZoomed = 0;
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
            this->zoomTot = this->zoomTot*zoom;
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


    void GameWindow::handleEvents (sf::Event& event, sf::Vector2f& mousePosScreen, sf::Vector2f& mousePosWorld, engine::Engine& ngine){
        this->selected = (char)MOVE;
        if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
            this->update(event,(sf::Vector2i)mousePosScreen);
            ngine.registerTarget(floor(mousePosWorld.x), floor(mousePosWorld.y), this->selected );
            ngine.execute();
        }
        if(event.type == sf::Event::MouseMoved )
        {
            this->update(event,(sf::Vector2i)mousePosScreen);
        }
    }


    void GameWindow::handleZoom (sf::Event& event, sf::Vector2f& mousePosScreen){
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::D)
        {
            this->update(event,(sf::Vector2i)mousePosScreen);
        }
        if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right)
        {
            this->setCenter(mousePosScreen);

            this->update(event,(sf::Vector2i)mousePosScreen);
        }
        if(event.type == sf::Event::MouseWheelMoved && this->getCurrentScene() == SceneId::FIGHTSCENE)
        {
            if(event.mouseWheel.delta == 1){
                this->setZoom(0.8); 
                this->isZoomed = 1;  
            }
            else{
                this->setZoom(1.25); 
                this->isZoomed = 1;    
            }   
            this->update(event,(sf::Vector2i)mousePosScreen);
        }
        this->selected = (char)MOVE;
    }
    

    GameWindow::~GameWindow ()
    {

    };
}
