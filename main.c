#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"
#include "moves.h"
#include "sort.h"
#include "tree.h"


int main() {
    t_map map;
    int x,y = 0;
    char showMap[4];

////////////////////////////////////////////////////////////////////////////////
// Générer un carte aléatoire selon la taille donnée et l'afficher si demandé //
////////////////////////////////////////////////////////////////////////////////
    printf("==========================================================================\n"
           "= Bonjour et bienvenue dans notre programme d'entrainement du rover MARC =\n"
           "==========================================================================\n");
    printf("Afin d'entrainer notre rover, veuillez entrer les dimensions de la carte (ATTENTION LA TAILLE NE DOIT PAS DEPASSER 99)\nLongueur de la carte :");
    scanf("%d", &x);
    printf("Hauteur de la carte :");
    scanf("%d", &y);
    char* my_map = GenerateMap(x,y);
    map = createMapFromChar(my_map,x,y);

    printf("\n|-> Génération d'une carte aléatoire");
    _sleep(500);
    printf(".");
    _sleep(500);
    printf(".");
    _sleep(500);
    printf(".\n");
    _sleep(500);

    do{
        printf("\n  Voulez vous afficher la carte (yes/no) :");
        scanf("%3s", showMap);
    }while(strcmp(showMap, "yes") != 0 && strcmp(showMap, "no") != 0);

    if (strcmp(showMap, "yes") == 0) {
        printf("Map created with dimensions %d x %d\n", map.y_max, map.x_max);
        for (int i = 0; i < map.y_max; i++) {
            for (int j = 0; j < map.x_max; j++) {
                printf("%d ", map.soils[i][j]);
            }
            printf("\n");
        }
        // printf the costs, aligned left 5 digits
        for (int i = 0; i < map.y_max; i++) {
            for (int j = 0; j < map.x_max; j++) {
                printf("%-5d ", map.costs[i][j]);
            }
            printf("\n");
        }
        displayMap(map);

    }


//////////////////////////////////////////////////
// Générer une position aléatoire pour le rover //
//////////////////////////////////////////////////
    t_localisation loc;
    do{
        loc = GenerateRandomLocalisation(x,y);
    }while(map.costs[loc.pos.x][loc.pos.y]);
    printf("\nRover généré aux coordonées :\nx : %d\ny : %d\n\n",loc.pos.x,loc.pos.y);


    int try = 0;
    int num_moves = 9;
    int depth = 0;

    t_node* best_node = NULL;
    t_move* tirage = NULL;
    t_node* mytree = NULL;
    t_move* moves = NULL;

    printf("\n");

////////////////////////////////////////////

    do{
        tirage = getRandomMoves(num_moves);
        //for(int i = 0; i<num_moves; i++){
          //  print_move(tirage[i]);
        //}


        mytree = createTree(map.costs[loc.pos.y][loc.pos.x], num_moves, depth, STAY,tirage, loc, map);
        //printTree(mytree,0);
        best_node = getBetterPath(mytree, map);
        moves = getBetterPathMoves(mytree, map);

        printf("|-> Tour Numéro %d : La case la plus proche en 5 mouvements a une valeur de : %d\n", try+1,best_node->value);
        loc = best_node->loc;
        try++;

        //--Si le rover termine sa phase sur un sol de type REG, il n'aurat que 4 mouvement pour la prochaine--//
        if(map.soils[loc.pos.y][loc.pos.x] == REG){
            depth = 1;
        }
        else{
            depth = 0;
        }

    }while(best_node->value != 0);

    printf("\n===============================================================\n= Bravo, Le rover est arrivé à destination en %d essaie(s) ! =\n"
           "===============================================================",try);

    displayRoverPath(mytree, map);
    return 0;
}

