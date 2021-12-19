
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
---
