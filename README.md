MARC-Rover
MARC-Rover est une application en C qui simule le déplacement d'un rover sur une carte martienne. Le programme lit une carte en entrée, calcule le chemin optimal en évitant les obstacles et affiche le parcours emprunté par le rover.

Fonctionnalités
Lecture de la carte : Le programme lit une carte textuelle définissant les différents types de terrains et obstacles.
Calcul du chemin optimal : Utilisation d'algorithmes pour déterminer le chemin le plus efficace vers la destination.
Affichage du parcours : Visualisation du chemin emprunté par le rover sur la carte.
Installation
Cloner le dépôt :

bash
Copier
Modifier
git clone https://github.com/KOR0N/MARC-Rover.git
cd MARC-Rover
Compiler le programme :

Assurez-vous d'avoir un compilateur C installé sur votre système.

bash
Copier
Modifier
gcc -o marc_rover main.c loc.c map.c moves.c queue.c sort.c stack.c tree.c
Cette commande compile les fichiers sources et génère un exécutable nommé marc_rover.

Utilisation
Préparer la carte :

Créez un fichier texte représentant la carte martienne. Chaque caractère représente un type de terrain ou un obstacle.

Exécuter le programme :

bash
Copier
Modifier
./marc_rover path_to_map_file.txt
Remplacez path_to_map_file.txt par le chemin vers votre fichier de carte.

Résultat :

Le programme affichera le chemin optimal calculé sur la carte en évitant les obstacles.

Structure du projet
main.c : Point d'entrée du programme.
loc.c et loc.h : Gestion des coordonnées et des positions.
map.c et map.h : Gestion de la carte et des terrains.
moves.c et moves.h : Gestion des mouvements du rover.
queue.c et queue.h : Implémentation de la file pour la gestion des chemins.
sort.c et sort.h : Fonctions de tri utilisées dans les algorithmes.
stack.c et stack.h : Implémentation de la pile pour la gestion des parcours.
tree.c et tree.h : Gestion des structures arborescentes pour les décisions de parcours.
