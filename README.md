
# Projet Logiciel Transverse de Nouhou, Mustafa et Alexandre

## PROJET : PROFUS

[![N|Solid](https://cldup.com/dTxpPi9lDf.thumb.png)](https://nodesource.com/products/nsolid)

[![Build Status](https://travis-ci.org/joemccann/dillinger.svg?branch=master)](https://travis-ci.org/joemccann/dillinger)

## Installation de d'environnement de projet : Le builder

#### Logiciels requis :
    make install-requirements
#### install submodules
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

    ./bin/client render //(affiche de la map de jeu utilisée)
    ./bin/client randomMap //(affichache aléatoire de map).
---