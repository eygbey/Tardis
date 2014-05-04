#include "competition.h"
#include <stdlib.h>

//MEMORY MANAGEMENT
void loadComp(struct Event** e, struct Competition* c){
    if( (*e)->firstComp == NULL ){
	(*e)->firstComp = (*e)->lastComp = c;
    }else{
        (*e)->lastComp->nextComp = c;
        (*e)->lastComp = c;
    }
}

void loadCon(struct Event** e, struct Contestant* c){
    if( (*e)->lastComp->firstContestant == NULL ){
        (*e)->lastComp->firstContestant = (*e)->lastComp->lastContestant = c;
    }else{
	(*e)->lastComp->lastContestant->nextContestant = c;
	(*e)->lastComp->lastContestant = c;
    }
}



