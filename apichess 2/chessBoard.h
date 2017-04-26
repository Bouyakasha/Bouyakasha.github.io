#ifndef CHESSBOARD_H_
#define CHESSBOARD_H_

#define MAX_VISIBILITY 2

struct piece {
  int type;
  //char *libelle;
  int id;
  int color;
  int square;
  float value;
  int isDead;
  int firstMove;
  struct piece *next;
};

struct square {
  int id;
  int color;
  struct piece *isEmpty;
};

struct chessBoard {
  int turn;
  int end;
  struct square **squareMat;
  struct piece *nextDeadPiece;
  struct piece *nextAlivePiece;
  int **pawnMoves;
  int **knightMoves;
  int **bishopMoves;
  int **rookMoves;
  int **kingMoves;
};

struct AISquare {
  int type, color, value;
};

/*
struct AIMat {
  struct square **AISquare;
};*/

struct AITree {
  struct AISquare **AIMat;
  int vBlack, vWhite, height;
  struct AITree *nodes;
};

void piecesInPlace(struct chessBoard *board);
void fillMovesMat(struct chessBoard *board);
struct chessBoard* initBoard();
struct piece* createPiece(int id, int color, int type, struct square square,
                 float value);
void pushPiece(struct chessBoard *board, struct piece *piece, int dead);
struct piece* popPiece(struct chessBoard *board, struct piece *piece,
		       int dead);
void deleteBoard(struct chessBoard *board);
void piecesInPlace(struct chessBoard *board);
int testStraight(struct chessBoard *board, struct piece *piece,
		 struct square square);
int testDiag(struct chessBoard *board, struct piece *piece,
                 struct square square);
int movePawn(struct chessBoard *board, struct piece *piece,
	     struct square square);
int moveKing(struct chessBoard *board, struct piece *piece,
	     struct square square);
int moveRook(struct chessBoard *board, struct piece *piece,
 	     struct square square);
int moveBishop(struct chessBoard *board, struct piece *piece,
	       struct square square);
int moveQueen(struct chessBoard *board, struct piece *piece,
               struct square square);
int moveKnight(struct chessBoard *board, struct piece *piece, 
	       struct square square);
void promotion(struct chessBoard *board, struct piece *piece, int type);
void printMap(struct chessBoard *board);
int tryMove(struct chessBoard *board, struct piece *piece,
	    struct square end);
int move(struct chessBoard *board, int coords, int coorde);
int getValue(struct chessBoard *board, int color);
int* createNode(struct chessBoard *board);
#endif // CHESSBOARD_H_
