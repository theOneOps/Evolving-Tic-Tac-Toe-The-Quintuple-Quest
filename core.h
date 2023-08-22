#ifndef MORPION36_CORE_H
#define MORPION36_CORE_H

#include "types.h"
#include "mask_core.h"

//By Harry

bool valid_coord(int x, int y); // fct pour verifier si une position est valide ou non s'après les dimensions de la grille

int value_code(int n, bool value_max); // fct pour attribuer les points aux 32 cases autour de la case joué par le bot/human

void eval_1_quintuplet(game_tab tab, pos position, int* code, player* pl_max); /*fonction pour evaluer les points
*/

void eval_1_direction(int* code, int* code_max, int* code_min);

void points_verticale(game_tab tab, pos position, int* code_max, int* code_min, player* pl_max);

void points_horizontal(game_tab tab, pos position, int* code_max, int* code_min, player* pl_max);

void points_bas_gauche(game_tab tab, pos position, int* code_max, int* code_min, player* pl_max);

void points_haut_gauche(game_tab tab, pos position, int* code_max, int* code_min, player* pl_max);

void eval_position(game_tab tab, pos position, player* pl_max);

void init_value(game_tab tab, player* pl_max);

void calc_value(game_tab tab, player* pl_max, pos position);

player* init_player(char team, bool robot);

//By Bill


token*** create_game_tab(int x,int y);//Fait

void freeTab(token*** tab, int x,int y,pile* p); //Fait

token* initToken(int x,int y);//Fait

void initialize_Tab(token*** TplateauJeu,int x,int y,pile* p);//Fait

//Fonctions pour determiner si un quintuplet a été formé...

bool finishquintupletvertical(game_tab tab,pos thePosition, char player,bool gameWithThirdExtension);//Fait

bool finishquintuplethorizontal(game_tab tab, pos thePosition, char player,bool gameWithThirdExtension);

bool finishquintupletHautGauche(game_tab tab, pos thePosition, char player,bool gameWithThirdExtension);

bool finishquintupletBasGauche(game_tab tab, pos thePosition, char player,bool gameWithThirdExtension);

bool thefinishquintuplet(game_tab tab, pos thePosition, char player,bool gameWithThirdExtension);//A appelé dans le main dans la boucle while ou do while du jeu...

pos bestPosition(game_tab tab, player* pl_max);

void poseTokenOnGameTab(game_tab tab, pos theposition, char sign,pile* p);

void play(game_tab tab, player *pl1, player *pl2, int* tourJeu, bool bot_vs_human, bool *finishMorpion, bool gameWithExtensionThird,pos new_position,sdlComponent** component,pile* p);

void set_players(bool bot_vs_human, player *pl1, player *pl2);

bool all_round_display(bool bot_vs_human);

void play_human(game_tab tab, player *pl, bool *finishMorpion, bool bot_vs_human,bool gameWithExtensionThird,pos new_position,sdlComponent** component,player *pl2,pile* p);

void play_bot(game_tab tab, player *pl, bool *finishMorpion, bool bot_vs_human, bool gameWithExtensionThird,sdlComponent** component,player *pl2,pile* p);

void display(game_tab tab, bool finish_display);


//Game with Six Extension

bool aboutsixExtension();//fonction qui permet de savoir si l'utilisateur veut jouer avec l'extension 6

void deleteTokenFunction(game_tab tab,pile *p,SDL_Window** windows);//AVec SDL...

void comebackFunction(game_tab tab,pile *p,SDL_Window** windows);//revenir en arrière avec le SDL...

void addTokenFunction(game_tab tab,pile *p,SDL_Window** windows);//ajouter un token à une position valide avec le SDL...

char** split_string(char* str, int* num_words);//pour split une chaîne de caractères en tableau de string...

void loadPileTokenOnTab(game_tab tab,pile *p,int counter);//fonction pour load les token de la pile sur la grille...

void poseTokenOnGameTabFromPile(game_tab tab,pos thePosition,char theSign);


//Game with the third extension...

bool aboutthirdextension();//fonction qui permet de savoir si l'utilisateur veut jouer avec l'extension 3

void affichenbquintuplet(player *pl1, player *pl2);

bool everyCaseFilled(game_tab tab);//fonction qui permet de savoir si toutes les cases su tableau ont une valeur différent de '_'... donc rempli apr X ou O....


//Pour compter les quintuplets possibles...


int countQuintupletPossibleVertical(game_tab tab,char sign,pos thePosition);

int countQuintupletPossibleHorizontal(game_tab tab,char sign,pos thePosition);

int countQuintupletPossibleHautGauche(game_tab tab,char sign,pos thePosition);

int countQuintupletPossibleBasGauche(game_tab tab,char sign,pos thePosition);

void reactualizeNbQuintupletPossible(game_tab tab,player *p1);

bool isFinishGame(player *p1,player *p2,game_tab tab);//dedans j'appelle egalement everyCaseFilled...

bool isHalfCompleted(game_tab tab);//fonction pour vérifier si au moins la moitié du tableau est rempli...

//Affichage SDL Fin du match avec l' extension 3...

void winnerExtensionThree(player* pl1, player *pl2);

//fonctions pour la partie sdl

//fonction pour clear la surface
void clear_surface(SDL_Surface * pWinSurf);
//
void efface_fenetre(sdlComponent **component);
//
void maj_fenetre(sdlComponent **component);


//fonction pour initaliser la fenêtre/le renderer/la surface de la fenêtre

void sdlInitWindows(sdlComponent** component);

//fonction pour mettre à jour le rendu après modification des cases de la grille...

void miseAJourRendererGrille(sdlComponent** component, game_tab tab);

//fonction pour mettre à jour le rendu tout court...

void miseAJourRenderer(sdlComponent** component);

//Fonction pour liberer les mémoires SDL et game_tab

void freeMemoryAll(sdlComponent** component, game_tab tab,pile* p);

void initSDLComponent(sdlComponent** component);

void afficheGrille(sdlComponent** component);

void message(char *myMessage, char *mytitle);

#endif //MORPION36_CORE_H

