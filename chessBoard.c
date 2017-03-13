# include <stdlib.h>
# include <stdio.h>
# include <err.h>
# include "chessBoard.h"


struct chessBoard* initBoard() {
  	struct chessBoard *board = malloc(sizeof (struct chessBoard));
  	board->turn = 0;
	board->end = -1;
  	pushKing(board, 1, 0);
  	pushKing(board, 2, 1);

  	pushQueen(board, 1, 0);
  	pushQueen(board, 2, 1);

  	for(size_t i = 1; i<3; i++) {
    		pushRook(board, i, 0);
    		pushRook(board, i, 1);
  	}

  	for(size_t i = 1; i<3; i++) {
    		pushBishop(board, i, 0);
    		pushBishop(board, i, 1);
  	}

  	for(size_t i = 1; i<3; i++) {
    		pushKnight(board, i, 0);
    		pushKnight(board, i, 1);
  	}

  	for(size_t i = 1; i<9; i++) {
    		pushPawn(board, i, 0);
    		pushPawn(board, i, 1);
  	}


  	board->squareMat = malloc(8*sizeof (struct square));
  	for (size_t i = 0; i < 8; i++) {
    		board->squareMat[i] = malloc(8*sizeof (struct square));
  	}
  	for (size_t i = 0; i < 8; i++) {
    		for (size_t j = 0; j < 8; j++) {
      			board->squareMat[i][j].id = ((i+1)*10)+(j+1);
      			//printf("id : %d\n", board->squareMat[i][j].id);
      			if (i%2 !=0 && j%2 == 0)
        			board->squareMat[i][j].color = 1;
      			else if (i%2 == 0 && j%2 != 0)
        			board->squareMat[i][j].color = 1;
      			else
       				board->squareMat[i][j].color = 0;
			board->squareMat[i][j].isEmpty = NULL;
			board->squareMat[i][j].pieceType = 0;
      			//printf("color : %d\n", board->squareMat[i][j].color);
    		}
  	}

  	return board;
}
void deleteBoard(struct chessBoard *board){
        popKing(board, 1, 0);
        popKing(board, 2, 1);
 	popQueen(board, 1, 0);
        popQueen(board, 2, 1);
	for(size_t i = 1; i<3; i++) {
        	popRook(board, i, 0);
	        popRook(board, i, 1);
        }
	for(size_t i = 1; i<3; i++) {
        	popBishop(board, i, 0);
	        popBishop(board, i, 1);
        }
	for(size_t i = 1; i<3; i++) {
        	popKnight(board, i, 0);
        	popKnight(board, i, 1);
        }
	for(size_t i = 1; i<9; i++) {
        	popPawn(board, i, 0);
	        popPawn(board, i, 1);
        }

	for(size_t i = 0; i<8; i++){
		free(board->squareMat[i]);
	}
	free(board->squareMat);
	free(board);
}
void piecesInPlace(struct chessBoard *board){
	board->nextKing->square = 15;
	board->squareMat[0][4].isEmpty = board->nextKing;
	board->squareMat[0][4].pieceType = 1;
	board->nextKing->next->square = 85;
	board->squareMat[7][4].isEmpty = board->nextKing->next;
	board->squareMat[7][4].pieceType = 1;

	board->nextQueen->square = 14;
	board->squareMat[0][3].isEmpty = board->nextQueen;
	board->squareMat[0][3].pieceType = 2;
        board->nextQueen->next->square = 84;
	board->squareMat[7][3].isEmpty = board->nextQueen->next;
	board->squareMat[7][3].pieceType = 2;

	struct rook *rook = NULL;
	for (int i = 1; i < 5 ; i++) {
		if (rook == NULL){
			rook = board->nextRook;
			rook->square = 11;
			board->squareMat[0][0].isEmpty = rook;
			board->squareMat[0][0].pieceType = 5;
		}
		else {
			if (rook->color == 1){
				rook->square = 18;
				board->squareMat[0][7].isEmpty = rook;
				board->squareMat[0][7].pieceType = 5;
			}
			else if (rook->id == 2){
				rook->square = 81;
				board->squareMat[7][0].isEmpty = rook;
				board->squareMat[7][0].pieceType = 5;
			}
			else {
				rook->square = 88;
				board->squareMat[7][7].isEmpty = rook;
				board->squareMat[7][7].pieceType = 5;
			}
		}
		rook = rook->next;
	}

	struct bishop *bishop = NULL;
        for (int i = 1; i < 5 ; i++) {
                if (bishop == NULL){
                        bishop = board->nextBishop;
                        bishop->square = 13;
			board->squareMat[0][2].isEmpty = bishop;
			board->squareMat[0][2].pieceType = 3;
                }
                else {
                        if (bishop->color == 1){
                                bishop->square = 16;
				board->squareMat[0][5].isEmpty = bishop;
				board->squareMat[0][5].pieceType = 3;
			}
                        else if (bishop->id == 2){
                                bishop->square = 83;
				board->squareMat[7][2].isEmpty = bishop;
				board->squareMat[7][2].pieceType = 3;
			}
                        else {
                                bishop->square = 86;
				board->squareMat[7][5].isEmpty = bishop;
				board->squareMat[7][5].pieceType = 3;
			}
                }
                bishop = bishop->next;
        }

	struct knight *knight = NULL;
        for (int i = 1; i < 5 ; i++) {
                if (knight == NULL){
                        knight = board->nextKnight;
                        knight->square = 12;
			board->squareMat[0][1].isEmpty = knight;
			board->squareMat[0][1].pieceType = 4;
                }
                else {
                        if (knight->color == 1){
                                knight->square = 17;
				board->squareMat[0][6].isEmpty = knight;
				board->squareMat[0][6].pieceType = 4;
			}
                        else if (knight->id == 2){
                                knight->square = 82;
				board->squareMat[7][1].isEmpty = knight;
				board->squareMat[7][1].pieceType = 4;
			}
                        else {
                                knight->square = 87;
				board->squareMat[7][6].isEmpty = knight;
				board->squareMat[7][6].pieceType = 4;
			}
                }
                knight = knight->next;
        }

	struct pawn *pawn = NULL;
	int countw = 8;
	int countb = 8;
        for (int i = 1; i < 17 ; i++) {
                if (pawn == NULL){
                        pawn = board->nextPawn;
                        pawn->square = (2*10) + countb;
			countb --;
			board->squareMat[1][countb].isEmpty = pawn;
			board->squareMat[1][countb].pieceType = 6;
                }
                else {
                        if (pawn->color == 1){
                                pawn->square = (2*10) + countb;
				countb --;
				board->squareMat[1][countb].isEmpty = pawn;
				board->squareMat[1][countb].pieceType = 6;
                        }
			else {
                                pawn->square = (8*10) + countw;
				countw --;
				board->squareMat[6][countw].isEmpty = pawn;
				board->squareMat[6][countw].pieceType = 6;
                	}
		}
                pawn = pawn->next;
        }


}
int getColor(struct square square){
	if (square.pieceType == 1)
		return ((struct king*)square.isEmpty)->color;
	if (square.pieceType == 2)
		return ((struct queen*)square.isEmpty)->color;
	if (square.pieceType == 3)
		return ((struct bishop*)square.isEmpty)->color;
	if (square.pieceType == 4)
		return ((struct knight*)square.isEmpty)->color;
	if (square.pieceType == 5)
		return ((struct rook*)square.isEmpty)->color;
	if (square.pieceType == 6)
		return ((struct pawn*)square.isEmpty)->color;
	return -1;
}

void promotion(struct chessBoard *board, struct pawn* pawn, int type){
	int tmp = pawn->square;
	int mat = tmp - 11;
	int cmat = mat%10;
	int lmat = (mat - cmat)/10;
	if (type == 2){
		struct queen *queen = board->nextQueen;
		for (; queen; queen = queen->next){
			if (queen->color == pawn->color && queen->isDead == 1){
				pawn->square = 0;
				pawn->isDead = 1;
				board->squareMat[lmat][cmat].isEmpty = queen;
				queen->isDead = 0;
				queen->square = tmp;
				return;
			}
		}
	}
	else if (type == 3){
		struct bishop *bishop = board->nextBishop;
                for (; bishop; bishop = bishop->next){
                        if (bishop->color == pawn->color && bishop->isDead == 1){
                                pawn->square = 0;
                                pawn->isDead = 1;
                                board->squareMat[lmat][cmat].isEmpty = bishop;
                                bishop->isDead = 0;
				bishop->square = tmp;
                                return;
                        }
                }
        }
	else if (type == 4){
		struct knight *knight = board->nextKnight;
                for (; knight; knight = knight->next){
                        if (knight->color == pawn->color && knight->isDead == 1){
                                pawn->square = 0;
                                pawn->isDead = 1;
                                board->squareMat[lmat][cmat].isEmpty = knight;
                                knight->isDead = 0;
				knight->square = tmp;
                                return;
                        }
                }
        }
	else if (type == 5){
		struct rook *rook = board->nextRook;
                for (; rook; rook = rook->next){
                        if (rook->color == pawn->color && rook->isDead == 1){
                                pawn->square = 0;
                                pawn->isDead = 1;
                                board->squareMat[lmat][cmat].isEmpty = rook;
                                rook->isDead = 0;
				rook->square = tmp;
                                return;
                        }
                }
        }
}

void printMap(struct chessBoard *board){
	printf("name of pieces by number\n");
	printf(" |1 = king \n");
	printf(" |2 = queen \n");
	printf(" |3 = bishop \n");
	printf(" |4 = knight \n");
	printf(" |5 = rook \n");
	printf(" |6 = pawn \n");
	printf("\n  --------\n");
	for (int i = 0; i<8; i++){
		printf("%d|", i+1);
		for (int j = 0; j<8; j++){
			if (board->squareMat[i][j].isEmpty != NULL)
				printf("%d", board->squareMat[i][j].pieceType);
			else
				printf(" ");
		}
		printf("\n");
	}
	printf("  --------\n");
	printf("  12345678\n");
}
int killPiece(struct square square){
	if (square.pieceType == 1){
		return 1;
	}
	if (square.pieceType == 2){
		struct queen *queen = (struct queen*)square.isEmpty;
		queen->isDead = 1;
	}
	if (square.pieceType == 3){
                struct bishop *bishop = (struct bishop*)square.isEmpty;
                bishop->isDead = 1;
	}
	if (square.pieceType == 4){
                struct knight *knight = (struct knight*)square.isEmpty;
                knight->isDead = 1;
        }
	if (square.pieceType == 5){
                struct rook *rook = (struct rook*)square.isEmpty;
                rook->isDead = 1;
	}
	if (square.pieceType == 6){
                struct pawn *pawn = (struct pawn*)square.isEmpty;
                pawn->isDead = 1;
        }
	return 0;
}
int move(struct chessBoard *board, int coords, int coorde){
	// modulo coords coorde
	int tmp = coords;
        int tmp2 = coorde;
        int mat = tmp - 11;
        int cmat = mat%10;
        int lmat = (mat-cmat)/10;
        int mat2 = tmp2 - 11;
        int cmat2 = mat2%10;
        int lmat2 = (mat2 - cmat2)/10;
	struct square start = board->squareMat[lmat][cmat];
	struct square end = board->squareMat[lmat2][cmat2];
	int try;
	// move piece ij vers xy
	if (start.pieceType == 1){
		struct king *king = (struct king*)start.isEmpty;
		try = moveKing(king, end);
		if (try == 0)
			return -1;
		else if (try == 1){
			board->squareMat[lmat2][cmat2].isEmpty = king;
			board->squareMat[lmat2][cmat2].pieceType = 1;
			board->squareMat[lmat][cmat].isEmpty = NULL;
			board->squareMat[lmat][cmat].pieceType = 0;
			king->square = coorde;
			return 0;
		}
		else if (try == 2){
			if ((try = killPiece(end)) == 1)
				return 1;
			board->squareMat[lmat2][cmat2].isEmpty = king;
                        board->squareMat[lmat2][cmat2].pieceType = 1;
                        board->squareMat[lmat][cmat].isEmpty = NULL;
                        board->squareMat[lmat][cmat].pieceType = 0;
                        king->square = coorde;
                        return 0;
		}
	}
	if (start.pieceType == 2){
                struct queen *queen = (struct queen*)start.isEmpty;
                try = moveQueen(board, queen, end);
		if (try == 0)
                        return -1;
                else if (try == 1){
                        board->squareMat[lmat2][cmat2].isEmpty = queen;
                        board->squareMat[lmat2][cmat2].pieceType = 2;
                        board->squareMat[lmat][cmat].isEmpty = NULL;
                        board->squareMat[lmat][cmat].pieceType = 0;
                        queen->square = coorde;
                        return 0;
                }
                else if (try == 2){
                        if ((try = killPiece(end)) == 1)
                                return 1;
                        board->squareMat[lmat2][cmat2].isEmpty = queen;
                        board->squareMat[lmat2][cmat2].pieceType = 2;
                        board->squareMat[lmat][cmat].isEmpty = NULL;
                        board->squareMat[lmat][cmat].pieceType = 0;
                        queen->square = coorde;
                        return 0;
                }
        }
	if (start.pieceType == 3){
                struct bishop *bishop = (struct bishop*)start.isEmpty;
                try = moveBishop(board, bishop, end);
		if (try == 0)
                        return -1;
                else if (try == 1){
                        board->squareMat[lmat2][cmat2].isEmpty = bishop;
                        board->squareMat[lmat2][cmat2].pieceType = 3;
                        board->squareMat[lmat][cmat].isEmpty = NULL;
                        board->squareMat[lmat][cmat].pieceType = 0;
                        bishop->square = coorde;
                        return 0;
                }
                else if (try == 2){
                        if ((try = killPiece(end)) == 1)
                                return 1;
                        board->squareMat[lmat2][cmat2].isEmpty = bishop;
                        board->squareMat[lmat2][cmat2].pieceType = 3;
                        board->squareMat[lmat][cmat].isEmpty = NULL;
                        board->squareMat[lmat][cmat].pieceType = 0;
                        bishop->square = coorde;
                        return 0;
                }
        }
	if (start.pieceType == 4){
                struct knight *knight = (struct knight*)start.isEmpty;
                try = moveKnight(knight, end);
		if (try == 0)
                        return -1;
                else if (try == 1){
                        board->squareMat[lmat2][cmat2].isEmpty = knight;
                        board->squareMat[lmat2][cmat2].pieceType = 4;
                        board->squareMat[lmat][cmat].isEmpty = NULL;
                        board->squareMat[lmat][cmat].pieceType = 0;
                        knight->square = coorde;
                        return 0;
                }
                else if (try == 2){
                        if ((try = killPiece(end)) == 1)
                                return 1;
                        board->squareMat[lmat2][cmat2].isEmpty = knight;
                        board->squareMat[lmat2][cmat2].pieceType = 4;
                        board->squareMat[lmat][cmat].isEmpty = NULL;
                        board->squareMat[lmat][cmat].pieceType = 0;
                        knight->square = coorde;
                        return 0;
                }
        }
	if (start.pieceType == 5){
                struct rook *rook = (struct rook*)start.isEmpty;
                try = moveRook(board, rook, end);
		if (try == 0)
                        return -1;
                else if (try == 1){
                        board->squareMat[lmat2][cmat2].isEmpty = rook;
                        board->squareMat[lmat2][cmat2].pieceType = 5;
                        board->squareMat[lmat][cmat].isEmpty = NULL;
                        board->squareMat[lmat][cmat].pieceType = 0;
                        rook->square = coorde;
                        return 0;
                }
                else if (try == 2){
                        if ((try = killPiece(end)) == 1)
                                return 1;
                        board->squareMat[lmat2][cmat2].isEmpty = rook;
                        board->squareMat[lmat2][cmat2].pieceType = 5;
                        board->squareMat[lmat][cmat].isEmpty = NULL;
                        board->squareMat[lmat][cmat].pieceType = 0;
                        rook->square = coorde;
                        return 0;
                }
        }
	if (start.pieceType == 6){
                struct pawn *pawn = (struct pawn*)start.isEmpty;
                try = movePawn(pawn, end);
		if (try == 0)
                        return -1;
                else if (try == 1){
                        board->squareMat[lmat2][cmat2].isEmpty = pawn;
                        board->squareMat[lmat2][cmat2].pieceType = 6;
                        board->squareMat[lmat][cmat].isEmpty = NULL;
                        board->squareMat[lmat][cmat].pieceType = 0;
                        pawn->square = coorde;
                        return 0;
                }
                else if (try == 2){
                        if ((try = killPiece(end)) == 1)
                                return 1;
                        board->squareMat[lmat2][cmat2].isEmpty = pawn;
                        board->squareMat[lmat2][cmat2].pieceType = 6;
                        board->squareMat[lmat][cmat].isEmpty = NULL;
                        board->squareMat[lmat][cmat].pieceType = 0;
                        pawn->square = coorde;
                        return 0;
                }
        }
	return -1;
	// return -1 if impossible, 0 if possible, and 1 if endgame
}
