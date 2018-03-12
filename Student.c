/*---------------------------------------------------------------------------------------------------------
DEFENSIVE STRATEGY
1) There are THREE functions for Defensive strategy. BlockThrees, BlockFours and detectOpponentWinningMove.
2) BlockThrees and BlockFours - Tries to identify patterns of Threes and Fours created by opponents and
   take action to prevent them from Winning.
3) detectOpponentWinningMove - This function identifies some "Definitive Winning" moves even before they
   are converted to Threes and takes action to prevent further progress.


OFFENSIVE STRATEGY
1) There are FOUR functions for Offensive strategy. buildCrossFours, detectOpenThrees, detectFours and
   detectOwnWinningMove.
2) buildCrossFours - Strategic function to create a particular pattern for "Definitive Win" if I am can
   successfully create this pattern.
3) detectOpenThrees and detectFours - Tries to identify patterns of Threes and Fours created achieved as a
   result of Offensive and Defensive strategy implementation. If a pattern that could result in WIN.
4) detectOwnWinningMove - This function identifies "Definitive Winning" moves as a result of Offensive
   and Defensive strategies.

-----------------------------------------------------------------------------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>
#include "Student.h"
#include <unistd.h>
typedef int bool;
#define true 1
#define false 0
#define PLAYER_ONE 1
#define PLAYER_TWO 2

///* assume that this is player 1, X */

int* getMove(int board[][SIZE], int *move)
{
    move[0]=-1;//Initialize the variable
    move[1]=-1;

    numOfStep++;//keeps track of number of steps
    if(numOfStep==1){//Initialize at the start to generate random patterns, can be disabled to create same pattern every time
        srand(time(NULL));
    }
    printf("Step Number: %d\n",numOfStep);
    do{
        detectFours(board, move);//detects own pattern of fours and CONVERT to WIN
        if(move[0]==-1){
            BlockFours(board, move);//detects opponents Fours and BLOCKS their WIN
        }
        if(move[0]==-1){
            detectOpponentWinningMove(board, move);//detect a "pattern of Winning Move" opponent is trying to create, BLOCK pro-actively
        }
        if(move[0]==-1){
            BlockThrees(board, move);//detect Open Three of opponent and BLOCK it
        }
        if(move[0]==-1){
            detectOwnWinningMove(board, move);//detect a "pattern of Winning Move" that can be converted to "Definitive WIN"
        }
        if(move[0]==-1){
            detectOpenThrees(board, move);//detect own Open Threes, converts them to Fours
        }
        if(move[0]==-1){
            buildCrossFours(board, move);//If no other move is possible start building a  "pattern of Winning Move"
        }
        printf("Move is %d, %d\n", move[0], move[1]);//the move for this step
        printf("----------------------------------\n");//End-of-Step
    }while (checkMove(board, move) == 0);
    return move;
}


int* detectFours(int board[][SIZE], int *move){//Detect if a pattern of FOUR exist, if TRUE - make it FIVE
    int X,Y,K,counter=0,X1,Y1;
    move[0]=-1;
    move[1]=-1;
    printf("I am STUDENT-1 in FOURS------\n");
    for(X=0;X<SIZE;X++){//For all rows
        for(Y=0;Y<SIZE;Y++){//every column, i.e. every possible move
            if(board[X][Y]==PLAYER_ONE){//if the present "place"
               //Horizontal pattern
                for (K = 0; K <= 4; K++) {//check if the Five-consecutive-places contains FOUR Xs
                    X1 = X - K;
                    Y1 = Y;
                    if(X1<0){//Ignore if X1 is less than index zero
                        continue;
                    }
                    if(board[X1][Y1]==PLAYER_TWO){//reset the counter if Player TWO is present in one of the place, ignore if it is in the last one
                        if(K==4){
                            continue;
                        }
                        counter=0;
                        break;
                    }
                    if(board[X1][Y1]==PLAYER_ONE){//increase the counter every-time a match is found
                        counter++;
                    }
                }
                if(counter==4){//If series of Four is found
                    for (K = -1; K <= 4; K++) {
                        X1 = X - K;
                        Y1 = Y;
                        if(X1<0){
                            continue;
                        }
                        if(board[X1][Y1]==0){//Complete the patter with Winning move by filling the empty place
                            move[0]=X1;
                            move[1]=Y1;
                            return move;
                            break;
                        }
                    }
                }
                counter=0;

                //Vertical pattern, same as above
                for (K = 0; K <= 4; K++) {
                    X1 = X;
                    Y1 = Y - K;
                    if(Y1<0){
                        continue;
                    }
                    if(board[X1][Y1]==PLAYER_TWO){
                        if(K==4){
                            continue;
                        }
                        counter=0;
                        break;
                    }
                    if(board[X1][Y1]==PLAYER_ONE){
                        counter++;
                    }
                }
                if(counter==4){
                    for (K = -1; K <= 4; K++) {
                        X1 = X;
                        Y1 = Y - K;
                        if(Y1<0){
                           continue;
                        }
                        if(board[X1][Y1]==0){
                            move[0]=X1;
                            move[1]=Y1;
                            return move;
                            break;
                        }
                    }
                }
                counter=0;

                //Diagonal Pattern - Lower-right to Upper-left
                for (K = 0; K <= 4; K++) {
                    X1 = X + K;
                    Y1 = Y - K;
                    if(X1>=SIZE || Y1<0){
                        continue;
                    }
                    if(board[X1][Y1]==PLAYER_TWO){
                        if(K==4){
                            continue;
                        }
                        counter=0;
                        break;
                    }
                    if(board[X1][Y1]==PLAYER_ONE){
                        counter++;
                    }
                }
                if(counter==4){
                    for (K = -1; K <= 4; K++) {
                        X1 = X + K;
                        Y1 = Y - K;
                        if(X1>=SIZE || Y1<0){
                            if(Y+1<SIZE && X-1>=0 && board[X-1][Y+1]==0){
                                move[0]=X-1;
                                move[1]=Y+1;
                                return move;
                            }
                            else{
                                break;
                            }
                        }
                        if(board[X1][Y1]==0){
                            move[0]=X1;
                            move[1]=Y1;
                            return move;
                            break;
                        }
                    }
                }
                counter=0;

                //Diagonal Pattern - Upper-right to Lower-left
                for (K = 0; K <= 4; K++) {
                    X1 = X - K;
                    Y1 = Y - K;
                    if(X1<0 || Y1<0){
                        continue;
                    }
                    if(board[X1][Y1]==PLAYER_TWO){
                        if(K==4){
                            continue;
                        }
                        counter=0;
                        break;
                    }
                    if(board[X1][Y1]==PLAYER_ONE){
                        counter++;
                    }
                }
                if(counter==4){
                    for (K = -1; K <= 4; K++) {
                        X1 = X - K;
                        Y1 = Y - K;
                        if(( X1<0 || Y1<0) && (X+1<SIZE && Y+1<SIZE)){
                            if(board[X+1][Y+1]==0){
                                move[0]=X+1;
                                move[1]=Y+1;
                                return move;
                            }
                            else{
                                break;
                            }
                        }
                        if(board[X1][Y1]==0){
                            move[0]=X1;
                            move[1]=Y1;
                            return move;
                            break;
                        }
                    }
                }
                counter=0;
            }
        }
    }
}

int* BlockFours(int board[][SIZE], int *move){//Block Fours made by opponent
    printf("I am STUDENT-1 in DEFENCE Blocking Fours------\n");
    int X,Y,X1,Y1,K,counter=0;
    move[0]=-1;
    move[1]=-1;
    for(X=0;X<SIZE;X++){
        for(Y=0;Y<SIZE;Y++){
            if(board[X][Y]==PLAYER_TWO){

                //Horizontal pattern
                for (K = 0; K <= 4; K++) {
                    X1 = X - K;
                    Y1 = Y;
                    if(X1<0){
                        continue;
                    }
                    if(board[X1][Y1]==PLAYER_ONE && K!=4){//ignore if 'X' is present in between, except in the last place of pattern (when K==4)
                        counter=0;
                        break;
                    }
                    if(board[X1][Y1]==PLAYER_TWO){//increase the counter
                        counter++;
                    }
                }
                if(counter==4){//if Four 'O' found
                        for (K = 0; K <= 4; K++) {
                        X1 = X - K;
                        Y1 = Y;
                        if(X1<0){
                            continue;
                        }
                        if(board[X1][Y1]==0){//Block by putting 'X' in the vacant place
                            move[0]=X1;
                            move[1]=Y1;
                            return move;
                        }
                        if(K==4 && board[X+1][Y]==0){//if NO Vacant place in between, put is before the start of Pattern (Example - [OXXXX-], "-" denotes vacant place)
                            move[0]=X+1;
                            move[1]=Y;
                            return move;
                        }
                    }
                }
                counter=0;

                //Vertical pattern, similar to Horizontal
                for (K = 0; K <= 4; K++) {
                    X1 = X;
                    Y1 = Y - K;
                    if(Y1<0){
                        continue;
                    }
                    if(board[X1][Y1]==PLAYER_ONE && K!=4){
                        counter=0;
                        break;
                    }
                    if(board[X1][Y1]==PLAYER_TWO){
                        counter++;
                    }
                }
                if(counter==4){
                        for (K = 0; K <=4; K++) {
                        X1 = X;
                        Y1 = Y - K;
                        if(Y1<0){
                            continue;
                        }
                        if(board[X1][Y1]==0){
                            move[0]=X1;
                            move[1]=Y1;
                            return move;
                            break;
                        }
                        if(K==4 && board[X][Y+1]==0){
                            move[0]=X;
                            move[1]=Y+1;
                            return move;
                        }
                    }
                }
                counter=0;

                // Diagonal pattern - lower right to upper left, similar to Horizontal
                for (K = 0; K <= 4; K++) {
                    X1 = X + K;
                    Y1 = Y - K;
                    if(X1>=SIZE || Y1<0){
                        continue;
                    }
                    if(board[X1][Y1]==PLAYER_ONE && K!=4){
                        counter=0;
                        break;
                    }
                    if(board[X1][Y1]==PLAYER_TWO){
                        counter++;
                    }
                }
                if(counter==4){
                    for (K = 0; K <= 4; K++) {
                        X1 = X + K;
                        Y1 = Y - K;
                        if(X1>=SIZE || Y1<0){
                            continue;
                        }
                        if(board[X1][Y1]==0){
                            move[0]=X1;
                            move[1]=Y1;
                            return move;
                            break;
                        }
                        if(K==4 && board[X-1][Y+1]==0){
                            move[0]=X-1;
                            move[1]=Y+1;
                            return move;
                        }
                    }
                }
                counter=0;

                //Diagonal pattern - upper right to lower left, similar to Horizontal
                for (K = 0; K <= 4; K++) {
                    X1 = X - K;
                    Y1 = Y - K;
                    if(X1<0 || Y1<0){
                        continue;
                    }
                    if(board[X1][Y1]==PLAYER_ONE && K!=4){
                        counter=0;
                        break;
                    }
                    if(board[X1][Y1]==PLAYER_TWO){
                        counter++;
                    }
                }

                if(counter==4){
                    for (K = 0; K <= 4; K++) {
                        X1 = X - K;
                        Y1 = Y - K;
                        if(X1<0 || Y1<0){
                            continue;
                        }
                        if(board[X1][Y1]==0){
                            move[0]=X1;
                            move[1]=Y1;
                            return move;
                        }
                        if(K==4 && board[X+1][Y+1]==0){
                            move[0]=X+1;
                            move[1]=Y+1;
                            return move;
                        }
                    }
                }
                counter=0;
            }
        }
    }
}

int* detectOpponentWinningMove(int board[][SIZE], int *move){//Detect opponent's "Definitive Winning" strategy at early stage and block it
    printf("I am STUDENT-1 in DEFENCE - detectWinningMove------\n");
    int X,Y,X1,Y1,K,counter=0;
    move[0]=-1;
    move[1]=-1;
    for(X=0;X<SIZE;X++){//For every row of the Board
        for(Y=0;Y<SIZE;Y++){//Every column, place
            if(board[X][Y]==0){//if it is not FILLED by any of the player, denoted by "B" in the pattern examples given later in the function
                /*
                //1st type of winning move, B is the place that need to be blocked, if NOT then will result in DEFINITIVE WIN of Opponent
                _ _ _ _ _
                _ _ _ _ _
                _ O _ O _
                _ _ B _ _
                _ O _ O _
                _ _ _ _ _

                */
                if(board[X-1][Y-1]==PLAYER_TWO && board[X-1][Y+1]==PLAYER_TWO && board[X+1][Y-1]==PLAYER_TWO && board[X+1][Y+1]==PLAYER_TWO){
                    move[0]=X;
                    move[1]=Y;
                    return move;
                }


                /*
                //2nd type of winning move, B is the place that need to be blocked, if NOT then will result in DEFINITIVE WIN of Opponent
                _ _ _ _ _
                _ O _ _ _
                _ _ B _ _
                _ _ O O _
                _ _ O _ _

                */

                //The code covers possible permutations of the pattern
                if(board[X+1][Y-1]==PLAYER_TWO && board[X-1][Y+1]==PLAYER_TWO && board[X-1][Y]==PLAYER_TWO && board[X-2][Y]==PLAYER_TWO){
                    move[0]=X;
                    move[1]=Y;
                    return move;
                }
                if(board[X-1][Y+1]==PLAYER_TWO && board[X+1][Y-1]==PLAYER_TWO && board[X+1][Y]==PLAYER_TWO && board[X+2][Y]==PLAYER_TWO){
                    move[0]=X;
                    move[1]=Y;
                    return move;
                }
                if(board[X+1][Y+1]==PLAYER_TWO && board[X-1][Y-1]==PLAYER_TWO && board[X-1][Y]==PLAYER_TWO && board[X-2][Y]==PLAYER_TWO){
                    move[0]=X;
                    move[1]=Y;
                    return move;
                }
                if(board[X+1][Y+1]==PLAYER_TWO && board[X-1][Y-1]==PLAYER_TWO && board[X+1][Y]==PLAYER_TWO && board[X+2][Y]==PLAYER_TWO){
                    move[0]=X;
                    move[1]=Y;
                    return move;
                }

                //Mirrored on axis (X as Y and Y as X)
                if(board[Y-1][X+1]==PLAYER_TWO && board[Y+1][X-1]==PLAYER_TWO && board[Y][X-1]==PLAYER_TWO && board[Y][X-2]==PLAYER_TWO){
                    move[0]=X;
                    move[1]=Y;
                    return move;
                }
                if(board[Y+1][X-1]==PLAYER_TWO && board[Y-1][X+1]==PLAYER_TWO && board[Y][X+1]==PLAYER_TWO && board[Y][X+2]==PLAYER_TWO){
                    move[0]=X;
                    move[1]=Y;
                    return move;
                }
                if(board[Y+1][X+1]==PLAYER_TWO && board[Y-1][X-1]==PLAYER_TWO && board[Y][X-1]==PLAYER_TWO && board[Y][X-2]==PLAYER_TWO){
                    move[0]=X;
                    move[1]=Y;
                    return move;
                }
                if(board[Y+1][X+1]==PLAYER_TWO && board[Y-1][X-1]==PLAYER_TWO && board[Y][X+1]==PLAYER_TWO && board[Y][X+2]==PLAYER_TWO){
                    move[0]=X;
                    move[1]=Y;
                    return move;
                }
                /*
                //3rd type of winning move, B is the place that need to be blocked, if NOT then will result in DEFINITIVE WIN of Opponent
                _ _ O _ _
                _ _ O _ _
                _ _ _ _ _
                _ _ B _ _
                _ _ _ O _
                _ _ _ _ O

                */

                //The code covers possible permutations of the pattern
                if(board[X+2][Y]==PLAYER_TWO && board[X+3][Y]==PLAYER_TWO && board[X-1][Y+1]==PLAYER_TWO && board[X-2][Y+2]==PLAYER_TWO){
                    move[0]=X;
                    move[1]=Y;
                    return move;
                }
                if(board[X+2][Y]==PLAYER_TWO && board[X+3][Y]==PLAYER_TWO && board[X-1][Y-1]==PLAYER_TWO && board[X-2][Y-2]==PLAYER_TWO){
                    move[0]=X;
                    move[1]=Y;
                    return move;
                }
                if(board[X-2][Y]==PLAYER_TWO && board[X-3][Y]==PLAYER_TWO && board[X+1][Y-1]==PLAYER_TWO && board[X+2][Y-2]==PLAYER_TWO){
                    move[0]=X;
                    move[1]=Y;
                    return move;
                }
                if(board[X-2][Y]==PLAYER_TWO && board[X-3][Y]==PLAYER_TWO && board[X+1][Y+1]==PLAYER_TWO && board[X+2][Y+2]==PLAYER_TWO){
                    move[0]=X;
                    move[1]=Y;
                    return move;
                }
                //Mirrored on axis (X as Y and Y as X)
                if(board[Y][X+2]==PLAYER_TWO && board[Y][X+3]==PLAYER_TWO && board[Y+1][X-1]==PLAYER_TWO && board[Y+2][X-2]==PLAYER_TWO){
                    move[0]=X;
                    move[1]=Y;
                    return move;
                }
                if(board[Y][X+2]==PLAYER_TWO && board[Y][X+3]==PLAYER_TWO && board[Y-1][X-1]==PLAYER_TWO && board[Y-2][X-2]==PLAYER_TWO){
                    move[0]=X;
                    move[1]=Y;
                    return move;
                }
                if(board[Y][X-2]==PLAYER_TWO && board[Y][X-3]==PLAYER_TWO && board[Y-1][X+1]==PLAYER_TWO && board[Y-2][X+2]==PLAYER_TWO){
                    move[0]=X;
                    move[1]=Y;
                    return move;
                }
                if(board[Y][X-2]==PLAYER_TWO && board[Y][X-3]==PLAYER_TWO && board[Y+1][X+1]==PLAYER_TWO && board[Y+2][X+2]==PLAYER_TWO){
                    move[0]=X;
                    move[1]=Y;
                    return move;
                }
            }
        }
    }
}

int* BlockThrees(int board[][SIZE], int *move){//Block the threes made by opponent
    printf("I am STUDENT-1 in DEFENCE Blocking Threes------\n");
    int X,Y,X1,Y1,K,counter=0;
    move[0]=-1;
    move[1]=-1;
    bool horiThree=false, vertThree=false, diaLlUrThree=false, diaLrUlThree=false;
    for(X=0;X<SIZE;X++){
        for(Y=0;Y<SIZE;Y++){//Every place on the board
            if(board[X][Y]==PLAYER_TWO){//If "O" is present
                //Horizontal pattern
                for (K = 0; K <= 4; K++) {
                    X1 = X - K;
                    Y1 = Y;
                    if(X1<0){//Ignore index less than zero
                        continue;
                    }
                    if(board[X1][Y1]==PLAYER_ONE){//Ignore if "X" present in-between as opponent can not convert this to a Win
                        counter=0;
                        break;
                    }
                    if(board[X1][Y1]==PLAYER_TWO){//Increase counter by one for each "O"
                        counter++;
                    }
                }
                if(counter>2){//if three or more "O"s present
                    horiThree=true;
                    for (K = 0; K <= 3; K++) {
                        X1 = X - K;
                        Y1 = Y;
                        if(X1<0){
                            continue;
                        }
                        if(board[X1][Y1]==0){//Block any empty place by putting "X"
                            move[0]=X1;
                            move[1]=Y1;
                            return move;
                            break;
                        }
                        if(K==3 && board[X+1][Y]==0){//If no empty place after the detected "O", check if the before-place is empty and Block by putting "X"
                            move[0]=X+1;
                            move[1]=Y;
                            return move;
                        }
                    }
                }
                counter=0;
                //Vertical Pattern
                for (K = 0; K <= 4; K++) {
                    X1 = X;
                    Y1 = Y - K;
                    if(Y1<0){
                        continue;
                    }
                    if(board[X1][Y1]==PLAYER_ONE){
                        counter=0;
                        break;
                    }
                    if(board[X1][Y1]==PLAYER_TWO){
                        counter++;
                    }
                }			/* for */
                if(counter>2){
                    vertThree=true;
                    for (K = 0; K <=3; K++) {
                        X1 = X;
                        Y1 = Y - K;
                        if(Y1<0){
                            continue;
                        }
                        if(board[X1][Y1]==0){
                            move[0]=X1;
                            move[1]=Y1;
                            return move;
                            break;
                        }
                        if(K==3 && board[X][Y+1]==0){
                            move[0]=X;
                            move[1]=Y+1;
                            return move;
                        }
                    }
                }
                counter=0;
                //Diagonal pattern, lower right to upper left
                for (K = 0; K <= 4; K++) {
                    X1 = X + K;
                    Y1 = Y - K;
                    if(X1>=SIZE || Y1<0){
                        continue;
                    }
                    if(board[X1][Y1]==PLAYER_ONE){
                        counter=0;
                        break;
                    }
                    if(board[X1][Y1]==PLAYER_TWO){
                        counter++;
                    }
                }
                if(counter>2){
                    diaLrUlThree=true;
                    for (K = 0; K <= 3; K++) {
                        X1 = X + K;
                        Y1 = Y - K;
                        if(X1>=SIZE || Y1<0){
                            continue;
                        }
                        if(board[X1][Y1]==0){
                            move[0]=X1;
                            move[1]=Y1;
                            return move;
                            break;
                        }
                        if(K==3 && board[X-1][Y+1]==0){
                            move[0]=X-1;
                            move[1]=Y+1;
                            return move;
                        }
                    }
                }
                counter=0;
                //Diagonal pattern, upper left to lower right
                for (K = 0; K <= 4; K++) {
                    X1 = X - K;
                    Y1 = Y - K;
                    if(X1<0 || Y1<0){
                        continue;
                    }
                    if(board[X1][Y1]==PLAYER_ONE){
                        counter=0;
                        break;
                    }
                    if(board[X1][Y1]==PLAYER_TWO){
                        counter++;
                    }
                }

                if(counter>2){
                    diaLlUrThree=true;
                    for (K = 0; K <= 3; K++) {
                        X1 = X - K;
                        Y1 = Y - K;
                        if(X1<0 || Y1<0){
                            continue;
                        }
                        if(board[X1][Y1]==0){
                            move[0]=X1;
                            move[1]=Y1;
                            return move;
                            break;
                        }
                        if(K==3 && board[X+1][Y+1]==0){
                            move[0]=X+1;
                            move[1]=Y+1;
                            return move;
                        }
                    }
                }
                counter=0;
            }
        }
    }
}

int* detectOwnWinningMove(int board[][SIZE], int *move){//Detect own "Definitive Winning" pattern and try to convert it to Win
    printf("I am STUDENT-1 in OFFENSIVE- detectWinningMove------\n");
    int X,Y,X1,Y1,K,counter=0;
    move[0]=-1;
    move[1]=-1;
    for(X=0;X<SIZE;X++){
        for(Y=0;Y<SIZE;Y++){
            if(board[X][Y]==0){//For every blank place on the board
                /*
                //1st type of winning move, B is the place need to be blocked
                _ _ _ _ _
                _ _ _ _ _
                _ X _ X _
                _ _ B _ _
                _ X _ X _
                _ _ _ _ _

                */
                if(board[X-1][Y-1]==PLAYER_ONE && board[X-1][Y+1]==PLAYER_ONE && board[X+1][Y-1]==PLAYER_ONE && board[X+1][Y+1]==PLAYER_ONE){
                    move[0]=X;
                    move[1]=Y;
                    return move;
                }


                /*
                //2nd type of winning move, B is the place need to be blocked
                _ _ _ _ _
                _ X _ _ _
                _ _ B _ _
                _ _ X X _
                _ _ X _ _

                */

                //code covers all permutations of the pattern
                if(board[X+1][Y-1]==PLAYER_ONE && board[X-1][Y+1]==PLAYER_ONE && board[X-1][Y]==PLAYER_ONE && board[X-2][Y]==PLAYER_ONE){
                    move[0]=X;
                    move[1]=Y;
                    return move;
                }
                if(board[X-1][Y+1]==PLAYER_ONE && board[X+1][Y-1]==PLAYER_ONE && board[X+1][Y]==PLAYER_ONE && board[X+2][Y]==PLAYER_ONE){
                    move[0]=X;
                    move[1]=Y;
                    return move;
                }
                if(board[X+1][Y+1]==PLAYER_ONE && board[X-1][Y-1]==PLAYER_ONE && board[X-1][Y]==PLAYER_ONE && board[X-2][Y]==PLAYER_ONE){
                    move[0]=X;
                    move[1]=Y;
                    return move;
                }
                if(board[X+1][Y+1]==PLAYER_ONE && board[X-1][Y-1]==PLAYER_ONE && board[X+1][Y]==PLAYER_ONE && board[X+2][Y]==PLAYER_ONE){
                    move[0]=X;
                    move[1]=Y;
                    return move;
                }

                //Mirrored on axis (X as Y and Y as X)
                if(board[Y-1][X+1]==PLAYER_ONE && board[Y+1][X-1]==PLAYER_ONE && board[Y][X-1]==PLAYER_ONE && board[Y][X-2]==PLAYER_ONE){
                    move[0]=X;
                    move[1]=Y;
                    return move;
                }
                if(board[Y+1][X-1]==PLAYER_ONE && board[Y-1][X+1]==PLAYER_ONE && board[Y][X+1]==PLAYER_ONE && board[Y][X+2]==PLAYER_ONE){
                    move[0]=X;
                    move[1]=Y;
                    return move;
                }
                if(board[Y+1][X+1]==PLAYER_ONE && board[Y-1][X-1]==PLAYER_ONE && board[Y][X-1]==PLAYER_ONE && board[Y][X-2]==PLAYER_ONE){
                    move[0]=X;
                    move[1]=Y;
                    return move;
                }
                if(board[Y+1][X+1]==PLAYER_ONE && board[Y-1][X-1]==PLAYER_ONE && board[Y][X+1]==PLAYER_ONE && board[Y][X+2]==PLAYER_ONE){
                    move[0]=X;
                    move[1]=Y;
                    return move;
                }
                /*
                //3rd type of winning move, B is the place need to be blocked
                _ _ X _ _
                _ _ X _ _
                _ _ _ _ _
                _ _ B _ _
                _ _ _ X _
                _ _ _ _ X

                */

                //code covers all permutations of the pattern
                if(board[X+2][Y]==PLAYER_ONE && board[X+3][Y]==PLAYER_ONE && board[X-1][Y+1]==PLAYER_ONE && board[X-2][Y+2]==PLAYER_ONE){
                    move[0]=X;
                    move[1]=Y;
                    return move;
                }
                if(board[X+2][Y]==PLAYER_ONE && board[X+3][Y]==PLAYER_ONE && board[X-1][Y-1]==PLAYER_ONE && board[X-2][Y-2]==PLAYER_ONE){
                    move[0]=X;
                    move[1]=Y;
                    return move;
                }
                if(board[X-2][Y]==PLAYER_ONE && board[X-3][Y]==PLAYER_ONE && board[X+1][Y-1]==PLAYER_ONE && board[X+2][Y-2]==PLAYER_ONE){
                    move[0]=X;
                    move[1]=Y;
                    return move;
                }
                if(board[X-2][Y]==PLAYER_ONE && board[X-3][Y]==PLAYER_ONE && board[X+1][Y+1]==PLAYER_ONE && board[X+2][Y+2]==PLAYER_ONE){
                    move[0]=X;
                    move[1]=Y;
                    return move;
                }

                //Mirrored on axis (X as Y and Y as X)
                if(board[Y][X+2]==PLAYER_ONE && board[Y][X+3]==PLAYER_ONE && board[Y+1][X-1]==PLAYER_ONE && board[Y+2][X-2]==PLAYER_ONE){
                    move[0]=X;
                    move[1]=Y;
                    return move;
                }
                if(board[Y][X+2]==PLAYER_ONE && board[Y][X+3]==PLAYER_ONE && board[Y-1][X-1]==PLAYER_ONE && board[Y-2][X-2]==PLAYER_ONE){
                    move[0]=X;
                    move[1]=Y;
                    return move;
                }
                if(board[Y][X-2]==PLAYER_ONE && board[Y][X-3]==PLAYER_ONE && board[Y-1][X+1]==PLAYER_ONE && board[Y-2][X+2]==PLAYER_ONE){
                    move[0]=X;
                    move[1]=Y;
                    return move;
                }
                if(board[Y][X-2]==PLAYER_ONE && board[Y][X-3]==PLAYER_ONE && board[Y+1][X+1]==PLAYER_ONE && board[Y+2][X+2]==PLAYER_ONE){
                    move[0]=X;
                    move[1]=Y;
                    return move;
                }
            }
        }
    }
}

int* detectOpenThrees(int board[][SIZE], int *move){//Detect Own "Open"(that has TWO blank places in the pattern, either on the corners or in between) Threes and convert it to Four
    int X,Y,K,counter=0,X1,Y1;
    printf("I am STUDENT-1 in THREES------\n");
    for(X=0;X<SIZE;X++){
        for(Y=0;Y<SIZE;Y++){
            if(board[X][Y]==PLAYER_ONE){//For every place marked as "X" on the board
                //Horizontal Pattern
                for (K = -1; K <= 3; K++) {
                    X1 = X - K;
                    Y1 = Y;
                    if(X1<0){
                        continue;
                    }
                    if(board[X1][Y1]==PLAYER_TWO){//Ignore if it is already blocked by opponent (has "O" in the pattern)
                        counter=0;
                        break;
                    }
                    if(board[X1][Y1]==PLAYER_ONE){//increase the counter
                        counter++;
                    }
                }
                if(counter>2){//if three or more "X" in the pattern
                    for (K = -1; K <= 3; K++) {
                        X1 = X - K;
                        Y1 = Y;
                        if(X1<0){
                            if(board[X+2][Y]==0){//corner case, when there are NO places on the left side, move to right places
                                move[0]=X+2;
                                move[1]=Y;
                                return move;
                            }
                            else{//if no place on the right, ignore this move
                                break;
                            }
                        }
                        if(board[X1][Y1]==0){//mark empty place as "X"
                            move[0]=X1;
                            move[1]=Y1;
                            return move;
                            break;
                        }
                    }
                }
                counter=0;
                //Vertical pattern
                for (K = -1; K <= 3; K++) {
                    X1 = X;
                    Y1 = Y - K;
                    if(Y1<0){
                        continue;
                    }
                    if(board[X1][Y1]==PLAYER_TWO){
                        counter=0;
                        break;
                    }
                    if(board[X1][Y1]==PLAYER_ONE){
                        counter++;
                    }
                }
                if(counter>2){
                    for (K = -1; K <= 3; K++) {
                        X1 = X;
                        Y1 = Y - K;
                        if(Y1<0){
                            if(board[X][Y+2]==0){
                                move[0]=X;
                                move[1]=Y+2;
                                return move;
                            }
                            else{
                                break;
                            }
                        }
                        if(board[X1][Y1]==0){
                            move[0]=X1;
                            move[1]=Y1;
                            return move;
                            break;
                        }
                    }
                }
                counter=0;
                //Diagonal Pattern, lower right to upper left
                for (K = -1; K <= 3; K++) {
                    X1 = X + K;
                    Y1 = Y - K;
                    if(X1>=SIZE || Y1<0){
                        continue;
                    }
                    if(board[X1][Y1]==PLAYER_TWO){
                        counter=0;
                        break;
                    }
                    if(board[X1][Y1]==PLAYER_ONE){
                        counter++;
                    }
                }
                if(counter>2){
                    for (K = -1; K <= 3; K++) {
                        X1 = X + K;
                        Y1 = Y - K;
                        if((X1>=SIZE && Y+2<SIZE) || (Y1<0 && X-2>-1)){
                            if(board[X-2][Y+2]==0){
                                move[0]=X-2;
                                move[1]=Y+2;
                                return move;
                            }
                            else{
                                break;
                            }
                        }
                        if(board[X1][Y1]==0){
                            move[0]=X1;
                            move[1]=Y1;
                            return move;
                            break;
                        }
                    }
                }
                counter=0;

                //Diagonal Pattern, upper right to lower left
                for (K = -1; K <= 3; K++) {
                    X1 = X - K;
                    Y1 = Y - K;
                    if(X1<0 || Y1<0){
                        continue;
                    }
                    if(board[X1][Y1]==PLAYER_TWO){
                        counter=0;
                        break;
                    }
                    if(board[X1][Y1]==PLAYER_ONE){
                        counter++;
                    }
                }
                if(counter>2){
                    for (K = -1; K <= 3; K++) {
                        X1 = X - K;
                        Y1 = Y - K;
                        if(( X1<0 || Y1<0) && (X+2<SIZE && Y+2<SIZE)){
                            if(board[X+2][Y+2]==0){
                                move[0]=X+2;
                                move[1]=Y+2;
                                return move;
                            }
                            else{
                                break;
                            }
                        }
                        if(board[X1][Y1]==0){
                            move[0]=X1;
                            move[1]=Y1;
                            return move;
                            break;
                        }
                    }
                }
                counter=0;
            }
        }
    }
}

int* buildCrossFours(int board[][SIZE], int *move){//Create "Definitive Win" patterns
    /*
    //DEFINITIVE Winning pattern I am trying to create with this function, B is the place whose row-column are denoted by X-Y.
        _ _ _ _ _
        _ _ _ _ _
        _ X _ X _
        _ _ B _ _
        _ X _ X _
        _ _ _ _ _

    I am first trying to put Four "X" and then Fifth at place denoted by B.
    */

    int X,Y,K, i=0;
    bool validMove;
    printf("I am STUDENT-1 Building Cross Fours------\n");
    while(i<30){//Maximum 30 iterations, to avoid Infinite loop
        if(randomMove[0]==-1){//if no valid move exist, generate a random move
            do{
                randomGen(board, randomMove);
                validMove=true;
            }while((checkMove(board, randomMove) == 0));// check for valid move
        }
        X=randomMove[0];
        Y=randomMove[1];
        for(K=-3;K<=3;K++){//check if the future moves are already used by opponent
            if(board[X+K][Y+K]==PLAYER_TWO){
                validMove=false;
            }
        }
        for(K=-3;K<=3;K++){//check if the future moves are already used by opponent
            if(board[X-K][Y+K]==PLAYER_TWO){
                validMove=false;
            }
        }
        if(validMove==false){//reset the planned moves, go back to generate a new random "move"
            i++;//increase counter
            randomMove[0]=-1;
            randomMove[1]=-1;
            continue;
        }
        //----------------------------------------------------------------------
        //start building winning move by putting Four "X" around place "B"
        if(board[X-1][Y-1]==0){
            move[0]= X-1;
            move[1]= Y-1;
            return move;
        }
        else if(board[X+1][Y-1]==0){
            move[0]= X+1;
            move[1]= Y-1;
            return move;
        }
        else if(board[X-1][Y+1]==0){
            move[0]= X-1;
            move[1]= Y+1;
            return move;
        }
        else if(board[X+1][Y+1]==0){
            move[0]= X+1;
            move[1]= Y+1;
            return move;
        }
        if(board[X][Y]==0){//Block place "B" by putting "X"
            move[0]= X;
            move[1]= Y;
            return move;
        }
        // Winning move is ready
        //-------------------------------------------------
        //--NEXT STEP
        if(board[X-2][Y-2]==PLAYER_TWO || board[X+2][Y+2]==PLAYER_TWO){//check the pattern blocked by opponent, select the pattern which is not blocked
            if (board[X+2][Y-2]==0){
                move[0]= X+2;
                move[1]= Y-2;
                return move;
            }
            else if(board[X-2][Y+2]==0){
                move[0]= X-2;
                move[1]= Y+2;
                return move;
            }
        }
        if(board[X+2][Y-2]==PLAYER_TWO || board[X-2][Y+2]==PLAYER_TWO){
            if (board[X-2][Y-2]==0){
                move[0]= X-2;
                move[1]= Y-2;
                return move;
            }
            else if(board[X+2][Y+2]==0){
                move[0]= X+2;
                move[1]= Y+2;
                return move;
            }
        }
        randomMove[0]=-1;
        randomMove[1]=-1;
        i++;
    }

    //This was the last function in our decision tree, and if there was no other move that was generated, then we generate a random move
    do{//Generate some random move
    randomGen(board, randomMove);
    move[0]=randomMove[0];
    move[1]=randomMove[1];
    }while(checkMove(board, move) == 0);
    return move;
}

int* randomGen(int board[][SIZE], int *randomMove){//Function to generate random move
    randomMove[0] = rand()%(11 - 3) + 3;//11 and 3 are the max/min limit of X we want to generate
    randomMove[1] = rand()%(11 - 3) + 3;//11 and 3 are the max/min limit of Y we want to generate
    return randomMove;
}


