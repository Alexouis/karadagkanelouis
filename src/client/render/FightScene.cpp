#include "FightScene.h"
#include "GameWindow.h"
#include "Button.h"
#include "Info.h"
#include <fstream>
#include <iostream> 
#include <iterator>

#define GAMEWINDOWHEIGHT 600
#define GAMEWINDOWWIDTH 2000
#define GAMEWINDOWZOOM 4

#define map_sizeX 22
#define map_sizeY 22

#define CODE_MASK(X)   ((   X & 0x70 ) >> 4 )  //return code
#define SPELL1 0x0 //[code value] =  [0000 0000]
#define SPELL2 0x1 //[code value] =  [0000 0001]
#define SPELL3 0x2 //[code value] =  [0000 0010]
#define SPELL4 0x3 //[code value] =  [0000 0011]
#define SPELL5 0x4 //[code value] =  [0000 0100]
#define MENU 0x10  //[code value] =  [0001 0000]
#define PASS 0x20  //[code value] =  [0010 0000]

namespace render{
    FightScene::FightScene(char id, GameWindow* gameWindow){

        this->id = id;
        this->gState = std::shared_ptr<state::State>(new state::State(map_sizeX,map_sizeY));
        this->gameMap->load("map_1.tmx");
        this->loadFrameInfos("data/frames_info.json");
        this->texture.loadFromFile("res/frames.png");
        this->playersAttacks = this->gState->getPlayersAttacks();

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
        unsigned int fontSize;
        sf::Font myfont;
        if(!myfont.loadFromFile("./extern/tmx-loader/fonts/Ubuntu-M.ttf"))
        {
            std::cerr<<"Could not find contb.ttf font."<<std::endl;
        }

        size = sf::Vector2f(80.f,30.f);
        pos = sf::Vector2i(60,30);
        fontSize = 15;
        std::unique_ptr<Box> holder = std::unique_ptr<Button>(new Button("MENU", fontSize,myfont, size, pos , CANCEL, MENU, gameWindow)); 
        boxes["MENU"]=std::move(holder);

        size = sf::Vector2f(100.f,100.f);
        pos = sf::Vector2i(980,530);
        fontSize = 15;
        holder = std::unique_ptr<Button>(new Button("\n\n   PASSER \n\nSON TOUR!",fontSize, myfont,size, pos, CLEAN, PASS, gameWindow));
        boxes["PASS"]=std::move(holder);

        size = sf::Vector2f(100.f,50.f);
        pos = sf::Vector2i(1180,525);
        fontSize = 25;
        holder = std::unique_ptr<Button>(new Button("Sort 1",fontSize, myfont, size, pos, SAVE, SPELL1, gameWindow));
        boxes["SORT1"]=std::move(holder);

        size = sf::Vector2f(100.f,50.f);
        pos = sf::Vector2i(1285,525);
        holder = std::unique_ptr<Button>(new Button("Sort 2",fontSize, myfont, size, pos, SAVE, SPELL2, gameWindow));
        boxes["SORT2"]=std::move(holder);

        size = sf::Vector2f(100.f,50.f);
        pos = sf::Vector2i(1390,525);
        holder = std::unique_ptr<Button>(new Button(" ",fontSize, myfont, size, pos, SAVE, SPELL3, gameWindow));
        boxes["SORT3"]=std::move(holder);

        size = sf::Vector2f(100.f,50.f);
        pos = sf::Vector2i(1495,525);
        holder = std::unique_ptr<Button>(new Button(" ",fontSize, myfont, size, pos, SAVE, SPELL4, gameWindow));
        boxes["SORT4"]=std::move(holder);

        size = sf::Vector2f(100.f,50.f);
        pos = sf::Vector2i(1600,525);
        fontSize = 25;
        holder = std::unique_ptr<Button>(new Button(" ",fontSize, myfont, size, pos, SAVE, SPELL5, gameWindow));
        boxes["SORT5"]=std::move(holder);

        pos = sf::Vector2i(800,10);
        this->playersStats = this->gState->getPlayerStats();
        std::stringstream ss;
        for(const auto& [key, value] : playersStats)
        {
            ss << key << " - HP : " << value.getHp() << " - PA : " << value.getAp() << " - PM : " << value.getMp() << std::endl ;
            holder= std::unique_ptr<Info>(new Info(ss.str(),myfont, fontSize, pos, gameWindow));
            boxes[key]=std::move(holder);
        } 

        pos = sf::Vector2i(880,440);
        ss << "Temps restant: "<< (int)this->gState->chronoCount;
        holder.reset(new Info(ss.str(),myfont, fontSize, pos, gameWindow));
        boxes["Chrono"]=std::move(holder);


    };

    void FightScene::update(){
        sf::Time t;
        state::Position p;
        std::stringstream ssChr,ssStats;
        this->playersStats = this->gState->getPlayerStats();
        char objIndex = this->gState->getActualPlayerIndex();
        for(char i=0; i<this->gState->getPlayersCount(); i++){
            p = this->gState->playerPosition(i);
            std::string playerClass = (this->gState->getPlayerClass(i) == state::playerClass::HERO) ? "valla" : "demon";
            this->animatedObjects[i]->update(t,this->frameInfos[playerClass],playerClass+"_idle_se",this->worldToScreen(p));
        }
        this->playersStats = this->gState->getPlayerStats();
        if(this->showVertex)
        {
            this->moveRange();
        }
        else
        {
            this->moveVertex.clear();
        }
        ssChr << "Temps restant: "<< (int)this->gState->chronoCount;
        this->boxes["Chrono"]->setText(ssChr.str());
        for(const auto& [key, value] : playersStats)
        {
            ssStats << key << "   HP : " << value.getHp() << "   PA : " << value.getAp() << "   PM : " << value.getMp() << std::endl ;
            this->boxes[key]->setText(ssStats.str());
        }
        if(this->gState->getGameOver())
        {
            this->gameOver = true;
        }
    };

    void FightScene::update(sf::Event& e, sf::Vector2i m_mousePosition, GameWindow* gameWindow){     
        if(CODE_MASK(gameWindow->selected)==0)
        {
            this->attackRange(gameWindow->selected);
        }
        else
        {
            this->attackVertex.clear();
        }
        for(const auto& [key, value] : this->boxes){
            (*value).update(e,m_mousePosition, gameWindow);
        }
        if(e.key.code == sf::Keyboard::D)
        {
            this->showVertex = !(this->showVertex);
        }
    };

    void FightScene::draw (sf::RenderTarget& target, sf::RenderStates states) const{
        target.draw(*(this->gameMap), states);

        for (int i=0; i<this->moveVertex.size(); i++){
            target.draw(this->moveVertex[i],states);
        }
        for (int i=0; i<this->attackVertex.size(); i++){
            target.draw(this->attackVertex[i],states);
        }
        for (const auto& animObj : animatedObjects){
            target.draw(*animObj,states);
        }
        
        for (const auto& [key, value] : boxes){
            target.draw(*value,states);
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

    void FightScene::moveRange()
    {
        this->playersStats = this->gState->getPlayerStats();
        moveVertex.clear();
        uint m_tileWidth = this->gameMap->getTileSize().x;
        uint m_tileHeight = this->gameMap->getTileSize().y;
        float m_tileRatio = static_cast<float>(m_tileWidth) / static_cast<float>(m_tileHeight);
        float x = static_cast<float>(m_tileWidth) / m_tileRatio;
        float y = static_cast<float>(m_tileHeight); 
        int p = playersStats[gState->getPlayersID()[gState->getActualPlayerIndex()].id].getMp();
        int dy_x = 0;
        sf::Color debugColour(255u, 0u, 20u, 120u);

        state::Position pos = this->gState->playerPosition(gState->getActualPlayerIndex());
        
        for(int i=pos.getX()-p; i<=pos.getX()+p; i++)
        {
            dy_x = p-abs(pos.getX()-i);
            for(int j=pos.getY()-dy_x; j<=pos.getY()+dy_x; j++)
            {
                sf::VertexArray m_gridVertices;
                m_gridVertices.append(sf::Vertex(this->gameMap->isometricToOrthogonal(sf::Vector2f(i*x    , j*y    )), debugColour));
                m_gridVertices.append(sf::Vertex(this->gameMap->isometricToOrthogonal(sf::Vector2f(i*x + x, j*y    )), debugColour));
                m_gridVertices.append(sf::Vertex(this->gameMap->isometricToOrthogonal(sf::Vector2f(i*x + x, j*y + y)), debugColour));
                m_gridVertices.append(sf::Vertex(this->gameMap->isometricToOrthogonal(sf::Vector2f(i*x    , j*y + y)), debugColour));
                m_gridVertices.setPrimitiveType(sf::Quads);
                moveVertex.push_back(m_gridVertices);                
            }
        }
    }

    int FightScene::attackRange(char selected)
    {
        int p = 0;
        std::vector<state::Attack> attacks = this->playersAttacks[gState->getPlayersID()[gState->getActualPlayerIndex()].id];
        switch(selected)
        {
            case 0x0:
            {
                p = attacks[0].range;
                break;
            }

            case 0x1:
            {
                p = attacks[1].range;
                break;
            }
            default:
            {
                return 0;
                break;
            }
        }
        attackVertex.clear();
        uint m_tileWidth = this->gameMap->getTileSize().x;
        uint m_tileHeight = this->gameMap->getTileSize().y;
        float m_tileRatio = static_cast<float>(m_tileWidth) / static_cast<float>(m_tileHeight);
        float x = static_cast<float>(m_tileWidth) / m_tileRatio;
        float y = static_cast<float>(m_tileHeight); 
        int dy_x = 0;
        sf::Color debugColour(20u, 0u, 255u, 120u);

        state::Position pos = this->gState->playerPosition(gState->getActualPlayerIndex());
        
        for(int i=pos.getX()-p; i<=pos.getX()+p; i++)
        {
            dy_x = p-abs(pos.getX()-i);
            for(int j=pos.getY()-dy_x; j<=pos.getY()+dy_x; j++)
            {
                sf::VertexArray m_gridVertices;
                m_gridVertices.append(sf::Vertex(this->gameMap->isometricToOrthogonal(sf::Vector2f(i*x    , j*y    )), debugColour));
                m_gridVertices.append(sf::Vertex(this->gameMap->isometricToOrthogonal(sf::Vector2f(i*x + x, j*y    )), debugColour));
                m_gridVertices.append(sf::Vertex(this->gameMap->isometricToOrthogonal(sf::Vector2f(i*x + x, j*y + y)), debugColour));
                m_gridVertices.append(sf::Vertex(this->gameMap->isometricToOrthogonal(sf::Vector2f(i*x    , j*y + y)), debugColour));
                m_gridVertices.setPrimitiveType(sf::Quads);
                attackVertex.push_back(m_gridVertices);
            }
        }

        return 0;
    }

    Json::Value& FightScene::getFrameInfos(){
        return this->frameInfos;
    } 


    void FightScene::bindState(engine::Engine& ngine){
        ngine.setState(this->gState);
    }

    sf::Vector2f FightScene::worldToScreen (state::Position position){
        uint m_tileHeight = this->gameMap->getTileSize().y;
        float y = static_cast<float>(m_tileHeight); 
        sf::Vector2f screenPos = sf::Vector2f((float)position.getX(), (float)position.getY());
        screenPos = this->gameMap->isometricToOrthogonal(sf::Vector2f(position.getX()*y+y/2,position.getY()*y+y/2));
        return screenPos;
    }

    sf::Vector2f FightScene::screenToWorld (sf::Vector2f position){
        uint m_tileHeight = this->gameMap->getTileSize().y;
        float y = static_cast<float>(m_tileHeight); 
        sf::Vector2f worldPos = this->gameMap->orthogonalToIsometric(position);
        worldPos.x = floor(worldPos.x/y);
        worldPos.y = floor(worldPos.y/y);
        return worldPos;
    }
    

    FightScene::~FightScene(){

    }
};

