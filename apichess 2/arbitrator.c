# include <stdlib.h>
# include <stdio.h>
# include <err.h>
# include "chessBoard.h"

void promotion(struct chessBoard *board, struct piece *piece, int type){
        int tmp = piece->square;
        int mat = tmp - 11;
        int cmat = mat%10;
        int lmat = (mat - cmat)/10;
	piece = popPiece(board, piece, 0);
        struct piece *piece2 = board->nextDeadPiece;
        for (; piece2; piece2 = piece2->next){
                if (piece2->color == piece->color && piece2->type == type){
                        piece->square = 0;
                        piece->isDead = 1;
                        pushPiece(board, piece, 1);
                        board->squareMat[lmat][cmat].isEmpty = popPiece(board, piece2, 1);
                        piece2->isDead = 0;
                        piece2->square = tmp;
			pushPiece(board, piece2, 0);
                        return;
        	}
        }
}

int tryMove(struct chessBoard *board, struct piece *piece,
            struct square end){
	if (piece->type == 1)
                return moveKing(board, piece, end);
        if (piece->type == 2)
                return moveQueen(board, piece, end);
        if (piece->type == 3)
                return moveBishop(board, piece, end);
        if (piece->type == 4)
                return moveKnight(board, piece, end);
        if (piece->type == 5)
                return moveRook(board, piece, end);
        if (piece->type == 6)
                return movePawn(board, piece, end);
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
        //struct square start = board->squareMat[lmat][cmat];
        struct square end = board->squareMat[lmat2][cmat2];
        int try;
        // move piece ij vers xy
	if (board->squareMat[lmat][cmat].isEmpty == NULL){
		return -1;
	}
        struct piece *piece = board->squareMat[lmat][cmat].isEmpty;
        try = tryMove(board, piece, end);
        if (try == 0){
                return -1;
	}
        else if (try == 1){
                board->squareMat[lmat2][cmat2].isEmpty = piece;
                board->squareMat[lmat][cmat].isEmpty = NULL;
                piece->square = coorde;
                return 0;
        }
        else if (try == 2){
                if (board->squareMat[lmat2][cmat2].isEmpty->type == 1)
                        return 1;
		popPiece(board, board->squareMat[lmat2][cmat2].isEmpty, 0);
                pushPiece(board, board->squareMat[lmat2][cmat2].isEmpty, 1);
                board->squareMat[lmat2][cmat2].isEmpty = piece;
                board->squareMat[lmat][cmat].isEmpty = NULL;
                piece->square = coorde;
                return 0;
        }
        return -1;
        // return -1 if impossible, 0 if possible, and 1 if endgame
}


