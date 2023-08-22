#include "core.h"
#include "display.h"
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <unistd.h>
#include "mask_core.h"


bool valid_coord(int x, int y)
{// verifie que des coordonner soit dans un tableau
    return ((x >= 0 && x < X)&&
            (y >= 0 && y < Y));
}

int value_code(int n, bool value_max)
{

    //fonction qui attribue les valeurs...
    if (value_max)
        return (int)(5. * pow(10, (n/6)-1));
    else
        return (int)(5. * (pow(10, n-1) - pow(10, n-2)));
}

void eval_1_quintuplet(game_tab tab, pos position, int* code, typePlayer pl_max)
{
    int x = position.posX;
    int y = position.posY;

    // en général, on vérifie si la case contient le signe du joueur,

    if (getTokenSign(getTokenTab(tab,x,y)) == '_')
    {
        //sinon code + 0

        //*code = *code;
        setPointerValue(code,getPointerValue(code));
    } else if(getTokenSign(getTokenTab(tab,x,y)) == pl_max->team)
    {
        //*code = *code + 6; //si c'est le cas alors code + 6
        setPointerValueInc(code,6);
    }
    else
    {
        //*code = *code + 1; //sinon + 1
        setPointerValueInc(code,1);
    }
}

void eval_1_direction(int* code, int* code_max, int* code_min)
{
    //cette fonction permet de calculer la valeur du code qui nous permettra de savoir si
    if (getPointerValue(code) == 0 || getPointerValue(code) % 13 ==0) //si jamais enlever (code % 13 ==0)
    {
        //*code_max += 1;

        setPointerValueInc(code_max,1);

        //*code_min += 1;

        setPointerValueInc(code_min,1);

    } else if (getPointerValue(code) <= 5)
    {
        //*code_max += value_code(*code, false); // si que des cases O par exemple, alors le joueur en cours va devoir jouer à une case avec code_max
        setPointerValueInc(code_max,value_code(getPointerValue(code),false));
        //*code_min += value_code((*code) * 6, true);
        setPointerValueInc(code_min,value_code(getPointerValue(code)*6,true));

    } else if (getPointerValue(code) % 6 == 0)
    {
        //*code_max += value_code(*code, true);
        setPointerValueInc(code_max,value_code(getPointerValue(code),true));

        //*code_min += value_code((*code) / 6, false);
        setPointerValueInc(code_min,value_code(getPointerValue(code)/6,false));
    }
}

void points_verticale(game_tab tab, pos position, int* code_max, int* code_min, typePlayer pl_max)
{
    /*c'est juste une valeur qui même si code pas valide ou pas,on sait immédiatement

    si on a un quintuplet ouvert ou pas car code divisible par 6 et % 6

    donne le nbre de signe pour le joueur en cours, et si code < 5, alors quintuplet > 5 ou non % 6 = quintuplet fermé

    et sinon quintuplet contient que des signes de l'autre joueur...

    */
    pos new_pos = position;

    int tmp_y = position.posY - 4;
    int x = position.posX;

    while(tmp_y <= position.posY) {
        if (!(valid_coord(x, tmp_y))) {
            tmp_y++;
        } else {
            int code = 0;

            for (int j = tmp_y; j < tmp_y + 5; j++) {
                if (!(valid_coord(x, j))) {
                    code += 13;

                } else {
                    new_pos.posY = j;
                    eval_1_quintuplet(tab, new_pos, &code, pl_max);
                }
            }
            eval_1_direction(&code, code_max, code_min);

            tmp_y++;
        }
    }
}

void points_horizontal(game_tab tab, pos position, int* code_max, int* code_min, typePlayer pl_max){

    pos new_pos = position;

    int tmp_x = position.posX - 4;
    int y = position.posY;

    while(tmp_x <= position.posX){
        if(!(valid_coord(tmp_x, y))){
            tmp_x++;
        } else {
            int code = 0;

            for (int i = tmp_x; i < tmp_x + 5; i++) {
                if (!(valid_coord(i, y)))
                    code += 13;
                else {
                    new_pos.posX = i;
                    eval_1_quintuplet(tab, new_pos, &code, pl_max);
                }
            }

            eval_1_direction(&code, code_max, code_min);

            tmp_x++;
        }
    }
}

void points_bas_gauche(game_tab tab, pos position, int* code_max, int* code_min, typePlayer pl_max){

    pos new_pos = position;

    int tmp_x = position.posX - 4;
    int tmp_y = position.posY + 4;

    while(tmp_x <= position.posX) {
        if (!(valid_coord(tmp_x, tmp_y))) {
            tmp_x++;
            tmp_y--;
        } else {
            int code = 0;

            int i = tmp_x;
            for (int j = tmp_y; j > tmp_y - 5; j--) {

                if (!(valid_coord(i, j)))
                    code += 13;
                else {
                    new_pos.posX = i;
                    new_pos.posY = j;
                    eval_1_quintuplet(tab, new_pos, &code, pl_max);
                }
                i++;
            }

            eval_1_direction(&code, code_max, code_min);

            tmp_x++;
            tmp_y--;
        }
    }
}

void points_haut_gauche(game_tab tab, pos position, int* code_max, int* code_min, typePlayer pl_max)
{

    pos new_pos = position;

    int tmp_x = position.posX - 4;
    int tmp_y = position.posY - 4;

    while(tmp_x <= position.posX)
    {
        if(!(valid_coord(tmp_x, tmp_y))){
            tmp_x++;
            tmp_y++;
        } else {
            int code = 0;

            int i = tmp_x;
            for (int j = tmp_y; j < tmp_y + 5; j++) {

                if (!(valid_coord(i, j)))
                    code += 13;
                else {
                    new_pos.posX = i;
                    new_pos.posY = j;
                    eval_1_quintuplet(tab, new_pos,&code, pl_max);
                }
                i++;
            }

            eval_1_direction(&code, code_max, code_min);

            tmp_x++;
            tmp_y++;
        }
    }
}

void eval_position(game_tab tab, pos position, typePlayer pl_max)
{

    //cette fonction met à jour les valeurs value_r et value_c de la case à la position passée en paramètre...

    int code_max = 0;
    int code_min = 0;

    points_verticale(tab, position, &code_max, &code_min, pl_max);
    points_bas_gauche(tab, position, &code_max,&code_min, pl_max);
    points_haut_gauche(tab, position, &code_max,&code_min, pl_max);
    points_horizontal(tab, position, &code_max,&code_min, pl_max);


    if (getPlayerSign(pl_max) == 'X')
    {
        //tab[position.posX][position.posY]->value_c = code_max;
        setvalue_C(getTokenTab(tab,position.posX,position.posY),code_max);

        //tab[position.posX][position.posY]->value_r = code_min;
        setvalue_R(getTokenTab(tab,position.posX,position.posY),code_min);

    } else {
        //tab[position.posX][position.posY]->value_c = code_min;
        setvalue_C(getTokenTab(tab,position.posX,position.posY),code_min);
        //tab[position.posX][position.posY]->value_r = code_max;
        setvalue_R(getTokenTab(tab,position.posX,position.posY),code_max);
    }
}

void init_value(game_tab tab, typePlayer pl_max)
{
    //cette fonction n'est appelé qu'une fois au tout début du jeu pour initialiser les value_r et value_c de chacune des cases...
    for(int i = 0; i < X; i++)
    {
        for(int j = 0; j < Y; j++)
        {
            pos position;
            position.posX = i;
            position.posY = j;
            eval_position(tab, position, pl_max);
        }
    }
}

void calc_value(game_tab tab, typePlayer pl_max, pos position)
{
    //cette fonction met à jour les valeurs value_r et value_c des 32 cases autour de la case jouée par un bot ou player humain

    int x = position.posX;
    int y = position.posY;

    for (int i = x-4; i <= x+4; i++)
    {
        if (valid_coord(i, position.posY))
        {
            pos new_position;
            new_position.posX = i;
            new_position.posY = position.posY;
            eval_position(tab, new_position, pl_max);
        }
    }

    for (int i = y-4; i <= y+4; i++)
    {
        if (valid_coord(position.posX, i))
        {
            pos new_position;
            new_position.posX = position.posX;
            new_position.posY = i;
            eval_position(tab, new_position, pl_max);
        }
    }

    int j = y-4;
    for (int i = x-4; i <= x+4; i++)
    {
        if (valid_coord(i, j))
        {
            pos new_position;
            new_position.posX = i;
            new_position.posY = j;
            eval_position(tab, new_position, pl_max);
        }
        j++;
    }

    j = y+4;
    for (int i = x-4; i <= x+4; i++)
    {
        if (valid_coord(i, j))
        {
            pos new_position;
            new_position.posX = i;
            new_position.posY = j;
            eval_position(tab, new_position, pl_max);
        }
        j--;
    }
}

typePlayer init_player(char team, bool robot)
{
    //initliastion du player

    typePlayer pl = (typePlayer)malloc(sizeof(player));
    pl->team = team;
    pl->robot = robot;
    pl->countNbQuintuplet = 0;
    pl->countQuintupletPossible = 0;

    return pl;
}

game_tab create_game_tab(int x,int y)
{
    //fonction création de la grille de jeu...
    game_tab res = (game_tab)malloc(x*sizeof(caseTypeAdr));
    for (int i=0;i<x;i++)
    {
        res[i] =(caseTypeAdr)malloc(sizeof(caseType)*y);
    }
    return res;
}

void initialize_Tab(game_tab TplateauJeu,int x,int y,typePile p)
{
    for (int i=0;i<x;i++)
    {
        for (int j=0;j<y;j++)
        {
            //(TplateauJeu[i][j]) = initToken(i,j);
            setTabToken(TplateauJeu,i,j,initToken(i,j));
        }
    }

    *p = create_pile();
    Ajout_tete(p, initToken(-1,-1));
}

void freeTab(game_tab tab, int x,int y,typePile p)
{
    //free la mémoire allouée pour le tableau...
    for(int i=0;i<x;i++)
    {
        free(getTokenAdr(tab,i));
    }
    free(getTokenAdrs(tab));
    emptyPile(p);//et on vide la pile...
}

caseType initToken(int x,int y)
{
    //  ici on initialise les valeurs des cases...
    caseType box = (caseType)malloc(sizeof(token));
    /*
    box->sign='_';
    box->position.posX=x,box->position.posY=y;
    box->filled=false;
    box->value_c=0;
    box->value_r=0;
    box->countTwo=false;
    box->countOne=false;
    box->threeCaseValid=false;
    */

    setSign(box,'_');
    setPosition(box,x,y);
    setFilled(box,false);
    setvalue_C(box,0);
    setvalue_R(box,0);
    setCountOneValue(box,false);
    setCountTwoValue(box,false);
    setThreeCaseValid(box,false);



    return box;
}

void poseTokenOnGameTab(game_tab tab, pos theposition, char sign,typePile p)
{

    //lorsque je pose un token, je mets à true l'attribut filled et je l'ajoute à la pile...

    //tab[theposition.posX][theposition.posY]->sign=sign;
    //tab[theposition.posX][theposition.posY]->filled=true;
    setTabTokenSign(tab,theposition.posX,theposition.posY,sign);
    setTabTokenFilled(tab,theposition.posX,theposition.posY,true);
    Ajout_tete(p, tab[theposition.posX][theposition.posY]);
    printf("passes à l'interieur \n");
}

void poseTokenOnGameTabFromPile(game_tab tab, pos theposition, char sign)
{
    /*
    tab[theposition.posX][theposition.posY]->sign=sign;
    tab[theposition.posX][theposition.posY]->countOne=false;
    tab[theposition.posX][theposition.posY]->countTwo=false;
    tab[theposition.posX][theposition.posY]->threeCaseValid=false;
    tab[theposition.posX][theposition.posY]->filled=false;
    */

    setTabTokenSign(tab,theposition.posX,theposition.posY,sign);
    setTabTokenCountOne(tab,theposition.posX,theposition.posY,false);
    setTabTokenCountTwo(tab,theposition.posX,theposition.posY,false);
    setTabTokenThreeCaseValid(tab,theposition.posX,theposition.posY,false);
    setTabTokenFilled(tab,theposition.posX,theposition.posY,false);

}

bool finishquintupletvertical(game_tab tab, pos thePosition, char sign, bool gameWithThirdExtension)
{
    int x = thePosition.posX, y= thePosition.posY,count=0;
    int resTrue = 0, resFalse = 0, res = 0;
    pos allPositions[40];
    if (gameWithThirdExtension==false)
    {
        for(int i=y-4;i<=y+4;i++)
        {
            if (valid_coord(x,i)) {
                if (getTokenSign(getTokenTab(tab,x,i)) == sign)
                    count += 1;
                else
                    count = 0;
            }

            if (count==5) {
                break;
            }
        }
    }
    else{
        for(int i = y-4;i<=y+4;i++)
        {
            if (valid_coord(x,i)) {
                if (getCountOne(getTokenTab(tab,x,i)) ==false || getCountTwo(getTokenTab(tab,x,i))==false) {
                    if (getTokenSign(getTokenTab(tab,x,i)) == sign)
                    {
                        count += 1;
                        allPositions[res]=tab[x][i]->position;
                        res+=1;
                        if (getCountOne(getTokenTab(tab,x,i)) == true && getCountTwo(getTokenTab(tab,x,i))== false) {
                            resTrue+=1;
                        }
                        else if (getCountOne(getTokenTab(tab,x,i))== false && getCountTwo(getTokenTab(tab,x,i))== false) {
                            resFalse+=1;
                        }
                    }
                    else
                    {
                        count = 0;
                        resFalse = 0;
                        resTrue = 0;
                        for (int k=0;k<res;k++)
                        {
                            allPositions[k].posX = -1;
                            allPositions[k].posY = -1;
                        }
                        res=0;
                    }
                }
            }

            if (count==5)
            {
                if (((resFalse==5 && resTrue==0) || (resFalse==4 && resTrue==1) || (resFalse==0 && resTrue==5)))
                {
                    for(int k=0;k<res;k++)
                    {
                        if (getCountOne(getTokenTab(tab,allPositions[k].posX,allPositions[k].posY))==false)
                        {
                            //tab[allPositions[k].posX][allPositions[k].posY]->countOne = true;//on compte pour la première fois ce quintuplet...
                            setCountOneValue(getTokenTab(tab,allPositions[k].posX,allPositions[k].posY),true);
                            //tab[allPositions[k].posX][allPositions[k].posY]->threeCaseValid=true;
                            setThreeCaseValid(getTokenTab(tab,allPositions[k].posX,allPositions[k].posY),true);
                        }
                        else if (getCountTwo(getTokenTab(tab,allPositions[k].posX,allPositions[k].posY)) == false)
                        {
                            //tab[allPositions[k].posX][allPositions[k].posY]->countTwo = true;//on compte pour la deuxième fois ce quintuplet...
                            setCountTwoValue(getTokenTab(tab,allPositions[k].posX,allPositions[k].posY),true);
                        }
                    }
                    break;
                }
                else
                {
                    count=0;
                    break;
                }
            }
        }
    }
    return (count==5)?true:false;
}

bool finishquintuplethorizontal(game_tab tab, pos thePosition, char sign,bool gameWithThirdExtension)
{
    int x = thePosition.posX, y= thePosition.posY,count=0;
    int resTrue = 0, resFalse = 0, res = 0;
    pos allPositions[40];
    if (gameWithThirdExtension==false)
    {
        for(int i=x-4;i<=x+4;i++)
        {
            if (valid_coord(i,y)) {
                if (getTokenSign(getTokenTab(tab,i,y)) == sign)
                    count += 1;
                else
                    count = 0;
            }

            if (count==5) {
                break;
            }
        }
    }
    else{
        for(int i=x-4;i<=x+4;i++)
        {
            if (valid_coord(i,y)) {
                if (getCountOne(getTokenTab(tab,i,y))==false || getCountTwo(getTokenTab(tab,i,y))==false) {
                    if (getTokenSign(getTokenTab(tab,i,y)) == sign)
                    {
                        count += 1;
                        allPositions[res] = tab[i][y]->position;
                        res+=1;
                        if (getCountOne(getTokenTab(tab,i,y))==true && getCountTwo(getTokenTab(tab,i,y))==false) {
                            resTrue+=1;
                        }
                        else if (getCountOne(getTokenTab(tab,i,y))==false && getCountTwo(getTokenTab(tab,i,y))==false) {
                            resFalse+=1;
                        }
                    }
                    else
                    {
                        count = 0;
                        resFalse=0;
                        resTrue=0;
                        for (int k=0;k<res;k++)
                        {
                            allPositions[k].posX=-1;
                            allPositions[k].posY=-1;
                        }
                        res=0;
                    }
                }
            }


            if (count==5)
            {
                if (((resFalse==5 && resTrue==0) || (resFalse==4 && resTrue==1) || (resFalse==0 && resTrue==5)))
                {
                    for(int k=0;k<res;k++)
                    {
                        if (getCountOne(getTokenTab(tab,allPositions[k].posX,allPositions[k].posY))==false)
                        {
                            //tab[allPositions[k].posX][allPositions[k].posY]->countOne = true;//on compte pour la première fois ce quintuplet...
                            setCountOneValue(getTokenTab(tab,allPositions[k].posX,allPositions[k].posY),true);
                            //tab[allPositions[k].posX][allPositions[k].posY]->threeCaseValid=true;
                            setThreeCaseValid(getTokenTab(tab,allPositions[k].posX,allPositions[k].posY),true);

                        }
                        else if (tab[allPositions[k].posX][allPositions[k].posY]->countTwo==false)
                        {
                            setCountTwoValue(getTokenTab(tab,allPositions[k].posX,allPositions[k].posY),true);
                            //tab[allPositions[k].posX][allPositions[k].posY]->countTwo = true;//on compte pour la deuxième fois ce quintuplet...
                        }
                    }
                    break;
                }
                else
                {
                    count=0;
                    break;
                }
            }
        }
    }

    return (count==5)?true:false;
}

bool finishquintupletHautGauche(game_tab tab, pos thePosition, char sign, bool gameWithThirdExtension)
{
    int x = thePosition.posX, y= thePosition.posY-4,count=0;
    int resTrue = 0, resFalse = 0,res=0;
    pos allPositions[40];
    if (gameWithThirdExtension==false)
    {
        for(int i=x-4;i<=x+4;i++)
        {
            if (valid_coord(i,y)) {
                if (getTokenSign(getTokenTab(tab,i,y)) == sign)
                    count += 1;
                else
                    count = 0;
            }

            if (count==5) {
                break;
            }
            y+=1;
        }
    }
    else{
        for(int i=x-4;i<=x+4;i++)
        {
            if (valid_coord(i,y)) {
                if (getCountOne(getTokenTab(tab,i,y))==false ||getCountTwo(getTokenTab(tab,i,y))==false) {
                    if (getTokenSign(getTokenTab(tab,i,y)) == sign)
                    {
                        count += 1;
                        allPositions[res] = tab[i][y]->position;
                        res+=1;
                        if (getCountOne(getTokenTab(tab,i,y))==true &&getCountTwo(getTokenTab(tab,i,y))==false) {
                            resTrue+=1;
                        }
                        else if (getCountOne(getTokenTab(tab,i,y))==false && getCountTwo(getTokenTab(tab,i,y))==false) {
                            resFalse+=1;
                        }
                    }
                    else
                    {
                        count = 0;
                        resFalse=0;
                        resTrue=0;
                        for (int k=0;k<res;k++)
                        {
                            allPositions[k].posX=-1;
                            allPositions[k].posY=-1;
                        }
                        res=0;
                    }
                }
            }

            if (count==5)
            {
                if (((resFalse==5 && resTrue==0) || (resFalse==4 && resTrue==1) || (resFalse==0 && resTrue==5)))
                {
                    for(int k=0;k<res;k++)
                    {
                        if (tab[allPositions[k].posX][allPositions[k].posY]->countOne==false)
                        {
                            //tab[allPositions[k].posX][allPositions[k].posY]->countOne = true;//on compte pour la première fois ce quintuplet...
                            setCountOneValue(getTokenTab(tab,allPositions[k].posX,allPositions[k].posY),true);
                            //tab[allPositions[k].posX][allPositions[k].posY]->threeCaseValid=true;
                            setThreeCaseValid(getTokenTab(tab,allPositions[k].posX,allPositions[k].posY),true);
                        }
                        else if (tab[allPositions[k].posX][allPositions[k].posY]->countTwo==false)
                        {
                            setCountTwoValue(getTokenTab(tab,allPositions[k].posX,allPositions[k].posY),true);
                            //tab[allPositions[k].posX][allPositions[k].posY]->countTwo = true;//on compte pour la deuxième fois ce quintuplet...
                        }
                    }
                    break;
                }
                else
                {
                    count=0;
                    break;
                }
            }
            y+=1;
        }
    }

    return (count==5)?true:false;
}

bool finishquintupletBasGauche(game_tab tab, pos thePosition, char sign, bool gameWithThirdExtension)
{
    int x = thePosition.posX, y= thePosition.posY+4,count=0;
    int resTrue = 0, resFalse = 0,res=0;
    pos allPositions[40];
    if (gameWithThirdExtension==false)
    {
        for(int i=x-4;i<=x+4;i++)
        {
            if (valid_coord(i,y)) {
                if (getTokenSign(getTokenTab(tab,i,y)) == sign)
                    count += 1;
                else
                    count = 0;
            }

            if (count==5) {
                break;
            }
            y-=1;
        }
    }
    else{
        for(int i=x-4;i<=x+4;i++)
        {
            if (valid_coord(i,y)) {
                if (getCountOne(getTokenTab(tab,i,y))==false || getCountTwo(getTokenTab(tab,i,y))==false) {
                    if (getTokenSign(getTokenTab(tab,i,y)) == sign)
                    {
                        count += 1;
                        allPositions[res] = tab[i][y]->position;
                        res+=1;
                        if (getCountOne(getTokenTab(tab,i,y))==true && getCountTwo(getTokenTab(tab,i,y))==false) {
                            resTrue+=1;
                        }
                        else if (getCountOne(getTokenTab(tab,i,y))==false && getCountTwo(getTokenTab(tab,i,y))==false) {
                            resFalse+=1;
                        }
                    }
                    else
                    {
                        count = 0;
                        resFalse=0;
                        resTrue=0;
                        for (int k=0;k<res;k++)
                        {
                            allPositions[k].posX=-1;
                            allPositions[k].posY=-1;
                        }
                        res=0;
                    }
                }
            }


            if (count==5)
            {
                if (((resFalse==5 && resTrue==0) || (resFalse==4 && resTrue==1) || (resFalse==0 && resTrue==5)))
                {
                    for(int k=0;k<res;k++)
                    {
                        if (tab[allPositions[k].posX][allPositions[k].posY]->countOne==false)
                        {
                             //tab[allPositions[k].posX][allPositions[k].posY]->countOne = true;//on compte pour la première fois ce quintuplet...
                            setCountOneValue(getTokenTab(tab,allPositions[k].posX,allPositions[k].posY),true);
                            //tab[allPositions[k].posX][allPositions[k].posY]->threeCaseValid=true;
                            setThreeCaseValid(getTokenTab(tab,allPositions[k].posX,allPositions[k].posY),true);
                        }
                        else if (tab[allPositions[k].posX][allPositions[k].posY]->countTwo==false)
                        {
                           setCountTwoValue(getTokenTab(tab,allPositions[k].posX,allPositions[k].posY),true);
                            //tab[allPositions[k].posX][allPositions[k].posY]->countTwo = true;//on compte pour la deuxième fois ce quintuplet...
                        }
                    }
                    break;
                }
                else
                {
                    count=0;
                    break;
                }
            }
            y-=1;
        }
    }

    return (count==5)?true:false;
}

bool thefinishquintuplet(game_tab tab, pos thePosition, char sign, bool gameWithThirdExtension)
{
    return (finishquintuplethorizontal(tab, thePosition, sign, gameWithThirdExtension) || finishquintupletvertical(tab, thePosition, sign, gameWithThirdExtension) || finishquintupletHautGauche(tab, thePosition, sign, gameWithThirdExtension) || finishquintupletBasGauche(tab, thePosition, sign, gameWithThirdExtension));
}

void tab_best_position(token new_token, char team_max, pos* best_positions, int* best_value, int *element_nb)
{
    if(team_max == 'X')
    {   //Si joueur X alors je compare la valeur_c de la case à la best value qui est initialisé à 0
        if(new_token.value_c > getPointerValue(best_value))
        {
            //*best_value = new_token.value_c;    //si value_c supérieur à best_value alors je le remets au tout debut du tableau
            setPointerValue(best_value,new_token.value_c);
            best_positions[0] = new_token.position;
            //*element_nb = 1;
            setPointerValue(element_nb,1);
        } else if(new_token.value_c == getPointerValue(best_value)) //si value_c egal à best_value alors je le remets à la suite dans le tableau
        {
            best_positions[getPointerValue(element_nb)] = new_token.position;
            //(*element_nb)+=1;//et j'augmente la valeur de l'index pour la prochaine position à mettre...
            setPointerValueInc(element_nb,1);
        }
        else {
            return;
        }
    } else
    {
        if(new_token.value_r > getPointerValue(best_value))
        {
            *best_value = new_token.value_r;
            best_positions[0] = new_token.position;
            setPointerValue(element_nb,1);
        } else if(new_token.value_r == getPointerValue(best_value))
        {
            best_positions[getPointerValue(element_nb)] = new_token.position;
            //(*element_nb)+=1;
            setPointerValueInc(element_nb,1);
        }
        else {
            return;
        }
    }
}

pos bestPosition(game_tab tab, player* pl_max)
{
    // fonction qui renvoie la meilleure position à jouer pour le bot...
    pos thePosition;
    pos best_positions[600]; //= (pos*)malloc(sizeof(pos));
    int best_value = 0;
    int element_nb = 0;
    int *ptr_nb = &element_nb;

    char team_max = pl_max->team;

    for(int i=0;i<X;i++)
    {
        for(int j=0;j<Y;j++)
        {
            if (tab[i][j]->filled==false)
            {
                //token *new_token = tab[i][j];

                tab_best_position(getTokenValue(tab,i,j), team_max, best_positions, &best_value, ptr_nb);
                //tab_best_position(*new_token, team_max, best_positions, &best_value, ptr_nb); //
            }
        }
    }

    int index = rand() % (element_nb);
    thePosition = best_positions[index];

    //renvoie une position au hasard parmis les meilleurs positions possibles à jouer pour le bot...

    return thePosition;
}

void set_players(bool bot_vs_human, typePlayer pl1, typePlayer pl2)
{   // affecte les joueurs
    if (bot_vs_human)
        pl1->robot = false;
}

void play_human(game_tab tab, typePlayer pl, bool *finishMorpion, bool bot_vs_human,bool WithExtensionThird,pos new_position,compSdl component,typePlayer pl2,typePile p) {
    if (getTokenSign(getTokenTab(tab,new_position.posX,new_position.posY))=='_')
    {
        poseTokenOnGameTab(tab, new_position, getPlayerSign(pl),p);
        calc_value(tab, pl, new_position);
    }
    else
        return;

    if (WithExtensionThird==true)
    {
        print_tab_V2(tab, X, Y);

        if (thefinishquintuplet(tab, new_position, getPlayerSign(pl),WithExtensionThird))
        {
            //pl->countNbQuintuplet += 1;
            setCountQuintupletInc(pl);
            printf("nb quintuplet pour le player %c :%d \n", getPlayerSign(pl), getCountQuintuplet(pl));
            sleep(2);
        }

        if (isFinishGame(pl,pl2,tab) && WithExtensionThird)
        {
            //*finishMorpion = true;
            setFinishMorpion(finishMorpion,true);
        }

        if (getFinishMorpion(finishMorpion) && WithExtensionThird)
        {
            affichenbquintuplet(pl, pl2);
            sleep(10);
        }

    }else
    {
        print_tab_V2(tab, X, Y);

        if (thefinishquintuplet(tab, new_position, getPlayerSign(pl),WithExtensionThird))
        {
            printf("le joueur %c a gagne \n",getPlayerSign(pl));
            //*finishMorpion = true;
            setFinishMorpion(finishMorpion,true);
        }
    }
    reactualizeNbQuintupletPossible(tab, pl);
}

void play_bot(game_tab tab,typePlayer pl, bool *finishMorpion, bool bot_vs_human,bool WithExtensionThird, compSdl component,typePlayer pl2,typePile p) {
    pos played_position = bestPosition(tab, pl);
    poseTokenOnGameTab(tab, played_position, getPlayerSign(pl),p);// on pose le signe du joueur sur la case à la position jouée...

    printf("la position en x %d \n", played_position.posX);
    printf("la position en y %d \n", played_position.posY);
    calc_value(tab, pl, played_position); // on remet à jour les cases autour de la case jouée par le bot...


    if (WithExtensionThird==true)
    {
        //Ici on joue bien avec l'extension 3...
        print_tab_V2(tab,X,Y);

        if (thefinishquintuplet(tab, played_position, getPlayerSign(pl),WithExtensionThird))
        {
            // si formation de quintuplet alors j'augmente le nombre de quintuplet de 1

            //pl->countNbQuintuplet += 1;
            setCountQuintupletInc(pl);
            printf("nb quintuplet pour le player %c :%d \n",getPlayerSign(pl),getCountQuintuplet(pl));
            sleep(2);
        }

        if (isFinishGame(pl,pl2,tab) && WithExtensionThird)
        {
            //*finishMorpion = true;
            setFinishMorpion(finishMorpion,true);
        }

        if (getFinishMorpion(finishMorpion) && WithExtensionThird)
        {
            affichenbquintuplet(pl, pl2);
            sleep(2);
        }

    }
    else // je vérifie si le joueur qui vient de jouer à former un quintuplet... dans ce cas-ci, on joue pas avec l'extension 3...
    {
        print_tab_V2(tab,X,Y);

        //affichage SDL

        if(thefinishquintuplet(tab, played_position, getPlayerSign(pl),WithExtensionThird))
        {
            printf("le joueur %c a gagne \n",getPlayerSign(pl));
            *finishMorpion = true;
        }
    }
    reactualizeNbQuintupletPossible(tab, pl); // ici je réactualise le nbre de quintuplets pour chaque joueur...
}

// Fonction qui permet de jouer une partie
void play(game_tab tab,typePlayer pl1, typePlayer pl2, int* tourJeu, bool bot_vs_human, bool *finishMorpion, bool WithExtensionThird,pos new_position, compSdl component,typePile p)
{
    //en fonction de la valuer de tourJeu, un joueur jouera... si pair alors le bot sinon l'humain...

    if (*tourJeu % 2 == 0)//quand c'est égal c'est le X qui sinon le O ...
    {
        if (!(pl1->robot))
            play_human(tab, pl1, finishMorpion, bot_vs_human, WithExtensionThird,new_position,component,pl2,p);
        else
        {
            play_bot(tab, pl1, finishMorpion, bot_vs_human, WithExtensionThird,component,pl2,p);
        }
    }
    else
        {
            play_bot(tab, pl2, finishMorpion, bot_vs_human, WithExtensionThird,component,pl1,p);
        }
    //Ici, je vérifie s'il y a possiblité d'arrêter le jeu et si on joue avec l'extension 3...
    if (isFinishGame(pl1,pl2,tab) && WithExtensionThird)
    {
        setFinishMorpion(finishMorpion,true);
    }

    //Ici, je vérifie si le jeu est terminé et si on joue avec l'extension 3...
    //Car en fonction de la réponse, l'afficahge change...

    if (getFinishMorpion(finishMorpion) && WithExtensionThird)
    {
        affichenbquintuplet(pl1, pl2);
        sleep(4);
    }
}

bool aboutthirdextension()//fonction qui permet de savoir si l'utilisateur veut jouer avec l'extension 3
{
    char answer;
    do{
        if (answer=='o' || answer=='n')
            break;

        printf("Voulez-vous jouer avec l'extension 3 ? (o/n) \n");
        scanf("%c",&answer);
    }while(answer!='o' || answer!='n');

    return (answer=='o')?true:false;
}

bool aboutsixExtension()//fonction qui permet de savoir si l'utilisateur veut jouer avec l'extension 3
{
    char answer;
    do{
        if (answer=='o' || answer=='n')
            break;

        printf("Voulez-vous jouer avec l'extension 6 ? (o/n) \n");
        scanf("%c",&answer);
    }while(answer!='o' || answer!='n');

    return (answer=='o')?true:false;
}

void affichenbquintuplet(typePlayer pl1, typePlayer pl2) // fonction d'affichage (dans la console) lorsque le jeu est fini...
{
    printf("the player with the %c has %d quintuplets and %d possible quintuplets\n",getPlayerSign(pl1),getCountQuintuplet(pl1), getCountQuintupletPossible(pl1));
    printf("And the player with the %c has %d quintuplets and %d possible quintuplets\n",getPlayerSign(pl2),getCountQuintuplet(pl2),getCountQuintupletPossible(pl2));

    if (getCountQuintuplet(pl1) > (getCountQuintupletPossible(pl2)+getCountQuintuplet(pl2)))
    {
        printf("The player with the %c has won the game\n",getPlayerSign(pl1));
    }
    else if (getCountQuintuplet(pl2) > (getCountQuintupletPossible(pl1) + getCountQuintuplet(pl1)))
    {
        printf("The player with the %c has won the game\n",getPlayerSign(pl2));
    }
    else
    {
        printf("The game is a draw\n");
    }
    sleep(4);
}

bool everyCaseFilled(game_tab tab) // Fonction qui permet d'arrêter le jeu lorque toutes les cases sont remplies...
{
    bool result = true;
    for(int i=0;i<X;i++)
    {
        for(int j=0;j<Y;j++)
        {
            if (getTokenSign(getTokenTab(tab,i,j))=='_')
            {
                result=result && false;
            }

        }
    }
    printf("rentre dans everyCaseFilled \n");
    return result;
}

int countQuintupletPossibleVertical(game_tab tab,char sign,pos thePosition)
{
    int x = thePosition.posX, y= thePosition.posY,count=0;
    int resTrue = 0, resFalse = 0;

    int res = 0;

    for(int i = y-4;i<=y+4;i++)
    {
        if (valid_coord(x, i))
        {
            if (getCountOne(getTokenTab(tab,x,i)) == false || getCountTwo(getTokenTab(tab,x,i)) == false)
            {
                if (getTokenSign(getTokenTab(tab,x,i)) == sign)
                {
                    count += 1;
                    if (getCountOne(getTokenTab(tab,x,i)) == true && getCountTwo(getTokenTab(tab,x,i)) == false)
                    {
                        resTrue += 1;
                    } else if (getCountOne(getTokenTab(tab,x,i)) == false && getCountTwo(getTokenTab(tab,x,i)) == false)
                    {
                        resFalse += 1;
                    }
                }
                if (getTokenSign(getTokenTab(tab,x,i)) == '_')
                {
                    count += 1;
                    resFalse +=1;
                }

                if (getTokenSign(getTokenTab(tab,x,i)) != sign && getTokenSign(getTokenTab(tab,x,i)) != '_')
                {
                    count = 0;
                    resFalse = 0;
                    resTrue = 0;
                }
            }
        }
        if (count==5)
            break;
    }

    if (count==5)
    {
        if ((resFalse == 5 && resTrue == 0) || (resFalse == 4 && resTrue == 1))
            res = 1;
        else
            res = 0;
    }
    return res;
}

int countQuintupletPossibleHorizontal(game_tab tab,char sign,pos thePosition)
{

    int x = thePosition.posX, y= thePosition.posY,count=0;
    int resTrue = 0, resFalse = 0;

    int res = 0;

    for(int i = x-4;i<=x+4;i++)
    {
        if (valid_coord(i, y))
        {
            if (getCountOne(getTokenTab(tab,i,y)) == false || getCountTwo(getTokenTab(tab,i,y))== false) {
                if (getTokenSign(getTokenTab(tab,i,y)) == sign)
                {
                    count += 1;
                    if (getCountOne(getTokenTab(tab,i,y)) == true && getCountTwo(getTokenTab(tab,i,y)) == false)
                    {
                        resTrue += 1;
                    } else if (getCountOne(getTokenTab(tab,i,y)) == false && getCountTwo(getTokenTab(tab,i,y)) == false)
                    {
                        resFalse += 1;
                    }
                }
                if (getTokenSign(getTokenTab(tab,i,y)) == '_')
                {
                    count += 1;
                    resFalse +=1;
                }

                if (getTokenSign(getTokenTab(tab,i,y)) != sign && getTokenSign(getTokenTab(tab,i,y)) !='_')
                {
                    count = 0;
                    resFalse = 0;
                    resTrue = 0;
                }
            }
        }
        if (count==5)
            break;
    }

    if (count==5)
    {
        if ((resFalse == 5 && resTrue == 0) || (resFalse == 4 && resTrue == 1))
            res = 1;
        else
            res = 0;
    }
    return res;
}

int countQuintupletPossibleHautGauche(game_tab tab,char sign,pos thePosition)
{
    int x = thePosition.posX, y= thePosition.posY,count=0;
    int resTrue = 0, resFalse = 0;

    int res = 0;

    for(int i = x-4;i<=x+4;i++)
    {
        if (valid_coord(i, y))
        {
            if (getCountOne(getTokenTab(tab,i,y)) == false || getCountTwo(getTokenTab(tab,i,y)) == false) {
                if (getTokenSign(getTokenTab(tab,i,y)) == sign)
                {
                    count += 1;
                    if (getCountOne(getTokenTab(tab,i,y)) == true && getCountTwo(getTokenTab(tab,i,y)) == false)
                    {
                        resTrue += 1;
                    } else if (getCountOne(getTokenTab(tab,i,y)) == false && getCountTwo(getTokenTab(tab,i,y)) == false)
                    {
                        resFalse += 1;
                    }
                }
                if (getTokenSign(getTokenTab(tab,i,y)) == '_')
                {
                    count += 1;
                    resFalse +=1;
                }

                if (getTokenSign(getTokenTab(tab,i,y)) != sign && getTokenSign(getTokenTab(tab,i,y))!='_')
                {
                    count = 0;
                    resFalse = 0;
                    resTrue = 0;
                }
            }
        }
        if (count==5)
            break;
        y+=1;
    }

    if (count==5)
    {
        if ((resFalse == 5 && resTrue == 0) || (resFalse == 4 && resTrue == 1))
            res = 1;
        else
            res = 0;
    }
    return res;
}

int countQuintupletPossibleBasGauche(game_tab tab,char sign,pos thePosition)
{
    int x = thePosition.posX, y= thePosition.posY,count=0;
    int resTrue = 0, resFalse = 0;// nbre de case à true / nbre de case à False...

    int res = 0;    // vaut 0 à la fin si quintuplet valide sinon 1...

    for(int i = x-4;i<=x+4;i++)
    {
        if (valid_coord(i, y))
        {
            if (getCountOne(getTokenTab(tab,i,y)) == false || getCountTwo(getTokenTab(tab,i,y)) == false) {
                if (getTokenSign(getTokenTab(tab,i,y)) == sign)
                {
                    count += 1;
                    if (getCountOne(getTokenTab(tab,i,y)) == true && getCountTwo(getTokenTab(tab,i,y)) == false)
                    {
                        resTrue += 1;
                    } else if (getCountOne(getTokenTab(tab,i,y)) == false && getCountTwo(getTokenTab(tab,i,y)) == false)
                    {
                        resFalse += 1;
                    }
                }
                if (getTokenSign(getTokenTab(tab,i,y)) == '_')
                {
                    count += 1;
                    resFalse +=1;
                }

                if (getTokenSign(getTokenTab(tab,i,y)) != sign && getTokenSign(getTokenTab(tab,i,y)) !='_')
                {
                    count = 0;
                    resFalse = 0;
                    resTrue = 0;
                }
            }
        }
        if (count==5)
            break;
        y-=1;
    }

    if (count==5)
    {
        if ((resFalse == 5 && resTrue == 0) || (resFalse == 4 && resTrue == 1))
            res = 1;
        else
            res = 0;
    }
    return res;
}

void reactualizeNbQuintupletPossible(game_tab tab,typePlayer p1) //    fonction qui permet de mettre à jour le nombre de quijntuplets possible des joueurs
{
    //p1->countQuintupletPossible = 0;
    setcountQuintupletPossible(p1,0);
    int verticalvalue=0;
    int horizontalvalue=0;
    int hautgauchevalue=0;
    int basgauchevalue=0;
    for (int i=0;i<X;i++)
    {
        for (int j=0;j<Y;j++)
        {
            pos thePosition;
            thePosition.posX = i;
            thePosition.posY = j;
            verticalvalue += countQuintupletPossibleVertical(tab,getPlayerSign(p1) ,thePosition);//  le nbre de quintuplets possible en vertical...
            horizontalvalue += countQuintupletPossibleHorizontal(tab,getPlayerSign(p1),thePosition);//   le nbre de quintuplets possible en horizontal...
            hautgauchevalue += countQuintupletPossibleHautGauche(tab,getPlayerSign(p1),thePosition);//   le nbre de quintuplets possible en diagonale haut gauche...
            basgauchevalue += countQuintupletPossibleBasGauche(tab,getPlayerSign(p1),thePosition);// le nbre de quintuplets possible en diagonal bas gauche...
        }
    }

    //Ensuite on ajoute la somme de ces quintuplets dans l'attribut countQUintupletPossible du player en question...
    //p1->countQuintupletPossible = ((verticalvalue+(X % 5))/X) + ((horizontalvalue+(X % 5))/X) + hautgauchevalue + basgauchevalue;
    setcountQuintupletPossible(p1,((verticalvalue+(X % 5))/X) + ((horizontalvalue+(X % 5))/X) + hautgauchevalue + basgauchevalue);

    printf("\n the player pl %c has %d quintuplet possible \n",getPlayerSign(p1),getCountQuintupletPossible(p1));
    //sleep(2);
}

bool isFinishGame(typePlayer p1,typePlayer p2,game_tab tab) //    fonction qui arrête le jeu...
{
    bool res = everyCaseFilled(tab);

    if(getCountQuintuplet(p1) > (getCountQuintupletPossible(p2) + getCountQuintuplet(p2)))
        res = true;
    else if(getCountQuintuplet(p2) > (getCountQuintupletPossible(p1) + getCountQuintuplet(p1)))
        res = true;
    else if ((getCountQuintuplet(p1) > 0 && (getCountQuintuplet(p2)==getCountQuintuplet(p1))) && (getCountQuintupletPossible(p1)==0 && getCountQuintupletPossible(p2)==0))
        res = true;
    else if (isHalfCompleted(tab) && (getCountQuintupletPossible(p1)==0) && (getCountQuintupletPossible(p2)==0))
        res=true;

    return res;
}

bool isHalfCompleted(game_tab tab)  //  fonction qui permet de savoir si la moitié de la grille est remplie...
{

    int count = 0,maxHalf = (X*Y)/2;

    for(int i=0;i<X;i++)
    {
        for(int j=0;j<Y;j++)
        {
            if (getFilled(getTokenTab(tab,i,j)))
                count++;
        }
    }
    return (count>=maxHalf) ? true : false;
}
