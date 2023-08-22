#ifndef PILE_H
#define PILE_H


#include <stdlib.h>
#include <stdio.h>
#include "types.h"


typedef struct T_cell
{
    token* val;
    struct T_cell* suiv;
}*pile;

typedef pile* typePile;
typedef pile** typePileAdr;

pile create_pile();
bool estVide(pile p);
void Ajout_tete(typePile,caseType);
void supp_unite(typePile,caseType);
void depiler(typePile p);
caseType tete_pile(typePile p);
void emptyPile(typePile p);
int hauteurPile(pile p);

void want_to_delete_token(game_tab tab, typePile p,int compteur);
void deleteTokenOnGameTab(game_tab pToken, pos pos1, typePile pCell);
void use_pile(game_tab tab, typePileAdr p);

#endif // PILE_H
