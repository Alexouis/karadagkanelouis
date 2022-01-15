/*
 * File             Engine.cpp
 * Directory        engine
 * Created Date     Friday, December 17th 2021, 8:09:49 pm
 * Author           Nouhou KANE
 * Email            nouhou.kane@ensea.fr
 * 
 * Copyright (c) 2021  ENSEA(FR)
 * __________________________________________________________________________
 */
#include <iostream>
#include "engine.h"
#include <iostream> 

#define CODE_MASK(X)   ((   X & 0x70 ) >> 4 )  //return code
#define CODE_ACTION(X) (((  X & 0x10 ) >> 4 ) | ((  X & 0x20 ) >> 5 )) //to knw if move or attack
#define VALUE_MASK(X)  (    X & 0xF  )         //return value
#define ACTION(X)      ((   X & 0xF0 ) >> 7 )  //return targetCode

#define SPELL1 0x0 //[targetCode code value] =  [0 000 0000]
#define SPELL2 0x1 //[targetCode code value] =  [0 000 0001]
#define SPELL3 0x2 //[targetCode code value] =  [0 000 0010]
#define SPELL4 0x3 //[targetCode code value] =  [0 000 0011]
#define SPELL5 0x4 //[targetCode code value] =  [0 000 0100]
#define MENU 0x10  //[targetCode code value] =  [0 001 0000]
#define PASS 0x20  //[targetCode code value] =  [0 010 0000]
#define START 0x30  //[code value] =  [0011 0000]


namespace engine{
    typedef void (*Func)(std::unique_ptr<Action_Args>&);
    Engine::Engine(){
        this->cmd.reserve(2);
        //this->selection.reserve(4);

        this->cmd[0] = &Engine::atck_cmd;
        this->cmd[1] = &Engine::move_cmd;

        this->selection[0][0] = &Action::select;
        this->selection[0][1] = &Action::cancel_select;
        this->selection[1][0] = &Action::doNothing;
        this->selection[1][1] = &Action::doNothing;
        this->selection[2][0] = &Action::passTurn;
        this->selection[2][1] = &Action::doNothing;
        this->selection[3][0] = &Action::startGame;
        this->selection[3][1] = &Action::doNothing;
    }

    //  Pour démarrer l’engine
    void Engine::start(){
        this->eThread = std::thread(&Engine::run, this);
        if(this->eThread.joinable()){ 
            this->eThread.join(); 
        }
    }

    //  Pour arrêter l’engine
    void Engine::stop(){
        this->fuel = false;
    }

    /*  qui va mettre en route le moteur de jeu (écoute des actions des joueurs + mise à jour du state 
        + exécution des IA).    */
    void Engine::run(){
        while(!this->currentState->getGameOver()){
            if(!this->qcmd.empty()){
                this->qcmd.front()->action(cmdHolder->args);
                this->qcmd.pop();
            }
        }
        this->cmdHolder.release();
    }

    //  Afin d’ajouter une nouvelle commande à la queue actuelle
    void Engine::addCommand(std::unique_ptr<Command>& cmd){
        this->qcmd.push(std::move(cmd));
    }

    //  Permet d’exécuter les commandes de la queue. Exécute la commande en tête de file
    void Engine::execute(){
        if(!this->qcmd.empty()){
            this->qcmd.front()->action(this->qcmd.front()->args);
            this->cmdHistory.push(std::move(this->qcmd.front()));
            this->qcmd.pop();
            this->cmdUndid.clear();
            return;
        }
        if(Engine::timeOut()){
            this->currentState->passTurn();
        }
    }

    //  Prend en paramètre une commande et l’exécute.
    void Engine::execute(std::unique_ptr<Command>& cmd){
        cmd->action(cmd->args);
        this->cmdHistory.push(std::move(cmd));
        this->currentState->lock();
    }

    //  Pour mettre à jour currentState et c’est-à-dire actualiser l’état de jeu dans l’engine
    void Engine::setState(std::shared_ptr<state::State>& gState){
        this->currentState = gState;
        this->currentState->connect(this);
    }
    //  Permet d’enregistrer les commandes dans la queue
    void Engine::registerTarget (int x, int y, char selected){
        if(ACTION(selected)){
            this->cmdHolder = (this->cmd[CODE_ACTION(this->selected)])(this->currentState, x, y);
            this->qcmd.push(std::move(cmdHolder));
            this->selected = selected;
        }
        else{
            this->registerTarget(selected);
            this->execute();
        }
    }

    //  Permet d’enregistrer les commandes dans la queue
    void Engine::registerTarget (char selected){
        this->selected = selected;
        char old_attack_index = this->currentState->getCurrAttackIndex(this->currentState->getActualPlayerIndex());
        auto args = std::unique_ptr<Action_Args>(new Action_Args(this->currentState, VALUE_MASK(selected), old_attack_index));
        this->cmdHolder = std::unique_ptr<Command>(new Command(this->selection[CODE_MASK(selected)], args));
        this->qcmd.push(std::move(cmdHolder));
    }

    //  Pour vérifier si l’action provient d’une IA ou d’un joueur réel
    bool Engine::isActionFromAI (){
        return this->currentState->isAI_Now();
    }

    //  Permet d’avertir l’engine quand le temps alloué au tour d’un joueur est atteint
    bool Engine::timeOut(){
        return (!state::State::chronoCount);
    }

    //  Permet de partager le state et l'engine aux IA
    void Engine::bind (ai::AI* g_ai){
        g_ai->bind(this, this->currentState);
    }

    /*  Permet comme le ferait un ctrl+Z de revenir en arrière durant un tour, en annulant les commandes 
        qui ont été réalisées. */
    void Engine::undo(){
        if(!this->cmdHistory.empty()){
            this->cmdHistory.top()->undo(this->cmdHistory.top()->args);
            this->cmdUndid.push_back(std::move(this->cmdHistory.top()));
            this->cmdHistory.pop();
        }
    }

    //  Permet comme le ferait un ctrl+Y de rétablir les commandes annulées
    void Engine::redo(){
        if(!this->cmdUndid.empty()){
            this->cmdUndid.back()->action(this->cmdUndid.back()->args);
            this->cmdHistory.push(std::move(this->cmdUndid.back()));
            this->cmdUndid.pop_back();
        }
    }


    std::unique_ptr<Command> Engine::move_cmd (std::shared_ptr<state::State>& gstate, int x, int y){
        int old_mp = gstate->get_MP(gstate->getActualPlayerIndex());
        state::Position old_pos = gstate->playerPosition(gstate->getActualPlayerIndex());
        void(*actions[2])(std::unique_ptr<Action_Args>&);
        actions[0] = &Action::move;
        actions[1] = &Action::cancel_move;
        auto args = std::unique_ptr<Action_Args>(new Action_Args(gstate, x, y, old_pos, old_mp));
        auto cmd = std::unique_ptr<Command>(new Command(actions, args));
        return cmd;
    }
    std::unique_ptr<Command> Engine::atck_cmd (std::shared_ptr<state::State>& gstate, int x, int y){
        int old_ap_thp[2];
        gstate->pull_AP_THP(x, y, old_ap_thp);
        void(*actions[2])(std::unique_ptr<Action_Args>&);
        actions[0] = &Action::attack;
        actions[1] = &Action::cancel_attack;
        auto args = std::unique_ptr<Action_Args>(new Action_Args(gstate, x, y, old_ap_thp));
        auto cmd = std::unique_ptr<Command>(new Command(actions, args));
        return cmd;
    }

    Engine::~Engine (){}
}