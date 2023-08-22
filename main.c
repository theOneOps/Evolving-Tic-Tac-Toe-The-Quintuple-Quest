#include "display.h"
#include "core.h"
#include <time.h>
#include "SDL.h"
#include <unistd.h>

int main(int argc, char* argv[])
{

    fflush(stdin);

    system("CLS"); //windows

    srand(time(NULL));

    game_tab tab = create_game_tab(X,Y);
    pile p;
    initialize_Tab(tab,X,Y,&p);

    bool bot_vs_human = who_play();

    typePlayer pl1 = init_player('X',true);
    typePlayer pl2 = init_player('O',true);

    //printf("initilaisation des joueurs reussi \n");

    set_players(bot_vs_human, pl1, pl2);

    printf("set_players réussi\n");

    bool gameWithExtensionThird = aboutthirdextension();

    sleep(1);

    bool gameWithExtensionSix = aboutsixExtension();

    if (gameWithExtensionSix)
    {
        printf("extension 6 lets 'go \n");
        sleep(1);
    }

    init_value(tab, pl1); //initialisation des valeurs du tableau

    //printf("initialisation des valeurs de la grille tab \n");

    SDL_Init(SDL_INIT_VIDEO);

    //printf("debut initiliasation des valeurs du composer \n");

    sdlComponent* composer;

    initSDLComponent(&composer);

    sdlInitWindows(&composer);

    //printf("\n fin initiliasation des valeurs du composer \n");//le window, le renderer, la surface du window...

    efface_fenetre(&composer);//On nettoie toute la surface du window... au debut du jeu

    //creation de la grille avec les lignes blanches et cases noires...

    afficheGrille(&composer);

    miseAJourRenderer(&composer);

    miseAJourRendererGrille(&composer,tab);

    miseAJourRenderer(&composer);

    //mise à jour de la grille avec les valeurs du tableau tab...
    bool is_finish = false;
    bool *finishMorpion = &is_finish;
    int tour = 0;
    int* tourJeu = &tour;
    int num1 = 1;

    if(bot_vs_human)
    {
        while (!(getFinishMorpion(finishMorpion)))
    {
        SDL_PumpEvents(); //do events
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
            {
                int mouseX = event.button.x;
                int mouseY = event.button.y;
                int cellX = mouseX / tailleImg;
                int cellY = mouseY / tailleImg;
                pos new_position;
                new_position.posX = cellX;
                new_position.posY = cellY;

                if (getTokenSign(getTokenTab(tab,cellX,cellY))=='_')
                {
                    if (getIsPlayerRobot(pl1))
                    {
                        play_bot(tab, pl1, finishMorpion, bot_vs_human, gameWithExtensionThird,&composer,pl2,&p);

                        if (getFinishMorpion(finishMorpion)==true && !gameWithExtensionThird)
                        {
                            message("Gagnant","le robot a gagne");
                            break;
                        }
                    }
                    else
                    {
                        if (getFilled(getTokenTab(tab,cellX,cellY))==false)
                        {
                            play_human(tab, pl1, finishMorpion, bot_vs_human, gameWithExtensionThird,new_position,&composer,pl2,&p);
                            setTabTokenSign(tab,cellX,cellY,getPlayerSign(pl1));
                            *tourJeu++;

                            if (getFinishMorpion(finishMorpion)==true && !gameWithExtensionThird)
                            {
                                message("Gagnant","Vous avez gagne");
                                break;
                            }
                        }

                   }
                   if (getIsPlayerRobot(pl2))
                    {
                        play_bot(tab, pl2, finishMorpion, bot_vs_human, gameWithExtensionThird,&composer,pl1,&p);

                        if (getFinishMorpion(finishMorpion)==true && !gameWithExtensionThird)
                        {
                            message("Gagnant","le robot a gagne");
                            break;
                        }
                    }
                    else
                    {

                        if (getFilled(getTokenTab(tab,cellX,cellY))==false)
                        {
                            play_human(tab, pl2, finishMorpion, bot_vs_human, gameWithExtensionThird,new_position,&composer,pl1,&p);
                            setTabTokenSign(tab,cellX,cellY,getPlayerSign(pl2));

                            *tourJeu++;

                            if (getFinishMorpion(finishMorpion)==true && !gameWithExtensionThird)
                            {
                                message("Gagnant","Vous avez gagne");
                                break;
                            }
                        }
                    }
                }
                afficheGrille(&composer);
                miseAJourRendererGrille(&composer,tab);
                miseAJourRenderer(&composer);
            }

            if (event.type== SDL_QUIT)
            {
                setFinishMorpion(finishMorpion,true);
                break;
            }

                if (gameWithExtensionSix)
                {
                    if (event.type == SDL_KEYDOWN && event.key.keysym.sym==SDLK_a)
                    {
                        SDL_Window *windows;
                        createWindowExtensionSix("operation 'ajouter' un token aa une position x et y",&windows);
                        fflush(stdin);
                        addTokenFunction(tab,&p,&windows);
                        afficheGrille(&composer);
                        miseAJourRendererGrille(&composer,tab);
                        miseAJourRenderer(&composer);
                    }

                    if (event.type == SDL_KEYDOWN && event.key.keysym.sym==SDLK_d)
                    {
                        SDL_Window *windows;
                        createWindowExtensionSix("operation 'enlever' un token aa une position x et y",&windows);
                        fflush(stdin);
                        deleteTokenFunction(tab,&p,&windows);
                        afficheGrille(&composer);
                        miseAJourRendererGrille(&composer,tab);
                        miseAJourRenderer(&composer);
                    }

                    if (event.type == SDL_KEYDOWN && event.key.keysym.sym==SDLK_c)
                    {
                        SDL_Window *windows;

                        createWindowExtensionSix("Operation 'Retour en Arriere'",&windows);
                        fflush(stdin);
                        comebackFunction(tab,&p,&windows);
                        afficheGrille(&composer);
                        miseAJourRendererGrille(&composer,tab);
                        miseAJourRenderer(&composer);
                    }
                }
            }
            miseAJourRenderer(&composer);

        }

    if (getFinishMorpion(finishMorpion) && gameWithExtensionThird)
    {
        winnerExtensionThree(pl1,pl2);
        print_tab_V2(tab,X,Y);
        affichenbquintuplet(pl1, pl2);
    }
    sleep(20);

    //libération de la mémoire...

    freeMemoryAll(&composer, tab,&p);

    printf("fin du programme \n");

    }
    else
    {
        SDL_Event event;
        pos theposition;
        theposition.posX=2,theposition.posY=3;
        while(!(getFinishMorpion(finishMorpion)))
        {
            play(tab,pl1,pl2,tourJeu,bot_vs_human,finishMorpion,gameWithExtensionThird,theposition,&composer,&p);
            afficheGrille(&composer);
            miseAJourRendererGrille(&composer,tab);
            miseAJourRenderer(&composer);
            *tourJeu+=1;


            while(SDL_PollEvent(&event))
            {
                if (gameWithExtensionSix)
                {
                    if (event.type == SDL_KEYDOWN && event.key.keysym.sym==SDLK_a)
                    {
                        SDL_Window *windows;
                        createWindowExtensionSix("operation 'ajouter' un token aa une position x et y",&windows);
                        fflush(stdin);
                        addTokenFunction(tab,&p,&windows);
                        // L'utilisateur a appuyé sur la touche A
                        afficheGrille(&composer);
                        miseAJourRendererGrille(&composer,tab);
                        miseAJourRenderer(&composer);
                    }

                    if (event.type == SDL_KEYDOWN && event.key.keysym.sym==SDLK_d)
                    {
                        SDL_Window *windows;
                        createWindowExtensionSix("operation 'enlever' un token aa une position x et y",&windows);
                        //printf("entrez dans A\n");
                        fflush(stdin);
                        deleteTokenFunction(tab,&p,&windows);
                        // L'utilisateur a appuyé sur la touche A
                        afficheGrille(&composer);
                        miseAJourRendererGrille(&composer,tab);
                        //SDL_RenderPresent(composer->renderer);
                        miseAJourRenderer(&composer);
                    }

                    if (event.type == SDL_KEYDOWN && event.key.keysym.sym==SDLK_c)
                    {
                        SDL_Window *windows;
                        createWindowExtensionSix("Operation 'Retour en Arriere'",&windows);
                        fflush(stdin);
                        comebackFunction(tab,&p,&windows);
                        // L'utilisateur a appuyé sur la touche A
                        afficheGrille(&composer);
                        miseAJourRendererGrille(&composer,tab);
                        //SDL_RenderPresent(composer->renderer);
                        miseAJourRenderer(&composer);
                    }
                }
            }

        }

        if (getFinishMorpion(finishMorpion) && gameWithExtensionThird)
        {
            winnerExtensionThree(pl1,pl2);
            print_tab_V2(tab,X,Y);
            affichenbquintuplet(pl1, pl2);
        }

        sleep(20);
        printf("fin du programme \n");
    }

    freeMemoryAll(&composer, tab,&p);
    printf("fin du programme \n");

    return 0;
}
