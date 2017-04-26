# include <stdlib.h>
# include <stdio.h>
# include <err.h>
# include "chessBoard.h"

int main() {
	struct chessBoard *board = initBoard();
	//piecesInPlace(board);
	int test = -1;
	int sf = -1;
	int gameMode = 0;
	while(test != 1){
		printf("choose game mode \ngameMode 1 is accessible\n0 for exit\n\n");
		sf = scanf("%d", &gameMode);
		if (sf == 1){
			if (gameMode == 1 || gameMode == 0)
				test = 1;
			else
				sf = -1;
		}
	}
	printMap(board);
	int player = -1;
	int coords, coorde;
	int endgame = -1;
	int turn;
	sf = -1;
	int pt = -1;
	while (endgame != 1){
		turn = board->turn;
		player = (turn%2) + 1;
		printf("player %d choose your move\n\n",player);
		sf = scanf("%d %d", &coords, &coorde);
		if (sf == 2){
			int mat = coords - 11;
        		int cmat = mat%10;
        		int lmat = (mat - cmat)/10;
			struct piece *piece = board->squareMat[lmat][cmat].isEmpty;
			if (player == piece->color + 1) {
				pt = move(board, coords, coorde);
				if (pt == -1)
					printf("impossible move\n");
				else if (pt == 1)
					endgame = 1;
				else {
					board->turn = turn + 1;
					sf = -1;
					printMap(board);
				}
			}
			else
				printf("impossible move\n");
		}
	}
	deleteBoard(board);
return 0;
}
