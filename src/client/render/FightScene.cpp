#include "FightScene.h"
#include <fstream>
#include <iostream> 

namespace render{
    FightScene::FightScene(){

        this->gState = new state::State(22,22);
        this->loadFrameInfos("data/frames_info.json");
        //this->texture = std::shared_ptr<sf::Texture>(new sf::Texture);
        this->texture.loadFromFile("res/frames.png");

        //this->loadTextures("res/frames.png");
        sf::Time t;
        //std::cout << "ste\n";
        std::unique_ptr<AnimatedObject> aniObjects;
        state::Position p;
        for(char i=0; i<2; i++){
            p = this->gState->playerPosition(i);
            std::string playerClass = (this->gState->getPlayerClass(i) == state::playerClass::HERO) ? "valla" : "demon";
            
            //std::cout << (i==0 ? "0" : "1")<< (i==1 ? "0" : "1") << playerClass <<"\n";
            aniObjects = std::unique_ptr<AnimatedObject>(new AnimatedObject(this->texture));
            this->animatedObjects.push_back(std::move(aniObjects));
            this->animatedObjects[i]->update(t,this->frameInfos[playerClass],playerClass+"_idle_se",sf::Vector2f(p.getX(),p.getY()));
        }  

    };

    void FightScene::update(){
        std::cout<< "FightScene upd\n";
        sf::Time t;
        char objIndex = this->gState->getActualPlayerIndex();
        state::Position p = this->gState->playerPosition(objIndex);
        std::string playerClass = (this->gState->getPlayerClass(objIndex) == state::playerClass::HERO) ? "valla" : "demon";
        std::cout << playerClass << std::endl;
        std::cout<<"fs upd pos = " <<(int)p.getX() << std::endl;
        this->animatedObjects[objIndex]->update(t,this->frameInfos[playerClass],playerClass+"_idle_se",sf::Vector2f(p.getX(),p.getY()));
        std::cout<<"fs upd pos = " <<(int)p.getX() << std::endl;
        //std::cout<< "FightScene upd idx = " << (int)objIndex << std::endl;
    };


    void FightScene::draw (sf::RenderTarget& target, sf::RenderStates states) const{

        for (const auto& animObj : animatedObjects){
            target.draw(*animObj,states);
        }

    };

    
  // const std::vector<std::unique_ptr<AnimatedObject>>& getAnimatedObjects() const{};
    //void setAnimatedObjects(const std::vector<std::unique_ptr<AnimatedObject>>& animatedObjects){};
    
    void FightScene::loadFrameInfos(std::string path){
        Json::Reader reader;
		std::ifstream test(path, std::ifstream::binary);
		bool parsingSuccessful = reader.parse( test, this->frameInfos, false );
		if ( !parsingSuccessful )
		{
			// report to the user the failure and their locations in the document.
			std::cout  << reader.getFormatedErrorMessages()
				<< "\n";
		}
    }

    Json::Value& FightScene::getFrameInfos(){
        return this->frameInfos;
    } 

    FightScene::~FightScene(){

    }
};

