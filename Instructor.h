// #ifndef Instructor
// #define Instructor

#define SIZE 15
#define ROW_CHAR(x) ((x) + 'a')

int checkMove(int board[][SIZE], int move[2]);

void writeBoards(int board[][SIZE], FILE *boards, FILE *moves, int move[2], int player);

int checkWin(int board[][SIZE]);

