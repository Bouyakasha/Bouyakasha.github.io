#ifndef AI_RULES_H_
#define AI_RULES_H_

/// AI FUNCTIONS ///
void aiMove(struct chessBoard *board, struct AIDatas *data,
	   int coords, int coorde);
int aiTryMove(struct chessBoard *board, struct AIDatas *data,
	      int coords, int coorde);
int aiTestStraight(struct AIDatas *data, int coords, int coorde);
int aiTestDiag(struct AIDatas *data, int coords, int coorde);
int aiMovePawn(struct chessBoard *board, struct AIDatas *data,
		int coords, int coorde);
int aiMoveKing(struct chessBoard *board, struct AIDatas *data,
		int coords, int coorde);
int aiMoveQueen(struct chessBoard *board, struct AIDatas *data,
		int coords, int coorde);
int aiMoveBishop(struct chessBoard *board, struct AIDatas *data,
		 int coords, int coorde);
int aiMoveRook(struct chessBoard *board, struct AIDatas *data,
		int coords, int coorde);
int aiMoveKnight(struct chessBoard *board, struct AIDatas *data,
		 int coords, int coorde);
struct AIDatas* createDatas(struct chessBoard *board);
struct AIDatas* cloneDatas(struct AIDatas *datas);
void freeDatas(struct AIDatas *datas);

#endif // AI_RULES_H_
