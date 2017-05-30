#ifndef PIECES_H_
#define PIECES_H_

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

struct piece* createPiece(int id, int color, int type, struct square square,
                 float value);
void pushPiece(struct chessBoard *board, struct piece *piece, int dead);
struct piece* popPiece(struct chessBoard *board, struct piece *piece,
                       int dead);
void deleteBoard(struct chessBoard *board);

#endif
