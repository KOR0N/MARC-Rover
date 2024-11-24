#include <stdlib.h>
#include <stdio.h>
#include "tree.h"
#include "map.h"

t_node *createTree(int value, int NbSons, int depth, int *avails, t_localisation loc, t_map map) {
    t_node *new_node = (t_node *)malloc(sizeof(t_node));
    new_node->value = value;
    new_node->NbSons = NbSons;
    new_node->depth = depth;

    if(NbSons > 4){
        new_node->sons = (t_node **)malloc(NbSons * sizeof(t_node *));
        for (int i = 0; i < NbSons; i++) {
            int *myavail = avails;
            t_localisation new_loc = move(loc, myavail[i]);
            //printf("%d",map.costs[new_loc.pos.y][new_loc.pos.x]);
            int *new_tab = createNewTab(myavail, myavail[i], NbSons);
            //printf("%d ",tab[i]);
            if (isValidLocalisation(new_loc.pos, 6, 7)) {
                new_node->sons[i] = createTree(map.costs[new_loc.pos.y][new_loc.pos.x], NbSons - 1, depth + 1, new_tab,
                                               new_loc, map);
            }
            else{new_node->sons[i] = createTree(100000, NbSons - 1, depth + 1, new_tab,
                                                new_loc, map);}
        }
    }

    else{
        return new_node->sons = NULL;
    }
    return new_node;
}

int* createNewTab(int *tab, int value, int size){
    int k = 0;
    int* new_tab = (int *)malloc((size-1) * sizeof(int));
    for(int i = 0; i<size; i++){
        if(tab[i] != value){
            new_tab[k] = tab[i];
            k++;
        }
    }
    return new_tab;
}

void printTree(t_node *node, int level) {
    if (node == NULL) return; // Cas de base : nœud NULL

    // Indentation pour représenter la profondeur
    for (int i = 0; i < level; i++) {
        printf("  "); // Deux espaces par niveau
    }

    // Afficher les informations du nœud
    printf("Node Value: %d, NbSons: %d, Profondeur: %d\n", node->value, node->NbSons, node->depth);

    // Parcourir et afficher les fils
    for (int i = 0; i < node->NbSons; i++) {
        printTree(node->sons[i], level + 1); // Appel récursif avec un niveau supplémentaire
    }
}
