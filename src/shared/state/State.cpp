#include "State.h"
#include <functional>
#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <csignal>
#include <json/json.h>
#include <limits>

namespace state {
    /*
    The State class corresponds to the state of the entire game
    
    */
    char state::State::chronoCount = 10;
    char state::State::chronoStep = 1;
    State::State (int mapWidth, int mapHeight){
        this->init();
        Json::Reader reader;
        Json::Value tilesState;
		std::ifstream test("res/map/tiles.json", std::ifstream::binary);
		bool parsingSuccessful = reader.parse( test, tilesState, false );
		if ( !parsingSuccessful ){
			// report to the user the failure and their locations in the document.
			std::cout  << reader.getFormatedErrorMessages() << "\n";
		}
         
        MapTile tile;
        tile.type  = GRASS;
        this->gameMap.resize(22);

        for(unsigned int i = 0; i < mapWidth; i++){
            for(unsigned int j = 0; j < mapHeight; j++){
                tile.state = (state::tileState)(tilesState[std::to_string(i)][std::to_string(j)].asInt());
                this->gameMap[j].push_back(tile);
                std::cout << (int)tile.state << " ";
            }
            std::cout << std::endl;
        }

        this->players.resize(this->playersCount);
        auto player = std::unique_ptr<Player>(new Player("goku",DEMON, Position(10,10), 1, false));
        ID p_id;
        p_id.id = player->getName();
        p_id.id.push_back('0');
        p_id.next = 1;
        p_id.prev = 1;
        this->players_id.push_back(p_id);

        this->players[0] = new std::map<std::string, std::unique_ptr<Player>>;
        this->players[1] = new std::map<std::string, std::unique_ptr<Player>>;
        this->players[p_id.id.back()-'0'][0][p_id.id] = std::move(player);

        this->gameMap[10][10].state = OCCUPIED;
        this->gameMap[10][10].player_index = 0;

        player = std::unique_ptr<Player>(new Player("buu",HERO, Position(11,11), 1, true));
        p_id.id = player->getName();
        p_id.id.push_back('1');
        p_id.next = 0;
        p_id.prev = 0;
        this->players_id.push_back(p_id);
        this->players[p_id.id.back()-'0'][0][p_id.id] = std::move(player);

        
        this->gameMap[11][11].state = OCCUPIED;
        this->gameMap[11][11].player_index = 1;

        
    };

    //  Pour initialise le state au lancement du jeu
    void State::init (){
        this->turn = 0;
        this->playersCount = 2;
        this->actualPlayerIndex = 0;
        this->gameOver = false;
        this->chrono = std::unique_ptr<Chrono>(new Chrono);
        this->chrono->bind(SIGALRM);
    };

    //  Pour créer les joueurs (objets Player) au lancement du jeu
    void State::initPlayer (){
    
    };

    //  Pour charger la carte en début de partie.
    void State::initMap (){

    };

    /*  Vérifie les points de vie des joueurs, si un des joueurs n’a plus de vie, 
        la fonction repère le vainqueur et appelle la fonction endGame()   */
    bool State::isDead (char p_index){
        std::string id = this->players_id[p_index].id;
        return (this->players[id.back()-'0']->find(id)->second->getStatus() == DEAD);
    };

    //  Permet de passer le tour du joueur actuel et donner la main au joueur suivant
    void State::passTurn (){
        this->actualPlayerIndex = this->players_id[this->actualPlayerIndex].next;
        std::string id = this->players_id[actualPlayerIndex].id;
        this->players[id.back()-'0']->find(id)->second->resetPoints();
        this->chrono->start(1,10);
    };

    //  Incrémente la valeur turn quand on passe un tour
    void State::incrementTurn (){
        this->turn++;
    };

    //  Cette fonction entame la fin du jeu, elle passe notamment la variable gameOver à true
    void State::endGame (){
        this->gameOver = true;
    };

    //  Initialise la position des joueurs en début de partie
    void State::initPositions (){
        //efter
    };

    /*  Permet durant le tour d’un joueur de lancer une attaque à une position passée en argument. 
        L’attaque n’aboutira que si un joueur se trouve à cette position   */
    void State::makeAttackOn (int targetX, int targetY){
        if((targetX >= 0) && (targetY >= 0) && (targetX < this->gameMap.size()) && (targetY < this->gameMap.size())){
            char st = this->gameMap[targetY][targetX].state;
            if(st == OCCUPIED){
                std::string attackerId = this->players_id[this->actualPlayerIndex].id;
                std::string taregtId = this->players_id[this->gameMap[targetY][targetX].player_index].id;
                this->players[attackerId.back()-'0']->find(attackerId)->second->attack(this->players[taregtId.back()-'0']->find(taregtId)->second);
                if(this->isDead(this->gameMap[targetY][targetX].player_index))
                {
                    this->winner = this->players[attackerId.back()-'0']->find(attackerId)->second->getPClass();
                    this->endGame();
                }
            }
        }
    };

    //  Permet à un joueur de se déplacer à une position passée en argument
    void State::moveCurrentPlayer (int dstX, int dstY){
        if((dstX >= 0) && (dstY >= 0) && (dstX < this->gameMap.size()) && (dstY < this->gameMap.size())){
            std::string id = this->players_id[this->actualPlayerIndex].id;
            Position prevPos = this->players[id.back()-'0']->find(id)->second->getPosition();
            this->gameMap[prevPos.y][prevPos.x].state = FREE;
            this->gameMap[dstY][dstX].player_index = this->actualPlayerIndex;
            this->players[id.back()-'0']->find(id)->second->move(dstX,dstY);
            this->gameMap[dstY][dstX].state = OCCUPIED;
        }
    };

    //  Cette fonction retourne la position du joueur dont l’index a été passé en argument
    Position State::playerPosition (char playerIndex) {
        std::string id = this->players_id[playerIndex].id;
        return this->players[id.back()-'0']->find(id)->second->getPosition();
    };

    //  Cette fonction retourne la classe du joueur dont l’index a été passé en argument
    state::playerClass State::getPlayerClass (char playerIndex) {
        const std::string id = this->players_id[playerIndex].id;
        return this->players[id.back()-'0']->find(id)->second->getPClass();
    }

    //  Permet d’accéder au nombre de joueurs
    char  State::getPlayersCount () const{
        return this->playersCount;
    }

    //  Permet de changer l’attaque sélectionnée/actuelle du joueur dont c’est le tour
    void State::setCurrPlayerAttack (char attackIndex){
        const std::string id = this->players_id[this->actualPlayerIndex].id;
        this->players[id.back()-'0']->find(id)->second->setCurrentAttackIndex(attackIndex);
    }

    //  Passe la variable padlock à true
    void State::lock(){
        this->padlock = true;
    }

    //  Passe la variable padlock à false
    void State::unlock(){
        this->padlock = false;
        this->ngine->execute();
    }

    //  Permet de savoir si le joueur dont c’est le tour est une IA ou non
    bool State::isAI_Now(){
        const std::string id = this->players_id[this->actualPlayerIndex].id;
        return this->players[id.back()-'0']->find(id)->second->getIsAI();
    }

    //  Permet d’initialiser la variable ngine avec l’engine du jeu
    void State::connect (engine::Engine* ngine){
        this->ngine = std::shared_ptr<engine::Engine>(ngine);
    }

    //  Renvoie l’index de l’ennemi le plus proche
    char State::closestEnemyIndexTo (char p_index, int* pos){
        ID *id = &this->players_id[p_index];
        char enemies = !(id->id.back()-'0');
        Position source = this->players[id->id.back()-'0']->find(id->id)->second->getPosition();
        Position target;
        char found;
        int d = 0, min = 2*this->gameMap.size();

        for(auto const& enemy : *(this->players[enemies])){
            target = enemy.second->getPosition();
            d = abs(target.x - source.x) + abs(target.y - source.y);
            if(d < min){
                min = d;
                pos[0] = target.x;
                pos[1] = target.y;
                found = this->gameMap[pos[1]][pos[0]].player_index;
            }
        }
        return found;
    }

    //  Renvoie l’index de l’ennemi le plus faible
    char State::weakestEnemyIndexTo (char p_index, int* pos){
        Player p;
        p.getLevel();
        ID *id = &this->players_id[p_index];
        char enemies = !(id->id.back()-'0');
        char found, level, weakest = 100;

        for(auto const& enemy : *(this->players[enemies])){
            level = enemy.second->getLevel();
            if(level < weakest){
                weakest = level;
                pos[0] = enemy.second->getPosition().x;
                pos[1] = enemy.second->getPosition().y;
                found = this->gameMap[pos[1]][pos[0]].player_index;
            }
        }
        return found;
    }

    char State::strngestEnemyIndexTo (char p_index, int* pos){
        Player p;
        p.getLevel();
        ID *id = &this->players_id[p_index];
        char enemies = !(id->id.back()-'0');
        char found, level, strongest = 0;

        for(auto const& enemy : *(this->players[enemies])){
            level = enemy.second->getLevel();
            if(level > strongest){
                strongest = level;
                pos[0] = enemy.second->getPosition().x;
                pos[1] = enemy.second->getPosition().y;
                found = this->gameMap[pos[1]][pos[0]].player_index;
            }
        }
        return found;
    }

    //  Renvoie l’index de l’ennemi ayant le moins de points de vie
    char State::enemyWithLessHp_Of(char p_index, int* pos){
        ID *id = &this->players_id[p_index];
        char enemies = !(id->id.back()-'0');
        int found, hp, weakest = 16000;

        for(auto const& enemy : *(this->players[enemies])){
            hp = enemy.second->getStats().getHp();
            if(hp < weakest){
                weakest = hp;
                pos[0] = enemy.second->getPosition().x;
                pos[1] = enemy.second->getPosition().y;
                found = this->gameMap[pos[1]][pos[0]].player_index;
            }
        }
        return found;
    }

    //  Renvoie l’index de l’ennemi ayant le moins de points de mouvement
    char State::enemyWithLessMp_Of(char p_index, int* pos){
        ID *id = &this->players_id[p_index];
        char enemies = !(id->id.back()-'0');
        char found, mp, weakest = 10;

        for(auto const& enemy : *(this->players[enemies])){
            mp = enemy.second->getStats().getMp();
            if(mp < weakest){
                weakest = mp;
                pos[0] = enemy.second->getPosition().x;
                pos[1] = enemy.second->getPosition().y;
                found = this->gameMap[pos[1]][pos[0]].player_index;
            }
        }
        return found;
    }

    //  Retourne les dégâts qu’infligerait un joueur à un autre pour une attaque donnée
    int State::damage(char p_index, char attacker_index, Attack attack)
    {
        return (attack.damage+this->get_playerPower(attacker_index)-this->get_Shield(p_index));

    }

    //  Démarre l’horloge globale (lance le chrono).
    void State::chronoStart (char chronoStep, char chronoCount){
        this->chrono->start(chronoStep, chronoCount);
    }

    //  Permet d’obtenir les stats de tous les joueurs 
    std::map<std::string,state::Stats> State::getPlayerStats() {
        std::map<std::string,state::Stats> playersStats;
        
        for(unsigned int i = 0; i < this->players_id.size(); i++) {
            std::string id = this->players_id[i].id;
            playersStats[id]=this->players[id.back()-'0']->find(id)->second->getStats();  
        }

        return(playersStats);
        
    }

    //  Permet d’obtenir un std ::vector contenant les structures ID des différents joueurs
    std::vector<ID> State::getPlayersID(){
        return(this->players_id);
    }

    /*  Permet d’obtenir un std::map<std::string,std::vector<Attack>> qui associe à l’identifiant 
        du joueur (nom concaténé à ‘0’ ou ‘1’) à sa liste d’attaques    */
    std::map<std::string,std::vector<Attack>> State::getPlayersAttacks(){
        std::map<std::string,std::vector<Attack>> playersAttacks;
        
        for(unsigned int i = 0; i < this->players_id.size(); i++)
        {
            std::string id = this->players_id[i].id;
            playersAttacks[id]=this->players[id.back()-'0']->find(id)->second->getAttacks();  
        }

        return(playersAttacks);
    }

    //  Permet d’obtenir les stats d’une d'un joueur donné 
    state::Stats State::getPlayerStats(char p_index){
        std::string id  = this->players_id[p_index].id;
        state::Stats st =this->players[id.back()-'0']->find(id)->second->getStats();
        return(st);
    }

    //  Récupère l'AP du joueur actuel et les HP de sa cible
    void State::pull_AP_THP (int x, int y, int ap_thp[2]){
        if((x >= 0) && (y >= 0) && (x < this->gameMap.size()) && (y < this->gameMap.size())){
            ap_thp[0] = this->getPlayerStats(this->actualPlayerIndex).getAp();
            char st = this->gameMap[y][x].state;
            if(st == OCCUPIED){
                std::string taregtId = this->players_id[this->gameMap[y][x].player_index].id;
                ap_thp[1] = this->players[taregtId.back()-'0']->find(taregtId)->second->getStats().getHp();
            }
            else{
                ap_thp[1] = -100;
            }
        }
    }

    //  Renvoie les MP du joueur dont l’index est passé en argument
    int State::get_MP (char p_index){
        return this->getPlayerStats(p_index).getMp();
    }

    //  Renvoie l’attaque du joueur dont l’index est passé en argument
    int State::get_playerPower (char p_index){
        return this->getPlayerStats(p_index).getAttack();
    }

    //  Renvoie le shield du joueur dont l’index est passé en argument
    int State::get_Shield (char p_index){
        return this->getPlayerStats(p_index).getShield();
    }

    //  Renvoie la valeur currentAttackPlayer du joueur dont l’index est passé en argument
    char State::getCurrAttackIndex (char p_index){
        std::string id = this->players_id[p_index].id;
        return this->players[id.back()-'0']->find(id)->second->getCurrentAttackIndex();
    }

    //  Va permettre d’annuler un déplacement
    void State::cancel_move (int old_pos_mp[3]){
        std::string id = this->players_id[this->actualPlayerIndex].id;
        Position prevPos = this->players[id.back()-'0']->find(id)->second->getPosition();
        this->gameMap[prevPos.y][prevPos.x].state = FREE;
        this->players[id.back()-'0']->find(id)->second->setPosition(Position(old_pos_mp[0],old_pos_mp[1]));
        this->players[id.back()-'0']->find(id)->second->setMp(old_pos_mp[2]);
        this->gameMap[old_pos_mp[1]][old_pos_mp[0]].player_index = this->actualPlayerIndex;
        this->gameMap[old_pos_mp[1]][old_pos_mp[0]].state = OCCUPIED;
    }

    //  Va permettre d’annuler une attaque
    void State::cancel_attack (int target[2], int old_ap_thp[2]){
        auto sourceID = this->players_id[this->actualPlayerIndex].id;
        this->players[sourceID.back()-'0']->find(sourceID)->second->setAp(old_ap_thp[0]);
        if(old_ap_thp[1] != -100){
            char st = this->gameMap[target[1]][target[0]].state;
            if(st == OCCUPIED){
                std::string taregtId = this->players_id[this->gameMap[target[1]][target[0]].player_index].id;
                this->players[taregtId.back()-'0']->find(taregtId)->second->setHp(old_ap_thp[1]);
            }
        }
    }

    //  Va permettre d’annuler la sélection d’un sort
    void State::cancel_select (int old_attack_index){
        auto id = this->players_id[this->actualPlayerIndex].id;
        this->players[id.back()-'0']->find(id)->second->setCurrentAttackIndex(old_attack_index);
    }

    State::~State (){

    };

    //-----------------------------Setters and Getters-----------------------------

    const std::vector<std::vector<MapTile>>& State::getGameMap() const{
        return this->gameMap;
    };
    void State::setGameMap(const std::vector<std::vector<MapTile>>& gameMap){
        this->gameMap = gameMap;
    };
    int State::getTurn() const{
        return this->turn;
    };
    void State::setTurn(int turn){
        this->turn = turn;
    };
    // get the index of the actual player
    char State::getActualPlayerIndex() const{
        return this->actualPlayerIndex;
    };
    void State::setActualPlayerIndex(char actualPlayerIndex){
        this->actualPlayerIndex = actualPlayerIndex;
    };
    bool State::getGameOver() const{
        return this->gameOver;
    };
    void State::setGameOver(bool gameOver){
        this->gameOver = gameOver;
    };
    playerClass State::getWinner() const{
        return this->winner;
    };
    bool State::BFS_Shortest_Path (Position src, Position dst){
        std::queue<Position> toExplore;
        Position directions[] = {Position(0,1), Position(1,0), Position(0,-1), Position(-1,0)};
        (*this)[dst].visited = 0;
        toExplore.push(dst);
        while ( !toExplore.empty() ) {
            Position curr = toExplore.front();
            if (curr == src) { return true; };
            toExplore.pop();
            for ( auto &direction : directions ) {
                Position neighbor = curr + direction;
                if(neighbor == (*this)[curr].next_grid) continue;
                if(this->inMap(neighbor) && this->isFree(neighbor)){
                    if ((*this)[neighbor].visited   == false) {
                        (*this)[neighbor].visited   = true;
                        (*this)[neighbor].next_grid = curr;
                        (*this)[neighbor].distance  = (*this)[curr].distance + 1;
                        toExplore.push(neighbor);
                    }
                }
            }

            (*this)[curr].visited = false;
        }
        return false;
    }

    MapTile& State::operator[] (Position p){
        return this->gameMap[p.y][p.x];
    }

    inline bool State::inMap (Position p){
        return ( (p.x >= 0) && (p.y >= 0) && (p.x < this->gameMap.size()) && (p.y < this->gameMap.size()));
    }

    inline bool State::isFree (Position p){
        return ( ((*this)[p].state == FREE) );
    }

    char State::getAttackIndex (char p_index){
        std::string id = this->players_id[p_index].id;
        return this->players[id.back()-'0']->find(id)->second->getCurrentAttackIndex();
    }

    Attack State::get_Attack (char p_index){
        char attack_index = this->getAttackIndex(p_index);
        std::string id = this->players_id[p_index].id;
        return this->players[id.back()-'0']->find(id)->second->getAttack(attack_index);
    }

};
