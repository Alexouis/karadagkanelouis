#include "FightScene.h"


namespace render{
    FightScene::FightScene(){

    };

    void FightScene::update(){
        sf::Vector2f pos(500,400);
        for (const auto& animObj : animatedObjects){
            sf::Time t;
            animObj->update(t,frameInfos,0,pos);
        }
    };

    const state::State*& FightScene::getGState() const{
       // return gState;
    };

    void FightScene::setGState(const state::State*& gState){
       // this->gState=&gState;
    };

    void FightScene::draw (sf::RenderTarget& target, sf::RenderStates states) const{

        for (const auto& animObj : animatedObjects){
            target.draw(*animObj,states);
        }

    };
};

