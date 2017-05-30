#ifndef CHESSBOARD_H_
#define CHESSBOARD_H_

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
void piecesInPlace(struct chessBoard *board);
void fillMovesMat(struct chessBoard *board);
struct chessBoard* initBoard();
void deleteBoard(struct chessBoard *board);
void piecesInPlace(struct chessBoard *board);
void printMap(struct chessBoard *board);
#endif // CHESSBOARD_H_
