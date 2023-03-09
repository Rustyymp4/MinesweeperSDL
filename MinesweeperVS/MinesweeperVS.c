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

#define ROUGE "\x1b[31m"
#define VERT "\x1b[32m"
#define JAUNE "\x1b[33m"
#define BLEU "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN "\x1b[36m"
#define COLOR_RESET "\x1b[0m"




#define wSize 16
#define hSize 16
#define mines 35

int remaining = hSize * wSize - mines;

const char* l[wSize] = { " 0]"," 1]"," 2]"," 3]"," 4]"," 5]"," 6]"," 7]"," 8]"," 9]","10]","11]","12]","13]","14]","15]" };

typedef struct Cell {
	const char* display;
	int bomb;
	int nearby;
	int isSelected;
	int isFlagged;
}Cell;




//i == ligne
//j == collone

void check(int inputI, int inputJ, struct Cell grid[16][16], SDL_Texture* colors[9]) {

	///On creuse les cases d'a cote

 	grid[inputI][inputJ].display = colors[grid[inputI][inputJ].nearby];


	if (grid[inputI][inputJ].bomb == 1) {
		return;
	}

	if (grid[inputI][inputJ].nearby > 0) {
		grid[inputI][inputJ].display = colors[grid[inputI][inputJ].nearby];
		grid[inputI][inputJ].isSelected = 1;
		remaining--;
		return;
	}

	if (wSize >= inputI && inputI > 0 && grid[inputI - 1][inputJ].isSelected == 0) {
		check(inputI - 1, inputJ, grid, colors);
		if (hSize >= inputJ && inputJ > 0 && grid[inputI - 1][inputJ - 1].isSelected == 0) {
			grid[inputI][inputJ].isSelected = 1;
			remaining--;
			check(inputI - 1, inputJ - 1, grid, colors);
		}
		if (0 <= inputJ && inputJ < hSize - 1 && grid[inputI - 1][inputJ + 1].isSelected == 0) {
			grid[inputI][inputJ].isSelected = 1;
			remaining--;
			check(inputI - 1, inputJ + 1, grid, colors);
		}
	}

	if (hSize >= inputJ && inputJ > 0 && grid[inputI][inputJ - 1].isSelected == 0) {
		grid[inputI][inputJ].isSelected = 1;
		remaining--;
		check(inputI, inputJ - 1, grid, colors);
		if (inputI <= wSize - 1 && grid[inputI + 1][inputJ - 1].isSelected == 0) {
			grid[inputI][inputJ].isSelected = 1;
			remaining--;
			check(inputI + 1, inputJ - 1, grid, colors);
		}
	}

	if (0 <= inputI && inputI < wSize - 1 && grid[inputI + 1][inputJ].isSelected == 0) {
		grid[inputI][inputJ].isSelected = 1;
		remaining--;
		check(inputI + 1, inputJ, grid, colors);
		if (0 <= inputJ && inputJ < hSize - 1 && grid[inputI + 1][inputJ + 1].isSelected == 0) {
			grid[inputI][inputJ].isSelected = 1;
			remaining--;
			check(inputI + 1, inputJ + 1, grid, colors);
		}
	}

	if (0 <= inputJ && inputJ < hSize - 1 && grid[inputI][inputJ + 1].isSelected == 0) {
		grid[inputI][inputJ].isSelected = 1;
		remaining--;
		check(inputI, inputJ + 1, grid,colors);
	}

}



/// <gridDIsplayInit>
/// .display = [#] par defaut, [>] quand isFlagged == 0, [ ] quand isSelected + nearby + bomb + isFlagged == 0, [*] quand winStatus ou loseStatus == 1
/// .bomb = 0 par defaut, si == 1 alors une bombe est presente, affecte .display quand winStatus ou loseStatus == 1
/// .nearby = 0 par defaut, peut etre aller de 0 a 8 selon les bombes environnantes, affecte .display quand n'est pas egal a 0
/// .isSelected = 0 par defaut, sert a ne pas pouvoir rejouer sur la meme case, sert a ne pas pouvoir avoir de bombe sur la premiere case, affecte .bombe lors de l'initiallisation
/// .isFlagged = 0 par defaut, sert a marquer une case qui va devenir injouable jusqu'a ce que le drappeau soit enleve, affecte .display lorsqu'egal a 1
/// </gridDIsplayInit>


void gaming() {

	char choixRF = "";
	Cell grid[wSize][hSize];



	///Initalisation du display 

	int width = 800;
	int height = 800;
	int w_case = width / wSize;
	int h_case = height / hSize;

	SDL_Window* window = SDL_CreateWindow("Display", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

	///Initialisation des images

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
	Flag = SDL_LoadBMP("Bomb.bmp");
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


	while (winStatus == 0 && loseStatus == 0) {

		choixRF = "";

		for (i = 0; i < wSize; i++) {
			for (j = 0; j < hSize; j++) {
				int x = 0 + i * w_case;
				int y = 0 + j * h_case;
				SDL_Rect rect = { x, y, w_case, h_case };
				SDL_RenderCopy(renderer, grid[i][j].display, NULL, &rect);
			}
		}

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

		///On lance la fonction de check




		///On met le numero et tout

		if (choixRF == 'r' && grid[inputI][inputJ].isFlagged == 0 && grid[inputI][inputJ].nearby == 0) {
			check(inputI, inputJ + 1, grid, colors);
		}

		if (choixRF == 'r' && grid[inputI][inputJ].isFlagged == 0 && grid[inputI][inputJ].nearby != 0) {
				grid[inputI][inputJ].display = colors[grid[inputI][inputJ].nearby];
		}


		///On empeche de selectionner des cases avec un drappeau

		if (choixRF == 'r' && grid[inputI][inputJ].isFlagged == 1) {

		}

		///On mets le drappeau a la case selectionnee

		if (choixRF == 'f' && grid[inputI][inputJ].isFlagged == 0) {
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
			printf("Le drappeau a bien ete enleve\n");
		}

		///Defaite

		if (grid[inputI][inputJ].bomb == 1 && choixRF == 'r') {
				for (i = 0; i < wSize; i++) {
					for (j = 0; j < hSize; j++) {


						if (grid[i][j].bomb == 1) {
							grid[i][j].display = textureBomb;
						}

						if (grid[i][j].bomb == 0 && grid[i][j].isFlagged == 1) {
							grid[i][j].display = textureBomb;
						}

						int x = 0 + i * w_case;
						int y = 0 + j * h_case;
						SDL_Rect rect = { x, y, w_case, h_case };
						SDL_RenderCopy(renderer, grid[i][j].display, NULL, &rect);
						abort;
					}
				}
		}

		///Condition de victoire 

		if (remaining < 0) {
			
			for (i = 0; i < wSize; i++) {
				for (j = 0; j < hSize; j++) {

					grid[i][j].display = colors[grid[i][j].nearby];

					if (grid[i][j].bomb == 1) {
						grid[i][j].display = textureBomb;
					}

					if (grid[i][j].bomb == 0 && grid[i][j].isFlagged == 1) {
						grid[i][j].display = textureBomb;
					}
					int x = 0 + i * w_case;
					int y = 0 + j * h_case;
					SDL_Rect rect = { x, y, w_case, h_case };
					SDL_RenderCopy(renderer, grid[i][j].display, NULL, &rect);
					printf("on imprime le tableau gagner");
					abort;
				}
			}
			
		}

	}



}



/// <main>
/// Ici on lance le programme,
///		-On demande l'input
///		-On initialise la grid et pose les bombes
///		Si winStatus ou loseStatus == 0
///			-On joue un tour
///			-On check les bombes environnantes a la case selectionne et aux possibles case .nearby == 0 environnantes
///		Si winStatus == 1
///			-On print un message de victoire
///		Si loseStatus == 1
///			-On print un message de defaite
/// </main>

int main() {

//Initialisation

	srand(time(NULL));

	//Execution
	while(winStatus == 0 && loseStatus == 0 ){
		gaming();
		srand(time(NULL));
		
	}

	

	

	//Destruction
	SDL_Quit();

}
