# include <stdlib.h>
# include <stdio.h>
# include <err.h>
# include "chessBoard.h"

void piecesInPlace(struct chessBoard *board){

	//  PAWN  //
	
	int id = 1; 
	struct piece *p = NULL;
	for (int i = 0; i<8; i++, id++){
		p = createPiece(id, 0, 6, board->squareMat[1][i], 1);
		board->squareMat[1][i].isEmpty = p;
		pushPiece(board, p, 0);
	}
	for (int i = 0; i<8; i++, id++){
        	p = createPiece(id, 1, 6, board->squareMat[6][i], 1);
		board->squareMat[6][i].isEmpty = p;
		pushPiece(board, p, 0);
	}
	
	//  ROOK  //
	p = createPiece(id, 0, 5, board->squareMat[0][0], 5.1);
	board->squareMat[0][0].isEmpty = p;
	pushPiece(board, p, 0);
	id++;
	p = createPiece(id, 0, 5, board->squareMat[0][7], 5.1);
	id++;
	pushPiece(board, p, 0);
	board->squareMat[0][7].isEmpty = p;
	p = createPiece(id, 1, 5, board->squareMat[7][0], 5.1);
	id++;
	pushPiece(board, p, 0);
	board->squareMat[7][0].isEmpty = p;
	p = createPiece(id, 1, 5, board->squareMat[7][7], 5.1);
	id++;
	pushPiece(board, p, 0);
	board->squareMat[7][7].isEmpty = p;
	
	//  BISHOP  //
	p = createPiece(id, 0, 3, board->squareMat[0][2], 3.33);
	id++;
	pushPiece(board, p, 0);
	board->squareMat[0][2].isEmpty = p;
        p = createPiece(id, 0, 3, board->squareMat[0][5], 3.33);
	id++;
	pushPiece(board, p, 0);
	board->squareMat[0][5].isEmpty = p;
        p = createPiece(id, 1, 3, board->squareMat[7][2], 3.33);
	id++;
	pushPiece(board, p, 0);
	board->squareMat[7][2].isEmpty = p;
        p = createPiece(id, 1, 3, board->squareMat[7][5], 3.33);
	id++;
	pushPiece(board, p, 0);
	board->squareMat[7][5].isEmpty = p;
	
	//  KNIGHT  //
	p = createPiece(id, 0, 4, board->squareMat[0][1], 3.2);
        id++;
	pushPiece(board, p, 0);
	board->squareMat[0][1].isEmpty = p;
	p = createPiece(id, 0, 4, board->squareMat[0][6], 3.2);
        id++;
	pushPiece(board, p, 0);
	board->squareMat[0][6].isEmpty = p;
	p = createPiece(id, 1, 4, board->squareMat[7][1], 3.2);
        id++;
	pushPiece(board, p, 0);
	board->squareMat[7][1].isEmpty = p;
	p = createPiece(id, 1, 4, board->squareMat[7][6], 3.2);
	id++;
	pushPiece(board, p, 0);
	board->squareMat[7][6].isEmpty = p;

	//  QUEEN  //
	p = createPiece(id, 0, 2, board->squareMat[0][3], 8.8);
        id++;
	pushPiece(board, p, 0);
	board->squareMat[0][3].isEmpty = p;
	p = createPiece(id, 1, 2, board->squareMat[7][4], 8.8);
	id++;
	pushPiece(board, p, 0);
	board->squareMat[7][4].isEmpty = p;

	//  KING  //
	p = createPiece(id, 0, 1, board->squareMat[0][4], 0);
        id++;
	pushPiece(board, p, 0);
	board->squareMat[0][4].isEmpty = p;
	p = createPiece(id, 1, 1, board->squareMat[7][3], 0);
	board->squareMat[7][3].isEmpty = p;
	pushPiece(board, p, 0);
	//printf("%d", board->squareMat[0][0].isEmpty->type);
	//printf("\n");
}

void fillMovesMat(struct chessBoard *board){
	//  PAWN  //
	board->pawnMoves[0][0] = 1;
        board->pawnMoves[1][0] = 0;
	board->pawnMoves[0][1] = 2;
        board->pawnMoves[1][1] = 0;
	board->pawnMoves[0][2] = 1;
        board->pawnMoves[1][2] = 1;
	board->pawnMoves[0][3] = 1;
        board->pawnMoves[1][3] = -1;

	board->pawnMoves[0][4] = -1;
        board->pawnMoves[1][4] = 0;
        board->pawnMoves[0][5] = -2;
        board->pawnMoves[1][5] = 0;
        board->pawnMoves[0][6] = -1;
        board->pawnMoves[1][6] = -1;
        board->pawnMoves[0][7] = -1;
        board->pawnMoves[1][7] = 1;

	//  KING //
	board->kingMoves[0][0] = 1;
	board->kingMoves[1][0] = 0;
	board->kingMoves[0][1] = 1;
        board->kingMoves[1][1] = 1;
	board->kingMoves[0][2] = 1;
        board->kingMoves[1][2] = -1;
	board->kingMoves[0][3] = 0;
        board->kingMoves[1][3] = 1;
	board->kingMoves[0][4] = 0;
        board->kingMoves[1][4] = -1;
	board->kingMoves[0][5] = -1;
        board->kingMoves[1][5] = 0;
	board->kingMoves[0][6] = -1;
        board->kingMoves[1][6] = 1;
	board->kingMoves[0][7] = -1;
        board->kingMoves[1][7] = -1;
	
	//  ROOK  //
	for (int i = 0, cpt = 1; i<7; i++, cpt++){
		board->rookMoves[0][i] = cpt;
	}
	for (int i = 7, cpt = -1; i<14; i++, cpt--){
		board->rookMoves[0][i] = cpt;
        }
	for (int i = 14, cpt = 1; i<21; i++, cpt++){
		board->rookMoves[0][i] = 0;
        }
	for (int i = 21, cpt = -1; i<28; i++, cpt--){
		board->rookMoves[0][i] = 0;
        }
	
	for (int i = 0, cpt = 1; i<7; i++, cpt++){
                board->rookMoves[1][i] = 0;
        }
        for (int i = 7, cpt = -1; i<14; i++, cpt--){
                board->rookMoves[1][i] = 0;
        }
        for (int i = 14, cpt = 1; i<21; i++, cpt++){
                board->rookMoves[1][i] = cpt;
        }
        for (int i = 21, cpt = -1; i<28; i++, cpt--){
                board->rookMoves[1][i] = cpt;
        }

	//  BISHOP  //
	for (int i = 0, cpt = 1; i<7; i++, cpt++){
                board->bishopMoves[0][i] = cpt;
                board->bishopMoves[1][i] = cpt;
        }
        for (int i = 7, cpt = -1; i<14; i++, cpt--){
                board->bishopMoves[0][i] = cpt;
                board->bishopMoves[1][i] = cpt;
        }
        for (int i = 14, cpt = 1; i<21; i++, cpt++){
                board->bishopMoves[0][i] = -cpt;
                board->bishopMoves[1][i] = cpt;
        }
        for (int i = 21, cpt = 1; i<28; i++, cpt++){
                board->bishopMoves[0][i] = cpt;
                board->bishopMoves[1][i] = -cpt;
        }

	//  KNIGHT  //
	board->knightMoves[0][0] = 1;
        board->knightMoves[1][0] = 2;
        board->knightMoves[0][1] = 1;
        board->knightMoves[1][1] = -2;
        board->knightMoves[0][2] = 2;
        board->knightMoves[1][2] = -1;
        board->knightMoves[0][3] = 2;
        board->knightMoves[1][3] = 1;
        board->knightMoves[0][4] = -1;
        board->knightMoves[1][4] = -2;
        board->knightMoves[0][5] = -1;
        board->knightMoves[1][5] = 2;
        board->knightMoves[0][6] = -2;
        board->knightMoves[1][6] = -1;
        board->knightMoves[0][7] = -2;
        board->knightMoves[1][7] = 1;
}

struct chessBoard* initBoard() {
  	struct chessBoard *board = malloc(sizeof (struct chessBoard));
  	board->turn = 0;
	board->end = -1;
	
	// Here we create the matrix board and squares //
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
      			//printf("color : %d\n", board->squareMat[i][j].color);
    		}
  	}
	board->nextDeadPiece = NULL;
	board->nextAlivePiece = NULL;
	// here we create all the matrix related to pieces moves //
		
	board->pawnMoves = malloc(2*sizeof (int*));
	for (size_t i = 0; i < 2; i++) {
		board->pawnMoves[i] = malloc(4*sizeof (int));
	}
	
	board->rookMoves = malloc(2*sizeof (int*));
	for (size_t i = 0; i < 2; i++) {
                board->rookMoves[i] = malloc(28*sizeof (int));
        }

	board->bishopMoves = malloc(2*sizeof (int*));
	for (size_t i = 0; i < 2; i++) {
                board->bishopMoves[i] = malloc(28*sizeof (int));
        }

	board->knightMoves = malloc(2*sizeof (int*));
	for (size_t i = 0; i < 2; i++) {
                board->knightMoves[i] = malloc(8*sizeof (int));
        }

	board->kingMoves = malloc(2*sizeof (int*));
	for (size_t i = 0; i < 2; i++) {
                board->kingMoves[i] = malloc(8*sizeof (int));
        }
	fillMovesMat(board);
	piecesInPlace(board);
  	return board;
}

void deleteBoard(struct chessBoard *board){
	// Here we free all pieces that are still alive //
	for (size_t i = 0; i < 8; i++) {
                for (size_t j = 0; j < 8; j++) {
			if (board->squareMat[i][j].isEmpty != NULL)
				free(board->squareMat[i][j].isEmpty);	
		}
	}
	// Now we free all dead pieces easily thanks to linked list//
	while (board->nextDeadPiece){
		struct piece *piece;
		piece = popPiece(board, board->nextDeadPiece, 1);
		free(piece);
	}
	while (board->nextAlivePiece){
                struct piece *piece;
                piece = popPiece(board, board->nextAlivePiece, 0);
                free(piece);
        }
	// finally we free the squares matrix, and the board //
	for(size_t i = 0; i<8; i++)
                free(board->squareMat[i]);
	free(board->squareMat);
	
	for(size_t i = 0; i<2; i++)
                free(board->pawnMoves[i]);
        free(board->pawnMoves);
	
	for(size_t i = 0; i<2; i++)
                free(board->kingMoves[i]);
        free(board->kingMoves);

	for(size_t i = 0; i<2; i++)
                free(board->knightMoves[i]);
        free(board->knightMoves);

	for(size_t i = 0; i<2; i++)
                free(board->rookMoves[i]);
        free(board->rookMoves);

	for(size_t i = 0; i<2; i++)
                free(board->bishopMoves[i]);
        free(board->bishopMoves);
	
	free(board);
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
				printf("%d", board->squareMat[i][j].isEmpty->type);
			else
				printf(" ");
		}
		printf("\n");
	}
	printf("  --------\n");
	printf("  12345678\n");
}
