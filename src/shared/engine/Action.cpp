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
        args->state->makeMove(args);
    }

    // attack() pour mettre à jour les points d’actions du joueur et diminuer les points de vie de l’adversaire concerné.
    void Action::attack (std::unique_ptr<Action_Args>& args){
        args->state->makeAttack(args);
    }

    //  Permet de préparer une attaque en sélectionnant un sort avant d’attaquer l’ennemi
    void Action::select (std::unique_ptr<Action_Args>& args){
        args->state->setCurrPlayerAttack(args->selected);
    }

    //  Permet de passer le tour du joueur actuel et donner la main au joueur suivant
    void Action::passTurn (std::unique_ptr<Action_Args>& args){
        args->state->passTurn(args->selected);
    }

    // Implémente l’action réalisée par le joueur en attente, quand ce n’est pas son tour
    void Action::doNothing (std::unique_ptr<Action_Args>& args){
        return;
    }

    // Permet d’initier le jeu après avoir cliquer sur le bouton JOUER du menu d’accueil
    void Action::startGame (std::unique_ptr<Action_Args>& args){
        args->state->chronoStart(state::State::chronoStep, state::State::chronoCount);
    }

    //  Va permettre d’annuler un déplacement
    void Action::cancel_move (std::unique_ptr<Action_Args>& args){
        args->state->cancel_move(args);
    }

    //  Va permettre d’annuler une attaque
    void Action::cancel_attack (std::unique_ptr<Action_Args>& args){
        args->state->cancel_attack(args);
    }

    //  Va permettre d’annuler la sélection d’un sort
    void Action::cancel_select (std::unique_ptr<Action_Args>& args){
        args->state->setCurrPlayerAttack(args->old_attack_index);
    }

    void Action::cancel_passTurn (std::unique_ptr<Action_Args>& args){
        args->state->cancel_passTurn(args->selected);
    }


}