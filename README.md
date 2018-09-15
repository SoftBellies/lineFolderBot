# Line Follower robot kit

le projet est de réaliser une soirée "initiation à l'électronique" dans le cadre d'un doctorat sauvage en numérique.

Les participants auront à construire un robot suiveur de ligne à partir d'un kit mis au point parr le hackerspace.

Le présent dépot sert à la conception du kit.

Idéalement:

* Réalisable en moins de 4 heures en comptant le temps pour les indications, la formation des groupes, les tests.
* On initie à des techniques que les participants pourront réutiliser à la maison. Donc hormis un pistolet à colle, un fer à souder et un tourne-vis, aucun autre outil ne doit être à utiliser.
* Le robot peut être amélioré

C'est pour respecter ces trois points que je pars sur les concepts suivants:

* Le circuit électronique lors de l'atelier sera réalisé sur une plaque à pastille. Pas de création de circuits préimprimés à l'avance.
* L'utilisation d'un arduino permet de laisser une marge d'amélioration au robot (par l'ajout de capteurs ou de moteurs)

Deux hypothèses sur le circuit électronique:

1) Les moteurs sont pilotés par un circuit L293d ce qui permettra de pouvoir inverser le sens de moteurs à volonté et faire faire des virages en mode "tank à chenille" au robot. 
Les inconvéniants sont que le circuit est plus compliqué. Il sera dur à mettre en place sur une plaque à pastille en évitant de faire des "ponts" avec des fils, et que le temps de la scéance ne permettra peut etre pas ça. A tester

2) Pas de L293d, mais de simples transistors pour actionner indépendemment les moteurs (sans possibilité de faire de marche arrière)

## Circuit avec L 293D:
Attention, ce circuit n'a pour le moment pas été testé
robot-avec-l293d-schema.svg
![Circuit avec composant L293D](https://git.ventresmous.fr/VentresMous/lineFollowerBot/raw/master/electronics/robot-avec-l293d-schema.svg "Circuit avec composant L293D")

## Circuit avec transistors

TO DO


## TO do:

* Circuit avec transistors
* Réaliser les circuits sur une plaque de prototypage, et en fonction du temps que ça prend choisir entre la version 1 ou 2
* Réaliser le prototype BOB-1 tout en prenant des photo etc... afin d'écrire la notice de montage.
* Ecrire le firmware arduino du robot.
* Organiser l'évènement.
