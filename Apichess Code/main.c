# include <stdlib.h>
# include <stdio.h>
# include <err.h>
# include "chessBoard.h"

int main() {
	struct chessBoard *board = initBoard();
	/*
	for (size_t i = 0; i < 8; i++) {
    		for (size_t j = 0; j < 8; j++) {
			printf("id : %d\n", board->squareMat[i][j].id);
			printf("color : %d\n", board->squareMat[i][j].color);
		}
	}
	printf("king 2 id :  %d\n",board->nextKing->id);
	printf("king 1 id :  %d\n",board->nextKing->next->id);
	struct pawn *p = board->nextPawn;
	printf("pawn id||color : %d||%d\n", p->id, p->color);
	for (int i = 0; i<15; i++){
		p = p->next;
		printf("pawn id||color : %d||%d\n", p->id, p->color);
	}
	*/
	piecesInPlace(board);
	int test = -1; 
	int sf = -1;
	int gameMode = 0;
	while(test != 1){
		printf("choose game mode \ngameMode 1 is accessible\n0 for exit");
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
		printf("player %d choose your move\n",player);
		sf = scanf("%d %d", &coords, &coorde);
		if (sf == 2){
			pt = move(board, coords, coorde);
			// if king is dead //
			if (pt == 1)
				endgame = 1;
			board->turn = turn + 1;
			sf = -1;
			printMap(board);
		}
	}
	/*p = board->nextPawn;
        printf("pawn place : %d\n", p->square);
        for (int i = 0; i<15; i++){
                p = p->next;
                printf("pawn place : %d\n", p->square);
        }
	
	struct king *king = popKing(board, 2, 1);
        printf("poped king id : %d\n", king->id);
        printf("poped king color : %d\n", king->color);
	
	struct bishop *bishop1 = board->squareMat[0][2].isEmpty;
	struct bishop *bishop2 = board->squareMat[0][5].isEmpty;
	struct bishop *bishop3 = board->squareMat[7][2].isEmpty;
	struct bishop *bishop4 = board->squareMat[7][5].isEmpty;
	printf("bishop id and color on [0][2] : %d|%d\n",
	       bishop1->id, bishop1->color);
	printf("bishop id and color on [0][5] : %d|%d\n",
	       bishop2->id, bishop2->color);
	printf("bishop id and color on [7][2] : %d|%d\n",
	        bishop3->id, bishop3->color);
	printf("bishop id and color on [7][5] : %d|%d\n",
	        bishop4->id, bishop4->color);

	//struct king *king2 = board->nextKing;
	//board->squareMat[2][6].isEmpty = king2;

	if (board->squareMat[2][6].isEmpty==NULL)
		printf("ntm\n");
	*/
	/*
	int try = 0;
	if ((try = movePawn(board->nextPawn,
		board->squareMat[2][7])) == 1)
		printf("try : %d -> good move\n", try);
	else
		printf("try : %d -> bad move\n", try);
	
	if ((try = movePawn(board->nextPawn, board->squareMat[3][7])) == 1)
                printf("try pawn : %d -> good move\n", try);
        else
                printf("try pawn : %d -> bad move\n", try);
	*/
	/*
	/////////////////////////////////////////
	//board->nextKing->square = 44;
	if ((try = moveKing(board->nextKing, board->squareMat[3][4])) == 1)
                printf("try king : %d -> good move\n", try);
        else
                printf("try king : %d -> bad move\n", try);
	//////////////////////////////////////////
	//board->nextRook->square = 31;
	if ((try = moveRook(board, board->nextRook,
		board->squareMat[6][0])) == 1)
                printf("try rook : %d -> good move\n", try);
        else
                printf("try rook : %d -> bad move\n", try);
        /////////////////////////////////////////
	//board->nextBishop->square = 33;
	if ((try = moveBishop(board, board->nextBishop,
		board->squareMat[6][6])) == 1)
                printf("try bishop : %d -> good move\n", try);
        else
                printf("try bishop : %d -> bad move\n", try);
	////////////////////////////////////////
	board->nextQueen->square = 33;
        if ((try = moveQueen(board, board->nextQueen,
                board->squareMat[6][2])) == 1)
                printf("try queen : %d -> good move\n", try);
        else
                printf("try queen : %d -> bad move\n", try);
	///////////////////////////////////////
	//board->nextKnight->square = 33;
        if ((try = moveKnight(board->nextKnight,board->squareMat[2][2])) == 1)
                printf("try knight : %d -> good move\n", try);
        else
                printf("try knight : %d -> bad move\n", try);
	///////////////////////////////////////
	*/
	deleteBoard(board);
	//board->squareMat[0][0].id = 0;
return 0;
}
