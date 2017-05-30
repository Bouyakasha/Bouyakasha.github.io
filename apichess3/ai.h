#ifndef AI_H_
#define AI_H_

#include "chessBoard.h"

#define MAX_VISIBILITY 2
# define H_MM_MAX 3
# define H_AB_MAX 5

#define max(a,b) \
  ({ __typeof__ (a) _a = (a); \
    __typeof__ (b) _b = (b); \
    _a > _b ? _a : _b; })

#define min(a,b) \
  ({ __typeof__ (a) _a = (a); \
    __typeof__ (b) _b = (b); \
    _a < _b ? _a : _b; })

struct AISquare {
  int type;
  int color;
  int value;
};

/*
struct AIMat {
  struct square **AISquare;
};*/

struct AIDatas {
  int turn;
  int pLeftw;
  int pLeftb;
  int eval;
  struct AISquare **AIMat;
};
int eval(struct AIDatas *datas, int color);
int* alpha_beta_call(struct chessBoard *board, struct AIDatas *datas);
int* alpha_beta_max(struct chessBoard *board, struct AIDatas *datas,
		   int h, int alpha, int beta);
int* alpha_beta_min(struct chessBoard *board, struct AIDatas *datas,
		   int h, int alpha, int beta);

#endif // AI_H_
