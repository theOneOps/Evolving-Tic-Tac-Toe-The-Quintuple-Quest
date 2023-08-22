#include "mask_core.h"

//depuis le game_tab....

//============================== Getters et Setters ========================================

caseType getTokenTab(game_tab tab,int i,int j)
{
    return tab[i][j];
}

int getPosXFromToken(caseType t)
{
    return t->position.posX;
}

int getPosYFromToken(caseType t)
{
    return t->position.posY;
}

token getTokenValue(game_tab tab,int i,int j)
{
    return *(tab[i][j]);
}

char getTokenSign(token * t)
{
    return t->sign;
}

void setTabToken(game_tab tab, int i, int j, token* t)
{
    tab[i][j]=t;
}

void setTokenSign(game_tab tab, int i, int j,char theSign)
{
    tab[i][j]->sign = theSign;
}


caseType getTokenAdr(game_tab tab,int i)
{
    return (*(tab[i]));
}

caseTypeAdr getTokenAdrs(game_tab tab)
{
    return (*tab);
}

//========================= set Attributs Token ================================

void setSign(caseType t, char theSign)
{
    t->sign =theSign;
}

void setPosition(caseType t, int x,int y)
{
    t->position.posX = x;
    t->position.posY = y;
}

void setCountOneValue(caseType t, bool b)
{
    t->countOne = b;
}

void setCountTwoValue(caseType t, bool b)
{
    t->countTwo = b;
}

void setThreeCaseValid(caseType t, bool b)
{
    t->threeCaseValid = b;
}

void setvalue_C(caseType t, int value)
{
    t->value_c = value;
}

void setFilled(caseType t, int value)
{
    t->filled = value;
}

void setvalue_R(caseType t, int value)
{
    t->value_r = value;
}

bool getCountOne(caseType t)
{
    return t->countOne;
}

bool getCountTwo(caseType t)
{
    return t->countTwo;
}

bool getFilled(caseType t)
{
    return t->filled;
}

//not added...

bool getThreeCaseValid(caseType t)
{
    return t->threeCaseValid;
}


//==========================================================================================

//============================Setters - Getters Grille game_tab ============================

void setTabTokenSign(game_tab tab,int x, int y,char s)
{
    tab[x][y]->sign = s;
}

void setTabTokenCountOne(game_tab tab,int x, int y,bool b)
{
    tab[x][y]->countOne = b;
}

void setTabTokenCountTwo(game_tab tab,int x, int y,bool b)
{
    tab[x][y]->countTwo = b;
}

void setTabTokenThreeCaseValid(game_tab tab,int x, int y,bool b)
{
    tab[x][y]->threeCaseValid = b;
}

void setTabTokenFilled(game_tab tab,int x, int y,bool b)
{
    tab[x][y]->filled = b;
}


//========================================================================






//depuis le player...


//============================== Getters et Setters ========================================

char getPlayerSign(player* p)
{
    return p->team;
}

bool getIsPlayerRobot(typePlayer p)
{
    return p->robot;
}

//not added ....

void setcountQuintupletPossibleInc(typePlayer p)
{
    p->countQuintupletPossible+=1;
}

void setCountQuintupletInc(typePlayer p)
{
    p->countNbQuintuplet+=1;
}

int getCountQuintupletPossible(typePlayer p)
{
    return p->countQuintupletPossible;
}

int getCountQuintuplet(typePlayer p)
{
    return p->countNbQuintuplet;
}

//not added yet...

void setcountQuintupletPossible(typePlayer p,int v)
{
    p->countQuintupletPossible = v;
}

//============================================================================================

//Getters et Setters des vatiables de type Int

int getPointerValue(int* value)
{
    return *value;
}

void setPointerValue(int * value, int v)
{
    *value = v;
}

void setPointerValueInc(int * value, int v)
{
    *value += v;
}

//not added...

bool getFinishMorpion(bool* finish)
{
    return *finish;
}

void setFinishMorpion(bool* finish,bool b)
{
    *finish=b;
}

//les Piles

caseType getValFromPile(pile p)
{
   return p->val;
}

caseType getValPileFromPileAdr(typePile p)
{
    return (*p)->val;
}

pile getPileNotPointer(typePile p)
{
    return *p;
}


pile getSuivPileFromPileAdr(typePile p)
{
    return (*p)->suiv;
}

pile getSuivPileFromPile(pile p)
{
    return p->suiv;
}

void setValPile(pile *p, caseType v)
{
    (*p)->val = v;
}

void setSuivPile(typePile p, typePile old)
{
    (*p)->suiv = *old;
}

void setPileToPile(typePile p, typePile old)
{
    *p = *old;
}

void setPileToSuivPile(typePile p)
{
    *p = (*p)->suiv;
}

void setSuivPileToSuivSuivPile(pile* t,pile new_t)
{
    *t = new_t;
}
