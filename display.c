#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>


#include "types.h"
#include "display.h"
#include <unistd.h>

// affiche une barre horizontale de la longueur de len
void print_bar(int len)
{
    for (int i = 0; i < len; i++)
        printf("%c", HORIZONTAL_BAR);
}

void print_space_vertical(int len, char *msg)
{
    int len_msg = strlen(msg);

    printf("\n%c     ", VERTICAL);
    printf("%s", msg);

    for (int i = 0; i < (len - 5 - len_msg); i++)
    {
        printf(" ");
    }

    printf("%c", VERTICAL);
}

// DEBUT AFFICHAGE QUI JOUE

// gere l'affichage de la question "qui joue ?"
void style(bool selected, char *demand, char *selec_1, char *selec_2)
{
    int len = strlen(demand);

    char selec[25];
    strcpy(selec, "> ");
    char not_selec[25];
    strcpy(not_selec, "  ");

    printf("%c", CORNER_LU);
    print_bar(len);
    printf("%c", CORNER_RU);
    printf("\n%c", VERTICAL);
    printf("%c", *demand);
    printf("%c\n", VERTICAL);
    printf("%c", VERTICAL_L);
    print_bar(len);
    printf("%c", VERTICAL_R);

    if (selected)
    {
        strcat(selec, selec_2);
        strcat(not_selec, selec_1);
        print_space_vertical(len, not_selec);
        print_space_vertical(len, selec);
        printf("\n");
    } else {
        strcat(selec, selec_1);
        strcat(not_selec, selec_2);
        print_space_vertical(len, selec);
        print_space_vertical(len, not_selec);
        printf("\n");
    }

    printf("%c", CORNER_LB);
    print_bar(len);
    printf("%c", CORNER_RB);
    printf("\n");

    printf("selectionnez avec les touches (z + entrer) et (s + entrer) puis valider avec (espace + entrer) \n \n");
}

bool question(char *demand, char *selec_1, char *selec_2)
{
    bool selected = false;
    char touch = 0;

    style(selected, demand, selec_1, selec_2);

    while(touch != 32) {
        touch = getchar();

        //system("clear"); //unix
        system("CLS"); //windows

        style(selected, demand, selec_1, selec_2);

        switch(touch)
        {
            case 122 :
                selected = false;
                break;

            case 115 :
                selected = true;
                break;
        }
    }

    //system("clear"); //unix
    system("CLS"); //windows

    return selected;
}

// question a l'utilisateur pour sab=voir si il veut jouer contre un bot ou voir une partie d'un bot contre un bot
bool who_play()
{
    char selec_1[15] = "bot vs bot";
    char selec_2[15] = "bot vs human";

    char *demand = "quelle partie voulez-vous faire ?";

    return question(demand, selec_1, selec_2);
}

bool all_results()
{
    char selec_1[25] = "a la fin";
    char selec_2[25] = "entre deux placements";

    char *demand = "voulez-vous voir le jeu entre deux placements de pions ou juste a la fin ?";

    return question(demand, selec_1, selec_2);
}

// FIN AFFICHAGE QUI JOUE
// DEBUT AFFICHAGE TABLEAU

// retourne le signe a afficher dans le tableau
char print_char(token* Token)
{
    if ((Token->sign) == 'X')
        return 'X';
    else if ((Token->sign) == 'O')
        return 'O';
    else
        return '_';
}

// affiche le tableau
void print_tab_V1(token*** Token, int x, int y)
{
    //system("clear"); //unix
    system("CLS"); //windows

    for (int i = 0; i <= x; i++)
    {
        for (int j = 0; j <= y; j++)
        {
            if (j == 0 && i == 0) {
                printf("    ");
            } else if (j == 0 && i != 0) {
                printf("%4d", i - 1);
            } else if (i == 0 && j != 0) {
                printf("%4d", j - 1);
            } else if (i > 0 && j > 0) {
                char value = print_char(Token[i-1][j-1]);
                printf("%4c", value);
            }
        }
        printf("\n");

    }
}

void print_tab_V2(token*** Token, int x, int y)
{
    //system("clear"); //unix
    system("CLS"); //windows

    for (int j = 0; j <= (2 * y + 3); j++)
    {
        for (int i = 0; i <= (4 * x + 3); i++)
        {
            int i_print = (i / 4) - 1;
            int i_hun = i_print/100;
            int i_ten = (i_print - (i_hun * 100)) / 10;
            int i_unit = i_print % 10;

            int j_print = (j / 2) - 2;
            int j_hun = j_print/100;
            int j_ten = (j_print - (j_hun * 100)) / 10;
            int j_unit = j_print % 10;

            if ((j < 3 && i < 3) || (i % 4 !=1 && j <3) || (j % 2 == 1 && i < 3)) {
                printf(" ");
            } else if (j == 0) {
                if (i_hun == 0)
                    printf(" ");
                else printf("%d", i_hun);
            } else if (j == 1) {
                if (i_ten == 0)
                    printf(" ");
                else printf("%d", i_ten);
            } else if (j == 2) {
                printf("%d", i_unit);
            } else if (i == 0) {
                if (j_hun == 0)
                    printf(" ");
                else printf("%d", j_hun);
            } else if (i == 1) {
                if (j_ten == 0)
                    printf(" ");
                else printf("%d", j_ten);
            } else if (i == 2) {
                printf("%d", j_unit);
            } else if (i == 3 && j == 3) {
                printf("%c", CORNER_LU);
            } else if (i == (4 * x + 3) && j == 3) {
                printf("%c", CORNER_RU);
            } else if (i == 3 && j == (2 * y + 3)) {
                printf("%c", CORNER_LB);
            } else if (i == (4 * x + 3) && j == (2 * y + 3)) {
                printf("%c", CORNER_RB);
            } else if (i % 4 == 3 && j % 2 == 1 && i != 3 && j != 3 && i != (4 * x + 3) && j != (2 * y + 3)) {
                printf("%c", CROSS);
            } else if (i % 4 != 3 && j % 2 == 1) {
                printf("%c", HORIZONTAL_BAR);
            } else if (i % 4 == 3 && j % 2 == 0) {
                printf("%c", VERTICAL);
            } else if (i % 4 == 3 && j == 3) {
                printf("%c", HORIZONTAL_U);
            } else if (i % 4 == 3 && j == (2 * y + 3) ){
                printf("%c", HORIZONTAL_B);
            } else if (i == 3 && j % 2 == 1) {
                printf("%c", VERTICAL_L);
            } else if (i == (4 * x + 3) && j % 2 == 1) {
                printf("%c", VERTICAL_R);
            } else if (i % 4 == 0 && j % 2 == 0) {
                char value = print_char(Token[i_print][j_print]);
                printf(" %c ", value);
            }
        }
        printf("\n");
    }
    printf("\n");
}

void print_tab_r(token*** Token, int x, int y)
{
    for (int j = 0; j <= y; j++)
    {
        for (int i = 0; i <= x; i++)
        {
            if (j == 0 && i == 0) {
                printf("    ");
            } else if (j == 0 && i != 0) {
                printf("%4d", i - 1);
            } else if (i == 0 && j != 0) {
                printf("%4d", j - 1);
            } else if (i > 0 && j > 0) {
                printf("%4d", Token[i-1][j-1]->value_r);
            }
        }
        printf("\n");
    }
}

void print_tab_c(token*** Token, int x, int y)
{
    for (int j = 0; j <= y; j++)
    {
        for (int i = 0; i <= x; i++)
        {
            if (j == 0 && i == 0) {
                printf("    ");
            } else if (j == 0 && i != 0) {
                printf("%4d", i - 1);
            } else if (i == 0 && j != 0) {
                printf("%4d", j - 1);
            } else if (i > 0 && j > 0) {
                printf("%4d", Token[i-1][j-1]->value_r);
            }
        }
        printf("\n");
    }
}
// FIN AFFICHAGE TABLEAU

pos ask_pos()
{
    pos position;
    char x[300];
    char y[300];


    print_bar(2 * (X+2));

    printf("\nEntrez la position de la case a jouer (x puis y) :\n");

    printf("x : ");
    scanf("%s", x);
    printf("y : ");
    scanf("%s", y);

    size_t x_length = strlen(x);
    size_t y_length = strlen(y);

    bool is_correct = true;

    for(int i=0;i<x_length;i++)
    {
        if (!isdigit(x[i]))
        {
            is_correct=false;
            break;
        }
    }
    for(int i=0;i<y_length;i++)
    {
        if (!isdigit(y[i]))
        {
            is_correct=false;
            break;
        }
    }

    if (is_correct==false)
    {
        position.posX = 3000;
        position.posY = 4000;
    }
    else
    {
        int value_x, value_y;
        value_x = atoi(x);
        value_y = atoi(y);
        position.posX = value_x;
        position.posY = value_y;
    }

    return position;
}

void print_botwinner(player *pl)
{
    char *msg;

    if (pl->team == 'X')
    {
        msg = "Le bot utilisant les croix a gagne la partie !";
    } else {
        msg = "Le bot utilisant les ronds a gagne la partie !";
    }

    printf("   %c", CORNER_LU);
    print_bar(strlen(msg) + 2);
    printf("%c\n", CORNER_RU);
    printf("   %c %s %c\n", VERTICAL, msg, VERTICAL);
    printf("   %c", CORNER_LB);
    print_bar(strlen(msg) + 2);
    printf("%c\n", CORNER_RB);
}
