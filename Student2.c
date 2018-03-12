#include <stdio.h>
#include <stdlib.h>
#include "Student2.h"
#include <unistd.h>
typedef int bool;
#define true 1
#define false 0
#define PLAYER_ONE 1
#define PLAYER_TWO 2

///* assume that this is player 2, O */


int* getMove2(int board[][SIZE], int *move){
    move[0]=-1;
    move[1]=-1;

    numOfStep2++;
    printf("Step Number: %d\n",numOfStep2);
    do{
        detectFours2(board, move);

        if(move[0]==-1){
            BlockFours2(board, move);
        }
        if(move[0]==-1){
            detectOpponentWinningMove2(board, move);
        }
        if(move[0]==-1){
            BlockThrees2(board, move);
        }
        if(move[0]==-1){
            detectOwnWinningMove2(board, move);
        }
        if(move[0]==-1){
            detectOpenThrees2(board, move);
        }
        if(move[0]==-1){
            buildCrossFours2(board, move);
        }
        printf("Move is %d, %d\n", move[0], move[1]);
        printf("----------------------------------\n");
        //sleep(2);
    }while (checkMove(board, move) == 0);

    return move;
}

int* BlockFours2(int board[][SIZE], int *move){
    printf("I am STUDENT-2 in DEFENCE Blocking Fours------\n");
    int X,Y,X1,Y1,K,counter=0;
    move[0]=-1;
    move[1]=-1;
    for(X=0;X<SIZE;X++){
        for(Y=0;Y<SIZE;Y++){
            if(board[X][Y]==PLAYER_ONE){
               /* Horizontal lines */
                for (K = 0; K <= 4; K++) {
                    X1 = X - K;
                    Y1 = Y;
                    if(X1<0){
                        continue;
                    }
                    if(board[X1][Y1]==PLAYER_TWO && K!=4){
                        counter=0;
                        break;
                    }
                    if(board[X1][Y1]==PLAYER_ONE){
                        counter++;
                    }
                }
                if(counter==4){
                        for (K = 0; K <= 4; K++) {
                        X1 = X - K;
                        Y1 = Y;
                        if(X1<0){
                            continue;
                        }
                        if(board[X1][Y1]==0){
                            move[0]=X1;
                            move[1]=Y1;
                            return move;
                        }
                        if(K==4 && board[X+1][Y]==0){
                            move[0]=X+1;
                            move[1]=Y;
                            return move;
                        }
                    }
                }
                counter=0;

                for (K = 0; K <= 4; K++) {	/* Vertical lines, from down to up */
                    X1 = X;
                    Y1 = Y - K;
                    if(Y1<0){
                        continue;
                    }
                    if(board[X1][Y1]==PLAYER_TWO && K!=4){
                        counter=0;
                        break;
                    }
                    if(board[X1][Y1]==PLAYER_ONE){
                        counter++;
                    }
                }			/* for */
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
                for (K = 0; K <= 4; K++) {	/* Diagonal lines, lower right to upper left */
                    X1 = X + K;
                    Y1 = Y - K;
                    if(X1>=SIZE || Y1<0){
                        continue;
                    }
                    if(board[X1][Y1]==PLAYER_TWO && K!=4){
                        counter=0;
                        break;
                    }
                    if(board[X1][Y1]==PLAYER_ONE){
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
                counter=0;				/* for */

                for (K = 0; K <= 4; K++) {	/* Diagonal lines, lower left to upper right */
                    X1 = X - K;
                    Y1 = Y - K;
                    if(X1<0 || Y1<0){
                        continue;
                    }
                    if(board[X1][Y1]==PLAYER_TWO && K!=4){
                        counter=0;
                        break;
                    }
                    if(board[X1][Y1]==PLAYER_ONE){
                        counter++;
                    }
                }

                if(counter==4){
                    //printf("-----------------------------Counter - %d\n",counter);
                    for (K = 0; K <= 4; K++) {
                        X1 = X - K;
                        Y1 = Y - K;
                        //printf("X1 - %d, Y1 - %d\n", X1,Y1);
                        if(X1<0 || Y1<0){
                            continue;
                        }
                        if(board[X1][Y1]==0){
                            //printf("X1 - %d, Y1 - %d\n", X1,Y1);
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

int* BlockThrees2(int board[][SIZE], int *move){
    printf("I am STUDENT-2 in DEFENCE Blocking Threes------\n");
    int X,Y,X1,Y1,K,counter=0;
    move[0]=-1;
    move[1]=-1;
    bool horiThree=false, vertThree=false, diaLlUrThree=false, diaLrUlThree=false;
    for(X=0;X<SIZE;X++){
        for(Y=0;Y<SIZE;Y++){
            //printf("X - %d, Y - %d, Player - %d\n", X,Y, board[X][Y]);
            if(board[X][Y]==PLAYER_ONE){
               /* Horizontal lines, from left to right */
                for (K = 0; K <= 4; K++) {
                    X1 = X - K;
                    Y1 = Y;
                    if(X1<0){
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
                    horiThree=true;
                    for (K = 0; K <= 3; K++) {
                        X1 = X - K;
                        Y1 = Y;
                        if(X1<0){
                            continue;
                        }
                        if(board[X1][Y1]==0){
                            move[0]=X1;
                            move[1]=Y1;
                            return move;
                            break;
                        }
                        if(K==3 && board[X+1][Y]==0){
                            move[0]=X+1;
                            move[1]=Y;
                            return move;
                        }
                    }
                }
                counter=0;

                for (K = 0; K <= 4; K++) {	/* Vertical lines, from down to up */
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
                for (K = 0; K <= 4; K++) {	/* Diagonal lines, lower right to upper left */
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
                counter=0;				/* for */

                for (K = 0; K <= 4; K++) {	/* Diagonal lines, lower left to upper right */
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
                    //printf("-----------------------------Counter - %d\n",counter);
                    diaLlUrThree=true;
                    for (K = 0; K <= 3; K++) {
                        X1 = X - K;
                        Y1 = Y - K;
                        //printf("X1 - %d, Y1 - %d\n", X1,Y1);
                        if(X1<0 || Y1<0){
                            continue;
                        }
                        if(board[X1][Y1]==0){
                            //printf("X1 - %d, Y1 - %d\n", X1,Y1);
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

int* buildCrossFours2(int board[][SIZE], int *move){
    int X,Y,K, i=0;
    bool validMove;
    printf("I am STUDENT-2 Building Cross Fours------\n");
    //printf("Random Move is: %d, %d\n", randomMove2[0], randomMove2[1]);
    while(i<30){
        if(randomMove2[0]==-1){//if no valid move exist, generate a random move
            do{
                randomGen(board, randomMove2);
                validMove=true;
            }while((checkMove(board, randomMove2) == 0));// || X<3 || X>11 || Y<3 || Y>11);// check for valid move, and if PLAYER_TWO places before and after "this place" exists
        }
        X=randomMove2[0];
        Y=randomMove2[1];
        //printf("X and Y are %d and %d\n", X,Y);
        for(K=-3;K<=3;K++){//check if the future moves are already used by opponent
            if(board[X+K][Y+K]==PLAYER_ONE){
                validMove=false;
            }
        }
        for(K=-3;K<=3;K++){//check if the future moves are already used by opponent
            if(board[X-K][Y+K]==PLAYER_ONE){
                validMove=false;
            }
        }
        if(validMove==false){//reset the planned moves, go back to generate a new random "move"
            i++;//increase counter
            randomMove2[0]=-1;
            randomMove2[1]=-1;
            continue;
        }
        //----------------------------------------------------------------------
        //start building winning move
        //printf("Building moves - 1\n");
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
        if(board[X][Y]==0){
            move[0]= X;
            move[1]= Y;
            return move;
        }
        //printf("Building moves - 2\n");
        // Winning move is ready
        //-------------------------------------------------
        //--NEXT STEP
        if(board[X-2][Y-2]==PLAYER_ONE || board[X+2][Y+2]==PLAYER_ONE){//check the pattern blocked by opponent, select the pattern which is not blocked
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
        if(board[X+2][Y-2]==PLAYER_ONE || board[X-2][Y+2]==PLAYER_ONE){
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
        randomMove2[0]=-1;
        randomMove2[1]=-1;
        i++;
    }
    //printf("--RANDOM MOVE----");
    do{//Generate some random move
    randomGen(board, randomMove2);
    move[0]=randomMove2[0];
    move[1]=randomMove2[1];
    }while(checkMove(board, move) == 0);
    return move;
}

int* detectOpenThrees2(int board[][SIZE], int *move){
    int X,Y,K,counter=0,X1,Y1;
    printf("I am STUDENT-2 in THREES------\n");
    for(X=0;X<SIZE;X++){
        for(Y=0;Y<SIZE;Y++){
            if(board[X][Y]==PLAYER_TWO){
               /* Horizontal lines, from left to right */
                for (K = -1; K <= 3; K++) {
                    X1 = X - K;
                    Y1 = Y;
                    if(X1<0){
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
                    for (K = -1; K <= 3; K++) {
                        X1 = X - K;
                        Y1 = Y;
                        if(X1<0){
                            if(board[X+2][Y]==0){
                                move[0]=X+2;
                                move[1]=Y;
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

                //----------------------------

                for (K = -1; K <= 3; K++) {
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
                //-----------------------------------------------

                for (K = -1; K <= 3; K++) {
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

                //---------------------------------------------------
                for (K = -1; K <= 3; K++) {
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

int* detectFours2(int board[][SIZE], int *move){
    int X,Y,K,counter=0,X1,Y1;
    move[0]=-1;
    move[1]=-1;
    printf("I am STUDENT-2 in FOURS------\n");
    for(X=0;X<SIZE;X++){
        for(Y=0;Y<SIZE;Y++){
            if(board[X][Y]==PLAYER_TWO){
               /* Horizontal lines, from left to right */
                for (K = 0; K <= 4; K++) {//check if the next 5 places contains FOUR Xs
                    X1 = X - K;
                    Y1 = Y;
                    if(X1<0){//Ignore if X1 is less than index zero
                        continue;
                    }
                    if(board[X1][Y1]==PLAYER_ONE){//reset the counter if Player TWO is present in the next 4 places, ignore if it is in the last one
                        if(K==4){
                            continue;
                        }
                        counter=0;
                        break;
                    }
                    if(board[X1][Y1]==PLAYER_TWO){
                        counter++;
                    }
                }
                if(counter==4){
                    //printf("\n1");
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
                //printf("------1111111------%d, %d", move[0], move[1]);

                //----------------------------

                for (K = 0; K <= 4; K++) {
                    X1 = X;
                    Y1 = Y - K;
                    if(Y1<0){
                        continue;
                    }
                    if(board[X1][Y1]==PLAYER_ONE){
                        if(K==4){
                            continue;
                        }
                        counter=0;
                        break;
                    }
                    if(board[X1][Y1]==PLAYER_TWO){
                        counter++;
                    }
                }
                if(counter==4){
                    //printf("\n2");
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
                //printf("------2222222------%d, %d", move[0], move[1]);
                //-----------------------------------------------

                for (K = 0; K <= 4; K++) {
                    X1 = X + K;
                    Y1 = Y - K;
                    if(X1>=SIZE || Y1<0){
                        continue;
                    }
                    if(board[X1][Y1]==PLAYER_ONE){
                        if(K==4){
                            continue;
                        }
                        counter=0;
                        break;
                    }
                    if(board[X1][Y1]==PLAYER_TWO){
                        counter++;
                    }
                }
                if(counter==4){
                    //printf("\n3");
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
                //printf("------3333333------%d, %d", move[0], move[1]);
                //---------------------------------------------------
                for (K = 0; K <= 4; K++) {
                    X1 = X - K;
                    Y1 = Y - K;
                    if(X1<0 || Y1<0){
                        continue;
                    }
                    if(board[X1][Y1]==PLAYER_ONE){
                        if(K==4){
                            continue;
                        }
                        counter=0;
                        break;
                    }
                    if(board[X1][Y1]==PLAYER_TWO){
                        counter++;
                    }
                }
                if(counter==4){
                    //printf("\n4");
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
                //printf("------4444444------%d, %d", move[0], move[1]);
            }
        }
    }
}

int* randomGen2(int board[][SIZE], int *randomMove2){
    //srand(time(NULL));
    randomMove2[0] = rand()%(11 - 3) + 3;//11 and 3 are the max/min limit of X we want to generate
    randomMove2[1] = rand()%(11 - 3) + 3;//11 and 3 are the max/min limit of Y we want to generate
    return randomMove2;
}

int* detectOpponentWinningMove2(int board[][SIZE], int *move){
    printf("I am STUDENT-2 in DEFENCE - detectWinningMove------\n");
    int X,Y,X1,Y1,K,counter=0;
    move[0]=-1;
    move[1]=-1;
    for(X=0;X<SIZE;X++){
        for(Y=0;Y<SIZE;Y++){
            if(board[X][Y]==0){
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

int* detectOwnWinningMove2(int board[][SIZE], int *move){
    printf("I am STUDENT-2 in OFFENSIVE- detectWinningMove------\n");
    int X,Y,X1,Y1,K,counter=0;
    move[0]=-1;
    move[1]=-1;
    for(X=0;X<SIZE;X++){
        for(Y=0;Y<SIZE;Y++){
            if(board[X][Y]==0){
                /*
                //1st type of winning move, B is the place need to be blocked
                _ _ _ _ _
                _ _ _ _ _
                _ X _ X _
                _ _ B _ _
                _ X _ X _
                _ _ _ _ _

                */
                if(board[X-1][Y-1]==PLAYER_TWO && board[X-1][Y+1]==PLAYER_TWO && board[X+1][Y-1]==PLAYER_TWO && board[X+1][Y+1]==PLAYER_TWO){
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
                //3rd type of winning move, B is the place need to be blocked
                _ _ X _ _
                _ _ X _ _
                _ _ _ _ _
                _ _ B _ _
                _ _ _ X _
                _ _ _ _ X

                */
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


