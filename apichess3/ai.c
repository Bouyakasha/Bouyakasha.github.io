# include <stdio.h>
# include <stdlib.h>
# include "ai.h"
# include "ai_rules.h"
# include "arbitrator.h"
# include "moveRules.h"
# include "pieces.h"
# include "tree_and_values.h"
# include <limits.h>
/*
int min_max_call(struct AIDatas *datas, boolean maxi) {
  return min_max(*datas, H_MM_max, maxi);
}

int min_max(struct AIDatas *datas, int h, boolean maxi) {
  int best_move, value;
  if ((h == 0) || *datas == NULL) {
    // eval call
    return eval(*datas);
  }
  struct AIDatas *child = NULL;
  if (maxi) {
    best_move = INT_MIN;
  // for each child
    for(; ; ) {
      value = min_max(*child, h-1, false);
      best_move = max(best_move, value);
    }
    return best_move;
  } else {
    best_move = INT_MAX;
    // for each child
    for () {
      value = min_max(*child, h-1, true);
      best_move = min(best_move, value);
    }
    return best_move;
  }
}
*/

int eval(struct AIDatas *datas, int color){
  int count = 0;
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++){
      if (datas->AIMat[i][j].color == color)
        count += datas->AIMat[i][j].value;
    }
  }
  return count;
}

int* alpha_beta_call(struct chessBoard *board, struct AIDatas *datas) {
  int *tab;
  tab = alpha_beta_max(board, datas, H_AB_MAX, INT_MIN, INT_MAX);
  return tab;
}

int* alpha_beta_max(struct chessBoard *board, struct AIDatas *datas, int h,
		   int alpha, int beta) {
  int best_score;
  if (h == 0) {
    // eval call
    best_score = eval(datas, 1);
  }
  int *tab = malloc(3*sizeof (int));
  int coords;
  int coorde;
  //struct AIDatas *child = cloneDatas(datas);
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++){
      struct AIDatas *child = NULL;
      if (datas->AIMat[i][j].type == 1 && datas->AIMat[i][j].color == 1){
	coords = ((i*10)+j) + 11;
        for(int k = 0; k < 8; k++){
	  coorde = coords + (board->kingMoves[0][i])*10 +
	  board->kingMoves[1][i];
	  if(aiMoveKing(board, datas, coords, coorde) != 0){
	    child = cloneDatas(datas);
	    aiMove(board, child, coords, coorde);
	  }
        }
      }
      else if (datas->AIMat[i][j].type == 2  && datas->AIMat[i][j].color == 1){
        coords = ((i*10)+j) + 11;
        for(int k = 0; k < 28; k++){
          coorde = coords + (board->rookMoves[0][i])*10 +
	  		board->rookMoves[1][i];
          if(aiMoveRook(board, datas, coords, coorde) != 0){
            child = cloneDatas(datas);
            aiMove(board, child, coords, coorde);
          }
        }
        for(int k = 0; k < 28; k++){
          coorde = coords + (board->bishopMoves[0][i])*10 +
	  		board->bishopMoves[1][i];
          if(aiMoveBishop(board, datas, coords, coorde) != 0){
            child = cloneDatas(datas);
            aiMove(board, child, coords, coorde);
          }
        }
      }
      else if (datas->AIMat[i][j].type == 3 && datas->AIMat[i][j].color == 1){
        coords = ((i*10)+j) + 11;
        for(int k = 0; k < 28; k++){
          coorde = coords + (board->bishopMoves[0][i])*10 +
	  		board->bishopMoves[1][i];
          if(aiMoveBishop(board, datas, coords, coorde) != 0){
            child = cloneDatas(datas);
            aiMove(board, child, coords, coorde);
          }
        }
      }
      else if (datas->AIMat[i][j].type == 4 && datas->AIMat[i][j].color == 1){
        coords = ((i*10)+j) + 11;
        for(int k = 0; k < 8; k++){
          coorde = coords + (board->knightMoves[0][i])*10 +
	  		board->knightMoves[1][i];
          if(aiMoveKnight(board, datas, coords, coorde) != 0){
            child = cloneDatas(datas);
            aiMove(board, child, coords, coorde);
          }
        }
      }
      else if (datas->AIMat[i][j].type == 5 && datas->AIMat[i][j].color == 1){
        coords = ((i*10)+j) + 11;
        for(int k = 0; k < 28; k++){
          coorde = coords + (board->rookMoves[0][i])*10 +
	  		board->rookMoves[1][i];
          if(aiMoveRook(board, datas, coords, coorde) != 0){
            child = cloneDatas(datas);
            aiMove(board, child, coords, coorde);
          }
        }
      }
      else if (datas->AIMat[i][j].type == 6 && datas->AIMat[i][j].color == 1){
        coords = ((i*10)+j) + 11;
        for(int k = 0; k < 28; k++){
          coorde = coords + (board->pawnMoves[0][i])*10 +
	  		board->pawnMoves[1][i];
          if(aiMovePawn(board, datas, coords, coorde) != 0){
            child = cloneDatas(datas);
            aiMove(board, child, coords, coorde);
          }
        }
      }
      
      if(child != NULL){
	tab = alpha_beta_min(board, child, h-1, alpha, beta);
        freeDatas(child);
	  if (best_score >= beta){
            tab[0] = beta;
            tab[1] = coords;
            tab[2] = coorde;
	    printf("coords : %d\n", tab[1]);
	    return tab;
	  }
          if (best_score > alpha)
            alpha = best_score;
	  tab[0] = best_score;
          tab[1] = coords;
          tab[2] = coorde;
      }
    }
  }
  return tab;
}


int* alpha_beta_min(struct chessBoard *board, struct AIDatas *datas, int h,
		   int alpha, int beta) {
  int best_score;
  if (h == 0) {
    // eval call
    best_score = (-1) * eval(datas, 0);
  }
  // for all move
  int *tab = malloc(3*sizeof (int));
  int coords;
  int coorde;
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++){
      struct AIDatas *child = NULL;
      if (datas->AIMat[i][j].type == 1 && datas->AIMat[i][j].color == 0){
        coords = ((i*10)+j) + 11;
        for(int k = 0; k < 8; k++){
          coorde = coords + (board->kingMoves[0][i])*10 +
	  		board->kingMoves[1][i];
          if(aiMoveKing(board, datas, coords, coorde) != 0){
            child = cloneDatas(datas);
            aiMove(board, child, coords, coorde);
          }
        }
      }
      else if (datas->AIMat[i][j].type == 2  && datas->AIMat[i][j].color == 0){
        coords = ((i*10)+j) + 11;
        for(int k = 0; k < 28; k++){
          coorde = coords + (board->rookMoves[0][i])*10 +
	  		board->rookMoves[1][i];
          if(aiMoveRook(board, datas, coords, coorde) != 0){
            child = cloneDatas(datas);
            aiMove(board, child, coords, coorde);
          }
        }
        for(int k = 0; k < 28; k++){
          coorde = coords + (board->bishopMoves[0][i])*10 +
			board->bishopMoves[1][i];
          if(aiMoveBishop(board, datas, coords, coorde) != 0){
            child = cloneDatas(datas);
            aiMove(board, child, coords, coorde);
          }
        }
      }
      else if (datas->AIMat[i][j].type == 3 && datas->AIMat[i][j].color == 0){
        coords = ((i*10)+j) + 11;
        for(int k = 0; k < 28; k++){
          coorde = coords + (board->bishopMoves[0][i])*10 +
			board->bishopMoves[1][i];
          if(aiMoveBishop(board, datas, coords, coorde) != 0){
            child = cloneDatas(datas);
            aiMove(board, child, coords, coorde);
          }
        }
      }
      else if (datas->AIMat[i][j].type == 4 && datas->AIMat[i][j].color == 0){
        coords = ((i*10)+j) + 11;
        for(int k = 0; k < 8; k++){
          coorde = coords + (board->knightMoves[0][i])*10 +
			board->knightMoves[1][i];
          if(aiMoveKnight(board, datas, coords, coorde) != 0){
            child = cloneDatas(datas);
            aiMove(board, child, coords, coorde);
          }
        }
      }
      else if (datas->AIMat[i][j].type == 5 && datas->AIMat[i][j].color == 0){
        coords = ((i*10)+j) + 11;
        for(int k = 0; k < 28; k++){
          coorde = coords + (board->rookMoves[0][i])*10 +
			board->rookMoves[1][i];
          if(aiMoveRook(board, datas, coords, coorde) != 0){
            child = cloneDatas(datas);
            aiMove(board, child, coords, coorde);
          }
        }
      }
      else if (datas->AIMat[i][j].type == 6 && datas->AIMat[i][j].color == 0){
        coords = ((i*10)+j) + 11;
        for(int k = 0; k < 28; k++){
          coorde = coords + (board->pawnMoves[0][i])*10 +
			board->pawnMoves[1][i];
          if(aiMovePawn(board, datas, coords, coorde) != 0){
            child = cloneDatas(datas);
            aiMove(board, child, coords, coorde);
          }
        }
      }
      if(child != NULL){
	tab = alpha_beta_max(board, child, h-1, alpha, beta);
        freeDatas(child);
	if (best_score <= alpha){
          tab[0] = alpha;
          tab[1] = coords;
          tab[2] = coorde;
	  return tab;
 	}
        if (best_score < beta)
          beta = best_score;
	tab[0] = best_score;
        tab[1] = coords;
        tab[2] = coorde;
      }
    }
  }
  return tab;
}
