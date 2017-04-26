# include <stdlib.h>
# include <stdio.h>
# include <err.h>
# include "chessBoard.h"

int testStraight(struct chessBoard *board, struct piece *piece,
                 struct square square){
        int tmp = piece->square;
        int tmp2 = square.id;
        int mat = tmp - 11;
        int cmat = mat%10;
        int lmat = (mat-cmat)/10;
        int mat2 = tmp2 - 11;
        int cmat2 = mat2%10;
        int lmat2 = (mat2 - cmat2)/10;
        ///// straight /////
        if (lmat < lmat2 && cmat == cmat2){
                for (int j = lmat + 1; j<lmat2 ; j++){
                        if (board->squareMat[j][cmat].isEmpty != NULL)
                                return 0;
                }
        }
        else if (lmat > lmat2 && cmat == cmat2){
                for (int j = lmat - 1; j>lmat2 ; j -= 1){
                        if (board->squareMat[j][cmat].isEmpty != NULL)
                                return 0;
                }
        }
        else if (lmat == lmat2 && cmat > cmat2){
                for (int j = cmat - 1; j>cmat2 ; j--){
                        if (board->squareMat[lmat][j].isEmpty != NULL)
                                return 0;
                }
        }
        else if (lmat == lmat2 && cmat < cmat2){
                for (int j = cmat + 1; j<cmat2 ; j++){
                        if (board->squareMat[lmat][j].isEmpty != NULL)
                        return 0;
                }
        }
        return 1;
}

int testDiag(struct chessBoard *board, struct piece *piece,
                 struct square square){
        int tmp = piece->square;
        int tmp2 = square.id;
        int mat = tmp - 11;
        int cmat = mat%10;
        int lmat = (mat-cmat)/10;
        int mat2 = tmp2 - 11;
        int cmat2 = mat2%10;
        int lmat2 = (mat2 - cmat2)/10;
        if (lmat < lmat2 && cmat < cmat2){
                for (int i = lmat + 1, j = cmat + 1;
                     i < lmat2 && j < cmat2; i++, j++){
                        if (board->squareMat[i][j].isEmpty != NULL)
                                return 0;
                }
        }
        else if (lmat < lmat2 && cmat > cmat2){
                for (int i = lmat + 1, j = cmat - 1;
                     i < lmat2 && j > cmat2; i++, j--){
                        if (board->squareMat[i][j].isEmpty != NULL)
                                return 0;
                }
        }
        else if (lmat > lmat2 && cmat > cmat2){
                for (int i = lmat - 1, j = cmat - 1;
                     i > lmat2 && j > cmat2; i--, j--){
                        if (board->squareMat[i][j].isEmpty != NULL)
                                return 0;
                }
        }
        else if (lmat > lmat2 && cmat < cmat2){
                for (int i = lmat - 1, j = cmat + 1;
                     i > lmat2 && j < cmat2; i--, j++){
                        if (board->squareMat[i][j].isEmpty != NULL)
                                return 0;
                }
        }
        return 1;
}

int movePawn(struct chessBoard *board, struct piece *piece,
             struct square square){
        int tmp = piece->square;
        int tmp2 = square.id;
        int mat = tmp - 11;
        int cmat = mat%10;
        int lmat = (mat-cmat)/10;
        int mat2 = tmp2 - 11;
        int cmat2 = mat2%10;
        int lmat2 = (mat2 - cmat2)/10;
        if (piece->color == 0){
	  if (square.isEmpty != NULL){
                for (int i = 2; i < 4; i++){
                        if (lmat + board->pawnMoves[0][i] == lmat2 &&
                        cmat + board->pawnMoves[1][i] == cmat2){
                                if (square.isEmpty->color != piece->color)
                                        return 2;
                        }
                }
          }else if (piece->firstMove == 1){
                if (lmat + board->pawnMoves[0][1] == lmat2 &&
                    cmat + board->pawnMoves[1][1] == cmat2){
                        return 1;
                }
		if (lmat + board->pawnMoves[0][0] == lmat2 &&
                    cmat + board->pawnMoves[1][0] == cmat2){
                        return 1;
		}
          }else if (lmat + board->pawnMoves[0][0] == lmat2 &&
                    cmat + board->pawnMoves[1][0] == cmat2){
                        return 1;
          }
	}
	else {
	  if (square.isEmpty != NULL){
                for (int i = 6; i < 8; i++){
                        if (lmat + board->pawnMoves[0][i] == lmat2 &&
                        cmat + board->pawnMoves[1][i] == cmat2){
                                if (square.isEmpty->color != piece->color)
                                        return 2;
                        }
                }
          }else if (piece->firstMove == 1){
                if (lmat + board->pawnMoves[0][5] == lmat2 &&
                    cmat + board->pawnMoves[1][5] == cmat2){
                        return 1;
                }
                if (lmat + board->pawnMoves[0][4] == lmat2 &&
                    cmat + board->pawnMoves[1][4] == cmat2){
                        return 1;
                }
          }else if (lmat + board->pawnMoves[0][4] == lmat2 &&
                    cmat + board->pawnMoves[1][4] == cmat2){
                        return 1;
          }
	}
        return 0;
}

int moveKing(struct chessBoard *board, struct piece *piece,
             struct square square){
        int tmp = piece->square;
        int tmp2 = square.id;
        int mat = tmp - 11;
        int cmat = mat%10;
        int lmat = (mat-cmat)/10;
        int mat2 = tmp2 - 11;
        int cmat2 = mat2%10;
        int lmat2 = (mat2 - cmat2)/10;
        for (int i = 0; i < 8; i++){
                if (lmat + board->pawnMoves[0][i] == lmat2 &&
                    cmat + board->pawnMoves[1][i] == cmat2){
                        if (square.isEmpty != NULL){
                                if (square.isEmpty->color != piece->color)
                                        return 2;
                                else
                                        return 0;
                        }else
                                return 1;
                }
        }
        return 0;
}

int moveRook(struct chessBoard *board, struct piece *piece,
             struct square square){
        int tmp = piece->square;
        int tmp2 = square.id;
        int mat = tmp - 11;
        int cmat = mat%10;
        int lmat = (mat-cmat)/10;
        int mat2 = tmp2 - 11;
        int cmat2 = mat2%10;
        int lmat2 = (mat2 - cmat2)/10;
        for (int i = 0; i < 28; i++){
          if (lmat + board->rookMoves[0][i] == lmat2 &&
              cmat + board->rookMoves[1][i] == cmat2){
	    int try;
            if (square.isEmpty != NULL){
              if (square.isEmpty->color != piece->color){
                if ((try = testStraight(board, piece, square)) == 1)
                  return 2;
                else{
		  return 0;
		}
              }
            }else if ((try = testStraight(board, piece, square)) == 1)
               return 1;
          }
        }
	//printf("ECHEC DES REGLES MDR\n");
        return 0;
}

int moveBishop(struct chessBoard *board, struct piece *piece,
               struct square square){
        int tmp = piece->square;
        int tmp2 = square.id;
        int mat = tmp - 11;
        int cmat = mat%10;
        int lmat = (mat-cmat)/10;
        int mat2 = tmp2 - 11;
        int cmat2 = mat2%10;
        int lmat2 = (mat2 - cmat2)/10;
        for (int i = 0; i < 28; i++){
          if (lmat + board->bishopMoves[0][i] == lmat2 &&
              cmat + board->bishopMoves[1][i] == cmat2){
	    int try;
            if (square.isEmpty != NULL){
              if (square.isEmpty->color != piece->color){
                if ((try = testDiag(board, piece, square)) == 1)
                  return 2;
                else
                  return 0;
              }
            }else if ((try = testDiag(board, piece, square)) == 1)
               return 1;
          }
        }
        return 0;
}

int moveQueen(struct chessBoard *board, struct piece *piece,
              struct square square){
        int tmp = piece->square;
        int tmp2 = square.id;
        int mat = tmp - 11;
        int cmat = mat%10;
        int lmat = (mat-cmat)/10;
        int mat2 = tmp2 - 11;
        int cmat2 = mat2%10;
        int lmat2 = (mat2 - cmat2)/10;
        ///// straight /////
        for (int i = 0; i < 28; i++){
          if (lmat + board->rookMoves[0][i] == lmat2 &&
              cmat + board->rookMoves[1][i] == cmat2){
	    int try;
            if (square.isEmpty != NULL){
              if (square.isEmpty->color != piece->color){
                if ((try = testStraight(board, piece, square)) == 1)
                  return 2;
                else
                  return 0;
              }
            }else if ((try = testStraight(board, piece, square)) == 1)
               return 1;
          }
        }
        ///// diago /////
        for (int i = 0; i < 28; i++){
          if (lmat + board->bishopMoves[0][i] == lmat2 &&
              cmat + board->bishopMoves[1][i] == cmat2){
            int try;
	    if (square.isEmpty != NULL){
              if (square.isEmpty->color != piece->color){
                if ((try = testDiag(board, piece, square)) == 1)
                  return 2;
                else
                  return 0;
              }
            }else if ((try = testDiag(board, piece, square)) == 1)
               return 1;
          }
        }
return 0;
}

int moveKnight(struct chessBoard *board, struct piece *piece, struct square square){
        int tmp = piece->square;
        int tmp2 = square.id;
        int mat = tmp - 11;
        int cmat = mat%10;
        int lmat = (mat-cmat)/10;
        int mat2 = tmp2 - 11;
        int cmat2 = mat2%10;
        int lmat2 = (mat2 - cmat2)/10;
        for (int i = 0; i < 8; i++){
          if (lmat + board->knightMoves[0][i] == lmat2 &&
              cmat + board->knightMoves[1][i] == cmat2){
            if (square.isEmpty != NULL){
              if (square.isEmpty->color != piece->color)
                  return 2;
              else
                  return 0;
            }else
               return 1;
          }
        }
return 0;
}

