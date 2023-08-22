#include <SDL.h>
#include <time.h>
#include "math.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "SDL_image.h"

#include "mask_extthree.h"

#define RADIUS 12//18

#define MAX_WORDS 256//pour la longueur maximales des string...


char** split_string(char* str, int* num_words)
{
    //cette fonction permet de split en tableau de string une chaîne de caractères
    char** words = malloc(MAX_WORDS * sizeof(char*)); // Allocate memory for word pointers
    int i = 0;

    char* token = strtok(str, " "); // Split string by space delimiter
    while (token != NULL && i < MAX_WORDS) {
        words[i] = token; // Store word pointer in array
        i++;
        token = strtok(NULL, " ");
    }

    *num_words = i; // Set number of words in output parameter
    return words; // Return array of word pointers
}

static SDL_Color grid_color = {255, 255, 255, 255}; //couleur blanche...

void initSDLComponent(sdlComponent** component)
{
    *component = (sdlComponent*)malloc(sizeof(sdlComponent));
}

void clear_surface(SDL_Surface * pWinSurf)
{
        Uint32 color = SDL_MapRGB(getWindPixelSurface(pWinSurf),93,29,10);
        SDL_FillRect(pWinSurf,NULL, color);
}

void efface_fenetre(sdlComponent** component)
{
    clear_surface(getSurfaceFromSdlComponent(component));
}

void maj_fenetre(sdlComponent** component){
    SDL_UpdateWindowSurface(getWindowFromSdlComponent(component));
}

void sdlInitWindows(sdlComponent** component)
{
    printf("entree dans la fonction sdlInitWindow \n");
    setInitWindowToSdlComponentWind(component);

    //(*component)->renderer = SDL_CreateRenderer((*component)->window, -1, 0);
    //(*component)->pWinSurf = SDL_GetWindowSurface((*component)->window);

    setComponentRenderer(component);
    setComponentPWinSurf(component);


    printf("sortie dans la fonction sdlInitWindow \n");
}


void afficheGrille(sdlComponent** component)//affiche la grille du rendu...
{
    // Dessiner les lignes horizontales
        for (int i = 0; i <= X; i++)
        {
            SDL_SetRenderDrawColor(getRendererFromComponent(component) , grid_color.r, grid_color.g, grid_color.b, grid_color.a);
            SDL_RenderDrawLine(getRendererFromComponent(component), 0, i * tailleImg, X * tailleImg, i * tailleImg);
        }

        // Dessiner les lignes verticales
        for (int i = 0; i <= Y; i++)
        {
            SDL_SetRenderDrawColor(getRendererFromComponent(component), grid_color.r, grid_color.g, grid_color.b, grid_color.a);
            SDL_RenderDrawLine(getRendererFromComponent(component), i * tailleImg, 0, i * tailleImg, X * tailleImg);
        }
}

void miseAJourRendererGrille(sdlComponent** component, game_tab tab)
{
    for(int i=0;i<X;i++)
    {
        for(int j=0;j<Y;j++)
        {
            SDL_Rect rect = {i*tailleImg+2, j*tailleImg+2, tailleImg-3, tailleImg-3};
            if (getTokenSign(getTokenTab(tab,i,j))=='X')
            {

                //Changer le fond en gris
                if (getThreeCaseValid(getTokenTab(tab,i,j)))
                {
                    SDL_SetRenderDrawColor(getRendererFromComponent(component), 128, 128, 128, 128); // couleur grise
                    SDL_RenderFillRect(getRendererFromComponent(component), &rect);
                }

                //ok
                int x1 = i * tailleImg, y1 = j * tailleImg; // première ligne
                int x2 = i * tailleImg + tailleImg, y2 = j * tailleImg + tailleImg;
                int x3 = i * tailleImg + tailleImg, y3 = j * tailleImg;
                int x4 = i * tailleImg, y4 = j * tailleImg + tailleImg;
                SDL_SetRenderDrawColor(getRendererFromComponent(component), 0, 0, 255, 255); // couleur bleu
                SDL_RenderDrawLine(getRendererFromComponent(component), x1, y1, x2, y2);
                SDL_RenderDrawLine(getRendererFromComponent(component), x3, y3, x4, y4);


            }
             else if (getTokenSign(getTokenTab(tab,i,j))=='O')
             {

                if (getThreeCaseValid(getTokenTab(tab,i,j)))
                {
                    SDL_SetRenderDrawColor(getRendererFromComponent(component), 128, 128, 128, 128); // couleur grise
                    SDL_RenderFillRect(getRendererFromComponent(component), &rect);
                }

                int cellX = i, cellY = j; // position de la case dans la grille
                int circleX = cellX * tailleImg + tailleImg / 2; // position horizontale du cercle
                int circleY = cellY * tailleImg + tailleImg / 2; // position verticale du cercle
                int radius = RADIUS;
                SDL_SetRenderDrawColor(getRendererFromComponent(component), 255, 0, 0, 255); // couleur rouge
                for (int i = 0; i < 360; i++)
                {
                    float angle = i * M_PI / 180.0f;
                    SDL_RenderDrawPoint(getRendererFromComponent(component), circleX + radius * cos(angle), circleY + radius * sin(angle));
                }
            }
            else if (getTokenSign(getTokenTab(tab,i,j))=='_') // nouveau cas : rien à dessiner
            {
                //effacer le rond en la mettant en noir...

                int cellX = i, cellY = j; // position de la case dans la grille
                int circleX = cellX * tailleImg + tailleImg / 2; // position horizontale du cercle
                int circleY = cellY * tailleImg + tailleImg / 2; // position verticale du cercle
                int radius = RADIUS;
                SDL_SetRenderDrawColor(getRendererFromComponent(component), 0, 0, 0, 0); // couleur noir
                for (int i = 0; i < 360; i++)
                {
                    float angle = i * M_PI / 180.0f;
                    SDL_RenderDrawPoint(getRendererFromComponent(component), circleX + radius * cos(angle), circleY + radius * sin(angle));
                }

                //effacer la croix en la mettant en noir...

                int x1 = i * tailleImg, y1 = j * tailleImg; // première ligne
                int x2 = i * tailleImg + tailleImg, y2 = j * tailleImg + tailleImg;
                int x3 = i * tailleImg + tailleImg, y3 = j * tailleImg;
                int x4 = i * tailleImg, y4 = j * tailleImg + tailleImg;
                SDL_SetRenderDrawColor(getRendererFromComponent(component), 0, 0, 0, 0); // couleur noir
                SDL_RenderDrawLine(getRendererFromComponent(component), x1, y1, x2, y2);
                SDL_RenderDrawLine(getRendererFromComponent(component), x3, y3, x4, y4);
            }
         }
     }
}

void miseAJourRenderer(sdlComponent** component)
{
    SDL_RenderPresent(getRendererFromComponent(component));
}

void freeMemoryAll(sdlComponent** component, game_tab tab,pile* p)
{
    //fonction qui permet de libérer la mémoire de tous les composants sdl, en plus de la table et la pile...

    SDL_FreeSurface(getSurfaceFromSdlComponent(component));
    freeTab(tab,X,Y,p);
    SDL_DestroyWindow(getWindowFromSdlComponent(component));
    SDL_DestroyRenderer(getRendererFromComponent(component));
    SDL_Quit();
}

void message(char *myTitle, char *myMessage){
        const SDL_MessageBoxButtonData buttons[] = {
        { /* .flags, .buttonid, .text */        0, 0, "ok" },
 //       { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "yes" },
 //       { SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 2, "cancel" },
    };
    const SDL_MessageBoxColorScheme colorScheme = {
        { /* .colors (.r, .g, .b) */
            /* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
            { 255,   0,   0 },
            /* [SDL_MESSAGEBOX_COLOR_TEXT] */
            {   0, 255,   0 },
            /* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
            { 255, 255,   0 },
            /* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
            {   0,   0, 255 },
            /* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
            { 255,   0, 255 }
        }
    };
    const SDL_MessageBoxData messageboxdata = {
        SDL_MESSAGEBOX_INFORMATION, /* .flags */
        NULL, /* .window */
        myTitle, /* .title */
        myMessage, /* .message */
        SDL_arraysize(buttons), /* .numbuttons */
        buttons, /* .buttons */
        &colorScheme /* .colorScheme */
    };
    int buttonid;
    if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0) {
        SDL_Log("error displaying message box");
        //return 1;
    }
}

void winnerExtensionThree(player* pl1, player *pl2)
{
    char theMessage[1000];
    sprintf(theMessage,"the player with the %c has %d quintuplets and %d possible quintuplets. \n And the player with the %c has %d quintuplets and %d possible quintuplets. \n",pl1->team,pl1->countNbQuintuplet
            ,pl1->countQuintupletPossible,pl2->team,
            pl2->countNbQuintuplet,pl2->countQuintupletPossible);

    char oldMessage[100];
    if (pl1->countNbQuintuplet > (pl2->countQuintupletPossible+pl2->countNbQuintuplet))
    {
        sprintf(oldMessage,"\n The player with the %c has won the game\n",pl1->team);
    }
    else if (pl2->countNbQuintuplet> (pl1->countQuintupletPossible+pl1->countNbQuintuplet))
    {
        sprintf(oldMessage,"\n The player with the %c has won the game\n",pl2->team);
    }
    else {
        sprintf(oldMessage,"\n The game is a draw\n");
    }

    strcat(theMessage,oldMessage);

    message("Fin du match",theMessage);
}

void addTokenFunction(game_tab tab,pile *p,SDL_Window** windows)
{
    // Initialisation de la SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("Erreur lors de l'initialisation de la SDL : %s", SDL_GetError());
        //return 1;
    }

    // Création de la fenêtre et du renderer
    SDL_Renderer *renderer;
    setInitRenderer(&renderer,windows);
    SDL_Surface* image_surface;
    setImgSurf(&image_surface,"data/addToken.png");

    if (image_surface == NULL)
    {
        //SDL_Log("Erreur lors du chargement de l'image : %s", SDL_GetError());
        printf("image non load \n");
        //return 1;
    }

    // Création d'une texture à partir de l'image
    SDL_Texture* texture;
    setInitTexture(&texture,&renderer,&image_surface);
    //SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image_surface);
    if (texture == NULL)
    {
        //SDL_Log("Erreur lors de la création de la texture : %s", SDL_GetError());
        printf("texture non créé non load \n");
        //return 1;
    }
    fflush(stdin);
    // Démarrage de la saisie de texte
    SDL_StartTextInput();

    // Boucle principale
    bool done = false;
    char value[256] = ""; // Valeur entrée par l'utilisateur
    while (!done)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    done = true;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_RETURN:
                            // L'utilisateur a validé la valeur
                            SDL_StopTextInput();
                            done = true; // Arrêt de la saisie de texte
                            break;
                        default:
                            break;
                    }
                    break;
                case SDL_TEXTINPUT:
                    // Ajout de la nouvelle entrée de texte à la valeur
                    strcat(value, event.text.text);
                    break;
                default:
                    break;
            }
        }
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);


        // Affichage du champ de saisie de texte
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }
    int length;
    char **table = split_string(value,&length);
    char tok;

    if ((strcmp(table[0],"X")== 0) || (strcmp(table[0],"O")== 0))
        tok = strcmp(table[0],"X")==0 ? 'X' : 'O';


    int num1 = atoi(table[1]),num2 =  atoi(table[2]);

    if (valid_coord(num1,num2))
    {
        if (getFilled(getTokenTab(tab,num1,num2)) ==false && getTokenSign(getTokenTab(tab,num1,num2))=='_')
        {
            pos thePosition;
            thePosition.posX = num1,thePosition.posY = num2;
            poseTokenOnGameTab(tab, thePosition,tok, p);
            message("Operation AJOUT token","REUSSI");
        }
    }
    else
    {
        printf("postion entree non valide \n");
        sleep(2);
    }


    // Fermeture de la fenêtre et de la SDL
     SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(*windows);
}

void deleteTokenFunction(game_tab tab,pile *p,SDL_Window** windows)
{
    pos thePosition;
    thePosition.posX=-1;thePosition.posY=-1;

    // Initialisation de la SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("Erreur lors de l'initialisation de la SDL : %s", SDL_GetError());
        //return 1;
    }

    // Création de la fenêtre et du renderer
    SDL_Renderer *renderer;
    setInitRenderer(&renderer,windows);
    SDL_Surface* image_surface;
    setImgSurf(&image_surface,"data/deleteToken.png");
    if (image_surface == NULL)
    {
        //SDL_Log("Erreur lors du chargement de l'image : %s", SDL_GetError());
        printf("image non load \n");
        //return 1;
    }

    // Création d'une texture à partir de l'image
    SDL_Texture* texture;
    setInitTexture(&texture,&renderer, &image_surface);
    if (texture == NULL) {
        //SDL_Log("Erreur lors de la création de la texture : %s", SDL_GetError());
        printf("texture non créé non load \n");
        //return 1;
    }
    fflush(stdin);
    // Démarrage de la saisie de texte
    SDL_StartTextInput();


    // Boucle principale
    bool done = false;
    char value[256] = ""; // Valeur entrée par l'utilisateur
    while (!done)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    done = true;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_RETURN:
                            // L'utilisateur a validé la valeur
                            SDL_StopTextInput();
                            done = true; // Arrêt de la saisie de texte
                            break;
                        default:
                            break;
                    }
                    break;
                case SDL_TEXTINPUT:
                    // Ajout de la nouvelle entrée de texte à la valeur
                    strcat(value, event.text.text);
                    break;
                default:
                    break;
            }
        }
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);


        // Affichage du champ de saisie de texte
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }
    int length;
    char **table = split_string(value,&length);


    int num1 = atoi(table[0]),num2= atoi(table[1]);

    if (valid_coord(num1,num2))
    {
        if (getFilled(getTokenTab(tab,num1,num2))==true && getTokenSign(getTokenTab(tab,num1,num2)) != '_')
        {
            thePosition.posX = num1,thePosition.posY = num2;
            deleteTokenOnGameTab(tab,thePosition,p);
            message("Operation DELETE token","REUSSI");
        }
        else
            message("Operation DELETE token","ECHOUEE, car case vide");
    }
    else
    {

        message("Operation DELETE token","ECHOUEE car position non valide");
    }


    // Fermeture de la fenêtre et de la SDL
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(*windows);
}

void comebackFunction(game_tab tab,pile *p,SDL_Window** windows)
{

    // Initialisation de la SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("Erreur lors de l'initialisation de la SDL : %s", SDL_GetError());
        //return 1;
    }

    // Création de la fenêtre et du renderer
    SDL_Renderer *renderer;
    setInitRenderer(&renderer,windows);
    SDL_Surface* image_surface;
    setImgSurf(&image_surface,"data/comeBack.png");
    if (image_surface == NULL) {
        //SDL_Log("Erreur lors du chargement de l'image : %s", SDL_GetError());
        printf("image non load \n");
        //return 1;
    }

    // Création d'une texture à partir de l'image
    SDL_Texture* texture;
    setInitTexture(&texture,&renderer, &image_surface);
    if (texture == NULL)
    {
        //SDL_Log("Erreur lors de la création de la texture : %s", SDL_GetError());
        printf("texture non créé non load \n");
        //return 1;
    }
    fflush(stdin);
    // Démarrage de la saisie de texte
    SDL_StartTextInput();


    // Boucle principale
    bool done = false;
    char value[256] = ""; // Valeur entrée par l'utilisateur
    while (!done)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    done = true;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_RETURN:
                            // L'utilisateur a validé la valeur
                            SDL_StopTextInput();
                            done = true; // Arrêt de la saisie de texte
                            break;
                        default:
                            break;
                    }
                    break;
                case SDL_TEXTINPUT:
                    // Ajout de la nouvelle entrée de texte à la valeur
                    strcat(value, event.text.text);
                    break;
                default:
                    break;
            }
        }
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);


        // Affichage du champ de saisie de texte
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }
    int length;
    char **table = split_string(value,&length);

    int num1 = atoi(table[0]);
    printf("valeur entree : %d\n",num1);
    sleep(3);

    if ((num1>0)&&(num1 < hauteurPile(getPileNotPointer(p))-1))
    {
        printf("le nombre de tokens présents sur la grille est %d \n",hauteurPile(getPileNotPointer(p))-1);
        sleep(2);
        want_to_delete_token(tab,p,num1);
        printf("le nombre de tokens présents sur la grille après la fonction want_to_delete(suppresion) est %d \n",hauteurPile(getPileNotPointer(p))-1);
        //loadPileTokenOnTab(tab,p,num1);
        printf("je suis entré dans la fonction loadPileTokenOnTab \n");
        sleep(3);
        message("Operation COME BACK","REUSSI");
    }
    else
        message("Operation COME BACK","ECHOUEE, car nombre entré invalide");

    // Fermeture de la fenêtre et de la SDL
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(*windows);
}
