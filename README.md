
# Projet Logiciel Transverse de Nouhou, Mustafa et Alexandre

## PROJET : PROFUS

[![N|Solid](https://cldup.com/dTxpPi9lDf.thumb.png)](https://nodesource.com/products/nsolid)

[![Build Status](https://travis-ci.org/joemccann/dillinger.svg?branch=master)](https://travis-ci.org/joemccann/dillinger)

## Installation de d'environnement de projet : Le builder

#### Logiciels requis :
    make install-requirements
#### If specific tag version (otherwise : error !)
    make install_extern_deps
#### install submodules (only if not tag but hole project)
    make install_submodules
#### clean extern configure build :
    make
#### Création et compilation du projet :
    make build
#### Configuration du projet :
    make configure
#### Lancer les tests :
    make test
#### code covereage :
    make code-covereage
#### Suppression de tous les fichiers générés :
    make clean
#### Suppression des fichiers headers :
    make clean-headers
#### configuration et compilation des dependences externes:
    make extern


#

## Executions jalons


---
#### [Jalon 1] :   
 
     ./bin/client client
---
#### [Jalon 2] :

    ./bin/client render //2.1->(affiche de la map de jeu utilisée)
    ./bin/client randomMap //2.1->(affichache aléatoire de map).
    ./bin/client engine //2.2->(engine simple : clique sur map --> effet).
    ./bin/client random_ai //2.final->(simple IA = essaie d'attaquer betement un joueur immobile).
---
#### [Jalon 3] :
    dans cette partie un joueur à la possibilité de jouer avec une IA plus performente que celle random. Pour jouer, il suffit d'appuier sur la touche "D" pour voir sa paortée de mouvement puis cliquer sur une position pour se déplacer. Pour attaquer, il faut cliquer sur un sort (sort1 ou sort2) puis cliquer sur la cible. Pour l'instant, il n'est pas possible d'annuler l'effet de click sur un sort à moins de passer son tour. on ne pourra pas se déplacer si on a plus de points de movement. On ne pourra pas attaquer non plus si on a plus de points d'attaque. Losrqu'on son temps a épuisé, le joeur pass sont tour automatiquement.
    Pour lancer une partie : ./bin/client heuristic_ai
---