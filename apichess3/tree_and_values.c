# include <stdlib.h>
# include <stdio.h>
# include <err.h>
# include "chessBoard.h"
# include "ai.h"
# include "ai_rules.h"
# include "arbitrator.h"
# include "moveRules.h"
# include "pieces.h"
# include "tree_and_values.h"

int getValue(struct chessBoard *board, int color){
	int sum = 0;
	struct piece *piece = board->nextAlivePiece;
	for (;piece; piece = piece->next){
		if (piece->color == color)
			sum += piece->value;
	}
	return sum;
}
int* createNode(struct chessBoard *board){
	int *tab = malloc(2*sizeof(int));
	float max = 0;
	for (struct piece *piece = board->nextAlivePiece;
	     piece; piece = piece->next) {
	  if (piece->type == 1 && piece->color == 1){
	    for (int i = 0; i < 8; i++){
	      int tmp = piece->square;
              int mat = tmp - 11;
              int cmat = mat%10;
              int lmat = (mat-cmat)/10;
	      lmat += board->kingMoves[0][i];
	      cmat += board->kingMoves[1][i];
	      if (lmat < 8 && lmat >= 0 && cmat < 8 && cmat >= 0){
	      struct square end = board->squareMat[lmat][cmat];
	      int r = moveKing(board, piece, end);
	      if (r == 2 &&
	      board->squareMat[lmat][cmat].isEmpty->value >= max) {
	        max = board->squareMat[lmat][cmat].isEmpty->value;
	        *tab = piece->square;
		*(tab+1) = end.id;
	     } else if (r == 1 && max == 0) {
		*tab = piece->square;
                *(tab+1) = end.id;
	     }
	    }
	  }
	}
	else if (piece->type == 2 && piece->color == 1){
	  for (int i = 0; i < 28; i++){
            int tmp = piece->square;
            int mat = tmp - 11;
            int cmat = mat%10;
            int lmat = (mat-cmat)/10;
            lmat += board->rookMoves[0][i];
            cmat += board->rookMoves[1][i];
            if (lmat < 8 && lmat >= 0 && cmat < 8 && cmat >= 0){
              struct square end = board->squareMat[lmat][cmat];
              int r = moveQueen(board, piece, end);
              if (r == 2 &&
              board->squareMat[lmat][cmat].isEmpty->value >= max){
                max = board->squareMat[lmat][cmat].isEmpty->value;
                *tab = piece->square;
                *(tab+1) = end.id;
              } else if (r == 1 && max == 0) {
		*tab = piece->square;
                *(tab+1) = end.id;
              }
	    }
          }
	  for (int i = 0; i < 28; i++){
            int tmp = piece->square;
            int mat = tmp - 11;
            int cmat = mat%10;
            int lmat = (mat-cmat)/10;
            lmat += board->bishopMoves[0][i];
            cmat += board->bishopMoves[1][i];
	    if (lmat < 8 && lmat >= 0 && cmat < 8 && cmat >= 0){
              struct square end = board->squareMat[lmat][cmat];
              int r = moveQueen(board, piece, end);
              if (r == 2 &&
              board->squareMat[lmat][cmat].isEmpty->value >= max) {
                max = board->squareMat[lmat][cmat].isEmpty->value;
                *tab = piece->square;
                *(tab+1) = end.id;
              } else if (r == 1 && max == 0) {
		*tab = piece->square;
                *(tab+1) = end.id;
              }
	    }
          }
	}
		else if (piece->type == 3 && piece->color == 1){
		  for (int i = 0; i < 28; i++){
                    int tmp = piece->square;
                    int mat = tmp - 11;
                    int cmat = mat%10;
                    int lmat = (mat-cmat)/10;
                    lmat += board->bishopMoves[0][i];
                    cmat += board->bishopMoves[1][i];
	  	    if (lmat < 8 && lmat >= 0 && cmat < 8 && cmat >= 0){
                      struct square end = board->squareMat[lmat][cmat];
                      int r = moveBishop(board, piece, end);
                      if (r == 2 &&
                      board->squareMat[lmat][cmat].isEmpty->value >= max) {
                        max = board->squareMat[lmat][cmat].isEmpty->value;
                        *tab = piece->square;
                        *(tab+1) = end.id;
                      } else if (r == 1 && max == 0) {
			*tab = piece->square;
                        *(tab+1) = end.id;
                      }
		    }
                  }
		}
		else if (piece->type == 4 && piece->color == 1){
		  for (int i = 0; i < 8; i++){
                    int tmp = piece->square;
                    int mat = tmp - 11;
                    int cmat = mat%10;
                    int lmat = (mat-cmat)/10;
                    lmat += board->knightMoves[0][i];
                    cmat += board->knightMoves[1][i];
		    if (lmat < 8 && lmat >= 0 && cmat < 8 && cmat >= 0){
                      struct square end = board->squareMat[lmat][cmat];
                      int r = moveKnight(board, piece, end);
                      if (r == 2 &&
                      board->squareMat[lmat][cmat].isEmpty->value >= max) {
                        max = board->squareMat[lmat][cmat].isEmpty->value;
                        *tab = piece->square;
                        *(tab+1) = end.id;
                      } else if (r == 1 && max == 0) {
			*tab = piece->square;
                        *(tab+1) = end.id;
                      }
		    }
                  }
		}
		else if (piece->type == 5 && piece->color == 1){
		  for (int i = 0; i < 28; i++){
                    int tmp = piece->square;
                    int mat = tmp - 11;
                    int cmat = mat%10;
                    int lmat = (mat-cmat)/10;
                    lmat += board->rookMoves[0][i];
                    cmat += board->rookMoves[1][i];
		    if (lmat < 8 && lmat >= 0 && cmat < 8 && cmat >= 0){
                      struct square end = board->squareMat[lmat][cmat];
                      int r = moveRook(board, piece, end);
                      if (r == 2 &&
                      board->squareMat[lmat][cmat].isEmpty->value >= max) {
                        max = board->squareMat[lmat][cmat].isEmpty->value;
                        *tab = piece->square;
                        *(tab+1) = end.id;
                      } else if (r == 1 && max == 0) {
			*tab = piece->square;
                        *(tab+1) = end.id;
                      }
		    }
                  }
		}
		else if (piece->type == 6 && piece->color == 1){
		  for (int i = 0; i < 4; i++){
                    int tmp = piece->square;
                    int mat = tmp - 11;
                    int cmat = mat%10;
                    int lmat = (mat-cmat)/10;
                    lmat += board->pawnMoves[0][i];
                    cmat += board->pawnMoves[1][i];
		    if (lmat < 8 && lmat >= 0 && cmat < 8 && cmat >= 0){
                      struct square end = board->squareMat[lmat][cmat];
                      int r = movePawn(board, piece, end);
                      if (r == 2 &&
                      board->squareMat[lmat][cmat].isEmpty->value >= max) {
                        max = board->squareMat[lmat][cmat].isEmpty->value;
                        *tab = piece->square;
                        *(tab+1) = end.id;
                      } else if (r == 1 && max == 0) {
			*tab = piece->square;
                        *(tab+1) = end.id;
                      }
		    }
                  }
		}
	}
	return tab;
}

