#include "sort.h"
#include <stdlib.h>
#include <time.h>

int l_proba[] = {22,15,7,7,21,21,7};
int nb_tirage = 0;

t_move proba(int val, int *p_proba){

    t_move L_move[] = {F_10,F_20,F_30,B_10,T_LEFT,T_RIGHT,U_TURN};
    int sum = p_proba[0];
    for (int i=0;i<8;i++){
        if (val<sum) {
            p_proba[i]-=1;
            return L_move[i];
        }
        else sum+=p_proba[i + 1];
    }
}

void tirage(t_move *L_move){
    int val;
    srand(time(NULL));
    for (int i=0;i<9;i++)
    {
        val = rand() %(100- nb_tirage);
        L_move[i] = proba(val, l_proba);
        nb_tirage+=1;
    }
}
