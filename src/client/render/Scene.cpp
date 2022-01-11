#include "Scene.h"
#include "GameWindow.h"
#include "Button.h"
#include "Info.h"
#include <iostream>

#define START 0x30  //[code value] =  [0011 0000]

namespace render {

    Scene::Scene ()
    {


    };

    Scene::Scene (char id, std::string type, GameWindow* gameWindow)
    {
        setId(id);
        init(type, gameWindow);

    };

    
    //  Pour charger les images qui vont être affichées.
    void Scene::loadImages (){

    };

    //  Pour charger les texture des éléments à afficher.
    void Scene::loadTextures (std::string textures_paths){
        this->texture.loadFromFile(textures_paths); // load texture de personnage si scene de combat
    };

    //  Gère l'initialisation de la scène.
    void Scene::init (std::string type, GameWindow* gameWindow){
        sf::Vector2f size;
        sf::Vector2i pos;
        unsigned int fontSize;
        sf::Font myfont;
        if(!myfont.loadFromFile("./extern/tmx-loader/fonts/Ubuntu-M.ttf"))
        {
            std::cerr<<"Could not find contb.ttf font."<<std::endl;
        }
        
        if(type == "start")
        {
            if (!(this->texture).loadFromFile("res/utiles/bgMenu.png"))
            {
                std::cerr<<"Could not find the image for the background"<<std::endl;
            }
            else
            {
                this->sprite.setTexture(this->texture);
            }

            size = sf::Vector2f(100.f,50.f);
            pos = sf::Vector2i(1000,450);
            fontSize = 15;
            std::unique_ptr<Box> holder = std::unique_ptr<Button>(new Button("JOUER", fontSize, myfont, size, pos , SAVE, START, gameWindow)); 
            boxes["JOUER"]=std::move(holder);
            pos = sf::Vector2i(10,10);
            holder = std::unique_ptr<Info>(new Info("PLT - Nouhou KANE, Alexandre LOUIS & Mustafa KARADAG",myfont,fontSize, pos, gameWindow));
            boxes["TITLE"]=std::move(holder);
        }

        else if(type == "end")
        {
            
        }
        
    };

    //  Permet d’actualiser le contenu de la fenêtre.
    void Scene::update(){
    };
    
    /*  Permet d’actualiser le contenu de la fenêtre et de transmettre des informations tel que 
        la position du clic ou le type d’évènement. */
    void Scene::update(sf::Event& e, sf::Vector2i m_mousePosition, GameWindow* gameWindow){        
        for(const auto& [key, value] : this->boxes){
            (*value).update(e,m_mousePosition, gameWindow);
        }
    };

    //  Est utilisée afin de définir le background d’une scène.
    void Scene::setTexture(std::string stexture)
    {
        if (!(this->texture).loadFromFile(stexture))
        {
            std::cerr<<"Could not find the image for the background"<<std::endl;
        }
        else
        {
            this->sprite.setTexture(this->texture);
        }
    }

    // permet de connaître l’état du jeu, s’il y a Game Over, on pourra mettre à jour la variable gameOver.
    bool Scene::isGameOver()
    {
          return this->gameOver;
    }

    //  permet de connaître la classe du vainqueur. Cette fonction est appelée si isGameOver() renvoie true.
    state::playerClass Scene::whosWinner()
    {
          return this->winner;
    }

    //  Pour dessiner et afficher à l’écran les éléments de la scène.
    void Scene::draw (sf::RenderTarget& target, sf::RenderStates states) const{
        target.draw(this->sprite, states);
        for (const auto& [key, value] : boxes){
            target.draw(*value,states);
        }
    }

    //  Pour partager le state avec les scènes.
    void Scene::bindState (engine::Engine& ngine){

    }

    /*  Permet de passer des coordonnées orthogonales en pixel de la fenêtre aux coordonnées de la 
        map (cases) du jeu. */
    sf::Vector2f Scene::screenToWorld (sf::Vector2f position){

    }

    //  Fait l’opération inverse.
    sf::Vector2f Scene::worldToScreen (state::Position position){

    }

    //-----------------------------Setters and Getters-----------------------------

    const std::map<std::string,std::unique_ptr<Box>>& Scene::getBoxes() const{
        return this->boxes;
    };

    void Scene::setBoxes(const std::map<std::string,std::unique_ptr<Box>>& boxes){
    };

    char Scene::getId() const{
        return this->id;
    };

    void Scene::setId(char id){
        this->id = id;
    };

    Scene::~Scene(){

    }

};