// Le projet avec flavieng la.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <SDL.h>
#include <SDL_image.h>
#include <stdlib.h>
#include <stdio.h>


/// <initialisation des variables>
/// Ici on initiallise toutes les variables universelles au programme
/// </initialisation des variables>


int i, j;
int winStatus = 0;
int loseStatus = 0;
int inputI = 17;
int inputJ = 17;
int checkI, checkJ;
int flags = 0;
int** grid;
int wSize, hSize, mines, winWSize, winHSize = 0;



#define wSize 16
#define hSize 16
#define mines 35

int remaining = hSize * wSize - mines;


typedef struct Cell {
	const char* display;
	int bomb;
	int nearby;
	int isSelected;
	int isFlagged;
}Cell;




//i == ligne
//j == collone


void choixDif() {

	int difficulty = 0;
	SDL_Window* window = SDL_CreateWindow("Display", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, SDL_WINDOW_RESIZABLE, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	SDL_Surface* DSS = NULL;
	SDL_Texture* textureDSS = NULL;
	DSS = SDL_LoadBMP("DSS.bmp");
	textureDSS = SDL_CreateTextureFromSurface(renderer, DSS);
	SDL_FreeSurface(DSS);

	SDL_Rect DSSRect = { 0, 200, 800, 400 };
	SDL_RenderCopy(renderer, textureDSS, NULL, &DSSRect);


	while (difficulty == 0) {

		SDL_RenderPresent(renderer);
		SDL_Event event;
		SDL_WaitEvent(&event);

		if (event.type == SDL_KEYDOWN) {

			if (event.key.keysym.scancode == SDL_SCANCODE_1 || event.key.keysym.scancode == SDL_SCANCODE_KP_1)
			{
				SDL_DestroyRenderer(renderer);
				SDL_DestroyWindow(window);
				difficulty = 1;
			}else if (event.key.keysym.scancode == SDL_SCANCODE_2 || event.key.keysym.scancode == SDL_SCANCODE_KP_2){
				SDL_DestroyRenderer(renderer);
				SDL_DestroyWindow(window);
				difficulty = 2;
			}else if (event.key.keysym.scancode == SDL_SCANCODE_3 || event.key.keysym.scancode == SDL_SCANCODE_KP_3){
				SDL_DestroyRenderer(renderer);
				SDL_DestroyWindow(window);
				difficulty = 3;
			}
			else{
				
				SDL_Surface* No = NULL;
				SDL_Texture* textureNo = NULL;
				No = SDL_LoadBMP("Gun.bmp");
				textureNo = SDL_CreateTextureFromSurface(renderer, No);
				SDL_FreeSurface(No);

				SDL_Rect NoRect = { 0, 200, 800, 400 };
				SDL_RenderCopy(renderer, textureNo, NULL, &NoRect);
			}
		}	

	}
	

}

void check(int inputI, int inputJ, struct Cell grid[16][16], SDL_Texture* colors[9]) {

	///On creuse les cases d'a cote

 	grid[inputI][inputJ].display = colors[grid[inputI][inputJ].nearby];
	grid[inputI][inputJ].isSelected = 1;



	if (grid[inputI][inputJ].bomb == 1) {
		return;
	}

	if (grid[inputI][inputJ].nearby > 0) {
		grid[inputI][inputJ].display = colors[grid[inputI][inputJ].nearby];
		grid[inputI][inputJ].isSelected = 1;
		return;
	}

	if (wSize >= inputI && inputI > 0 && grid[inputI - 1][inputJ].isSelected == 0) {
		check(inputI - 1, inputJ, grid, colors);
		if (hSize >= inputJ && inputJ > 0 && grid[inputI - 1][inputJ - 1].isSelected == 0) {
			grid[inputI][inputJ].isSelected = 1;
			check(inputI - 1, inputJ - 1, grid, colors);
		}
		if (0 <= inputJ && inputJ < hSize - 1 && grid[inputI - 1][inputJ + 1].isSelected == 0) {
			grid[inputI][inputJ].isSelected = 1;
			check(inputI - 1, inputJ + 1, grid, colors);
		}
	}

	if (hSize >= inputJ && inputJ > 0 && grid[inputI][inputJ - 1].isSelected == 0) {
		grid[inputI][inputJ].isSelected = 1;
		check(inputI, inputJ - 1, grid, colors);
		if (inputI < wSize - 1 && grid[inputI + 1][inputJ - 1].isSelected == 0) {
			grid[inputI][inputJ].isSelected = 1;
			check(inputI + 1, inputJ - 1, grid, colors);
		}
	}

	if (0 <= inputI && inputI < wSize - 1 && grid[inputI + 1][inputJ].isSelected == 0) {
		grid[inputI][inputJ].isSelected = 1;
		check(inputI + 1, inputJ, grid, colors);
		if (0 <= inputJ && inputJ < hSize - 1 && grid[inputI + 1][inputJ + 1].isSelected == 0) {
			grid[inputI][inputJ].isSelected = 1;
			check(inputI + 1, inputJ + 1, grid, colors);
		}
	}

	if (0 <= inputJ && inputJ < hSize - 1 && grid[inputI][inputJ + 1].isSelected == 0) {
		grid[inputI][inputJ].isSelected = 1;
		check(inputI, inputJ + 1, grid,colors);
	}

}


void gaming() {

	char choixRF = "";
	Cell grid[wSize][hSize];



	///Initalisation du display 

	int width = 800;
	int height = 800;
	int w_case = width / wSize;
	int h_case = height / hSize;

	SDL_Window* window = SDL_CreateWindow("Display", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, SDL_WINDOW_RESIZABLE, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	///Initialisation des images

	SDL_Surface* GOS1 = NULL;
	SDL_Texture* textureGOS1 = NULL;
	GOS1 = SDL_LoadBMP("GOS1.bmp");
	textureGOS1 = SDL_CreateTextureFromSurface(renderer, GOS1);
	SDL_FreeSurface(GOS1);

	SDL_Surface* GOS2 = NULL;
	SDL_Texture* textureGOS2 = NULL;
	GOS2 = SDL_LoadBMP("GOS2.bmp");
	textureGOS2 = SDL_CreateTextureFromSurface(renderer, GOS2);
	SDL_FreeSurface(GOS2);

	SDL_Surface* GOS3 = NULL;
	SDL_Texture* textureGOS3 = NULL;
	GOS3 = SDL_LoadBMP("GOS3.bmp");
	textureGOS3 = SDL_CreateTextureFromSurface(renderer, GOS3);
	SDL_FreeSurface(GOS3);

	SDL_Surface* GOS4 = NULL;
	SDL_Texture* textureGOS4 = NULL;
	GOS4 = SDL_LoadBMP("GOS4.bmp");
	textureGOS4 = SDL_CreateTextureFromSurface(renderer, GOS4);
	SDL_FreeSurface(GOS4);

	SDL_Surface* VS1 = NULL;
	SDL_Texture* textureVS1 = NULL;
	VS1 = SDL_LoadBMP("VS1.bmp");
	textureVS1 = SDL_CreateTextureFromSurface(renderer, VS1);
	SDL_FreeSurface(VS1);

	SDL_Surface* VS2 = NULL;
	SDL_Texture* textureVS2 = NULL;
	VS2 = SDL_LoadBMP("VS2.bmp");
	textureVS2 = SDL_CreateTextureFromSurface(renderer, VS2);
	SDL_FreeSurface(VS2);

	SDL_Surface* VS3 = NULL;
	SDL_Texture* textureVS3 = NULL;
	VS3 = SDL_LoadBMP("VS3.bmp");
	textureVS3 = SDL_CreateTextureFromSurface(renderer, VS3);
	SDL_FreeSurface(VS3);

	SDL_Surface* VS4 = NULL;
	SDL_Texture* textureVS4 = NULL;
	VS4 = SDL_LoadBMP("VS4.bmp");
	textureVS4 = SDL_CreateTextureFromSurface(renderer, VS4);
	SDL_FreeSurface(VS4);

	SDL_Surface* VS5 = NULL;
	SDL_Texture* textureVS5 = NULL;
	VS5 = SDL_LoadBMP("VS5.bmp");
	textureVS5 = SDL_CreateTextureFromSurface(renderer, VS5);
	SDL_FreeSurface(VS5);

	SDL_Surface* VS6 = NULL;
	SDL_Texture* textureVS6 = NULL;
	VS6 = SDL_LoadBMP("VS6.bmp");
	textureVS6 = SDL_CreateTextureFromSurface(renderer, VS6);
	SDL_FreeSurface(VS6);

	SDL_Surface* Tile = NULL;
	SDL_Texture* textureTile = NULL;
	Tile = SDL_LoadBMP("Tiles.bmp");
	textureTile = SDL_CreateTextureFromSurface(renderer, Tile);
	SDL_FreeSurface(Tile);

	SDL_Surface* Ground = NULL;
	SDL_Texture* textureGround = NULL;
	Ground = SDL_LoadBMP("Ground.bmp");
	textureGround = SDL_CreateTextureFromSurface(renderer, Ground);
	SDL_FreeSurface(Ground);

	SDL_Surface* Bomb = NULL;
	SDL_Texture* textureBomb = NULL;
	Bomb = SDL_LoadBMP("Bomb.bmp");
	textureBomb = SDL_CreateTextureFromSurface(renderer, Bomb);
	SDL_FreeSurface(Bomb);

	SDL_Surface* Flag = NULL;
	SDL_Texture* textureFlag = NULL;
	Flag = SDL_LoadBMP("Flag.bmp");
	textureFlag = SDL_CreateTextureFromSurface(renderer, Flag);
	SDL_FreeSurface(Flag);

	SDL_Surface* Nearby1 = NULL;
	SDL_Texture* textureNearby1 = NULL;
	Nearby1 = SDL_LoadBMP("Nearby1.bmp");
	textureNearby1 = SDL_CreateTextureFromSurface(renderer, Nearby1);
	SDL_FreeSurface(Nearby1);

	SDL_Surface* Nearby2 = NULL;
	SDL_Texture* textureNearby2 = NULL;
	Nearby2 = SDL_LoadBMP("Nearby2.bmp");
	textureNearby2 = SDL_CreateTextureFromSurface(renderer, Nearby2);
	SDL_FreeSurface(Nearby2);

	SDL_Surface* Nearby3 = NULL;
	SDL_Texture* textureNearby3 = NULL;
	Nearby3 = SDL_LoadBMP("Nearby3.bmp");
	textureNearby3 = SDL_CreateTextureFromSurface(renderer, Nearby3);
	SDL_FreeSurface(Nearby3);

	SDL_Surface* Nearby4 = NULL;
	SDL_Texture* textureNearby4 = NULL;
	Nearby4 = SDL_LoadBMP("Nearby4.bmp");
	textureNearby4 = SDL_CreateTextureFromSurface(renderer, Nearby4);
	SDL_FreeSurface(Nearby4);

	SDL_Surface* Nearby5 = NULL;
	SDL_Texture* textureNearby5 = NULL;
	Nearby5 = SDL_LoadBMP("Nearby5.bmp");
	textureNearby5 = SDL_CreateTextureFromSurface(renderer, Nearby5);
	SDL_FreeSurface(Nearby5);

	SDL_Surface* Nearby6 = NULL;
	SDL_Texture* textureNearby6 = NULL;
	Nearby6 = SDL_LoadBMP("Nearby6.bmp");
	textureNearby6 = SDL_CreateTextureFromSurface(renderer, Nearby6);
	SDL_FreeSurface(Nearby6);

	SDL_Surface* Nearby7 = NULL;
	SDL_Texture* textureNearby7 = NULL;
	Nearby7 = SDL_LoadBMP("Nearby7.bmp");
	textureNearby7 = SDL_CreateTextureFromSurface(renderer, Nearby7);
	SDL_FreeSurface(Nearby7);

	SDL_Surface* Nearby8 = NULL;
	SDL_Texture* textureNearby8 = NULL;
	Nearby8 = SDL_LoadBMP("Nearby7.bmp");
	textureNearby8 = SDL_CreateTextureFromSurface(renderer, Nearby8);
	SDL_FreeSurface(Nearby8);

	SDL_Texture* colors[9] =
	{
		textureGround,
		textureNearby1,
		textureNearby2,
		textureNearby3,
		textureNearby4,
		textureNearby5,
		textureNearby6,
		textureNearby7,
		textureNearby8

	};


	for (i = 0; i < wSize; i++) {
		for (j = 0; j < hSize; j++) {
			int x = 0 + i * w_case;
			int y = 0 + j * h_case;
			grid[i][j].display = textureTile;
			grid[i][j].bomb = 0;
			grid[i][j].nearby = 0;
			grid[i][j].isSelected = 0;
			grid[i][j].isFlagged = 0; 
			SDL_Rect rect = { x, y, w_case, h_case };
			SDL_RenderCopy(renderer, grid[i][j].display, NULL, &rect);
		}
	}




	///Initialisation du jeu 


		///Initialisation des bombes

	int i, j, count = 0;
	while (count < mines) {


		i = rand() % wSize;
		j = rand() % hSize;
		if (grid[i][j].bomb != 1) {
			grid[i][j].bomb = 1;

			///On fait les nearby des cases aux alentours

			//centre
			grid[i][j].nearby++;

			//bas droite
			if (i < 15 && j < 15) {
				grid[i + 1][j + 1].nearby++;
			}

			//droite
			if (i < 15) {
				grid[i + 1][j].nearby++;
			}

			//haut droite
			if (i < 15 && j > 0) {
				grid[i + 1][j - 1].nearby++;
			}

			//bas
			if (j < 15) {
				grid[i][j + 1].nearby++;
			}

			//haut
			if (j > 0) {
				grid[i][j - 1].nearby++;
			}

			//haut gauche
			if (j > 0 && i > 0) {
				grid[i - 1][j - 1].nearby++;
			}

			//gauche
			if (i > 0) {
				grid[i - 1][j].nearby++;
			}

			//bas gauche
			if (j < 15 && i > 0) {
				grid[i - 1][j + 1].nearby++;
			}

			count++;

		}
	}

	///Boucle de jeu


	while (1) {


		choixRF = "";
		remaining = hSize * wSize - mines;

		for (i = 0; i < wSize; i++) {
			for (j = 0; j < hSize; j++) {
				if (grid[i][j].display != textureFlag && grid[i][j].display != textureTile) {
					remaining--;
				}
				int x = 0 + i * w_case;
				int y = 0 + j * h_case;
				SDL_Rect rect = { x, y, w_case, h_case };
				SDL_RenderCopy(renderer, grid[i][j].display, NULL, &rect);
			}
		}

		printf("%d spots left to dig!\n" ,remaining);
		SDL_RenderPresent(renderer);


		//EVENT
		SDL_Event event;
		SDL_WaitEvent(&event);

		if (event.type == SDL_MOUSEBUTTONDOWN) {
			if (event.button.button == SDL_BUTTON_LEFT) {
				inputI = event.button.x;
				inputJ = event.button.y;
				inputJ = inputJ / h_case;
				inputI = inputI / w_case;
				choixRF = 'r';
			}
			else if (event.button.button == SDL_BUTTON_RIGHT) {
				inputI = event.button.x;
				inputJ = event.button.y;
				inputJ = inputJ / h_case;
				inputI = inputI / w_case;
				choixRF = 'f';
			}
		}


		///Les inputs

		if (choixRF == 'r' && grid[inputI][inputJ].isFlagged == 0 && grid[inputI][inputJ].nearby == 0) {
			check(inputI, inputJ, grid, colors);
		}

		if (choixRF == 'r' && grid[inputI][inputJ].isFlagged == 0 && grid[inputI][inputJ].nearby != 0) {
			grid[inputI][inputJ].display = colors[grid[inputI][inputJ].nearby];
		}


		///On mets le drappeau a la case selectionnee

		if (choixRF == 'f' && grid[inputI][inputJ].isFlagged == 0 && grid[inputI][inputJ].isSelected == 0) {
			grid[inputI][inputJ].isFlagged = 1;
			flags++;
			grid[inputI][inputJ].display = textureFlag;
			choixRF = ' ';
		}

		///On enleve le drappeau de la case selectionnee

		if (choixRF == 'f' && grid[inputI][inputJ].isFlagged == 1) {
			grid[inputI][inputJ].isFlagged = 0;
			grid[inputI][inputJ].display = textureTile;
			flags--;
		}

		///Defaite



		while (grid[inputI][inputJ].bomb == 1 && choixRF == 'r' && grid[inputI][inputJ].isFlagged == 0) {

			SDL_Rect rect = { 0, 200, 800, 400 };
			SDL_RenderCopy(renderer, textureGOS1, NULL, &rect);
			SDL_RenderPresent(renderer);
			SDL_Delay(200);

			SDL_Rect rect2 = { 0, 200, 800, 400 };
			SDL_RenderCopy(renderer, textureGOS2, NULL, &rect2);
			SDL_RenderPresent(renderer);
			SDL_Delay(200);

			SDL_Rect rect3 = { 0, 200, 800, 400 };
			SDL_RenderCopy(renderer, textureGOS3, NULL, &rect3);
			SDL_RenderPresent(renderer);
			SDL_Delay(200);

			SDL_Rect rect4 = { 0, 200, 800, 400 };
			SDL_RenderCopy(renderer, textureGOS4, NULL, &rect4);
			SDL_RenderPresent(renderer);
			SDL_Delay(200);
			
			SDL_Event event;
			SDL_WaitEvent(&event);

			if (event.type == SDL_KEYDOWN) {

				if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
				{
					SDL_DestroyRenderer(renderer);
					SDL_DestroyWindow(window);
					abort;
					
				}

				if (event.key.keysym.scancode == SDL_SCANCODE_SPACE)
				{
					SDL_DestroyRenderer(renderer);
					SDL_DestroyWindow(window);
					gaming();
				}
			}

		}

		///Condition de victoire 

		if (remaining == 0) {
			
			SDL_Rect rect = { 0, 200, 800, 400 };
			SDL_RenderCopy(renderer, textureVS1, NULL, &rect);
			SDL_RenderPresent(renderer);
			SDL_Delay(75);

			SDL_Rect rect2 = { 0, 200, 800, 400 };
			SDL_RenderCopy(renderer, textureVS2, NULL, &rect2);
			SDL_RenderPresent(renderer);
			SDL_Delay(75);

			SDL_Rect rect3 = { 0, 200, 800, 400 };
			SDL_RenderCopy(renderer, textureVS3, NULL, &rect3);
			SDL_RenderPresent(renderer);
			SDL_Delay(75);

			SDL_Rect rect4 = { 0, 200, 800, 400 };
			SDL_RenderCopy(renderer, textureVS4, NULL, &rect4);
			SDL_RenderPresent(renderer);
			SDL_Delay(75);

			SDL_Rect rect5 = { 0, 200, 800, 400 };
			SDL_RenderCopy(renderer, textureVS5, NULL, &rect5);
			SDL_RenderPresent(renderer);
			SDL_Delay(75);

			SDL_Rect rect6 = { 0, 200, 800, 400 };
			SDL_RenderCopy(renderer, textureVS6, NULL, &rect6);
			SDL_RenderPresent(renderer);
			SDL_Delay(75);

			SDL_Event event;
			SDL_WaitEvent(&event);

			if (event.type == SDL_KEYDOWN) {

				if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
				{
					SDL_DestroyRenderer(renderer);
					SDL_DestroyWindow(window);
					abort;

				}

				if (event.key.keysym.scancode == SDL_SCANCODE_SPACE)
				{
					SDL_DestroyRenderer(renderer);
					SDL_DestroyWindow(window);
					gaming();
				}
			}
			
		}

	}

}


int main(SDL_Renderer* renderer, SDL_Window* window) {

//Initialisation

	srand(time(NULL));
	choixDif();
	//Execution
	while(winStatus == 0 && loseStatus == 0){
		gaming();
		srand(time(NULL));
		
	}

	//Destruction
	SDL_Quit;

}
