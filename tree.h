#ifndef UNTITLED1_NAREATREE_H
#define UNTITLED1_NAREATREE_H

#include "moves.h"
#include "map.h"

typedef struct s_node{
    int value;
    int NbSons;
    int depth;
    struct s_node **sons;
    t_move *avails;
}t_node;

t_node *createTree(int value, int NbSons, int depth,int *avails,t_localisation loc, t_map map);

int* createNewTab(int *tab, int index, int size);

void printTree(t_node *node, int level);



#endif //UNTITLED1_NAREATREE_H

