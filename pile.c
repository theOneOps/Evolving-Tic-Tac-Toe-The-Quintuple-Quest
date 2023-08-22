#include <stdlib.h>
#include <stdio.h>
#include "types.h"

#include "pile.h"
#include "core.h"
#include "unistd.h"


pile create_pile()
{
    pile p = NULL;
    return p;
}

bool estVide(pile new_p)
{
    return new_p==NULL;
}
/*
void Ajout_tete(typePile new_p, caseType value)
{
    pile the_pile = malloc(sizeof(struct T_cell)); // Correction: allouer de la mémoire pour une struct T_cell
    the_pile->val = value;
    the_pile->suiv = *new_p;
    *new_p = the_pile;
}
*/

void Ajout_tete(typePile new_p, caseType value)
{
    pile the_pile = malloc(sizeof(struct T_cell)); // Correction: allouer de la mémoire pour une struct T_cell
    //the_pile->val = value;
    setValPile(&the_pile,value);
    //the_pile->suiv = *new_p;
    setSuivPile(&the_pile,new_p);
    //*new_p = the_pile;
    setPileToPile(new_p,&the_pile);
}

void supp_unite(pile* new_p, caseType value)
{
    if (estVide(getPileNotPointer(new_p)))
    {
        printf("file vide, rien a supprimer \n");
    }
    else if ((*new_p)->val->position.posX == value->position.posX && (*new_p)->val->position.posY == value->position.posY)
    {

        pile temp = getPileNotPointer(new_p);
        //*new_p = (*new_p)->suiv;
        setPileToSuivPile(new_p);
        free(temp);
    }
    else
    {
        pile tmp = getPileNotPointer(new_p);

        while (getSuivPileFromPile(tmp) != NULL)
        {
            //printf("entree dans la fonction suppUnite \n");
            if (getPosXFromToken(getValFromPile(getSuivPileFromPile(tmp))) == getPosXFromToken(value) && getPosYFromToken(getValFromPile(getSuivPileFromPile(tmp))) == getPosYFromToken(value))
            {   //(tmp->suiv->val->position.posX == value->position.posX && tmp->suiv->val->position.posY == value->position.posY)
                //je me suis trompé dans le if... à revoir...
                //pile temp = getSuivPileFromPile(tmp);

                pile temp = tmp->suiv;
                //setSuivPileToSuivSuivPile(&tmp,getSuivPileFromPile(getSuivPileFromPile(tmp)));
                tmp->suiv = tmp->suiv->suiv;
                free(temp);
                break;
            }
            //tmp = tmp->suiv;
            tmp = getSuivPileFromPile(tmp);
        }
    }
}



void depiler(typePile p)
{//nouveau

    if (!estVide(getPileNotPointer(p)))
    {
        //pile p2;
        //pile p2 = (*p)->suiv;
        pile p2 = getSuivPileFromPileAdr(p);
        //setPileToPile(&p2,getSuivPileFromPileAdr(p));

        free(getPileNotPointer(p));// liberation de la memoire sur l'ancienne t?te
        //*p = p2;     // nouvelle t?te
        setPileToPile(p,&p2);
    }
}

int hauteurPile(pile p)
{
    if (p == NULL)
        return 0;
    else return 1 + hauteurPile(getSuivPileFromPile(p));
}

caseType tete_pile(typePile p)
{
    if (p != NULL)
        return getValPileFromPileAdr(p);
    else {
        return NULL;
    }
}

void emptyPile(pile* p)
{
    while (!estVide(getPileNotPointer(p)))
        depiler(p);
}

//--------------------------------------- FIN FONCTION PILE -------------------------------------------


//------------------------------------ DEBUT FONCTION AVEC PILE ET GAME_TAB ---------------------------


void deleteTokenOnGameTab(game_tab pToken, pos pos1, typePile pCell)
{
    //pToken[pos1.posX][pos1.posY]->sign = '_';
    setTabTokenSign(pToken,pos1.posX,pos1.posY,'_');
    supp_unite(pCell,getTokenTab(pToken,pos1.posX,pos1.posY));
    //pToken[pos1.posX][pos1.posY]->filled=false;
    setTabTokenFilled(pToken,pos1.posX,pos1.posY,false);
}

void want_to_delete_token(game_tab tab, typePile p, int counts)
{
    pos tabPos[500];
    int i = 0;
    while(counts!=0)
    {
        token* tok = tete_pile(p);
        if (tok==NULL)
        {
            printf("la pile est vide \n");
            break;
        }
        tabPos[i].posX = tok->position.posX;
        tabPos[i].posY = tok->position.posY;
        depiler(p);
        i++;
        counts--;
    }

    for(int j=0;j<i;j++)
    {
        pos thePosition = tabPos[j];
        if (valid_coord(thePosition.posX,thePosition.posY))
        {
            poseTokenOnGameTabFromPile(tab,thePosition,'_');
        }
    }
}
