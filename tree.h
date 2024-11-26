#ifndef UNTITLED1_NAREATREE_H
#define UNTITLED1_NAREATREE_H

#include "moves.h"
#include "map.h"

typedef struct s_node{
    int value;
    int NbSons;
    int depth;
    struct s_node **sons;
    struct s_node *parent;
    t_move *avails;
    t_move type_move;
    t_localisation loc;
}t_node;


typedef struct s_node2{
    int value;
    int NbSons;
    struct s_node **sons;
    t_move *avails;
}t_node2;

t_move* createNewTab(t_move *tab, int index, int size);

void printTree(t_node *node, int level);

t_node* createNode(int value, int NbSons, int depth, t_move type_move, t_localisation localisation);

/**
 * @brief Construit un arbre à partir de la localisation et de la carte.
 * @param value
 * @param NbSons
 * @param depth
 * @param type_move
 * @param *avails
 * @param loc
 * @param map
 * @return la racine de l'arbre
 */
t_node* createTree(int value, int NbSons, int depth,t_move type_move, int *avails,t_localisation loc, t_map map);

int CalculatePath(t_node *node);

/**
 * @brief Récupère la case la plus proche de la station.
 * @param root : racine de l'arbre.
 * @param map : carte utilisée pour le calcul des coûts.
 */
t_node* getBetterPath(t_node *root, t_map map);

/**
 * @brief Récupère les mouvements effectués par le rover sur le chemin le plus proche de la station.
 * @param root : racine de l'arbre.
 * @param map : carte utilisée pour le calcul des coûts.
 */
t_move* getBetterPathMoves(t_node *root, t_map map);

#endif //UNTITLED1_NAREATREE_H

