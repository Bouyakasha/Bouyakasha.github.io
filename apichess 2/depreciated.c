# include <stdlib.h>
# include <stdio.h>
# include <err.h>

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

