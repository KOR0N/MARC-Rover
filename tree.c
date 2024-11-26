#include <stdlib.h>
#include <stdio.h>
#include "tree.h"
#include "map.h"

const int VAL_MAX = 99999;

t_move* createNewTab(t_move *tab, int index, int size){
    int k = 0;
    t_move* new_tab = (t_move *)malloc((size-1) * sizeof(t_move));
    for(int i = 0; i<size; i++){
        if(i != index){
            new_tab[k] = tab[i];
            k++;
        }
    }
    return new_tab;
}

void printTree(t_node *node, int level) {
    if (node == NULL) return; // Cas de base lorsque nœud NULL

    // Indentation pour représenter la profondeur
    for (int i = 0; i < level; i++) {
        printf("  "); // Deux espaces par niveau
    }

    // Afficher les informations du nœud
    printf("Node Value: %d, NbSons: %d, Profondeur: %d\n", node->value, node->NbSons, node->depth);
    print_move(node->type_move);

    // Parcourir et afficher les fils
    for (int i = 0; i < node->NbSons; i++) {
        printTree(node->sons[i], level + 1); // Appel récursif avec un niveau supplémentaire
    }
}


t_node *createNode(int value, int NbSons, int depth, t_move type_move, t_localisation localisation) {
    t_node *new_node = (t_node *)malloc(sizeof(t_node));

    if (new_node == NULL) {
        return NULL;
    }

    new_node->value = value;
    new_node->NbSons = NbSons;
    new_node->depth = depth;
    new_node->loc = localisation;
    new_node->parent = NULL;
    if(NbSons > 0){
        new_node->sons = (t_node **)malloc(NbSons * sizeof(t_node *));
    }
    else{
        new_node->sons = NULL;
    }
    new_node->type_move = type_move;

    return new_node;
}


t_node *createTree(int value, int NbSons, int depth, t_move type_move, int *avails, t_localisation loc, t_map map) {
    t_node *new_node = createNode(value, NbSons, depth, type_move,loc);
    if (new_node == NULL) {
        return NULL;  // Échec de l'allocation mémoire
    }

    if (depth <= 5) {
        for (int i = 0; i < NbSons; i++) {
            int *myavail = avails;

            // Gestion spéciale pour les sols de type ERG
            if (depth == 0 && map.soils[loc.pos.y][loc.pos.x] == ERG) {
                myavail[i] = Erg(myavail[i]);
            }

            t_localisation new_loc = move(loc, myavail[i]);
            t_move *new_tab = createNewTab(avails, i, NbSons);

            if (isValidLocalisation(new_loc.pos, map.x_max, map.y_max) && map.costs[new_loc.pos.y][new_loc.pos.x] < 10000) {
                new_node->sons[i] = createTree(map.costs[new_loc.pos.y][new_loc.pos.x], NbSons - 1, depth + 1, myavail[i],new_tab, new_loc, map);
                if (new_node->sons[i] != NULL) {
                    new_node->sons[i]->parent = new_node; // Définie le parent du sous-nœud
                }
            }
            else {
                new_node->sons[i] = NULL;  // Si localisation invalide ou crevasse, le rover est mort donc pas de sous-nœud
            }
        }
    } else {
        return NULL;  // Pas de fils pour ce nœud
    }

    return new_node;
}


t_node *getBetterPath(t_node *node, t_map map) {
    // Vérifier si le nœud est NULL
    if (node == NULL) {
        return NULL;  // Aucune feuille dans cette branche
    }

    // Si le rover est arrivé à la station ou de profondeur 5
    if (node->value == 0 || node->depth == 5) {
        return node;  // Retourner directement le nœud
    }

    // Parcourir récursivement les fils pour trouver le meilleur chemin
    t_node *best_node = NULL;
    int min_value = VAL_MAX;

    for (int i = 0; i < node->NbSons; i++) {
        t_node *current_node = getBetterPath(node->sons[i], map);

        // Mettre à jour si on trouve une valeur plus petite
        if (current_node != NULL && current_node->value < min_value) {
            min_value = current_node->value;
            best_node = current_node;
        }
    }

    return best_node;  // Retourner le meilleur nœud trouvé
}


t_move* getBetterPathMoves(t_node *root, t_map map){
    t_node *best_node = getBetterPath(root, map);

    if (best_node == NULL) {
        printf("Aucun chemin trouvé.\n");
        return;
    }

    // Tableau pour stocker les mouvements
    t_move *moves = (t_move *)malloc((best_node->depth + 1) * sizeof(t_move));
    int move_count = 0;

    // Remonter l'arbre de la feuille jusqu'à la racine pour avoir les mouvements
    t_node *current_node = best_node;
    while (current_node != NULL && current_node->depth > 0) {
        moves[move_count++] = current_node->type_move;  // Stocke le mouvement
        current_node = current_node->parent;  // Remonte d'un parent
    }

    // Afficher les mouvements dans l'ordre correct
    //printf("Mouvements optimaux :\n");
//    for (int i = move_count - 1; i >= 0; i--) {
  //      printf("%s ", getMoveAsString(moves[i]));
    //}
   // printf("\n");
    return moves;
}

void displayRoverPath(t_node *root, t_map map,t_move *moves) {

    if (moves == NULL) {
        printf("Aucun chemin valide trouvé.\n");
        return;
    }

    // Création d'une copie de la carte pour l'affichage
    char display_map[map.y_max][map.x_max];
    for (int i = 0; i < map.y_max; i++) {
        for (int j = 0; j < map.x_max; j++) {
            display_map[i][j] = 'o';  // Initialise toutes les cases à 'o'
        }
    }

    // Position actuelle du rover
    t_localisation loc = root->loc;
    display_map[loc.pos.y][loc.pos.x] = 'D';  // Position de départ

    // Parcourir les mouvements et dessiner le chemin
    for (int i = 0; i < root->depth; i++) {
        // Mettre à jour la localisation en fonction du mouvement
        loc = move(loc, moves[i]);

        // Vérification des limites pour éviter les débordements
        if (loc.pos.x < 0 || loc.pos.x >= map.x_max || loc.pos.y < 0 || loc.pos.y >= map.y_max) {
            printf("Erreur : déplacement hors de la carte.\n");
            return;
        }

        // Marquer le chemin et la position d'arrêt
        if (moves[i] == F_10 || moves[i] == F_20 || moves[i] == F_30 || moves[i] == B_10) {
            display_map[loc.pos.y][loc.pos.x] = 'P';  // Points d'arrêt
        } else {
            // Déplacement horizontal ou vertical
            display_map[loc.pos.y][loc.pos.x] = (moves[i] == T_LEFT || moves[i] == T_RIGHT) ? '-' : '|';
        }
    }

    // Marquer la destination finale (base station)
    display_map[loc.pos.y][loc.pos.x] = 'F';

    // Affichage de la carte
    printf("\nChemin du rover :\n");
    for (int i = 0; i < map.y_max; i++) {
        for (int j = 0; j < map.x_max; j++) {
            printf("%c ", display_map[i][j]);
        }
        printf("\n");
    }
}


//tu vas reussir dauvel il faut croire en soi
//et quand tu auras fini tu peux me le transferer XD
