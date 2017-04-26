# include <stdlib.h>
# include <stdio.h>
# include <SDL/SDL.h>
# include <SDL/SDL_ttf.h>
# include <SDL/SDL_image.h>
# include <err.h>
# include "chessBoard.h"

int main() {
	
	SDL_Surface *screen = NULL, *menu = NULL, *whiteCase = NULL, *blackCase = NULL, *redCase = NULL, *caseColored = NULL; //case Rouge = case selectionner

    	SDL_Surface *pieceWhitePawn = NULL, *pieceBlackPawn = NULL, *pieceBlackKing = NULL, *pieceWhiteKing = NULL;
    	SDL_Surface *pieceWhiteRook = NULL, *pieceBlackRook = NULL, *pieceWhiteBishop = NULL, *pieceBlackBishop = NULL;
    	SDL_Surface *pieceBlackKnight = NULL, *pieceWhiteKnight = NULL, *pieceBlackQueen = NULL, *pieceWhiteQueen = NULL;
   	//SDL_Surface *cursor = NULL;


    	SDL_Rect posWhiteCase, posBlackCase, posMenu, coordCaseSelect, /*pos,*/ pos2, posCaseColored;
    	//SDL_Rect posCursor;
    	SDL_Event event;

    	int i,j,offset = 80; //décallage est le décallage de l'échiquier en ordonnée (pour que l'échiquier soit collé au bas)
    	long /*srcX, srcY,*/ destX, destY, mouseX, mouseY;   //coordonnées de la souris au moment du clic.
    	int caseSelect = 0; // 0 = pas de case Selectionnée,  la case est Selectionnée = 1;
    	//int aQuiDeJouer = 0; // 0 = Aux blancs de jouer, 1 = Aux noirs de jouer.
    	//int posRoiNX,posRoiNY,posRoiBX,posRoiBY;
    	//int roiBlanc = 1, roiNoir = 1;  // si les rois sont encore là.
	int coords = 0;
	//////////////////////////////////

	struct chessBoard *board = initBoard();
	//piecesInPlace(board);
	//	
	SDL_Init(SDL_INIT_VIDEO);

    screen = SDL_SetVideoMode(1024, 768, 32, SDL_HWSURFACE | SDL_DOUBLEBUF /* | SDL_FULLSCREEN*/ ); /* Double Buffering */
    SDL_WM_SetCaption("APICHESS - API", NULL);

  	menu = IMG_Load("chess_init.jpg");
	posMenu.x = 0;
	posMenu.y = 0;
	

    /////////////// Mise En mémoire des différentes images des cases ///////////

    whiteCase = SDL_LoadBMP("caseBlanche2.bmp");///////////////////////////////
    blackCase = SDL_LoadBMP("caseNoire2.bmp");///////////////////////////////////
    redCase = SDL_LoadBMP("caseSelectionnee.bmp");////////////////////////////
    caseColored = SDL_LoadBMP("caseSelectionnee.bmp");///////////////////////////////

    ////////////////////////////////////////////////////////////////////////////

    SDL_SetAlpha(redCase, SDL_SRCALPHA, 128); //permet de rendre la couleur du selectionnement un peu transparent.

    pieceBlackBishop = SDL_LoadBMP("pieceFouNoir.bmp");
    pieceWhiteBishop = SDL_LoadBMP("pieceFouBlanc.bmp");
    pieceBlackQueen = SDL_LoadBMP("pieceDameNoir.bmp");
    pieceWhiteQueen = SDL_LoadBMP("pieceDameBlanc.bmp");
    pieceBlackKnight = SDL_LoadBMP("pieceCavalierNoir.bmp");
    pieceWhiteKnight = SDL_LoadBMP("pieceCavalierBlanc.bmp");

    pieceBlackKing = SDL_LoadBMP("pieceRoiNoir.bmp");
    pieceWhiteKing = SDL_LoadBMP("pieceRoiBlanc.bmp");
    pieceBlackRook = SDL_LoadBMP("pieceTourNoir.bmp");
    pieceWhiteRook = SDL_LoadBMP("pieceTourBlanc.bmp");
    pieceBlackPawn = SDL_LoadBMP("piecePionNoir.bmp");
    pieceWhitePawn = SDL_LoadBMP("piecePionBlanc.bmp");
    //cursor = SDL_LoadBMP("curseur.bmp");


/////// Ici, on rend la couleur rose (du fond des images des pièces) invisible afin de voir l'échiquier.
    SDL_SetColorKey(pieceBlackBishop, SDL_SRCCOLORKEY, SDL_MapRGB(pieceBlackBishop->format, 255, 0, 255));
    SDL_SetColorKey(pieceWhiteBishop, SDL_SRCCOLORKEY, SDL_MapRGB(pieceWhiteBishop->format, 255, 0, 255));
    SDL_SetColorKey(pieceBlackQueen, SDL_SRCCOLORKEY, SDL_MapRGB(pieceBlackQueen->format, 255, 0, 255));
    SDL_SetColorKey(pieceWhiteQueen, SDL_SRCCOLORKEY, SDL_MapRGB(pieceWhiteQueen->format, 255, 0, 255));
    SDL_SetColorKey(pieceBlackKnight, SDL_SRCCOLORKEY, SDL_MapRGB(pieceBlackKnight->format, 255, 0, 255));
    SDL_SetColorKey(pieceWhiteKnight, SDL_SRCCOLORKEY, SDL_MapRGB(pieceWhiteKnight->format, 255, 0, 255));
    SDL_SetColorKey(pieceBlackKing, SDL_SRCCOLORKEY, SDL_MapRGB(pieceBlackKing->format, 255, 0, 255));
    SDL_SetColorKey(pieceWhiteKing, SDL_SRCCOLORKEY, SDL_MapRGB(pieceWhiteKing->format, 255, 0, 255));
    SDL_SetColorKey(pieceBlackRook, SDL_SRCCOLORKEY, SDL_MapRGB(pieceBlackRook->format, 255, 0, 255));
    SDL_SetColorKey(pieceWhiteRook, SDL_SRCCOLORKEY, SDL_MapRGB(pieceWhiteRook->format, 255, 0, 255));
    SDL_SetColorKey(pieceBlackPawn, SDL_SRCCOLORKEY, SDL_MapRGB(pieceBlackPawn->format, 255, 0, 255));
    SDL_SetColorKey(pieceWhitePawn, SDL_SRCCOLORKEY, SDL_MapRGB(pieceWhitePawn->format, 255, 0, 255));
    //SDL_SetColorKey(cursor, SDL_SRCCOLORKEY, SDL_MapRGB(cursor->format, 255, 0, 255));
	//fin partie init vid debut ttf//////

    SDL_EnableKeyRepeat(10, 10); /* Activation de la répétition des touches */
    TTF_Init();  // Initialisation de la librairie qui permet d'afficher du texte.
    SDL_Surface *message = NULL, *messageIndicator = NULL;
    TTF_Font *font, *font2;
    SDL_Color textColor = { 0, 0, 0, 42 }; // Couleur de l'écriture (ici noir)

    SDL_Rect positionMessage, positionMessageIndicator;
    positionMessage.x = 50;
    positionMessage.y = 0;

    font = TTF_OpenFont( "Dbbrnms.ttf", 34 );
    font2 = TTF_OpenFont( "Dbbrnms.ttf", 22 );
    message = TTF_RenderText_Blended(font, "Selectionnez la pièce avec le clic gauche et déplacez la avec le clic droit", textColor);
	////////////
   void displayIndicatorPosition(int player)
   {
/////////////////////// Affiche quel joueur doit jouer ///////////////////////////////////
       //SDL_Rect positionMessageIndicator;
        /*TTF_Init(); 
        SDL_Surface *message = NULL, *messageIndicator = NULL;
        TTF_Font *font, *font2;
        SDL_Color textColor = { 0, 0, 0 }; // Couleur de l'écriture (ici noir)

        SDL_Rect positionMessage, positionMessageIndicator;
        positionMessage.x = 50;
        positionMessage.y = 0;

        font = TTF_OpenFont( "Dbbrnms.ttf", 34 );
        font2 = TTF_OpenFont( "Dbbrnms.ttf", 22 );      
        message = TTF_RenderText_Blended(font, "Selectionnez la pièce avec le clic gauche et déplacez la avec le clic droit", textColor);*/
        positionMessageIndicator.x = 700;
        positionMessageIndicator.y = 80;
        if (player == 1)
        {
            messageIndicator = TTF_RenderText_Blended(font2, "Aux Blancs de jouer !", textColor);
        }
        else
       {
            messageIndicator = TTF_RenderText_Blended(font2, "Aux Noirs de jouer !", textColor);
       }
        SDL_BlitSurface(messageIndicator, NULL, screen, &positionMessageIndicator);
        SDL_FreeSurface(messageIndicator);
///////////////////////////////////////////////////////////////////////////////////////////////

        positionMessageIndicator.x = 25;
        positionMessageIndicator.y = offset - 48;
        messageIndicator = TTF_RenderText_Blended(font, "1", textColor);

        SDL_BlitSurface(messageIndicator, NULL, screen, &positionMessageIndicator);
        SDL_FreeSurface(messageIndicator);

	positionMessageIndicator.x = 105;
        messageIndicator = TTF_RenderText_Blended(font, "2", textColor);

        SDL_BlitSurface(messageIndicator, NULL, screen, &positionMessageIndicator);
        SDL_FreeSurface(messageIndicator);

        positionMessageIndicator.x = 185;
        messageIndicator = TTF_RenderText_Blended(font, "3", textColor);

        SDL_BlitSurface(messageIndicator, NULL, screen, &positionMessageIndicator);
        SDL_FreeSurface(messageIndicator);

        positionMessageIndicator.x = 265;
        messageIndicator = TTF_RenderText_Blended(font, "4", textColor);

        SDL_BlitSurface(messageIndicator, NULL, screen, &positionMessageIndicator);
        SDL_FreeSurface(messageIndicator);

        positionMessageIndicator.x = 345;
        messageIndicator = TTF_RenderText_Blended(font, "5", textColor);

        SDL_BlitSurface(messageIndicator, NULL, screen, &positionMessageIndicator);
        SDL_FreeSurface(messageIndicator);

        positionMessageIndicator.x = 425;
        messageIndicator = TTF_RenderText_Blended(font, "6", textColor);

        SDL_BlitSurface(messageIndicator, NULL, screen, &positionMessageIndicator);
        SDL_FreeSurface(messageIndicator);

        positionMessageIndicator.x = 505;
        messageIndicator = TTF_RenderText_Blended(font, "7", textColor);

        SDL_BlitSurface(messageIndicator, NULL, screen, &positionMessageIndicator);
        SDL_FreeSurface(messageIndicator);

        positionMessageIndicator.x = 585;
        messageIndicator = TTF_RenderText_Blended(font, "8", textColor);

	SDL_BlitSurface(messageIndicator, NULL, screen, &positionMessageIndicator);
        SDL_FreeSurface(messageIndicator);

        positionMessageIndicator.x = 665;
        positionMessageIndicator.y = offset + 12;
        messageIndicator = TTF_RenderText_Blended(font, "1", textColor);

        SDL_BlitSurface(messageIndicator, NULL, screen, &positionMessageIndicator);
        SDL_FreeSurface(messageIndicator);

        positionMessageIndicator.x = 665;
        positionMessageIndicator.y = offset + 92;
        messageIndicator = TTF_RenderText_Blended(font, "2", textColor);

        SDL_BlitSurface(messageIndicator, NULL, screen, &positionMessageIndicator);
        SDL_FreeSurface(messageIndicator);

        positionMessageIndicator.x = 665;
        positionMessageIndicator.y = offset + 172;
        messageIndicator = TTF_RenderText_Blended(font, "3", textColor);

        SDL_BlitSurface(messageIndicator, NULL, screen, &positionMessageIndicator);
        SDL_FreeSurface(messageIndicator);

        positionMessageIndicator.x = 665;
        positionMessageIndicator.y = offset + 252;
        messageIndicator = TTF_RenderText_Blended(font, "4", textColor);

        SDL_BlitSurface(messageIndicator, NULL, screen, &positionMessageIndicator);
        SDL_FreeSurface(messageIndicator);

        positionMessageIndicator.x = 665;
        positionMessageIndicator.y = offset + 332;
        messageIndicator = TTF_RenderText_Blended(font, "5", textColor);

        SDL_BlitSurface(messageIndicator, NULL, screen, &positionMessageIndicator);
        SDL_FreeSurface(messageIndicator);
	
	positionMessageIndicator.x = 665;
        positionMessageIndicator.y = offset + 412;
        messageIndicator = TTF_RenderText_Blended(font, "6", textColor);

        SDL_BlitSurface(messageIndicator, NULL, screen, &positionMessageIndicator);
        SDL_FreeSurface(messageIndicator);

        positionMessageIndicator.x = 665;
        positionMessageIndicator.y = offset + 492;
        messageIndicator = TTF_RenderText_Blended(font, "7", textColor);

        SDL_BlitSurface(messageIndicator, NULL, screen, &positionMessageIndicator);
        SDL_FreeSurface(messageIndicator);

        positionMessageIndicator.x = 665;
        positionMessageIndicator.y = offset + 572;
        messageIndicator = TTF_RenderText_Blended(font, "8", textColor);

        SDL_BlitSurface(messageIndicator, NULL, screen, &positionMessageIndicator);
        SDL_FreeSurface(messageIndicator);
   }



    SDL_ShowCursor(SDL_ENABLE);  //SDL_DISABLE pour ne plus afficher la souris 'normale' (pratique pour n'utiliser que le curseur personnalisé)
	//////////
void coloreCase(int abscisse, int ordonnee)   //////////////// Colore la case d'abscisse X et d'ordonnée Y;
{
        
        posCaseColored.x = abscisse * 80;
        posCaseColored.y = ordonnee * 80 + offset;
        SDL_BlitSurface(caseColored, NULL, screen, &posCaseColored);

}

void displayPieces(struct chessBoard *board)

{
j = 0;
    for (i=0;i<8;i=i+1){
            for (j=0;j<8;j=j+1){
		if (board->squareMat[i][j].isEmpty != NULL){
                    if (board->squareMat[i][j].isEmpty->color == 1){
                                        if (board->squareMat[i][j].isEmpty->type == 3){
                                        pos2.x = j*80;
                                        pos2.y = i*80 + offset;
                                        SDL_BlitSurface(pieceBlackBishop, NULL, screen, &pos2);

                                        }
                                        else if (board->squareMat[i][j].isEmpty->type == 5){
					
                                        pos2.x = j*80;
                                        pos2.y = i*80 + offset;
                                        SDL_BlitSurface(pieceBlackRook, NULL, screen, &pos2);

                                        }
                                        else if (board->squareMat[i][j].isEmpty->type == 6){
					
                                        pos2.x = j*80;
                                        pos2.y = i*80 + offset;
                                        SDL_BlitSurface(pieceBlackPawn, NULL, screen, &pos2);
                                        }
                                        else if (board->squareMat[i][j].isEmpty->type == 4)
					{
                                        pos2.x = j*80;
                                        pos2.y = i*80 + offset;
                                        SDL_BlitSurface(pieceBlackKnight, NULL, screen, &pos2);

                                        }

                                        else if (board->squareMat[i][j].isEmpty->type == 2)

                                        {
                                        pos2.x = j*80;
                                        pos2.y = i*80 + offset;
                                        SDL_BlitSurface(pieceBlackQueen, NULL, screen, &pos2);
                                        }

                                        else if (board->squareMat[i][j].isEmpty->type == 1)
                                        {
                                        pos2.x = j*80;
                                        pos2.y = i*80 + offset;
                                        SDL_BlitSurface(pieceBlackKing, NULL, screen, &pos2);

                                        }

                                }

                        if (board->squareMat[i][j].isEmpty->color == 0 )

                                    {
                                        if (board->squareMat[i][j].isEmpty->type == 3)
                                        {
                                        pos2.x = j*80;
                                        pos2.y = i*80 + offset;
                                        SDL_BlitSurface(pieceWhiteBishop, NULL, screen, &pos2);
                                        }

                                        else if (board->squareMat[i][j].isEmpty->type == 5)
                                        {
                                        pos2.x = j*80;
                                        pos2.y = i*80 + offset;
                                        SDL_BlitSurface(pieceWhiteRook, NULL, screen, &pos2);

                                        }
                                        else if (board->squareMat[i][j].isEmpty->type == 6)
                                        {
                                        pos2.x = j*80;
                                        pos2.y = i*80 + offset;
                                        SDL_BlitSurface(pieceWhitePawn, NULL, screen, &pos2);
                                        }

                                        else if (board->squareMat[i][j].isEmpty->type == 4)
                                        {
                                        pos2.x = j*80;
                                        pos2.y = i*80 + offset;
                                        SDL_BlitSurface(pieceWhiteKnight, NULL, screen, &pos2);
                                        }
                                        else if (board->squareMat[i][j].isEmpty->type == 2)
                                        {
                                        pos2.x = j*80;
                                        pos2.y = i*80 + offset;
                                        SDL_BlitSurface(pieceWhiteQueen, NULL, screen, &pos2);

                                        }

                                        else if (board->squareMat[i][j].isEmpty->type == 1)
                                        {
                                        pos2.x = j*80;
                                        pos2.y = i*80 + offset;
                                        SDL_BlitSurface(pieceWhiteKing, NULL, screen, &pos2);

                                        }

                                    }
			}
                }
	
    }
	printf("%d",pos2.x);

}
	///////////
int coloreCaseSelectionne()
{
              int srcX = 0;
		int srcY = 0;
		int r = 0;
		int r2 = 0;
		int r1 = 0;
	 	srcX = event.button.x;
		srcY = event.button.y;
	      mouseX = event.button.x; // On récupere la position du curseur de la souris
              mouseY = event.button.y;
              mouseX = mouseX / 80;    //On regarde sur quelle case de l'échiquier il se trouve en abscisse
  	      srcX = srcX+offset;
	      if(srcX < 80 && srcY > 0)
		srcX = 1;
	      else
		srcX = srcX/80;
	      
              if (mouseY>=offset)         //On regarde sur quelle case de l'échiquier il se trouve en ordonnée
                    {                  // (avec le décallage)
                    mouseY = (mouseY-offset) / 80;
		    srcY = srcY/80;
		    srcY = srcY;
                    }
              else
                    {
                    mouseY = -1; //Le curseur de la souris est au dessus de l'échiquier.
                    }
             /* Si le clic est dans la zone de l'échiquier, caseSelect passe a 1 pour colorer la case Selectionnée.
                voir juste avant le flipscreen. */
              if ((mouseX < 8) && (mouseX >= 0) && (mouseY < 8) && (mouseY >= 0)) //si on est sur l'échiquier par rapport aux X et aux Y
                    {
              caseSelect = 1;
              coordCaseSelect.x = mouseX * 80;
              coordCaseSelect.y = (mouseY * 80) + offset;
	      r1 = srcX;
	       r2 = srcY*10;
		r = r1 + r2;
		    }
               else
                    {
                    caseSelect = 0;
		    r = 0;
                    }
return r;
}

	//////////
	int test = -1;
	int sf = -1;
	int gameMode = 0;
	while(test != 1){
		printf("choose game mode \n gameMode 2 for vs AI \n gamemode 1  for player vs player\n 0 for exit\n\n");
		sf = scanf("%d", &gameMode);
		if (sf == 1){
			if (gameMode == 1 || gameMode == 0 || gameMode == 2)
				test = 1;
			else
				sf = -1;
		}
	}
	////////
    int continuer = 1;
    while (continuer==1)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_KEYDOWN:
		continuer = 0;
		break;
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE: // Veut arrêter le jeu
                        continuer = 0;
                        break;
                    case SDLK_KP1: // Demande à jouer
                        gameMode=2;
			continuer = 0;
                        break;
                    case SDLK_KP2: // Demande l'éditeur de niveaux
                        gameMode = 1;
			continuer = 0;
                        break;
		    default:
		  	;
                }
                break;
		default:
		  ;
        }

        // Effacement de l'écran
        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
        SDL_BlitSurface(menu, NULL, screen, &posMenu);
        SDL_Flip(screen);
    }

    SDL_FreeSurface(menu);
    //SDL_Quit();

    //return EXIT_SUCCESS;


	////////

	printMap(board);
	int player = -1;
	coords = 0; 
	int coorde = 0;
	int endgame = -1;
	int turn;
	//sf = -1;
	int pt = -1;
	while (endgame != 1){
		//
		//coorde = 0;
		//coords = 0;
		turn = board->turn;
                player = (turn%2) + 1;
		displayIndicatorPosition(player); 
                //printf("player %d choose your move\n\n",player);
		//
		//message = TTF_RenderText_Blended(font, "Selectionnez d'abord une pièce à déplacer avec le clic gauche", textColor);
		message = TTF_RenderText_Blended(font, "Selectionnez la pièce avec le clic gauche et déplacez la avec le clic droit", textColor);
	       	SDL_BlitSurface(message, NULL, screen, &positionMessage);
        	SDL_FreeSurface(message);
		SDL_Delay(20);
		//////
		if (gameMode == 2 && player == 2) {
			int *tab = createNode(board);
			pt = move(board, *tab, *(tab+1));
			if (pt == -1)
                        	printf("impossible move\n");
                        else if (pt == 1)
                                endgame = 1;
                        else {
                                board->turn = turn + 1;
                                //sf = -1;
                                printMap(board);
                                printf("white player : %d\n", getValue(board, 0));
                        	printf("black player : %d\n", getValue(board, 1));
                       	}
		}else{

		/////
		SDL_WaitEvent(&event); //attente d'un évenement.
        	switch(event.type) // Choix de l'action à réaliser suivant l'évenement.
        	{
            		case SDL_QUIT:  // Cas du clic sur la croix rouge (en haut a droite)
                		endgame = 1;
	               		break;
		        case SDL_KEYDOWN:     // Cas d'une touche appuyé
	                	switch(event.key.keysym.sym)
                		{
                        		case SDLK_ESCAPE: // Cas de la touche ECHAP
	                			endgame = 1;
                        			break;
					default:
						;
                		}
           /* case SDL_MOUSEMOTION:
            positionCurseur.x = event.motion.x;  On sauvegarde la position de la souris, pour le curseur.*/
           /* positionCurseur.y = event.motion.y;
            break;
            */
	           	case SDL_MOUSEBUTTONUP:  // Cas du clic de la souris 
	        		if (event.button.button == SDL_BUTTON_LEFT) // gauche
		                   {
        			           coords = coloreCaseSelectionne();
					   ////
					  ////
					   printf("coords = %d", coords);
	                	   }
	                	if (event.button.button == SDL_BUTTON_RIGHT) // droit !
        	           	{
	                   		destX =  event.button.x; // On récupere la position du curseur de la souris
                			destY =  event.button.y;
                			destX =  destX+offset  ;    //On regarde sur quelle case de l'échiquier il se trouve en abscisse
                			if (destY>=offset)         //On regarde sur quelle case de l'échiquier il se trouve en ordonnée
                    			{                  // (avec le décallage)
                    				destY = (destY) / 80;
						destY = destY;
                    			}
                			else
                    			{
                    				destY = -1;
                    			}
					if(destX < 80 && destX>0)
						destX = 1;
					else
						destX = destX/80;
                			coorde =  (destX) + (destY*10) ; //gestion du déplacemement
					coorde = coorde;
					coorde = coorde;
	                   		printf("coorde = %d",coorde);
				}
				break;
			default:
				;
        	}
		if(coorde && coords){
			//printf("ce %d ",coorde);
			//move
			int mat = coords - 11;
                        int cmat = mat%10;
                        int lmat = (mat - cmat)/10;
                        struct piece *piece = board->squareMat[lmat][cmat].isEmpty;
                        if (player == piece->color + 1) {
                                pt = move(board, coords, coorde);
                                if (pt == -1)
                                        printf("impossible move\n");
				else if (pt == 1)
					endgame = 1;
				else{
                                	board->turn = turn + 1;
                                	//sf = -1;
					printf("white player : %d\n", getValue(board, 0));
					printf("black player : %d\n", getValue(board, 1));
         				positionMessageIndicator.x = 700;
        				positionMessageIndicator.y = 160;
					//messageIndicator = TTF_RenderText_Blended(font2,itoa(getValue(board, 0)) , textColor);

		                       	printMap(board);
                        	    }
			}
                        else
                                printf("impossible move\n");
			coorde = 0;
			coords = 0;	
		}
	}
        	SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));
	
////////////////////////////////////////////////////////////////////////////////
////////////////////// Display Black Case //////////////////////////////
////////////////////////////////////////////////////////////////////////////////
for (i=0; i<8; i=i+2)
    {
        for (j=0; j<8; j=j+2)
            {
            posBlackCase.x = i*80;
            posBlackCase.y = j*80 + 80+ offset;
            SDL_BlitSurface(blackCase, NULL, screen, &posBlackCase);
            posBlackCase.x = i*80 + 80;
            posBlackCase.y = j*80 + offset;
            SDL_BlitSurface(blackCase, NULL, screen, &posBlackCase);
             }
        }
////////////////////////////////////////////////////////////////////////////////
////////////////////// AFFICHAGE DES CASES BLANCHES ////////////////////////////
////////////////////////////////////////////////////////////////////////////////
for (i=0; i<8; i=i+2)
    {
        for (j=0; j<8; j=j+2)
          {
          posWhiteCase.x = i*80 ;
          posWhiteCase.y = j*80 + offset;
          SDL_BlitSurface(whiteCase, NULL, screen, &posWhiteCase);
          posWhiteCase.x = i*80 + 80;
          posWhiteCase.y = j*80 + 80 + offset;
          SDL_BlitSurface(whiteCase, NULL, screen, &posWhiteCase);
          }
    }
	/////////
 	displayPieces(board);
	if (caseSelect)   ////// Affichage du vert autour de la case selectionnée, si l'utilisateur a cliqué sur une case.
   	{
        SDL_BlitSurface(redCase, NULL, screen, &coordCaseSelect);
  	}
	displayIndicatorPosition(player);
//    SDL_BlitSurface(curseur, NULL, screen, &positionCurseur); //Afin d'afficher l'autre curseur.
        SDL_Flip(screen); //Mise à jour de l'écran.	
		
}
	if (endgame == -1)
	{
    	SDL_Delay(1000);
    	SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));
    	message = TTF_RenderText_Blended(font, "Fin de la partie", textColor);
    	positionMessage.x = 350;
    	positionMessage.y = 250;
    	SDL_BlitSurface(message, NULL, screen, &positionMessage);
    	positionMessage.x = 300;
    	positionMessage.y = 450;
    	SDL_Flip(screen);
    	SDL_Delay(1000);
	}

	deleteBoard(board);
    	SDL_FreeSurface(blackCase);
    	SDL_FreeSurface(whiteCase); //on libere la mémoire utilisée.
    	SDL_FreeSurface(redCase);
    	SDL_FreeSurface(caseColored);
    	SDL_FreeSurface(pieceBlackBishop);
    	SDL_FreeSurface(pieceWhiteBishop);
    	SDL_FreeSurface(pieceBlackQueen);
    	SDL_FreeSurface(pieceWhiteQueen);
    	SDL_FreeSurface(pieceBlackKnight);
    	SDL_FreeSurface(pieceWhiteKnight);
    	SDL_FreeSurface(pieceBlackKing);
    	SDL_FreeSurface(pieceWhiteKing);
    	SDL_FreeSurface(pieceBlackRook);
    	SDL_FreeSurface(pieceWhiteRook);
    	SDL_FreeSurface(pieceBlackPawn);
    	SDL_FreeSurface(pieceWhitePawn);
    	SDL_FreeSurface(message);
    	SDL_FreeSurface(messageIndicator);

    	TTF_CloseFont(font);
    	TTF_Quit();
    	SDL_Quit();
	return 0;

}
