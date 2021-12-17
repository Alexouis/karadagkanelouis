#include "FightScene.h"


namespace render{
    FightScene::FightScene(){

    };

    void FightScene::update(){
        for (int i=0;i<animatedObjects.size();i++){
            sf::Time t;
  //          int posx=state::State::players[0][players_id[i]]::Position.getX();
 //           int posy=state::State::players[0][players_id[i]]::Position.getY();
            animatedObjects[i]->update(t,frameInfos,0,sf::Vector2f(0,0));
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

