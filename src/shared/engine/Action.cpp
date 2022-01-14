/*
 * File             Action.cpp
 * Directory        engine
 * Created Date     Tuesday, December 21st 2021, 3:18:20 pm
 * Author           Nouhou KANE
 * Email            nouhou.kane@ensea.fr
 * 
 * Copyright (c) 2021  ENSEA(FR)
 * __________________________________________________________________________
 */

#include "Action.h"
#include <iostream>
namespace engine{
    Action::Action(){

    }

    // Pour modifier la position du joueur quand il désire se déplacer
    void Action::move (std::unique_ptr<Action_Args>& args){
        args->state->moveCurrentPlayer(args->point[0], args->point[1]);
    }

    // attack() pour mettre à jour les points d’actions du joueur et diminuer les points de vie de l’adversaire concerné.
    void Action::attack (std::unique_ptr<Action_Args>& args){
        args->state->makeAttackOn(args->point[0], args->point[1]);
    }

    //  Permet de préparer une attaque en sélectionnant un sort avant d’attaquer l’ennemi
    void Action::select (std::unique_ptr<Action_Args>& args){
        args->state->setCurrPlayerAttack(args->selected);
    }

    //  Permet de passer le tour du joueur actuel et donner la main au joueur suivant
    void Action::passTurn (std::unique_ptr<Action_Args>& args){
        args->state->passTurn();
    }

    // Implémente l’action réalisée par le joueur en attente, quand ce n’est pas son tour
    void Action::doNothing (std::unique_ptr<Action_Args>& args){
        return;
    }

    // Permet d’initier le jeu après avoir cliquer sur le bouton JOUER du menu d’accueil
    void Action::startGame (std::unique_ptr<Action_Args>& args){
        args->state->chronoStart(state::State::chronoStep, state::State::chronoCount);
    }

    void Action::cancel_move (std::unique_ptr<Action_Args>& args){
        args->state->cancel_move(args->old_pos_mp);
    }
    void Action::cancel_attack (std::unique_ptr<Action_Args>& args){
        args->state->cancel_attack(args->point, args->old_ap_thp);
    }
    void Action::cancel_select (std::unique_ptr<Action_Args>& args){
        args->state->setCurrPlayerAttack(args->old_attack_index);
    }


}