# include <stdlib.h>
# include <stdio.h>
# include <SDL/SDL.h>
# include <SDL/SDL_ttf.h>
# include <SDL/SDL_image.h>
# include <err.h>
# include "chessBoard.h"
# include "ai.h"
# include "ai_rules.h"
# include "arbitrator.h"
# include "moveRules.h"
# include "pieces.h"
# include "tree_and_values.h"
int main() {

	SDL_Surface *screen = NULL, *menu = NULL, *whiteCase = NULL;
	SDL_Surface *blackCase = NULL, *redCase = NULL, *caseColored = NULL; 

	SDL_Surface *pieceWhitePawn = NULL, *pieceBlackPawn = NULL;
	SDL_Surface *pieceBlackKing = NULL, *pieceWhiteKing = NULL;
	SDL_Surface *pieceWhiteRook = NULL, *pieceBlackRook = NULL;
	SDL_Surface *pieceWhiteBishop = NULL, *pieceBlackBishop = NULL;
	SDL_Surface *pieceBlackKnight = NULL, *pieceWhiteKnight = NULL;
	SDL_Surface *pieceBlackQueen = NULL, *pieceWhiteQueen = NULL;


	SDL_Rect posWhiteCase, posBlackCase, posMenu, coordCaseSelect, pos2, posCaseColored;
	SDL_Event event;

	int i,j,offset = 80; 
	long destX, destY, mouseX, mouseY; 
	int gameMode, caseSelect = 0; 
	int coords = 0;
	//////////////////////////////////

	struct chessBoard *board = initBoard();
	//	
	SDL_Init(SDL_INIT_VIDEO);

	screen = SDL_SetVideoMode(1024, 768, 32, SDL_HWSURFACE | SDL_DOUBLEBUF ); 
	SDL_WM_SetCaption("APICHESS - API", NULL);

	menu = IMG_Load("img/chess_init.jpg");
	posMenu.x = 0;
	posMenu.y = 0;


	/////////////// Pics loading ///////////

	whiteCase = SDL_LoadBMP("img/caseBlanche2.bmp");
	blackCase = SDL_LoadBMP("img/caseNoire2.bmp");
	redCase = SDL_LoadBMP("img/caseSelectionnee.bmp");
	caseColored = SDL_LoadBMP("img/caseSelectionnee.bmp");

	////////////////////////////////////////////////////////////////////////////

	SDL_SetAlpha(redCase, SDL_SRCALPHA, 128); //set the color more transparent

	pieceBlackBishop = SDL_LoadBMP("img/pieceFouNoir.bmp");
	pieceWhiteBishop = SDL_LoadBMP("img/pieceFouBlanc.bmp");
	pieceBlackQueen = SDL_LoadBMP("img/pieceDameNoir.bmp");
	pieceWhiteQueen = SDL_LoadBMP("img/pieceDameBlanc.bmp");
	pieceBlackKnight = SDL_LoadBMP("img/pieceCavalierNoir.bmp");
	pieceWhiteKnight = SDL_LoadBMP("img/pieceCavalierBlanc.bmp");

	pieceBlackKing = SDL_LoadBMP("img/pieceRoiNoir.bmp");
	pieceWhiteKing = SDL_LoadBMP("img/pieceRoiBlanc.bmp");
	pieceBlackRook = SDL_LoadBMP("img/pieceTourNoir.bmp");
	pieceWhiteRook = SDL_LoadBMP("img/pieceTourBlanc.bmp");
	pieceBlackPawn = SDL_LoadBMP("img/piecePionNoir.bmp");
	pieceWhitePawn = SDL_LoadBMP("img/piecePionBlanc.bmp");


	/////// Hide the pink Background from the pics
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
	// init vid  ttf//////

	SDL_EnableKeyRepeat(10, 10); 
	TTF_Init();  
	SDL_Surface *message = NULL, *messageIndicator = NULL;
	TTF_Font *font, *font2;
	SDL_Color textColor = { 0, 0, 0, 42 }; 

	SDL_Rect positionMessage, positionMessageIndicator;
	positionMessage.x = 50;
	positionMessage.y = 0;

	font = TTF_OpenFont( "Dbbrnms.ttf", 34 );
	font2 = TTF_OpenFont( "Dbbrnms.ttf", 22 );
	message = TTF_RenderText_Blended(font, "Selectionnez la pièce avec le clic gauche et déplacez la avec le clic droit", textColor);
	////////////
	void displayIndicatorPosition(int player)
	{
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



	SDL_ShowCursor(SDL_ENABLE);  
	//////////
	void coloreCase(int abscisse, int ordonnee)   //////////////// Color the  case with X, Y coordonate;
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
		//printf("%d",pos2.x);

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
		mouseX = event.button.x; 
		mouseY = event.button.y;
		mouseX = mouseX / 80;    
		srcX = srcX+offset;
		if(srcX < 80 && srcY > 0)
			srcX = 1;
		else
			srcX = srcX/80;

		if (mouseY>=offset)       
		{                  
			mouseY = (mouseY-offset) / 80;
			srcY = srcY/80;
			srcY = srcY;
		}
		else
		{
			mouseY = -1; 
		}

		if ((mouseX < 8) && (mouseX >= 0) && (mouseY < 8) && (mouseY >= 0)) 
		//if in therange of the board
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
	gameMode = 0;
	int continuer = 1;
	while (continuer==1)
	{	
		SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
		SDL_BlitSurface(menu, NULL, screen, &posMenu);
		SDL_Flip(screen);
		while(SDL_PollEvent(&event)){
		switch(event.type)
		{
			case SDL_QUIT:
				continuer = 0;
				TTF_CloseFont(font);
				TTF_Quit();
				SDL_Quit();
				exit(0);
				break;
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym)
				{
					case SDLK_ESCAPE: //quit
						continuer = 0;
						TTF_CloseFont(font);
						TTF_Quit();
						SDL_Quit();
						exit(0);
						break;
					case SDLK_KP1: // JcJ
						gameMode = 1;
						continuer = 0;
						break;
					case SDLK_KP2: // JcAI
						gameMode = 2;
						continuer = 0;
						break;
					default:
						;
				}
				break;
			default:
				;
		}

		}
		}
		event.type = SDL_NOEVENT;

	SDL_FreeSurface(menu);
	////////

	printMap(board);
	int player = -1;
	coords = 0; 
	int coorde = 0;
	int endgame = -1;
	int turn;
	int pt = -1;
	while (endgame != 1){
		turn = board->turn;
		player = (turn%2) + 1;
		displayIndicatorPosition(player); 
		message = TTF_RenderText_Blended(font, "Selectionnez la pièce avec le clic gauche et déplacez la avec le clic droit", textColor);
		SDL_BlitSurface(message, NULL, screen, &positionMessage);
		SDL_FreeSurface(message);
		SDL_Delay(20);
		if (gameMode == 2 && player == 2) {
			struct AIDatas *datas = createDatas(board);
			int *tab = alpha_beta_call(board, datas);
			printf("coords : %d\n", *(tab+1));
			pt = move(board,*(tab+1), *(tab+2));
			if (pt == -1)
				printf("impossible move\n");
			else if (pt == 1)
				endgame = 1;
			else {
				board->turn = turn + 1;
				printMap(board);
				printf("white player : %d\n", getValue(board, 0));
				printf("black player : %d\n", getValue(board, 1));
			}
		}else{

			while(SDL_PollEvent(&event)){ 
				switch(event.type) // choice of the action depending to the event
				{
					case SDL_QUIT:  
						endgame = 1;
						TTF_CloseFont(font);
						TTF_Quit();
						SDL_Quit();
						exit(0);
						break;
					case SDL_KEYDOWN:     
						switch(event.key.keysym.sym)//keyboard
						{
							case SDLK_ESCAPE: //Button ESC
								endgame = 1;
								TTF_CloseFont(font);
								TTF_Quit();
								SDL_Quit();
								exit(0);
								break;
							default:
								;
						}
					
					case SDL_MOUSEBUTTONUP:  // mousse click case 
						if (event.button.button == SDL_BUTTON_LEFT) //left
						{
							coords = coloreCaseSelectionne();
							//printf("coords = %d", coords);
						}
						if (event.button.button == SDL_BUTTON_RIGHT) //right
						{
							destX =  event.button.x; 
							destY =  event.button.y;
							destX =  destX+offset  ;    
							if (destY>=offset)         
							{                  
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
							coorde =  (destX) + (destY*10) ; 
							coorde = coorde;
							coorde = coorde;
							//printf("coorde = %d",coorde);
						}
						break;
					default:
						;
				}
			}
			event.type = SDL_NOEVENT;
			if(coorde && coords){
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
						printf("white player : %d\n", getValue(board, 0));
						printf("black player : %d\n", getValue(board, 1));
						positionMessageIndicator.x = 700;
						positionMessageIndicator.y = 160;

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
		/////////////////////Display White case //////////////////////////////////////// 
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
		if (caseSelect)   //Display when left click
		{
			SDL_BlitSurface(redCase, NULL, screen, &coordCaseSelect);
		}
		displayIndicatorPosition(player);
		SDL_Flip(screen); //screen update	

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
	SDL_FreeSurface(whiteCase); //Free the memory
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
