#ifndef MOVERULES_H_
#define MOVERULES_H_


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


#endif
