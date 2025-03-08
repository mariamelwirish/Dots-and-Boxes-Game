#include "calculateScores.h"

void calculateScores(r1, c1, r2, c2){
    if(checkBox(r1, c1, r2, c2)==1){
        scores[cur_player]++;
    }
    else{
        switchTurn();
    }
}