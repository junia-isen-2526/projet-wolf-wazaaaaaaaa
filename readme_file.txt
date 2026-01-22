README - Projet "Promenons-nous dans les bois"

================================================================================
 PROJET
================================================================================

Ce projet a été réalisé par Arno,Xan et Rayan. Il s'agit d'une 
simulation sur C-Lion sur la comptine pour enfant "Promenons-nous 
dans les bois", où un enfant explore une forêt tout en évitant de se faire 
attraper par le loup.

================================================================================
PRINCIPE DU JEU
================================================================================

L'enfant se promène dans une forêt représentée sous forme de carte avec des 
arbres et des chemins. À chaque phrase de la comptine qu'il chante, il avance 
pour explorer la foret et la cartographier . Pendant ce temps,Le loup se prépare en enfilant ses vêtements petit à petit.

Une fois que le loup a terminé de s'habiller, il surgit et commence à poursuivre l'enfant. Ensuite il doit alors rapidement retourner à son point de départ pour se mettre en sécurité avant de se faire attraper. S'il réussit à s'échapper, il gagne.

================================================================================
OBJECTIFS RÉALISÉS
================================================================================

Nous avons développé un programme qui simule entièrement cette partie de 
cache-cache dans la forêt. L'enfant explore de manière aléatoire pendant la 
phase de découverte, puis cherche intelligemment le chemin le plus court vers 
son point de départ lors de la fuite. Le loup, quant à lui, poursuit l'enfant 
en se déplaçant librement sur toute la carte, sans être gêné par les arbres.

À la fin de chaque partie, le programme génère automatiquement un fichier de 
cartographie au format Mermaid qui permet de visualiser tout le parcours 
effectué par l'enfant sous forme de graphe.

================================================================================
DÉFIS RENCONTRÉS
================================================================================

Le problème des culs-de-sac
----------------------------
L'une de nos premières difficultés a été de gérer les situations où l'enfant 
se retrouvait coincé dans une impasse. Au début, l'enfant pouvait s'enfoncer 
dans un chemin sans issue et ne plus pouvoir revenir en arrière efficacement. 
Nous avons dû repenser la logique de déplacement pour que l'enfant puisse 
identifier les directions prometteuses et éviter de se piéger lui-même.

La structure de données pour mémoriser le parcours
---------------------------------------------------
Nous avions initialement imaginé une structure complexe où chaque position 
visitée stockerait toutes ses positions voisines, et chaque voisin stockerait 
à son tour ses propres voisins. Cette approche créait une architecture très 
compliquée et difficile à gérer. Après réflexion, nous avons opté pour une 
solution beaucoup plus simple : un simple tableau qui enregistre 
chronologiquement toutes les positions visitées par l'enfant. Cette méthode 
s'est révélée bien plus efficace et facile à maintenir.

La gestion de la mémoire
-------------------------
Nous devions nous assurer que le programme pouvait stocker un très grand nombre 
de positions visitées sans provoquer de débordement mémoire. Après plusieurs 
essais sur différentes forêts, nous avons déterminé une taille appropriée pour 
notre tableau de stockage.

================================================================================
NOTRE MÉTHODE DE TRAVAIL
================================================================================

Pour mener à bien ce projet, nous avons divisé le travail en trois. Deux membres de l'équipe s'est concentré sur tout ce qui concerne l'enfant : ses déplacements, son exploration et la mémorisation de son parcours.Le troisième membre s'est occupé des fonctions 
utilitaires comme la lecture des fichiers de forêt et la génération du graphe 
final.

Nous avons travaillé de manière progressive, en nous réunissant régulièrement 
pour mettre en commun nos avancées et résoudre les problèmes ensemble. Chacun 
développait sa partie de son côté, puis nous testions l'ensemble du programme 
sur les différentes cartes de forêt fournies pour vérifier que tout 
fonctionnait correctement.

Cette organisation nous a permis d'avancer efficacement tout en gardant une vue 
d'ensemble cohérente du projet. Les moments de mise en commun étaient 
particulièrement importants car c'est là que nous détections les 
incompatibilités entre nos différentes parties de code.

================================================================================
CE QUE PRODUIT LE PROGRAMME
================================================================================

Lorsqu'on lance la simulation, le programme affiche en temps réel toute la 
partie qui se déroule : les phrases de la comptine, les déplacements de 
l'enfant, les vêtements que le loup enfile, puis la course-poursuite finale. 
À la fin, il indique si l'enfant a réussi à s'échapper ou s'il s'est fait 
attraper, ainsi que le nombre total de cases explorées.

Le programme génère également un fichier spécial qui peut être visualisé sous 
forme de graphe, montrant tous les chemins empruntés par l'enfant durant son 
exploration. C'est une représentation visuelle très intéressante de l'aventure 
vécue.

================================================================================
PISTES D'AMÉLIORATION
================================================================================

Si nous devions continuer ce projet,Rayan avait pour idée d'ajouter une fonction "Super-Sub" qui a pour objectif de pouvoir aider l'enfant grâce à un lutin qui distrairait le loup avec de la viande ci celui-ci se rapproche un peu trop de la zone ou l'enfant se déplace.
On aurait voulu aussi ajouter plusieurs enfants qui explorent la forêt simultanément et doivent coopérer pour s'échapper. L'ajout d'une interface 3d rendrait également le Jeu beaucoup plus drôle et agréable à tester.

