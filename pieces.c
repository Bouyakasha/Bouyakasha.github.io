# include <stdlib.h>
# include <stdio.h>
# include <err.h>
# include "chessBoard.h"

void pushKing(struct chessBoard *board, int id, int color){
        struct king *king = malloc(sizeof (struct king));
        king->id = id;
        king->color = color;
        king->square = 0;
        king->inCheck = 0;
        king->next = board->nextKing;
        board->nextKing = king;
}

int popKing(struct chessBoard *board, int id, int color){
        int res;
        struct king *tmp = board->nextKing;
        if (tmp->id == id && tmp->color == color){
                board->nextKing = tmp->next;
                res = tmp->id*10 + tmp->color;
                free(tmp);
                return res;
        }
        while (tmp->next->id != id && tmp->next->color != color)
                tmp = tmp->next;
        struct king *tmp2 = tmp->next;
        tmp->next = tmp2->next;
        res = tmp2->id*10 + tmp2->color;
        free(tmp2);
        return res;
}

void pushQueen(struct chessBoard *board, int id, int color){
        struct queen *queen = malloc(sizeof (struct queen));
        queen->id = id;
        queen->color = color;
        queen->square = 0;
	queen->isDead = 0;
        queen->next = board->nextQueen;
        board->nextQueen = queen;
}

int popQueen(struct chessBoard *board, int id, int color){
        int res;
        struct queen *tmp = board->nextQueen;
        if (tmp->id == id && tmp->color == color){
                board->nextQueen = tmp->next;
                res = tmp->id*10 + tmp->color;
                free(tmp);
                return res;
        }
        while (tmp->next->id != id && tmp->next->color != color)
                tmp = tmp->next;
        struct queen *tmp2 = tmp->next;
        tmp->next = tmp2->next;
        res = tmp2->id*10 + tmp2->color;
        free(tmp2);
        return res;
}

void pushKnight(struct chessBoard *board, int id, int color){
        struct knight *knight = malloc(sizeof (struct knight));
        knight->id = id;
        knight->color = color;
        knight->square = 0;
	knight->isDead = 0;
        knight->next = board->nextKnight;
        board->nextKnight = knight;
}

int popKnight(struct chessBoard *board, int id, int color){
        int res;
        struct knight *tmp = board->nextKnight;
        if (tmp->id == id && tmp->color == color){
                board->nextKnight = tmp->next;
                res = tmp->id*10 + tmp->color;
                free(tmp);
                return res;
        }
        while (tmp->next->id != id && tmp->next->color != color)
                tmp = tmp->next;
        struct knight *tmp2 = tmp->next;
        tmp->next = tmp2->next;
        res = tmp2->id*10 + tmp2->color;
        free(tmp2);
        return res;
}

void pushRook(struct chessBoard *board, int id, int color){
        struct rook *rook = malloc(sizeof (struct rook));
        rook->id = id;
        rook->color = color;
        rook->square = 0;
	rook->isDead = 0;
        rook->next = board->nextRook;
        board->nextRook = rook;
}

int popRook(struct chessBoard *board, int id, int color){
        int res;
        struct rook *tmp = board->nextRook;
        if (tmp->id == id && tmp->color == color){
                board->nextRook = tmp->next;
                res = tmp->id*10 + tmp->color;
                free(tmp);
                return res;
        }
        while (tmp->next->id != id && tmp->next->color != color)
                tmp = tmp->next;
        struct rook *tmp2 = tmp->next;
        tmp->next = tmp2->next;
        res = tmp2->id*10 + tmp2->color;
        free(tmp2);
        return res;
}

void pushBishop(struct chessBoard *board, int id, int color){
        struct bishop *bishop = malloc(sizeof (struct bishop));
        bishop->id = id;
        bishop->color = color;
        bishop->square = 0;
	bishop->isDead = 0;
        bishop->next = board->nextBishop;
        board->nextBishop = bishop;
}

int popBishop(struct chessBoard *board, int id, int color){
        int res;
        struct bishop *tmp = board->nextBishop;
        if (tmp->id == id && tmp->color == color){
                board->nextBishop = tmp->next;
                res = tmp->id*10 + tmp->color;
                free(tmp);
                return res;
        }
        while (tmp->next->id != id && tmp->next->color != color)
                tmp = tmp->next;
        struct bishop *tmp2 = tmp->next;
        tmp->next = tmp2->next;
        res = tmp2->id*10 + tmp2->color;
        free(tmp2);
        return res;
}

void pushPawn(struct chessBoard *board, int id, int color){
        struct pawn *pawn = malloc(sizeof (struct pawn));
        pawn->id = id;
        pawn->color = color;
        pawn->square = 0;
        pawn->firstMove = 1;
	pawn->isDead = 0;
        pawn->next = board->nextPawn;
        board->nextPawn = pawn;
}

int popPawn(struct chessBoard *board, int id, int color){
        int res;
        struct pawn *tmp = board->nextPawn;
        if (tmp->id == id && tmp->color == color){
                board->nextPawn = tmp->next;
                res = tmp->id*10 + tmp->color;
                free(tmp);
                return res;
        }
        while (tmp->next->id != id && tmp->next->color != color)
                tmp = tmp->next;
        struct pawn *tmp2 = tmp->next;
        tmp->next = tmp2->next;
        res = tmp2->id*10 + tmp2->color;
        free(tmp2);
        return res;
}

int movePawn(struct pawn *pawn, struct square square){
        int capacity = 1 + pawn->firstMove;
        int tmp = pawn->square;
        int tmp2 = square.id;
        int try;
        if (tmp + 10 == tmp2 || tmp + (capacity*10) == tmp2){
                if (square.isEmpty!=NULL)
                        return 0;
                else
                        return 1;
        }
        if (tmp + 11 == tmp2 || tmp + 9 == tmp2){
                if (square.isEmpty!=NULL){
                        if ((try = getColor(square)) == pawn->color)
                                return 0;
                        else
                                return 2;
                }
                else
                        return 0;
        }
	if (tmp - 10 == tmp2 || tmp - (capacity*10) == tmp2){
                if (square.isEmpty!=NULL)
                        return 0;
                else
                        return 1;
        }
        if (tmp - 11 == tmp2 || tmp - 9 == tmp2){
                if (square.isEmpty!=NULL){
                        if ((try = getColor(square)) == pawn->color)
                                return 0;
                        else
                                return 2;
                }
                else
                        return 0;
        }
        return 0;
}

int moveKing(struct king *king, struct square square){
        int tmp = king->square;
        int tmp2 = square.id;
        if (tmp2 == tmp)
                return 0;
        if (tmp + 1 == tmp2 || tmp - 1 == tmp2 || tmp + 10 == tmp2 ||
	   tmp - 10 == tmp2 || tmp + 11 == tmp2 || tmp - 11 == tmp2 ||
	   tmp + 9 == tmp2 || tmp - 9 == tmp2 ){
                if (square.isEmpty!=NULL){
                        int try;
                        if ((try = getColor(square)) == king->color)
                                return 0;
                        else
                                return 2;
                }
                return 1;
        }
        return 0;
}

int moveRook(struct chessBoard *board, struct rook *rook,
	     struct square square){
        int tmp = rook->square;
        int mod = tmp%10;
        int tmp2 = square.id;
        int mat = tmp - 11;
        int cmat = mat%10;
        int lmat = (mat-cmat)/10;
        int mat2 = tmp2 - 11;
        int cmat2 = mat2%10;
        int lmat2 = (mat2 - cmat2)/10;
        for (int i = 1; i+mod < 9; i++){
                if (tmp + i == tmp2){
                        if (square.isEmpty!=NULL){
                                int try;
                                if ((try = getColor(square)) == rook->color)
                                        return 0;
                        }
                        for (int j = cmat + 1; j<cmat2 ; j++){
                                if (board->squareMat[lmat][j].isEmpty != NULL)
                                        return 0;
                        }
			if (square.isEmpty!=NULL)
                                return 2;
                        return 1;
                }
        }
        for (int i = 1; mod-i > 0; i++){
                if (tmp - i == tmp2){
                        if (square.isEmpty!=NULL){
                                int try;
                                if ((try = getColor(square)) == rook->color)
                                        return 0;
                        }
                        for (int j = cmat - 1; j>cmat2 ; j--){
                                if (board->squareMat[lmat][j].isEmpty != NULL)
                                        return 0;
                        }
			if (square.isEmpty!=NULL)
                                return 2;
                        return 1;
                }
        }

	for (int i = 10; tmp+i < 89; i += 10){
                if (tmp + i == tmp2){
                        if (square.isEmpty!=NULL){
                                int try;
                                if ((try = getColor(square)) == rook->color)
                                        return 0;
                        }
                        for (int j = lmat + 1; j<lmat2 ; j++){
                                if (board->squareMat[j][cmat].isEmpty != NULL)
                                        return 0;
                        }
			if (square.isEmpty!=NULL)
                                return 2;
                        return 1;
                }
        }
        for (int i = 10; tmp-i > 10; i += 10){
                if (tmp - i == tmp2){
                        if (square.isEmpty!=NULL){
                                int try;
                                if ((try = getColor(square)) == rook->color)
                                        return 0;
                        }
                        for (int j = lmat - 1; j>lmat2 ; j -= 1){
                                if (board->squareMat[j][cmat].isEmpty != NULL)
                                        return 0;
                        }
			if (square.isEmpty!=NULL)
                                return 2;
                        return 1;
                }
        }
        return 0;
}

int moveBishop(struct chessBoard *board, struct bishop *bishop,
               struct square square){
        int tmp = bishop->square;
        int tmp2 = square.id;
        int try = tmp;
        int mat = tmp - 11;
        int cmat = mat%10;
        int lmat = (mat-cmat)/10;
        int mat2 = tmp2 - 11;
        int cmat2 = mat2%10;
        int lmat2 = (mat2 - cmat2)/10;
        for (int i = 11; try%10 != 9 && try%10 != 0; i += 11){
                try = tmp + i;
                if (try == tmp2){
                        if (square.isEmpty!=NULL){
                                int try2;
                                if ((try2=getColor(square)) == bishop->color)
                                        return 0;
                        }
                        for (int i = lmat + 1, j = cmat + 1;
			     i < lmat2 && j < cmat2; i++, j++){
                                if (board->squareMat[i][j].isEmpty != NULL)
                                        return 0;
                        }
			if (square.isEmpty!=NULL)
                                return 2;
                        return 1;
                }
        }
        try = tmp;
        for (int i = 9; try%10 != 9 && try%10 != 0; i += 9){
                try = tmp + i;
                if (try == tmp2){
                        if (square.isEmpty!=NULL){
                                int try2;
                                if ((try2=getColor(square)) == bishop->color)
                                        return 0;
                        }
                        for (int i = lmat + 1, j = cmat - 1;
			     i < lmat2 && j > cmat2; i++, j--){
                                if (board->squareMat[i][j].isEmpty != NULL)
                                        return 0;
                        }
			if (square.isEmpty!=NULL)
                                return 2;
                        return 1;
                }
        }
	try = tmp;
        for (int i = 11; try%10 != 9 && try%10 != 0; i += 11){
                try = tmp - i;
                if (try == tmp2){
                        if (square.isEmpty!=NULL){
                                int try2;
                                if ((try2=getColor(square)) == bishop->color)
                                        return 0;
                        }
                        for (int i = lmat - 1, j = cmat - 1;
			     i > lmat2 && j < cmat2; i--, j--){
                                if (board->squareMat[i][j].isEmpty != NULL)
                                        return 0;
                        }
			if (square.isEmpty!=NULL)
                        	return 2;
                        return 1;
                }
        }
        try = tmp;
        for (int i = 9; try%10 != 9 && try%10 != 0; i += 9){
                try = tmp - i;
                if (try == tmp2){
                        if (square.isEmpty!=NULL){
                                int try2;
                                if ((try2=getColor(square)) == bishop->color)
                                        return 0;
                        }
                        for (int i = lmat - 1, j = cmat + 1;
			     i > lmat2 && j > cmat2; i--, j++){
                                if (board->squareMat[i][j].isEmpty != NULL)
                                        return 0;
                        }
			if (square.isEmpty!=NULL)
                        	return 2;
                        return 1;
                }
        }
        return 0;
}

int moveQueen(struct chessBoard *board, struct queen *queen,
	      struct square square){
	int tmp = queen->square;
	int mod = tmp%10;
        int tmp2 = square.id;
        int try = tmp;
        int mat = tmp - 11;
        int cmat = mat%10;
        int lmat = (mat-cmat)/10;
        int mat2 = tmp2 - 11;
        int cmat2 = mat2%10;
        int lmat2 = (mat2 - cmat2)/10;
	///// straight /////
	if (lmat < lmat2 && cmat == cmat2){
		for (int i = 10; tmp+i < 89; i += 10){
                	if (tmp + i == tmp2){
                        	if (square.isEmpty!=NULL){
                                	int try2;
                               	 	if ((try2 = getColor(square))
					    == queen->color)
                                        	return 0;
                        	}
                        	for (int j = lmat + 1; j<lmat2 ; j++){
                                	if (board->squareMat[j][cmat].isEmpty
					    != NULL)
                                        	return 0;
                        	}
				if (square.isEmpty!=NULL)
                                        return 2;
                        	return 1;
                	}
        	}
	}
	if (lmat > lmat2 && cmat == cmat2){
		for (int i = 10; tmp-i > 10; i+=10){
                	if (tmp - i == tmp2){
                        	if (square.isEmpty!=NULL){
                                	int try2;
                                	if ((try2 = getColor(square))
					    == queen->color)
                                        	return 0;
                        	}
                        	for (int j = lmat - 1; j>lmat2 ; j -= 1){
                                	if (board->squareMat[j][cmat].isEmpty
					    != NULL)
                                        	return 0;
                        	}
				if (square.isEmpty!=NULL)
                                        return 2;
                        	return 1;
                	}
        	}
	}
	if (lmat == lmat2 && cmat > cmat2){
		for (int i = 1; mod-i > 0; i++){
                	if (tmp - i == tmp2){
                        	if (square.isEmpty!=NULL){
                                	int try2;
                                	if ((try2 = getColor(square))
					    == queen->color)
                                        	return 0;
                        	}
                        	for (int j = cmat - 1; j>cmat2 ; j--){
                                	if (board->squareMat[lmat][j].isEmpty
					    != NULL)
                                        	return 0;
                        	}
				if (square.isEmpty!=NULL)
                                        return 2;
                        	return 1;
                	}
        	}
	}
	if (lmat == lmat2 && cmat < cmat2){
		for (int i = 1; i+mod < 9; i++){
                        if (tmp + i == tmp2){
                                if (square.isEmpty!=NULL){
                                        int try2;
                                        if ((try2 = getColor(square))
					    == queen->color)
                                                return 0;
                                }
                                for (int j = cmat + 1; j<cmat2 ; j++){
                                        if (board->squareMat[lmat][j].isEmpty
					    != NULL)
                                                return 0;
                                }
				if (square.isEmpty!=NULL)
                                        return 2;
                                return 1;
                        }
                }
	}
	///// diago /////
	if (lmat < lmat2 && cmat < cmat2){
		for (int i = 11; try%10 != 9 && try%10 != 0; i += 11){
                	try = tmp + i;
                	if (try == tmp2){
                        	if (square.isEmpty!=NULL){
                                	int try2;
                                	if ((try2 = getColor(square))
					    == queen->color)
                                	        return 0;
                        	}
                        	for (int i = lmat + 1, j = cmat + 1;
				     i < lmat2 && j < cmat2; i++, j++){
                                	if (board->squareMat[i][j].isEmpty
					    != NULL)
                                	        return 0;
                        	}
				if (square.isEmpty!=NULL)
                                        return 2;
                        	return 1;
                	}
        	}
	}
	if (lmat < lmat2 && cmat > cmat2){
		for (int i = 9; try%10 != 9 && try%10 != 0; i += 9){
                	try = tmp + i;
                	if (try == tmp2){
                        	if (square.isEmpty!=NULL){
                                	int try2;
                                	if ((try2 = getColor(square))
					    == queen->color)
                                	        return 0;
                        	}
                        	for (int i = lmat + 1, j = cmat - 1;
				     i < lmat2 && j > cmat2; i++, j--){
                                	if (board->squareMat[i][j].isEmpty
					    != NULL)
                                	        return 0;
                        	}
				if (square.isEmpty!=NULL)
                                        return 2;
                        	return 1;
                	}
        	}
        }
        if (lmat > lmat2 && cmat > cmat2){
		for (int i = 11; try%10 != 9 && try%10 != 0; i += 11){
                	try = tmp - i;
                	if (try == tmp2){
                        	if (square.isEmpty!=NULL){
                                	int try2;
                                	if ((try2 = getColor(square))
					    == queen->color)
                                	        return 0;
                        	}
                        	for (int i = lmat - 1, j = cmat - 1;
				     i > lmat2 && j < cmat2; i--, j--){
                                	if (board->squareMat[i][j].isEmpty
					    != NULL)
                                	        return 0;
                        	}
				if (square.isEmpty!=NULL)
                                        return 2;
                        	return 1;
                	}
        	}
        }
        if (lmat > lmat2 && cmat < cmat2){
		for (int i = 9; try%10 != 9 && try%10 != 0; i += 9){
                	try = tmp - i;
                	if (try == tmp2){
                        	if (square.isEmpty!=NULL){
                                	int try2;
                                	if ((try2 = getColor(square))
					    == queen->color)
                                	        return 0;
                        	}
                        	for (int i = lmat - 1, j = cmat + 1;
				     i > lmat2 && j > cmat2; i--, j++){
                                	if (board->squareMat[i][j].isEmpty
					    != NULL)
                                	        return 0;
                        	}
				if (square.isEmpty!=NULL)
					return 2;
                        	return 1;
                	}
        	}
        }
return 0;
}

int moveKnight(struct knight *knight, struct square square){
	int tmp = knight->square;
        int tmp2 = square.id;
        int mat = tmp - 11;
        int cmat = mat%10;
        int lmat = (mat-cmat)/10;
        int mat2 = tmp2 - 11;
        int cmat2 = mat2%10;
        int lmat2 = (mat2 - cmat2)/10;
	if (lmat < lmat2 && cmat > cmat2){
		if (lmat + 2 == lmat2 && cmat - 1 == cmat2){
			if (square.isEmpty!=NULL){
                        	int try2;
                                if ((try2 = getColor(square))== knight->color)
                                	return 0;
				else
					return 2;
                	}
			return 1;
		}
		else if (lmat + 1 == lmat2 && cmat - 2 == cmat2){
			if (square.isEmpty!=NULL){
                                int try2;
                                if ((try2 = getColor(square))== knight->color)
                                        return 0;
				else
					return 2;
                        }
                        return 1;
		}
	}
	if (lmat < lmat2 && cmat < cmat2){
        	if (lmat + 2 == lmat2 && cmat + 1 == cmat2){
                        if (square.isEmpty!=NULL){
                                int try2;
                                if ((try2 = getColor(square))== knight->color)
                                        return 0;
				else
					return 2;
                        }
                        return 1;
                }
                else if (lmat + 1 == lmat2 && cmat + 2 == cmat2){
                        if (square.isEmpty!=NULL){
                                int try2;
                                if ((try2 = getColor(square))== knight->color)
                                        return 0;
				else
					return 2;
                        }
                        return 1;
                }
        }
	if (lmat > lmat2 && cmat > cmat2){
        	if (lmat - 2 == lmat2 && cmat - 1 == cmat2){
                        if (square.isEmpty!=NULL){
                                int try2;
                                if ((try2 = getColor(square))== knight->color)
                                        return 0;
				else
					return 2;
                        }
                        return 1;
                }
                else if (lmat - 1 == lmat2 && cmat - 2 == cmat2){
                        if (square.isEmpty!=NULL){
                                int try2;
                                if ((try2 = getColor(square))== knight->color)
                                        return 0;
				else
					return 2;
                        }
                        return 1;
                }
        }
	if (lmat > lmat2 && cmat < cmat2){
        	if (lmat - 2 == lmat2 && cmat + 1 == cmat2){
                        if (square.isEmpty!=NULL){
                                int try2;
                                if ((try2 = getColor(square))== knight->color)
                                        return 0;
				else
					return 2;
                        }
                        return 1;
                }
                else if (lmat - 1 == lmat2 && cmat + 2 == cmat2){
                        if (square.isEmpty!=NULL){
                                int try2;
                                if ((try2 = getColor(square))== knight->color)
                                        return 0;
				else
					return 2;
                        }
                        return 1;
                }
        }
return 0;
}
