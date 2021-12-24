#include "FightScene.h"
#include "Button.h"
#include <fstream>
#include <iostream> 

#define GAMEWINDOWHEIGHT 600
#define GAMEWINDOWWIDTH 2000
#define GAMEWINDOWZOOM 4

namespace render{
    FightScene::FightScene(){

        this->gState = std::shared_ptr<state::State>(new state::State(22,22));
        this->gameMap->load("map_1.tmx");
        this->loadFrameInfos("data/frames_info.json");
        this->texture.loadFromFile("res/frames.png");

        this->initButtons();

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

    void FightScene::initButtons()
    {   
        sf::Font myfont;
        if(!myfont.loadFromFile("./extern/tmx-loader/fonts/Ubuntu-M.ttf"))
        {
            std::cerr<<"Could not find contb.ttf font."<<std::endl;
        }
        std::unique_ptr<Box> holder = std::unique_ptr<Button>(new Button("MENU", myfont,sf::Vector2f(250.f,100.f), sf::Vector2f(-2650,(GAMEWINDOWZOOM+0.5)*200), CANCEL)); 
        this->boxes.push_back(std::move(holder));
        holder = std::unique_ptr<Button>(new Button("\n\nPASSER \n\nSON TOUR!", myfont,sf::Vector2f(450.f,300.f), sf::Vector2f(GAMEWINDOWWIDTH/2,(GAMEWINDOWZOOM+1)*GAMEWINDOWHEIGHT), CANCEL));
        this->boxes.push_back(std::move(holder));
        holder = std::unique_ptr<Button>(new Button("Sort 1", myfont, sf::Vector2f(250.f,200.f), sf::Vector2f(GAMEWINDOWWIDTH*1.5,(GAMEWINDOWZOOM+1)*GAMEWINDOWHEIGHT), SAVE));
        this->boxes.push_back(std::move(holder));
        holder = std::unique_ptr<Button>(new Button("Sort 2", myfont, sf::Vector2f(250.f,200.f), sf::Vector2f(GAMEWINDOWWIDTH*1.5+250,(GAMEWINDOWZOOM+1)*GAMEWINDOWHEIGHT), SAVE));
        this->boxes.push_back(std::move(holder));
        holder = std::unique_ptr<Button>(new Button("", myfont, sf::Vector2f(250.f,200.f), sf::Vector2f(GAMEWINDOWWIDTH*1.5+500,(GAMEWINDOWZOOM+1)*GAMEWINDOWHEIGHT), SAVE));
        this->boxes.push_back(std::move(holder));
        holder = std::unique_ptr<Button>(new Button("", myfont, sf::Vector2f(250.f,200.f), sf::Vector2f(GAMEWINDOWWIDTH*1.5+750,(GAMEWINDOWZOOM+1)*GAMEWINDOWHEIGHT), SAVE));
        this->boxes.push_back(std::move(holder));
        holder.reset(new Button("", myfont, sf::Vector2f(250.f,200.f), sf::Vector2f(GAMEWINDOWWIDTH*1.5+1000,(GAMEWINDOWZOOM+1)*GAMEWINDOWHEIGHT), SAVE));
        this->boxes.push_back(std::move(holder));

    };

    void FightScene::update(sf::Event& e, sf::Vector2i m_mousePosition){
        sf::Time t;
        char objIndex = this->gState->getActualPlayerIndex();
        state::Position p;
        for(char i=0; i<this->gState->getPlayersCount(); i++){
            p = this->gState->playerPosition(i);
            std::string playerClass = (this->gState->getPlayerClass(i) == state::playerClass::HERO) ? "valla" : "demon";
            this->animatedObjects[i]->update(t,this->frameInfos[playerClass],playerClass+"_idle_se",this->worldToScreen(p));
        }  
        for(auto &boxe : this->boxes){
            (*boxe).update(e,m_mousePosition);
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
			std::cout  << reader.getFormatedErrorMessages()
				<< "\n";
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

