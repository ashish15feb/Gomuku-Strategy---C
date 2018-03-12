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
2) detectOpenThrees and detectFours - Tries to identify patterns of Threes and Fours created achieved as a
   result of Offensive and Defensive strategy implementation. If a pattern that could result in WIN.
3) detectOwnWinningMove - This function identifies "Definitive Winning" moves as a result of Offensive
   and Defensive strategies.

-----------------------------------------------------------------------------------------------------------
*/

#define SIZE 15
// #define ROW_CHAR(x) ((x) + 'a')

int* getMove(int board[][SIZE], int *move);

//VARIABLES
static int numOfStep=0, randomMove[2]={-1,-1};//Variables used in this function


//FUNCTIONS

    //Defensive
int* randomGen(int board[][SIZE], int *move);//randomly generates X, Y
int* BlockThrees(int board[][SIZE], int *move);//Detects opponent's Three
int* BlockFours(int board[][SIZE], int *move);//Detects opponent's Four
int* detectOpponentWinningMove(int board[][SIZE], int *move);//Detects known winning moves in advance and blocks them

    //Offensive
int* buildCrossFours(int board[][SIZE], int *move);//Create winning strategies
int* detectOpenThrees(int board[][SIZE], int *move);//Detect own Open Threes and converts to fours
int* detectFours(int board[][SIZE], int *move);//Detect own Open Fours and converts to WIN
int* detectOwnWinningMove(int board[][SIZE], int *move);//Detects known winning moves in advance and blocks them
