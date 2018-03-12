
#define SIZE 15
// #define ROW_CHAR(x) ((x) + 'a')

int* getMove2(int board[][SIZE], int *move);

static int numOfStep2=0, randomMove2[2]={-1,-1};//Variables used in this function
int* BlockThrees2(int board[][SIZE], int *move);//Detects opponent's Three
int* BlockFours2(int board[][SIZE], int *move);//Detects opponent's Four
int* buildCrossFours2(int board[][SIZE], int *move);//Create winning strategies
int* detectOpenThrees2(int board[][SIZE], int *move);//Detect own Open Threes and converts to fours
int* detectFours2(int board[][SIZE], int *move);//Detect own Open Fours and converts to WIN
int* randomGen2(int board[][SIZE], int *move);//randomly generates X, Y
int* detectOpponentWinningMove2(int board[][SIZE], int *move);//Detects known winning moves in advance and blocks them
int* detectOwnWinningMove2(int board[][SIZE], int *move);//Detects known winning moves in advance and blocks them
