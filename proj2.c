#include <stdio.h>
#include <stdlib.h>
#include "Instructor.h"
#include "Student.h"
#include "Student2.h"

// #define SIZE 15
// #define ROW_CHAR(x) ((x) + 'a')

int main(int argc, char *argv[])
{ int i, k, board[SIZE][SIZE]={0}, move[2] = {-1, -1};
  FILE *moves, *boards;//Files where output of each step is saved
  int steps = 0;

    if (argc != 3) {
        printf("The correct usage is: %s moves boards\n", argv[0]);
        return 0;
    }
    if ((moves = fopen(argv[1], "w")) == NULL) {
        printf("%s is not a valid file.\n", argv[1]);
        return 0;
    }
    if ((boards = fopen(argv[2], "w")) == NULL) {
        printf("%s is not a valid file.\n", argv[2]);
        return 0;
    }

  while(1)
  { steps++;
    getMove(board, move);
    if (checkMove (board, move) == 0) 	// invalid move, declare lose
    { printf("(%d %d) is invalid. Player 1 loses in %d moves.\n", move[0], move[1], steps);
      break;				// need to close files.  return 0;
    }
    board[move[0]][move[1]] = 1;	// 'X'; 	// make the move
    fprintf(moves, "\n%3d: ", steps);
    writeBoards(board, boards, moves, move, 1);

    if (checkWin(board) == 1)		// player 1 wins
    { printf("Player 1 wins in %d moves.\n", steps);
      break;				// need to close files.  return 0;
    }
    if ( steps == 113) 			// full board (SIZE*SIZE/2+1), no win, game tied.
    { printf("Game ties! \n");
      break;                            // need to close files.  return 0;
    }

    getMove2(board, move);
    if (checkMove (board, move) == 0)   // invalid move, declare lose
    { printf("(%d %d) is invalid. Player 2 loses in %d moves.\n", move[0], move[1], steps);
      break;                            // need to close files.  return 0;
    }
    board[move[0]][move[1]] = 2;	// 'O';      // make the move
    writeBoards(board, boards, moves, move, 2);

    if (checkWin(board) == 1)           // player 21 wins
    { printf("Player 2 wins in %d moves.\n", steps);
      break;                            // need to close files.  return 0;
    }

  } // end while(1)

  return 0;
}
