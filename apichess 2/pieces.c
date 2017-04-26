# include <stdlib.h>
# include <stdio.h>
# include <err.h>
# include "chessBoard.h"

struct piece* createPiece(int id, int color, int type, struct square square, 
		 float value){
	struct piece *p = malloc(sizeof (struct piece));
        p->type = type;
        p->id = id;
        p->color = color;
        p->square = square.id;
        //square.isEmpty = p;
        p->value = value;
        p->isDead = 0;
        if (type == 6)
		p->firstMove = 1;
        p->next = NULL;
	//printf("%d\n",square.isEmpty->type);
	return p;
}

void pushPiece(struct chessBoard *board, struct piece *piece, int dead){
        if (dead == 1){
		piece->isDead = 1;
        	piece->next = board->nextDeadPiece;
        	board->nextDeadPiece = piece;
	}else {
		piece->next = board->nextAlivePiece;
                board->nextAlivePiece = piece;
	}
}

struct piece* popPiece(struct chessBoard *board, struct piece *piece, int dead){
        if (dead == 1){
		struct piece *tmp = board->nextDeadPiece;
        	if (tmp->id == piece->id){
                	board->nextDeadPiece = tmp->next;
			return tmp;
        	}
        	while (tmp->next->id != piece->id)
                	tmp = tmp->next;
        	struct piece *tmp2 = tmp->next;
        	tmp->next = tmp2->next;
		return tmp2;
	}else {
		struct piece *tmp = board->nextAlivePiece;
                if (tmp->id == piece->id){
                        board->nextAlivePiece = tmp->next;
                        return tmp;
                }
                while (tmp->next->id != piece->id)
                        tmp = tmp->next;
                struct piece *tmp2 = tmp->next;
                tmp->next = tmp2->next;
                return tmp2;
	}
}

