#include "FightScene.h"
#include "GameWindow.h"
#include "Button.h"
#include <fstream>
#include <iostream> 

#define GAMEWINDOWHEIGHT 600
#define GAMEWINDOWWIDTH 2000
#define GAMEWINDOWZOOM 4

#define map_sizeX 22
#define map_sizeY 22


#define SPELL1 0x0 //[code value] =  [0000 0000]
#define SPELL2 0x1 //[code value] =  [0000 0001]
#define SPELL3 0x2 //[code value] =  [0000 0010]
#define SPELL4 0x3 //[code value] =  [0000 0011]
#define SPELL5 0x4 //[code value] =  [0000 0100]
#define MENU 0x10  //[code value] =  [0001 0000]
#define PASS 0x20  //[code value] =  [0010 0000]

namespace render{
    FightScene::FightScene(GameWindow* gameWindow){

        this->gState = std::shared_ptr<state::State>(new state::State(map_sizeX,map_sizeY));
        this->gameMap->load("map_1.tmx");
        this->loadFrameInfos("data/frames_info.json");
        this->texture.loadFromFile("res/frames.png");

        this->initButtons(gameWindow);

        sf::Time t;
        std::unique_ptr<AnimatedObject> aniObjects;
        state::Position p;
        for(char i=0; i<this->gState->getPlayersCount(); i++){
            p = this->gState->playerPosition(i);
            std::string playerClass = (this->gState->getPlayerClass(i) == state::playerClass::HERO) ? "valla" : "demon";
            aniObjects = std::unique_ptr<AnimatedObject>(new AnimatedObject(this->texture));
            this->animatedObjects.push_back(std::move(aniObjects));
            this->animatedObjects[i]->update(t,this->frameInfos[playerClass],playerClass+"_idle_se",this->worldToScreen(p));
        }  

    };

    void FightScene::initButtons(GameWindow* gameWindow)
    {   
        sf::Vector2f size;
        sf::Vector2i pos;
        sf::Font myfont;
        if(!myfont.loadFromFile("./extern/tmx-loader/fonts/Ubuntu-M.ttf"))
        {
            std::cerr<<"Could not find contb.ttf font."<<std::endl;
        }
        size = sf::Vector2f(50.f,50.f);
        pos = sf::Vector2i(10,10);
        std::unique_ptr<Box> holder = std::unique_ptr<Button>(new Button("MENU", myfont, size, pos , CANCEL, MENU, gameWindow)); 
        this->boxes.push_back(std::move(holder));

        size = sf::Vector2f(450.f,300.f);
        pos = sf::Vector2i(10,10);
        holder = std::unique_ptr<Button>(new Button("\n\nPASSER \n\nSON TOUR!", myfont,size, pos, CANCEL, PASS, gameWindow));
        this->boxes.push_back(std::move(holder));

        size = sf::Vector2f(250.f,200.f);
        pos = sf::Vector2i(50,10);
        holder = std::unique_ptr<Button>(new Button("Sort 1", myfont, size, pos, SAVE, SPELL1, gameWindow));
        this->boxes.push_back(std::move(holder));

        size = sf::Vector2f(50.f,50.f);
        pos = sf::Vector2i(800,500);
        holder = std::unique_ptr<Button>(new Button("Sort 2", myfont, size, pos, SAVE, SPELL2, gameWindow));
        this->boxes.push_back(std::move(holder));

        size = sf::Vector2f(250.f,200.f);
        pos = sf::Vector2i(1520,530);
        holder = std::unique_ptr<Button>(new Button("", myfont, size, pos, SAVE, SPELL3, gameWindow));
        this->boxes.push_back(std::move(holder));

        size = sf::Vector2f(250.f,200.f);
        pos = sf::Vector2i(1530,530);
        holder = std::unique_ptr<Button>(new Button("", myfont, size, pos, SAVE, SPELL4, gameWindow));
        this->boxes.push_back(std::move(holder));

        size = sf::Vector2f(250.f,200.f);
        pos = sf::Vector2i(1540,530);
        holder.reset(new Button("", myfont, size, pos, SAVE, SPELL5, gameWindow));
        this->boxes.push_back(std::move(holder));

    };

    void FightScene::update(sf::Event& e, sf::Vector2i m_mousePosition, GameWindow* gameWindow){
        sf::Time t;
        char objIndex = this->gState->getActualPlayerIndex();
        state::Position p;
        for(char i=0; i<this->gState->getPlayersCount(); i++){
            p = this->gState->playerPosition(i);
            std::string playerClass = (this->gState->getPlayerClass(i) == state::playerClass::HERO) ? "valla" : "demon";
            this->animatedObjects[i]->update(t,this->frameInfos[playerClass],playerClass+"_idle_se",this->worldToScreen(p));
        }  
        for(auto &boxe : this->boxes){
            (*boxe).update(e,m_mousePosition, gameWindow);
        }
    };


    void FightScene::draw (sf::RenderTarget& target, sf::RenderStates states) const{
        target.draw(*(this->gameMap), states);
        for (const auto& button : boxes){
            target.draw(*button,states);
        }
        for (const auto& animObj : animatedObjects){
            target.draw(*animObj,states);
        }

    };


    void FightScene::loadFrameInfos(std::string path){
        Json::Reader reader;
		std::ifstream test(path, std::ifstream::binary);
		bool parsingSuccessful = reader.parse( test, this->frameInfos, false );
		if ( !parsingSuccessful ){
			// report to the user the failure and their locations in the document.
			std::cout  << reader.getFormatedErrorMessages() << "\n";
		}
    }

    Json::Value& FightScene::getFrameInfos(){
        return this->frameInfos;
    } 


    void FightScene::bindState(engine::Engine& ngine){
        ngine.setState(this->gState);
    }

    sf::Vector2f FightScene::worldToScreen (state::Position position){
        sf::Vector2f screenPos = sf::Vector2f((float)position.getX(), (float)position.getY());
        screenPos.x=screenPos.x*270+270/2;
        screenPos.y=screenPos.y*270+270/2;
        screenPos = this->gameMap->isometricToOrthogonal(screenPos);
        return screenPos;
    }

    sf::Vector2f FightScene::screenToWorld (sf::Vector2f position){
        sf::Vector2f worldPos = this->gameMap->orthogonalToIsometric(position);
        worldPos.x = floor(worldPos.x/278);
        worldPos.y = floor(worldPos.y/278);
        return worldPos;
    }

    FightScene::~FightScene(){

    }
};

