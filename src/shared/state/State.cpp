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
        auto player = std::unique_ptr<Player>(new Player("goku",DEMON, Position(10,10), 1, user));
        ID p_id;
        p_id.id = player->getName();
        p_id.id.push_back('0');
        p_id.next = 1;
        p_id.prev = 1;
        this->players_id.push_back(p_id);
        this->users_index.push_back(0);

        this->players[0] = new std::map<std::string, std::unique_ptr<Player>>;
        this->players[1] = new std::map<std::string, std::unique_ptr<Player>>;
        this->players[p_id.id.back()-'0'][0][p_id.id] = std::move(player);

        this->gameMap[10][10].state = OCCUPIED;
        this->gameMap[10][10].player_index = 0;

        player = std::unique_ptr<Player>(new Player("buu",HERO, Position(11,11), 1, deep_ai));
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
        this->teamCount[0] = this->playersCount/2;
        this->teamCount[1] = this->playersCount/2;
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
    void State::passTurn (char selected){
        this->actualPlayerIndex = this->players_id[this->actualPlayerIndex].next;
        std::string id = this->players_id[actualPlayerIndex].id;
        this->players[id.back()-'0']->find(id)->second->resetPoints();
        if(selected==0){
            ai::AI::test = true;
            this->chrono->start(1,10);
        }
    };

    //  Permet d'annuler la fonction passTurn et de revenir au tour du joueur précédent
    void State::cancel_passTurn(char selected){
        if(selected!=0){
            this->actualPlayerIndex = this->players_id[this->actualPlayerIndex].prev;
        }
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
    void State::makeAttack (std::unique_ptr<engine::Action_Args>& args){
        if(this->inMap(args->point)){
            char st = (*this)[args->point].state;
            //std::cout << "t attttt = " << targetX << " " << targetY << std::endl;
            if(st == OCCUPIED){
                //std::cout << "t attttt = " << args->point[0] << " " << args->point[1] << std::endl;
                std::string attackerId = this->players_id[args->p_index].id;
                std::string taregtId   = this->players_id[(*this)[args->point].player_index].id;
                (*this)[attackerId]->attack((*this)[taregtId]);
                if(this->isDead((*this)[args->point].player_index)){
                    this->unlink((*this)[args->point].player_index);
                    this->teamCount[(taregtId.back()-'0')]--;
                    if(!teamCount[(taregtId.back()-'0')]){
                        this->winner = (*this)[attackerId]->getPClass();
                        this->endGame();
                    }

                }
            }
        }
    };

    //  Permet à un joueur de se déplacer à une position passée en argument
    void State::makeMove (std::unique_ptr<engine::Action_Args>& args){
        if(this->inMap(args->point)){
            if((*this)[args->point].state != OCCUPIED){
                std::string id = this->players_id[args->p_index].id;
                Position prevPos = (*this)[id]->getPosition();
                (*this)[prevPos].state = FREE;
                (*this)[args->point].player_index = args->p_index;
                (*this)[id]->move(args->point[0],args->point[1]);
                (*this)[args->point].state = OCCUPIED;
            }
            else{
                args->old_pos_mp[0] = -1;
            }
        }
    };

    //  Cette fonction retourne la position du joueur dont l’index a été passé en argument
    Position State::playerPosition (char playerIndex) {
        std::string id = this->players_id[playerIndex].id;
        return (*this)[id]->getPosition();
    };

    //  Cette fonction retourne la classe du joueur dont l’index a été passé en argument
    state::playerClass State::getPlayerClass (char playerIndex) {
        const std::string id = this->players_id[playerIndex].id;
        return (*this)[id]->getPClass();
    }

    //  Permet d’accéder au nombre de joueurs
    char  State::getPlayersCount () const{
        return this->playersCount;
    }

    //  Permet de changer l’attaque sélectionnée/actuelle du joueur dont c’est le tour
    void State::setCurrPlayerAttack (char attackIndex){
        const std::string id = this->players_id[this->actualPlayerIndex].id;
        (*this)[id]->setCurrentAttackIndex(attackIndex);
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
        return ((*this)[id]->getInput() != from::user);
    }

    //  Permet d’initialiser la variable ngine avec l’engine du jeu
    void State::connect (engine::Engine* ngine){
        this->ngine = std::shared_ptr<engine::Engine>(ngine);
    }

    //  Renvoie l’index de l’ennemi le plus proche
    char State::closestEnemyIndexTo (char p_index, int* pos){
        ID *id = &this->players_id[p_index];
        char enemies = !(id->id.back()-'0');
        Position source = (*this)[id->id]->getPosition();
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
                std::cout << "closest pos = " << pos[0] <<" " << pos[1] << std::endl;
                
                found = (*this)[pos].player_index;
            }
        }
        return found;
    }

    //  Renvoie l’index de l’ennemi le plus faible par rapport au joueur dont on passe l’index.
    char State::weakestEnemyIndexTo (char p_index, int* pos){
        ID *id = &this->players_id[p_index];
        char enemies = !(id->id.back()-'0');
        char found, level, weakest = 100;

        for(auto const& enemy : *(this->players[enemies])){
            level = enemy.second->getLevel();
            if(level < weakest){
                weakest = level;
                pos[0] = enemy.second->getPosition().x;
                pos[1] = enemy.second->getPosition().y;
                found = (*this)[pos].player_index;
            }
        }
        return found;
    }

    /*  Renvoie l’index de l’ennemi le plus fort (avec le niveau le plus élevé) par rapport au joueur 
        dont on passe l’index   */
    char State::strngestEnemyIndexTo (char p_index, int* pos){
        ID *id = &this->players_id[p_index];
        char enemies = !(id->id.back()-'0');
        char found, level, strongest = 0;

        for(auto const& enemy : *(this->players[enemies])){
            level = enemy.second->getLevel();
            if(level > strongest){
                strongest = level;
                pos[0] = enemy.second->getPosition().x;
                pos[1] = enemy.second->getPosition().y;
                found = (*this)[pos].player_index;
            }
        }
        return found;
    }

    //  Renvoie l’index de l’ennemi ayant le moins de points de vie par rapport au joueur dont on passe l’index.
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
                found = (*this)[pos].player_index;
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
                found = (*this)[pos].player_index;
            }
        }
        return found;
    }

    //  Retourne les dégâts qu’infligerait un joueur à un autre pour une attaque donnée
    int State::damage(char p_index, char attacker_index, Attack attack)
    {
        return (attack.damage+this->get_playerPower(attacker_index)-this->get_Shield(p_index));

    }

    // Permet de simuler les conséquences d'une attaque
    void State::simu_attack(char p_index, char t_index, char atck_index, state::Stats& p_stats,  state::Stats& t_stats){
        Attack atck = this->get_Attack(p_index, atck_index);
        int new_ap = p_stats.getAp()-atck.cost;
        new_ap = (new_ap > 0 ? new_ap : 0);
        p_stats.setAp(new_ap);
        int new_hp = t_stats.getShield()+t_stats.getHp()-atck.damage-p_stats.getAttack();
        t_stats.setHp(new_hp);
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
            playersStats[id]=(*this)[id]->getStats();  
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
            playersAttacks[id]=(*this)[id]->getAttacks();  
        }

        return(playersAttacks);
    }

    //  Permet d’obtenir les stats d’une d'un joueur donné 
    state::Stats State::getPlayerStats(char p_index){
        std::string id  = this->players_id[p_index].id;
        state::Stats st =(*this)[id]->getStats();
        return(st);
    }

    //  Récupère l'AP du joueur actuel et les HP de sa cible
    void State::pull_AP_THP (int x, int y, int ap_thp[2]){
        if(this->inMap(x,y)){
            ap_thp[0] = this->getPlayerStats(this->actualPlayerIndex).getAp();
            char st = this->gameMap[y][x].state;
            if(st == OCCUPIED){
                std::string taregtId = this->players_id[this->gameMap[y][x].player_index].id;
                ap_thp[1] = (*this)[taregtId]->getStats().getHp();
                std::cout << "t ap thp pos = " << x <<" " << y << std::endl;
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

    //  Renvoie les HP du joueur dont l’index est passé en argument
    int State::get_HP (char p_index){
        return this->getPlayerStats(p_index).getHp();
    }

    //  Renvoie la puissance l’attaque du joueur dont l’index est passé en argument
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
        return (*this)[id]->getCurrentAttackIndex();
    }

    //  Va permettre d’annuler un déplacement
    void State::cancel_move (std::unique_ptr<engine::Action_Args>& args){
        if(args->old_pos_mp[0] != -1){
            std::string id = this->players_id[args->p_index].id;
            Position prevPos = (*this)[id]->getPosition();
            (*this)[prevPos].state = FREE;
            (*this)[id]->setPosition(Position(args->old_pos_mp[0],args->old_pos_mp[1]));
            (*this)[id]->setMp(args->old_pos_mp[2]);
            (*this)[args->old_pos_mp].player_index = args->p_index;
            (*this)[args->old_pos_mp].state = OCCUPIED;
        }
    }

    //  Va permettre d’annuler une attaque
    void State::cancel_attack (std::unique_ptr<engine::Action_Args>& args){
        bool dead;
        auto sourceID = this->players_id[args->p_index].id;
        (*this)[sourceID]->setAp(args->old_ap_thp[0]);
        if(args->old_ap_thp[1] != -100){
            char st = (*this)[args->point].state;
            if(st == OCCUPIED){
                char t_index = (*this)[args->point].player_index;
                if(this->get_HP(t_index) <= 0){ dead = true; }
                std::string taregtId = this->players_id[t_index].id;
                (*this)[taregtId]->setHp(args->old_ap_thp[1]);
                if(this->get_HP(t_index) > 0){
                   (*this)[taregtId]->setStatus(WAITING);
                   this->gameOver = false;
                   if(dead){
                       this->link(t_index);
                       this->teamCount[(taregtId.back()-'0')]++;
                   }
                }
            }
        }
    }

    //  Va permettre d’annuler la sélection d’un sort
    void State::cancel_select (std::unique_ptr<engine::Action_Args>& args){
        auto id = this->players_id[args->p_index].id;
        (*this)[id]->setCurrentAttackIndex(args->old_attack_index);
    }

    //  Permet de changer tous les joueurs qui ne le sont pas en IA
    void State::turn_all_in_AI(){
        for (char index : users_index){
           this->turn_in_AI(index); 
        }
    }

    //  Permet de changer le statut du joueur dont l’index est passé en argument est de faire de lui un IA
    void State::turn_in_AI(char p_index){
        std::string id = this->players_id[p_index].id;
        (*this)[id]->setInput(user);
    }

    //  Permet de changer tous les joueurs qui n’étaient pas des IA à l’origine, de nouveau en joueurs réels
    void State::restore_all_users(){
        for (char index : users_index){
           this->restore_user(index); 
        }
    }

    /*  Permet de changer le statut du joueur dont l’index est passé en argument est de faire de lui un joueur 
    réel, qui n’est pas une IA. */
    void State::restore_user(char p_index){
        std::string id = this->players_id[p_index].id;
        (*this)[id]->setInput(user);
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

    /*  Prend en paramètres une position de départ et une position d’arrivée et détermine le chemin le plus 
        court pour réaliser ce trajet en prenant en compte les obstacles   */
    bool State::BFS_Shortest_Path (Position src, Position dst){
        std::cout << "bfs " <<std::endl;
        this->clear ();
        std::queue<Position> toExplore;
        Position directions[] = {Position(0,1), Position(1,0), Position(0,-1), Position(-1,0)};
        (*this)[dst].visited = true;
        (*this)[dst].distance = 0;
        toExplore.push(dst);
        while ( !toExplore.empty() ) {
            Position curr = toExplore.front();
            std::cout << "bfs distance = " << (*this)[curr].distance <<std::endl;
            std::cout << "bfs cuurr = " << curr.x << " " << curr.y << std::endl;

            if (curr == src) { return true; };
            toExplore.pop();
            for ( auto &direction : directions ) {
                Position neighbor = curr + direction;
                bool condition = (this->isFree(neighbor) || neighbor == src);
                if(this->inMap(neighbor) && condition){
                    if ((*this)[neighbor].visited   == false) {
                        (*this)[neighbor].visited   = true;
                        (*this)[neighbor].next_grid = curr;
                        (*this)[neighbor].distance  = (*this)[curr].distance + 1;
                        toExplore.push(neighbor);
                    }
                }
            }
        }
        return false;
    }

    /*  Il s'agit d'un opérateur nous permettant d’accéder plus simplement et plus rapidement à la variable 
        gameMap. En effet, si on se trouve dans la classe State, il suffit désormais de faire (*this)[position] 
        pour accéder à la case de la map souhaitée */
    inline MapTile& State::operator[] (Position p){
        return this->gameMap[p.y][p.x];
    }

    inline MapTile& State::operator[] (int point[2]){
        return this->gameMap[point[1]][point[0]];
    }

    inline std::unique_ptr<Player>& State::operator[] (std::string id){
        return this->players[id.back()-'0']->find(id)->second;
    }

    /*  Ces fonctions permettent de vérifier qu’une position se trouve au sein de la map. Elle renvoie true si 
        c’est le cas, false sinon    */
    inline bool State::inMap (Position p){
        return ( (p.x >= 0) && (p.y >= 0) && (p.x < this->gameMap.size()) && (p.y < this->gameMap.size()));
    }

    inline bool State::inMap (int p[2]){
        return ( (p[0] >= 0) && (p[1] >= 0) && (p[0] < this->gameMap.size()) && (p[1] < this->gameMap.size()));
    }

    inline bool State::inMap (int x, int y){
        return ( (x >= 0) && (y >= 0) && (x < this->gameMap.size()) && (y < this->gameMap.size()));
    }

    //  permet de vérifier qu’une case de la map est libre ou non. Elle renvoie true si c’est le cas, false sinon
    inline bool State::isFree (Position p){
        return ( ((*this)[p].state == FREE) );
    }

    /*  prend en argument l’index du joueur qui nous intéresse et renvoie l’index de son attaque 
        actuellement sélectionnée  */
    char State::getAttackIndex (char p_index){
        std::string id = this->players_id[p_index].id;
        return (*this)[id]->getCurrentAttackIndex();
    }

    /*  prend en argument l’index du joueur qui nous intéresse et renvoie l’attaque (l’objet) actuellement 
        sélectionnée par le joueur */
    Attack State::get_Attack (char p_index, char atck_index){
        std::string id = this->players_id[p_index].id;
        return (*this)[id]->getAttack(atck_index);
    }

    //  Renvoie les AP du joueur dont l’index est passé en argument
    int State::get_AP (char p_index){
        return this->getPlayerStats(p_index).getAp();
    }

    /*  Vérifie que le joueur dont on passe l'index en argument a suffisamment de PA pour réaliser l'attaque
        dont l'index est passé en argument  */
    bool State::hasEnough_AP (char p_index, char attack_index){
        return (this->get_AP(p_index) >= this->get_Attack(p_index, attack_index).cost);
    }

    /*  Permet de reinitialiser le statut 'visited' (utilisé pour le déplacement des IA) des cases de la map 
        à false */
    void State::clear (){
        int sizeXY = this->gameMap.size();
        for(int x = 0; x < sizeXY; x++){
            for(int y = 0; y < sizeXY; y++){
                (*this)[Position(x,y)].visited = false;
            }
        }
    }

    //  Renvoie le nombre d'ennemis du joueur dont l'index est passé en argument
    int State::enemiesCount(char p_index){
        std::string id = this->players_id[p_index].id;
        return this->teamCount[!(id.back()-'0')];
    }

    Position State::barycentre (char p_index){
        ID *id = &this->players_id[p_index];
        Position bar = Position(0,0), temp;
        char enemies = !(id->id.back()-'0');
        int w = 0, level;

        for(auto const& enemy : *(this->players[enemies])){
            level = enemy.second->getLevel();
            temp  = enemy.second->getPosition();
            bar   = bar + temp*level;
            w    += level;  
        }

        return (bar/w);

    }
    Position State::searchFreeAround (Position p){
        this->clear ();
        std::queue<Position> toExplore;
        Position directions[] = {Position(0,1), Position(1,0), Position(0,-1), Position(-1,0)};
        (*this)[p].visited = true;
        toExplore.push(p);
        while ( !toExplore.empty() ) {
            Position curr = toExplore.front();
            std::cout << "bfs distance = " << (*this)[curr].distance <<std::endl;
            std::cout << "bfs cuurr = " << curr.x << " " << curr.y << std::endl;
            toExplore.pop();
            for ( auto &direction : directions ) {
                Position neighbor = curr + direction;
                if(this->inMap(neighbor)){
                    if(this->isFree(neighbor)) { return neighbor; }
                    else{
                        if ((*this)[neighbor].visited   == false) {
                            (*this)[neighbor].visited   = true;
                            toExplore.push(neighbor);
                        }
                    }
                }
            }
        }

        return Position(-1,0);
    }

    void State::link (char p_index){
        char p_prev = this->players_id[p_index].prev;
        char p_next = this->players_id[p_index].next;
        this->players_id[p_prev].next = p_index;
        this->players_id[p_next].prev = p_index;
    }
    void State::unlink (char p_index){
        char p_prev = this->players_id[p_index].prev;
        char p_next = this->players_id[p_index].next;
        this->players_id[p_prev].next = p_next;
        this->players_id[p_next].prev = p_prev;
    }

};
