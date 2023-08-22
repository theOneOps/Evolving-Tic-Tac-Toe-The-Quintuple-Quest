#ifndef MASK_CORE_H
#define MASk_CORE_H

#include "pile.h"
#include "display.h"
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <unistd.h>
#include "SDL.h"

caseType getTokenTab(game_tab tab,int i,int j);

int getPosXFromToken(caseType t);

int getPosYFromToken(caseType t);

token getTokenValue(game_tab tab,int i,int j);

char getTokenSign(token * t);

void setTabToken(game_tab tab, int i, int j, token* t);

void setTokenSign(game_tab tab, int i, int j,char theSign);

caseType getTokenAdr(game_tab tab,int i);

caseTypeAdr getTokenAdrs(game_tab tab);

//========================= set Attributs Token ================================

void setSign(caseType t, char theSign);

void setPosition(caseType t, int x,int y);

void setCountOneValue(caseType t, bool b);

void setCountTwoValue(caseType t, bool b);

void setThreeCaseValid(caseType t, bool b);

void setvalue_C(caseType t, int value);

void setFilled(caseType t, int value);

void setvalue_R(caseType t, int value);

bool getFilled(caseType t);

bool getCountOne(caseType t);

bool getCountTwo(caseType t);

bool getThreeCaseValid(caseType t);

//==========================================================================================

//============================Setters - Getters Grille game_tab ============================

void setTabTokenSign(game_tab tab,int x, int y,char s);

void setTabTokenCountOne(game_tab tab,int x, int y,bool b);

void setTabTokenCountTwo(game_tab tab,int x, int y,bool b);

void setTabTokenThreeCaseValid(game_tab tab,int x, int y,bool b);

void setTabTokenFilled(game_tab tab,int x, int y,bool b);

//========================================================================

//depuis le player...


//============================== Getters et Setters ========================================

char getPlayerSign(typePlayer p);

bool getIsPlayerRobot(typePlayer p);

//Getters et Setters des vatiables de type Int

int* getValuePointer(int value);

int getPointerValue(int* value);

void setPointerValue(int * value, int v);

void setPointerValueInc(int * value, int v);

//to range after

//===================== FinishMorpion et fonctions pour compter les quintuplets possibles ou non  ====================

bool getFinishMorpion(bool* finish);

void setFinishMorpion(bool* finish,bool b);

void setcountQuintupletPossibleInc(typePlayer p);

void setCountQuintupletInc(typePlayer p);

int getCountQuintupletPossible(typePlayer p);

int getCountQuintuplet(typePlayer p);

void setcountQuintupletPossible(typePlayer p,int v);

//masquage des données (pour la structure de la Pile)

caseType getValFromPile(pile p);

caseType getValPileFromPileAdr(typePile p);

pile getPileNotPointer(typePile p);

pile getSuivPileFromPileAdr(typePile p);

pile getSuivPileFromPile(pile p);

void setValPile(pile *p, caseType v);

void setSuivPile(typePile p, typePile old);

void setPileToPile(typePile p, typePile old);

void setPileToSuivPile(typePile p);

void setSuivPileToSuivSuivPile(pile* t,pile new_t);

#endif
