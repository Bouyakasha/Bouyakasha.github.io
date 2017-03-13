#ifndef CHESSBOARD_H_
#define CHESSBOARD_H_

struct pawn {
  int id;
  int color;
  int square;
  int firstMove;
  int isDead;
  struct pawn *next;
};

struct knight {
  int id;
  int color;
  int square;
  int isDead;
  struct knight *next;
};

struct bishop {
  int id;
  int color;
  int square;
  int isDead;
  struct bishop *next;
};

struct rook {
  int id;
  int color;
  int square;
  int isDead;
  struct rook *next;
};

struct queen {
  int id;
  int color;
  int square;
  int isDead;
  struct queen *next;
};

struct king {
  int id;
  int color;
  int square;
  int inCheck;
  struct king *next;
};


struct square {
  int id;
  int color;
  void *isEmpty;
  int pieceType;
};

struct chessBoard {
  int turn;
  int end;
  struct square **squareMat;
  struct king *nextKing;
  struct queen *nextQueen;
  struct rook *nextRook;
  struct bishop *nextBishop;
  struct knight *nextKnight;
  struct pawn *nextPawn;
};

struct chessBoard* initBoard();
void pushKing(struct chessBoard *board, int id, int color);
int popKing(struct chessBoard *board, int id, int color);
void pushQueen(struct chessBoard *board, int id, int color);
int popQueen(struct chessBoard *board, int id, int color);
void pushKnight(struct chessBoard *board, int id, int color);
int popKnight(struct chessBoard *board, int id, int color);
void pushRook(struct chessBoard *board, int id, int color);
int popRook(struct chessBoard *board, int id, int color);
void pushBishop(struct chessBoard *board, int id, int color);
int popBishop(struct chessBoard *board, int id, int color);
void pushPawn(struct chessBoard *board, int id, int color);
int popPawn(struct chessBoard *board, int id, int color);
void deleteBoard(struct chessBoard *board);
void piecesInPlace(struct chessBoard *board);
int getColor(struct square square);
int movePawn(struct pawn *pawn, struct square square);
int moveKing(struct king *king, struct square square);
int moveRook(struct chessBoard *board, struct rook *rook,
 	     struct square square);
int moveBishop(struct chessBoard *board, struct bishop *bishop,
	       struct square square);
int moveQueen(struct chessBoard *board, struct queen *queen,
               struct square square);
int moveKnight(struct knight *knight, struct square square);
void promotion(struct chessBoard *board, struct pawn *pawn, int type);
void printMap(struct chessBoard *board);
int killPiece(struct square square);
int move(struct chessBoard *board, int coords, int coorde);
#endif // CHESSBOARD_H_
