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

struct AIDatas* createDatas(struct chessBoard *board){
	struct AIDatas *datas = malloc(sizeof (struct AIDatas));
	datas->turn = board->turn;
	datas->pLeftw = 0;
	datas->pLeftb = 0;
	datas->eval = 0;
	datas->AIMat = malloc(8 * sizeof (struct AISquare));
	for (int i = 0; i < 8; i++){
	  datas->AIMat[i] = malloc(8 * sizeof (struct AISquare));
	}
	for (int i = 0; i < 8; i++){
          for(int j = 0; j < 8; j++){
            if (board->squareMat[i][j].isEmpty != NULL){
              struct piece *p = board->squareMat[i][j].isEmpty;
	      if (board->squareMat[i][j].isEmpty->color == 0)
                datas->pLeftw ++;
              else
                datas->pLeftb ++;
              datas->AIMat[i][j].type = p->type;
              datas->AIMat[i][j].color = p->color;
              datas->AIMat[i][j].value = p->value;
	    }
	    else
	      datas->AIMat[i][j].type = -1;
              datas->AIMat[i][j].color = -1;
              datas->AIMat[i][j].value = 0;
           }
        }
	return datas;
}

struct AIDatas* cloneDatas(struct AIDatas *datas){
	struct AIDatas *datas2 = malloc(sizeof (struct AIDatas));
	datas2->AIMat = malloc(8 * sizeof (struct AISquare));
        for (int i = 0; i < 8; i++){
          datas2->AIMat[i] = malloc(8 * sizeof (struct AISquare));
        }
	datas2->turn = datas->turn;
        datas2->pLeftw = datas->pLeftw;
        datas2->pLeftb = datas->pLeftb;
	datas2->eval = 0;
	for (int i = 0; i < 8; i++){
          for(int j = 0; j < 8; j++){
            if (datas->AIMat[i][j].type != -1){
              datas2->AIMat[i][j].type = datas->AIMat[i][j].type;
              datas2->AIMat[i][j].color = datas->AIMat[i][j].color;
              datas2->AIMat[i][j].value = datas->AIMat[i][j].value;
            }
            else
              datas2->AIMat[i][j].type = -1;
              datas2->AIMat[i][j].color = -1;
              datas2->AIMat[i][j].value = 0;
          }
        }
        return datas2;
}

void freeDatas(struct AIDatas *datas){
	for(size_t i = 0; i<8; i++)
                free(datas->AIMat[i]);
        free(datas->AIMat);
	free(datas);
}

int aiTestStraight(struct AIDatas *datas, int coords, int coorde){
	int mat = coords - 11;
        int cmat = mat%10;
        int lmat = (mat-cmat)/10;
        int mat2 = coorde - 11;
        int cmat2 = mat2%10;
        int lmat2 = (mat2 - cmat2)/10;
	if (lmat < lmat2 && cmat == cmat2){
                for (int j = lmat + 1; j<lmat2 ; j++){
                        if (datas->AIMat[j][cmat].type != -1)
                                return 0;
                }
        }
        else if (lmat > lmat2 && cmat == cmat2){
                for (int j = lmat - 1; j>lmat2 ; j -= 1){
                        if (datas->AIMat[j][cmat].type != -1)
                                return 0;
                }
        }
        else if (lmat == lmat2 && cmat > cmat2){
                for (int j = cmat - 1; j>cmat2 ; j--){
                        if (datas->AIMat[lmat][j].type != -1)
                                return 0;
                }
        }
        else if (lmat == lmat2 && cmat < cmat2){
                for (int j = cmat + 1; j<cmat2 ; j++){
                        if (datas->AIMat[lmat][j].type != -1)
                        return 0;
                }
        }
        return 1;
}

int aiTestDiag(struct AIDatas *datas, int coords, int coorde){
	int mat = coords - 11;
        int cmat = mat%10;
        int lmat = (mat-cmat)/10;
        int mat2 = coorde - 11;
        int cmat2 = mat2%10;
        int lmat2 = (mat2 - cmat2)/10;
	if (lmat < lmat2 && cmat < cmat2){
                for (int i = lmat + 1, j = cmat + 1;
                     i < lmat2 && j < cmat2; i++, j++){
                        if (datas->AIMat[i][j].type != -1)
                                return 0;
                }
        }
        else if (lmat < lmat2 && cmat > cmat2){
                for (int i = lmat + 1, j = cmat - 1;
                     i < lmat2 && j > cmat2; i++, j--){
                        if (datas->AIMat[i][j].type != -1)
                                return 0;
                }
        }
        else if (lmat > lmat2 && cmat > cmat2){
                for (int i = lmat - 1, j = cmat - 1;
                     i > lmat2 && j > cmat2; i--, j--){
                        if (datas->AIMat[i][j].type != -1)
                                return 0;
                }
        }
        else if (lmat > lmat2 && cmat < cmat2){
                for (int i = lmat - 1, j = cmat + 1;
                     i > lmat2 && j < cmat2; i--, j++){
                        if (datas->AIMat[i][j].type != -1)
                                return 0;
                }
        }
        return 1;
}

int aiMovePawn(struct chessBoard *board, struct AIDatas *datas,
	       int coords, int coorde){
	int mat = coords - 11;
        int cmat = mat%10;
        int lmat = (mat-cmat)/10;
        int mat2 = coorde - 11;
        int cmat2 = mat2%10;
        int lmat2 = (mat2 - cmat2)/10;
	if (datas->AIMat[lmat][cmat].color == 0){
          if (datas->AIMat[lmat2][cmat2].type != -1){
                for (int i = 2; i < 4; i++){
                        if (lmat + board->pawnMoves[0][i] == lmat2 &&
                        cmat + board->pawnMoves[1][i] == cmat2){
                                if (datas->AIMat[lmat2][cmat2].color != 0)
                                        return 2;
                        }
                }
          }else if (lmat == 1){
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
          if (datas->AIMat[lmat2][cmat2].type != -1){
                for (int i = 6; i < 8; i++){
                        if (lmat + board->pawnMoves[0][i] == lmat2 &&
                        cmat + board->pawnMoves[1][i] == cmat2){
                                if (datas->AIMat[lmat2][cmat2].color != 1)
                                        return 2;
                        }
                }
          }else if (lmat == 6){
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

int aiMoveKing(struct chessBoard *board, struct AIDatas *datas,
	       int coords, int coorde){
	int mat = coords - 11;
        int cmat = mat%10;
        int lmat = (mat-cmat)/10;
        int mat2 = coorde - 11;
        int cmat2 = mat2%10;
        int lmat2 = (mat2 - cmat2)/10;
	for (int i = 0; i < 8; i++){
                if (lmat + board->kingMoves[0][i] == lmat2 &&
                    cmat + board->kingMoves[1][i] == cmat2){
                        if (datas->AIMat[lmat2][cmat2].type != -1){
                                if (datas->AIMat[lmat][cmat].color !=
					datas->AIMat[lmat2][cmat2].color)
                                        return 2;
                        }else
                                return 1;
                }
        }
        return 0;
}

int aiMoveRook(struct chessBoard *board, struct AIDatas *datas,
	       int coords, int coorde){
	int mat = coords - 11;
        int cmat = mat%10;
        int lmat = (mat-cmat)/10;
        int mat2 = coorde - 11;
        int cmat2 = mat2%10;
        int lmat2 = (mat2 - cmat2)/10;
 	for (int i = 0; i < 28; i++){
          if (lmat + board->rookMoves[0][i] == lmat2 &&
              cmat + board->rookMoves[1][i] == cmat2){
            int try;
            if (datas->AIMat[lmat2][cmat2].type != -1){
              if (datas->AIMat[lmat][cmat].color !=
		  datas->AIMat[lmat2][cmat2].color){
                if ((try = aiTestStraight(datas, coords, coorde)) == 1)
                  return 2;
                else{
                  return 0;
                }
              }
            }else if ((try = aiTestStraight(datas, coords, coorde)) == 1)
               return 1;
          }
        }
        //printf("ECHEC DES REGLES MDR\n");
        return 0;
}

int aiMoveBishop(struct chessBoard *board, struct AIDatas *datas,
		 int coords, int coorde){
	int mat = coords - 11;
        int cmat = mat%10;
        int lmat = (mat-cmat)/10;
        int mat2 = coorde - 11;
        int cmat2 = mat2%10;
        int lmat2 = (mat2 - cmat2)/10;
	for (int i = 0; i < 28; i++){
          if (lmat + board->bishopMoves[0][i] == lmat2 &&
              cmat + board->bishopMoves[1][i] == cmat2){
            int try;
            if (datas->AIMat[lmat2][cmat2].type != -1){
              if (datas->AIMat[lmat][cmat].color !=
		  datas->AIMat[lmat2][cmat2].color){
                if ((try = aiTestDiag(datas, coords, coorde)) == 1)
                  return 2;
                else
                  return 0;
              }
            }else if ((try = aiTestDiag(datas, coords, coorde)) == 1)
               return 1;
          }
        }
        return 0;
}

int aiMoveQueen(struct chessBoard *board, struct AIDatas *datas,
		int coords, int coorde){
	int mat = coords - 11;
        int cmat = mat%10;
        int lmat = (mat-cmat)/10;
        int mat2 = coorde - 11;
        int cmat2 = mat2%10;
        int lmat2 = (mat2 - cmat2)/10;
	/// straight ///
	for (int i = 0; i < 28; i++){
          if (lmat + board->rookMoves[0][i] == lmat2 &&
              cmat + board->rookMoves[1][i] == cmat2){
            int try;
            if (datas->AIMat[lmat2][cmat2].type != -1){
              if (datas->AIMat[lmat][cmat].color !=
		  datas->AIMat[lmat2][cmat2].color){
                if ((try = aiTestStraight(datas, coords, coorde)) == 1)
                  return 2;
                else{
                  return 0;
                }
              }
            }else if ((try = aiTestStraight(datas, coords, coorde)) == 1)
               return 1;
          }
        }
	/// diag ///
	for (int i = 0; i < 28; i++){
          if (lmat + board->bishopMoves[0][i] == lmat2 &&
              cmat + board->bishopMoves[1][i] == cmat2){
            int try;
            if (datas->AIMat[lmat2][cmat2].type != -1){
              if (datas->AIMat[lmat][cmat].color !=
		  datas->AIMat[lmat2][cmat2].color){
                if ((try = aiTestDiag(datas, coords, coorde)) == 1)
                  return 2;
                else
                  return 0;
              }
            }else if ((try = aiTestDiag(datas, coords, coorde)) == 1)
               return 1;
          }
        }
	return 0;
}

int aiMoveKnight(struct chessBoard *board, struct AIDatas *datas,
		 int coords, int coorde){
	int mat = coords - 11;
        int cmat = mat%10;
        int lmat = (mat-cmat)/10;
        int mat2 = coorde - 11;
        int cmat2 = mat2%10;
        int lmat2 = (mat2 - cmat2)/10;
	for (int i = 0; i < 8; i++){
          if (lmat + board->knightMoves[0][i] == lmat2 &&
              cmat + board->knightMoves[1][i] == cmat2){
            if (datas->AIMat[lmat2][cmat2].type != -1){
              if (datas->AIMat[lmat][cmat].color !=
		  datas->AIMat[lmat2][cmat2].color)
                  return 2;
              else
                  return 0;
            }else
               return 1;
          }
        }
return 0;
}

int aiTryMove(struct chessBoard *board, struct AIDatas *datas,
	      int coords, int coorde){
	int mat = coords - 11;
        int cmat = mat%10;
        int lmat = (mat-cmat)/10;
	if (datas->AIMat[lmat][cmat].type == 1)
		return aiMoveKing(board, datas, coords, coorde);
	else if (datas->AIMat[lmat][cmat].type == 2)
		return aiMoveQueen(board, datas, coords, coorde);
	else if (datas->AIMat[lmat][cmat].type == 3)
		return aiMoveBishop(board, datas, coords, coorde);
	else if (datas->AIMat[lmat][cmat].type == 4)
		return aiMoveKnight(board, datas, coords, coorde);
	else if (datas->AIMat[lmat][cmat].type == 5)
		return aiMoveRook(board, datas, coords, coorde);
	else if (datas->AIMat[lmat][cmat].type == 6)
		return aiMovePawn(board, datas, coords, coorde);
	return 0;
}

void aiMove(struct chessBoard *board, struct AIDatas *datas,
	   int coords, int coorde){
	int mat = coords - 11;
        int cmat = mat%10;
        int lmat = (mat-cmat)/10;
        int mat2 = coorde - 11;
        int cmat2 = mat2%10;
        int lmat2 = (mat2 - cmat2)/10;
	int try = aiTryMove(board, datas, coords, coorde);
	if (try == 0){
                return;
        }
        else if (try == 1){
          datas->AIMat[lmat2][cmat2].type = datas->AIMat[lmat][cmat].type;
          datas->AIMat[lmat2][cmat2].color = datas->AIMat[lmat][cmat].color;
	  datas->AIMat[lmat2][cmat2].value = datas->AIMat[lmat][cmat].value;
	  datas->AIMat[lmat][cmat].type = -1;
        }
        else if (try == 2){
          datas->AIMat[lmat2][cmat2].type = datas->AIMat[lmat][cmat].type;
          datas->AIMat[lmat2][cmat2].color = datas->AIMat[lmat][cmat].color;
          datas->AIMat[lmat2][cmat2].value = datas->AIMat[lmat][cmat].value;
          datas->AIMat[lmat][cmat].type = -1;
        }
}
