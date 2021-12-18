#include "FightScene.h"
#include <fstream>
#include <iostream> 

namespace render{
    FightScene::FightScene(){
       // std::ifstream img("frames_info.json", );
       loadFrameInfos("data/frames_info_json");
       //for()
       
    };

    void FightScene::update(){
        sf::Time t;
        char objIndex = this->gState->getActualPlayerIndex();
        animatedObjects[objIndex]->update(t,this->frameInfos,0,sf::Vector2f(500,500));
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

