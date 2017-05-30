#ifndef ARBITRATOR_H_
#define ARBITRATOR_H_

void promotion(struct chessBoard *board, struct piece *piece, int type);
int tryMove(struct chessBoard *board, struct piece *piece,
            struct square end);
int move(struct chessBoard *board, int coords, int coorde);

#endif // CHESSBOARD_H_

