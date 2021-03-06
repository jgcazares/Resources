// Example program:
// Using SDL2 to create an application window

#if defined (_WIN32) || (_WIN64)

#include "SDL.h"
#include  "SDL_image.h"
#include "SDL_mixer.h"

#endif

#if defined (_WIN32) || (_WIN64)
#include <direct.h>
#define getcwd_getcwd
#endif


#if defined (__APPLE__)

#include SDL2/SDL2.h
#include SDL2_image/SDL_image.h
#include SDL2_mixer/SDL_mixer.h

#endif

#if defined (__linux__)

#include SDL2/SDL2.h
#include SDL2/SDL_image.h
#include SDL/SDL_image.h

#endif

#if defined (__linux__)

#include <unistd.h>

#endif


#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

//variables for the backgrounds speed
int bkgdSpeed = 100;

SDL_Rect bkgd1Pos, bkgd2Pos;

//background floats
float b1pos_x = 0, b1pos_y = 0;
float b2pos_x = 0, b2pos_y = -786;

//code for framerate independence
float deltaTime = 0.0;
int thisTime = 0;
int lastTime = 0;

//MOVE THE BAKCGROUND
void UpdateBackground(float deltaTime) {

	//Update the bkgd 1
	b1pos_y += (bkgdSpeed * 1) * deltaTime;

	//set the new bkgd10 poition
	bkgd1Pos.y = (int)(b1pos_y + 0.5f);

	//reset when off the bottom of the screen
	if (bkgd1Pos.y >= 768)
	{

		bkgd1Pos.y = -768;
		b1pos_y = bkgd1Pos.y;


	}


	//Update the bkgd 2
	b2pos_y += (bkgdSpeed * 1) * deltaTime;

	//set the new bkgd10 poition
	bkgd2Pos.y = (int)(b2pos_y + 0.5f);

	//reset when off the bottom of the screen
	if (bkgd2Pos.y >= 768)
	{

		bkgd1Pos.y = -768;
		b2pos_y = bkgd2Pos.y;


	}

}


////////*****************joystick dead zone*********************
//analog stick dead zone
const int JOYSTICK_DEAD_ZONE = 8000;

//joystick direction vars
float xDir, yDir;

//create sedl rectangle for the two player graphic
SDL_Rect cursorPos, activePos;

//cursor float movement
float pos_X, pos_Y;

//cursor speed
int cursorSpeed = 400;

void moveCursor(const SDL_ControllerAxisEvent){

	if(event.which == 0){
		if(event.axis == 0){

			if(event.value < -JOYSTICK_DEAD_ZONE){
				xDir = -1.0f;
			}else if(event.value > JOYSTICK_DEAD_ZONE){
				xDir = 1.0f;
			}else{
				xDir = 0.0f;
			}
		}

		if(event.axis == 1){

			if(event.value < -JOYSTICK_DEAD_ZONE){
				yDir = -1.0f;
			}else if(event.value > JOYSTICK_DEAD_ZONE){
				yDir = 1.0f;
			}else{
				yDir = 0.0f;
			}

		}



	}


}

void UpdateCursor(float deltaTime){
	//update the cursor
	pos_X += (cursorSpeed * xDir) * deltaTime;
	pos_Y += (cursorSpeed * yDir) * deltaTime;

	cursorPos.x = (int)(pos_X + 0.5f);
	cursorPos.y = (int)(pos_Y + 0.5f);

	activePos.x = cursorPos.x;
	activePos.y = cursorPos.y;

	if(cursorPos.x < 0){
		cursorPos.x = 0;
		pos_X = cursorPos.x;

	}

	if(cursorPos.x > 1024 - cursorPos.w){
		cursorPos.x = 1024 - cursorPos.w;
		pos_X = cursorPos.x;
	}

	if(cursorPos.y < 0){
		cursorPos.y = 0;
		pos_Y = cursorPos.y;
	}

	if(cursorPos.y > 768 - cursorPos.h){
		cursorPos.y = 768 - cursorPos.h;
		pos_Y = cursorPos.y;
	}

}


//variables for all the menus button over
bool players1Over = false, players2Over = false, instructionsOver = false,
		quitOver = false, menuOver = false, playOver = false;

//class header includes
#include "player.h"
#include "enemy.h"
#include <vector>
#include <stdlib.h>
#include <time.h>

vector<Enemy> enemyList;

int main(int argc, char* argv[]) {

	//initialize the random seed
	srand (time(NULL));

#if defined (_WIN32) || (_WIN64)

	std::cout << "running on windows" << endl;
	std::cout << "Added on windows" << endl;
	//get the current working directory
	string currentWorkingDirectory(getcwd(NULL, 0));

	//create a string linking to the mac images folder
	string images_dir = currentWorkingDirectory + "\\Resources\\images\\";

	//audio for windows
	string audio_dir = currentWorkingDirectory + "\\Resources\\audio\\";

#endif


#if defined (__APPLE__)

	cout << "running on apple" << endl;
	//get the current working directory
	string currentWorkingDirectory(getcwd(NULL, 0));

	//create a string linking to the mac images folder
	string images_dir = currentWorkingDirectory + "/Resources/images/";

	//week 5 audio directory
	//create a string to hold the current woeking directory on __APPLE__
	string audio_dir = currentWorkingDirectory + "/Resources/audio/";

	

#endif

#if defined (__linux__)

	cout << "running on linux" << endl;
	//get the current working directory
	string currentWorkingDirectory(getcwd(NULL, 0));

	//create a string linking to the mac images folder
	string images_dir = currentWorkingDirectory + "/Resources/images/";

	//audio for linnux
	string audio_dir = currentWorkingDirectory + "/Resources/audio/";

#endif

	SDL_Window *window;                    // Declare a pointer

	SDL_Init(SDL_INIT_EVERYTHING);              // Initialize SDL2

										   // Create an application window with the following settings:
	window = SDL_CreateWindow(
		"An SDL2 window",                  // window title
		SDL_WINDOWPOS_UNDEFINED,           // initial x position
		SDL_WINDOWPOS_UNDEFINED,           // initial y position
		1024,                               // width, in pixels
		768,                               // height, in pixels
		SDL_WINDOW_OPENGL                  // flags - see below
		);

	// Check that the window was successfully created
	if (window == NULL) {
		// In the case that the window could not be made...
		printf("Could not create window: %s\n", SDL_GetError());
		return 1;
	}

	//declare the renderer
	SDL_Renderer* renderer = NULL;

	//create the renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);


	//***********CREATE BACKGROUND************
	// create a SDL surface to hold the background image
	SDL_Surface *surface = IMG_Load((images_dir + "Background.png").c_str());

	//create an sdl texture
	SDL_Texture *bkgd1;

	//place the surface into the texture bkgd1
	bkgd1 = SDL_CreateTextureFromSurface(renderer, surface);

	//create an sdl texture
	SDL_Texture *bkgd2;

	//place the surface into the texture bkgd1
	bkgd2 = SDL_CreateTextureFromSurface(renderer, surface);

	//free the sdl surface
	SDL_FreeSurface(surface);

	//set the X Y W H for the rectangle
	bkgd1Pos.x = 0;
	bkgd1Pos.y = 0;
	bkgd1Pos.w = 1024;
	bkgd1Pos.h = 768;



	//set the X Y W H for the rectangle
	bkgd2Pos.x = 0;
	bkgd2Pos.y = -768;
	bkgd2Pos.w = 1024;
	bkgd2Pos.h = 768;

	//////***********************************CREATE BAKCGROUND END *******************

	////////************************cursor START****************************
	surface = IMG_Load((images_dir + "Cursor.png").c_str());

	//create an sdl texture
	SDL_Texture *cursor;

	//place the surface into the texture bkgd1
	cursor = SDL_CreateTextureFromSurface(renderer, surface);

	//free the sdl surface
	SDL_FreeSurface(surface);


	//create sdl rect for title
	//SDL_Rect cursorPos, activePos;

	//set the X Y W H for the cursor graphic
	cursorPos.x = 0;
	cursorPos.y = 0;
	cursorPos.w = 58;
	cursorPos.h = 52;

	//set the X Y W H for the rectangle
	activePos.x = 10;
	activePos.y = 10;
	activePos.w = 10;
	activePos.h = 10;

	//cursor speed
	//int cursorSpeed = 400;

	////////***********************CURSOR END


	//////*******************CREATE MENU START***************************************


	/////*****************************TITLE START**************************
	// create a SDL surface to hold the background image
	surface = IMG_Load((images_dir + "Title.png").c_str());

	//create an sdl texture
	SDL_Texture *title;

	//place the surface into the texture bkgd1
	title = SDL_CreateTextureFromSurface(renderer, surface);

	//free the sdl surface
	SDL_FreeSurface(surface);

	//create sdl rect for title
	SDL_Rect TitlePos;

	//set the X Y W H for the rectangle
	TitlePos.x = 264;
	TitlePos.y = 73;
	TitlePos.w = 532;
	TitlePos.h = 71;

	////*********************** TITLE END

	///************************PLAYER ONE****************************
	surface = IMG_Load((images_dir + "one_N.png").c_str());

	//create an sdl texture
	SDL_Texture *oneN;

	//place the surface into the texture bkgd1
	oneN = SDL_CreateTextureFromSurface(renderer, surface);

	//free the sdl surface
	SDL_FreeSurface(surface);

	//over state
	surface = IMG_Load((images_dir + "one_O.png").c_str());

	//create an sdl texture
	SDL_Texture *oneO;

	//place the surface into the texture bkgd1
	oneO = SDL_CreateTextureFromSurface(renderer, surface);

	//free the sdl surface
	SDL_FreeSurface(surface);

	//create sdl rect for title
	SDL_Rect oneNPos;

	//set the X Y W H for the rectangle
	oneNPos.x = 380;
	oneNPos.y = 261;
	oneNPos.w = 311;
	oneNPos.h = 42;

	////////**********************PLAYER ONE END

	////////************************PLAYER TWO****************************
	surface = IMG_Load((images_dir + "two_N.png").c_str());

	//create an sdl texture
	SDL_Texture *twoN;

	//place the surface into the texture bkgd1
	twoN = SDL_CreateTextureFromSurface(renderer, surface);

	//free the sdl surface
	SDL_FreeSurface(surface);

	//over state
	surface = IMG_Load((images_dir + "two_O.png").c_str());

	//create an sdl texture
	SDL_Texture *twoO;

	//place the surface into the texture bkgd1
	twoO = SDL_CreateTextureFromSurface(renderer, surface);

	//free the sdl surface
	SDL_FreeSurface(surface);

	//create sdl rect for title
	SDL_Rect twoNPos;

	//set the X Y W H for the rectangle
	twoNPos.x = 360;
	twoNPos.y = 343;
	twoNPos.w = 352;
	twoNPos.h = 42;

	//////////************************PLAYER TWO END************************


	////////************************INSTRUCTIONS****************************
	surface = IMG_Load((images_dir + "instructions_N.png").c_str());

	//create an sdl texture
	SDL_Texture *instructN;

	//place the surface into the texture bkgd1
	instructN = SDL_CreateTextureFromSurface(renderer, surface);

	//free the sdl surface
	SDL_FreeSurface(surface);

	//over state
	surface = IMG_Load((images_dir + "instructions_O.png").c_str());

	//create an sdl texture
	SDL_Texture *instructO;

	//place the surface into the texture bkgd1
	instructO = SDL_CreateTextureFromSurface(renderer, surface);

	//free the sdl surface
	SDL_FreeSurface(surface);

	//create sdl rect for title
	SDL_Rect instructNPos;

	//set the X Y W H for the rectangle
	instructNPos.x = 351;
	instructNPos.y = 424;
	instructNPos.w = 374;
	instructNPos.h = 42;

	//////////************************ISTRUCTIONS END************************


	////////************************QUIT START****************************
	surface = IMG_Load((images_dir + "Quit_N.png").c_str());

	//create an sdl texture
	SDL_Texture *quitN;

	//place the surface into the texture bkgd1
	quitN = SDL_CreateTextureFromSurface(renderer, surface);

	//free the sdl surface
	SDL_FreeSurface(surface);

	//over state
	surface = IMG_Load((images_dir + "quit_O.png").c_str());

	//create an sdl texture
	SDL_Texture *quitO;

	//place the surface into the texture bkgd1
	quitO = SDL_CreateTextureFromSurface(renderer, surface);

	//free the sdl surface
	SDL_FreeSurface(surface);

	//create sdl rect for title
	SDL_Rect quitNPos;

	//set the X Y W H for the rectangle
	quitNPos.x = 391;
	quitNPos.y = 503;
	quitNPos.w = 288;
	quitNPos.h = 42;

	//////////************************QUIT END************************



	////****************** MAIN MENU END*************************************



	/////*****************************win menu START**************************

	/////*************win graphics***********************
	// create a SDL surface to hold the background image
	surface = IMG_Load((images_dir + "win.png").c_str());

	//create an sdl texture
	SDL_Texture *winText;

	//place the surface into the texture bkgd1
	winText = SDL_CreateTextureFromSurface(renderer, surface);

	//free the sdl surface
	SDL_FreeSurface(surface);

	//create sdl rect for title
	SDL_Rect winPos;

	//set the X Y W H for the rectangle
	winPos.x = 240;
	winPos.y = 288;
	winPos.w = 596;
	winPos.h = 114;
	/////////////*****************WIN END****************************


	/////*************PLAY AGAIN graphics***********************
	// create a SDL surface to hold the background image
	surface = IMG_Load((images_dir + "Play_N.png").c_str());

	//create an sdl texture
	SDL_Texture *playN;

	//place the surface into the texture bkgd1
	playN = SDL_CreateTextureFromSurface(renderer, surface);

	//free the sdl surface
	SDL_FreeSurface(surface);

	// create a SDL surface to hold the background image
	surface = IMG_Load((images_dir + "Play_O.png").c_str());

	//create an sdl texture
	SDL_Texture *playO;

	//place the surface into the texture bkgd1
	playO = SDL_CreateTextureFromSurface(renderer, surface);

	//free the sdl surface
	SDL_FreeSurface(surface);

	//create sdl rect for title
	SDL_Rect playNPos;

	//set the X Y W H for the rectangle
	playNPos.x = 875;
	playNPos.y = 702;
	playNPos.w = 125;
	playNPos.h = 40;
	////*********************** win menu end***********************************


	////////////***********LOSE MENU************************************

	/////*************LOSE graphics***********************
	// create a SDL surface to hold the background image
	surface = IMG_Load((images_dir + "Lose.png").c_str());

	//create an sdl texture
	SDL_Texture *loseText;

	//place the surface into the texture bkgd1
	loseText = SDL_CreateTextureFromSurface(renderer, surface);

	//free the sdl surface
	SDL_FreeSurface(surface);

	//create sdl rect for title
	SDL_Rect losePos;

	//set the X Y W H for the rectangle
	losePos.x = 240;
	losePos.y = 288;
	losePos.w = 596;
	losePos.h = 114;
	/////////////*****************LOSE END****************************






	/////*****************************instructions menu START**************************

	/////*************instuctions graphics***********************
	// create a SDL surface to hold the background image
	surface = IMG_Load((images_dir + "Instructions.png").c_str());

	//create an sdl texture
	SDL_Texture *instuctionsText;

	//place the surface into the texture bkgd1
	instuctionsText = SDL_CreateTextureFromSurface(renderer, surface);

	//free the sdl surface
	SDL_FreeSurface(surface);

	//create sdl rect for title
	SDL_Rect instuctionsTextPos;

	//set the X Y W H for the rectangle
	instuctionsTextPos.x = 120;
	instuctionsTextPos.y = 271;
	instuctionsTextPos.w = 781;
	instuctionsTextPos.h = 258;

	/////*************small menu graphics***********************
	// create a SDL surface to hold the background image
	surface = IMG_Load((images_dir + "menu_N.png").c_str());

	//create an sdl texture
	SDL_Texture *menuN;

	//place the surface into the texture bkgd1
	menuN = SDL_CreateTextureFromSurface(renderer, surface);

	//free the sdl surface
	SDL_FreeSurface(surface);

	// create a SDL surface to hold the background image
	surface = IMG_Load((images_dir + "menu_O.png").c_str());

	//create an sdl texture
	SDL_Texture *menuO;

	//place the surface into the texture bkgd1
	menuO = SDL_CreateTextureFromSurface(renderer, surface);

	//free the sdl surface
	SDL_FreeSurface(surface);

	//create sdl rect for title
	SDL_Rect menuPos;

	//set the X Y W H for the rectangle
	menuPos.x = 22;
	menuPos.y = 702;
	menuPos.w = 145;
	menuPos.h = 41;



	////*********************** Instcutions menu***********************************

	//
	//
	//	//The surface contained by the window
	//	SDL_Surface* screenSurface = NULL;
	//
	//	//Get window surface
	//	screenSurface = SDL_GetWindowSurface(window);
	//
	//	//Fill the surface white
	//	SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0, 42, 254));
	//
	//	//Update the surface
	//	SDL_UpdateWindowSurface(window);
	//

	//******turn on events****
	SDL_GameControllerEventState(SDL_ENABLE);
	
	//****set up the game controller*******
	SDL_GameController* gGameController0 = NULL;

	//*****open gam controller*****
	gGameController0 = SDL_GameControllerOpen(0);

	//****set up the game controller2*******
	SDL_GameController* gGameController1 = NULL;

	//*****open gam controller2*****
	gGameController1 = SDL_GameControllerOpen(1);



	//*****sdl event to handle input
	SDL_Event event;

	//set up variables for the game states
	enum GameState { MENU, INSTRUCTIONS, PLAYERS1, PLAYERS2, WIN, LOSE };

	//Set up the initial state
	GameState gameState = MENU;

	//boolean values to control movement through the states
	bool menu, instructions, players1, players2, win, lose;
	bool quit = false;


	//open up the audio channel
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	//load the music file
	Mix_Music *bgm = MixLoadMUS((audio_dir + "background.wav").c_str());

	//if the music is not playing play it
	if(!Mix_PlayingMusic())
		Mix_PlayMusic(bgm, -1);

	//set up a sound efect chunk for the button over state
	Mix_Chunck *overSound = Mix_LoadWAV((audio_dir + "over.wav").c_str());

	//set up a sound effect of the button pressed state
	Mix_Chunk *pressedSound =Mix_LoadWAV((audio_dir + "pressed.wav").c_str());

	//set up the sound effect of the button pressed state
	Mix_Chunk *explosionSound = Mix_LoadWAV((audio_dir + "enemy.wav").c_str());

	//bool value to control the over sound effect
	bool alreadyOver = false;

	// ************************* create the player ***********************************

	Player player1 = Player(renderer, 0, images_dir.c_str(), audio_dir.c_str(), 250.0, 500.0);
	Player player2 = Player(renderer, 1, images_dir.c_str(), audio_dir.c_str(), 750.0, 500.0);

	// ************************* player end ******************************************



	// The window is open: could enter program loop here (see SDL_PollEvent())
	while (!quit)
	{

		switch (gameState)
		{
		case MENU:
			alreadyOver = false;
			menu = true;

			while (menu)
			{

				//set up the frame rate for the section or case
				thisTime = SDL_GetTicks();
				deltaTime = (float)(thisTime - lastTime) / 1000;
				lastTime = thisTime;



				//check for input events
				if (SDL_PollEvent(&event))
				{
					//check to see if the sdl window is closed
					if (event.type == SDL_QUIT)
					{
						quit = true;
						menu = false;
						break;
					}

					switch (event.type)
					{

					case SDL_CONTROLLERBUTTONDOWN:

						if (event.cdevice.which == 0)
						{
							if (event.cbutton.button == SDL_CONTROLLER_BUTTON_A)
							{
								//if the player choses 1 player game
								if(players1Over){
									//play the over sound plays fine though the levels, must pause/delay for quit
									Mix_PlayChannel(-1, pressedSound, 0);
									menu = false;
									gameState = PLAYERS1;
									players1Over = false;
								}

								//if the player chooses 2 player game
								if(players2Over){
									Mix_PlayChannel(-1, pressedSound, 0);
									menu = false;
									gameState = PLAYERS2;
									players2Over = false;
								}

								//if player chooses instructions
								if(instructionsOver){
									Mix_PlayChannel(-1, pressedSound, 0);
									menu = false;
									gameState = INSTRUCTIONS;
									instructionsOver = false;
								}

								//if the player chooses to quuit the game
								if(quitOver){
									Mix_PlayChannel(-1, pressedSound, 0);
									//add slight delay
									SDL_Delay(200);
									menu = false;
									quit = true;
									quitOver = false;
								}
							}

						}
						break;

						///////*******************NEW***********************
					case SDL_CONTROLLERAXISMOTION:

						moveCursor(event.caxis);
						break;
						/////////////**************new**********************

					}
				}

				//****************************UPDATE SECTION*******************************
				UpdateBackground(deltaTime);
				UpdateCursor(deltaTime);

				//check for collision between cursor active state and buttons
				players1Over = SDL_HasIntersection(&activePos, &oneNPos);
				players2Over = SDL_HasIntersection(&activePos, &twoNPos);
				instructionsOver = SDL_HasIntersection(&activePos, &instructNPos);
				quitOver = SDL_HasIntersection(&activePos, &quitNPos);

				// **************************New audio code *******************************

				//if the cursor is over a button, play the over sound
				if(players1Over || players2Over || instructionsOver || quitOver){
					if(alreadyOver == false){
						Mix_PlayChannel(-1, overSound, 0);
						alreadyOver = true;
					}
				}

				//if the cursor is not over any button reset the alreadyOver var
				if(!players1Over && !players2Over && !instructionsOver && !quitOver){
					alreadyOver = false;
				}
			

				//*********************************DRAW SECTION***************************************

				//clear sdl renderer
				SDL_RenderClear(renderer);

				//draw the bkgd image
				SDL_RenderCopy(renderer, bkgd1, NULL, &bkgd1Pos);

				//draw the bkgd2 image
				SDL_RenderCopy(renderer, bkgd2, NULL, &bkgd2Pos);

				//draw the title image
				SDL_RenderCopy(renderer, title, NULL, &cursorPos);

				/////////*******************NEW******************************************************
				//draw the player 1 button
				if(players1Over){
					SDL_RenderCopy(renderer, oneN, NULL, &oneNPos);
				}else{
					SDL_RenderCopy(renderer, oneO, NULL, &oneNPos);
				}

				//draw the player 2 button
				if(players2Over){
					SDL_RenderCopy(renderer, twoN, NULL, &twoNPos);
				}else{
					SDL_RenderCopy(renderer, twoO, NULL, &twoNPos);
				}

				//draw the instructions button
				if(instructionsOver){
					SDL_RenderCopy(renderer, instructN, NULL, &instructNPos);
				}else{
					SDL_RenderCopy(renderer, instructO, NULL, &instructNPos);
				}

				//draw the quit game button
				if(quitOver){
					SDL_RenderCopy(renderer, quitN, NULL, &quitNPos);
				}else{
					SDL_RenderCopy(renderer, quitN, NULL, &quitNPos);
				}
				////////************************NEW*************************************************

				//draw the cursor  image
				SDL_RenderCopy(renderer, cursor, NULL, &cursorPos);

				//sdl renderer present
				SDL_RenderPresent(renderer);



			}
			break;// end thre menu event



		case INSTRUCTIONS:
			alreadyOver = false;
			instructions = true;


			while (instructions)
			{


				//set up the frame rate for the section or case
				thisTime = SDL_GetTicks();
				deltaTime = (float)(thisTime - lastTime) / 1000;
				lastTime = thisTime;


				//check for input events
				if (SDL_PollEvent(&event))
				{
					//check to see if the sdl window is closed
					if (event.type == SDL_QUIT)
					{
						quit = true;
						instructions = false;
						break;
					}

					switch (event.type)
					{

					case SDL_CONTROLLERBUTTONDOWN:

						if (event.cdevice.which == 0)
						{
							if (event.cbutton.button == SDL_CONTROLLER_BUTTON_A)
							{
								//if player chooses the main menu
								if(menuOver){
									Mix_PlayChannel(-1, pressedSound, 0);
									instructions = false;
									gameState = MENU;
									menuOver = false;
								}
							}

						}
						break;
						///////*******************NEW***********************
					case SDL_CONTROLLERAXISMOTION:

						moveCursor(event.caxis);
						break;
						/////////////**************new**********************
					}
				}

				//****************************UPDATE SECTION*******************************
				UpdateBackground(deltaTime);

				//cursor
				UpdateCursor(deltaTime);

				//check to see if the curosr is over the menu button
				menuOver = SDL_HasIntersection(&activePos, &menuPos);

				// **************************New audio code *******************************

				//if the cursor is over a button, play the over sound
				if(menuOver){
					if(alreadyOver == false){
						Mix_PlayChannel(-1, overSound, 0);
						alreadyOver = true;
					}
				}

				//if the cursor is not over any button reset the alreadyOver var
				if(!menuOver){
					alreadyOver = false;
				}

				//*********************************DRAW SECTION***************************************

				//clear sdl renderer
				SDL_RenderClear(renderer);

				//draw the bkgd image
				SDL_RenderCopy(renderer, bkgd1, NULL, &bkgd1Pos);

				//draw the bkgd2 image
				SDL_RenderCopy(renderer, bkgd2, NULL, &bkgd2Pos);

				//draw the title image
				SDL_RenderCopy(renderer, title, NULL, &cursorPos);

				//draw the title image
				SDL_RenderCopy(renderer, instuctionsText, NULL, &instuctionsTextPos);

				// ****************************** NEW *******************************
				//draw main menu button
				if(menuOver){
					SDL_RenderCopy(renderer, menuO, NULL, &menuPos);
					SDL_RenderCopy(renderer, menuN, NULL, &menuPos);
				}

				// ****************************** NEW *******************************

				//draw the cursor  image
				SDL_RenderCopy(renderer, cursor, NULL, &cursorPos);

				//sdl renderer present
				SDL_RenderPresent(renderer);


			}

			break;



		case PLAYERS1:

			enemyList.clear();

			//reset the player
			player1.Reset();

			players1 = true;

			//create the enemy pool
			for(int i = 0; i < 6; i++)
			{
				//create the enemy
				Enemy tmpEnemy(renderer, images_dir);

				//add to the enemy list
				enemyList.push_back(tmpEnemy);
			}


			while (players1)
			{

				//set up the frame rate for the section or case
				thisTime = SDL_GetTicks();
				deltaTime = (float)(thisTime - lastTime) / 1000;
				lastTime = thisTime;


				//check for input events
				if (SDL_PollEvent(&event))
				{
					//check to see if the sdl window is closed
					if (event.type == SDL_QUIT)
					{
						quit = true;
						players1 = false;
						break;
					}

					switch (event.type)
					{

					case SDL_CONTROLLERBUTTONDOWN:

						if (event.cdevice.which == 0)
						{
							if (event.cbutton.button == SDL_CONTROLLER_BUTTON_X)
							{
								players1 = false;
								gameState = WIN;
							}
							if (event.cbutton.button == SDL_CONTROLLER_BUTTON_Y)
							{
								players1 = false;
								gameState = LOSE;
							}

							//send button press info to player 1p
							if(player1.active){
							player1.OnControllerButton(event.cbutton);
							}
						}
						break;

					case SDL_CONTROLLERAXISMOTION:

						if(player1.active){
						player1.OnControllerAxis(event.caxis);
						}
						break;

					}
				}

				//****************************UPDATE SECTION*******************************
				UpdateBackground(deltaTime);

				//update the player1
				if(player1.active){
				player1.Update(deltaTime, renderer);
				}

				//update the enemies
				for(int i = 0; i < enemyList.size(); i++)
				{
					//update enemy
					enemyList[i].Update(deltaTime);
				}


				//only check if the player is active
				if(player1.active){


					//use the plaer 1 bullet list to see if the active bullets hit any of the enemies
					for(int i = 0; i < player1.bulletList.size(); i++)
					{
						//check to see if the bullet is active onscreen
						if(player1.bulletList[i].active == true){

							//check all enemies against active bullet
							for(int j = 0; j < enemyList.size(); j++){

								//if there is a collision between the two objects
								if(SDL_HasIntersection(&player1.bulletList[i].posRect, &enemyList[j].posRect)){

									//play the explosion sound
									Mix_PlayChannel(-1, explosionSound, 0);

									//reset the enemy
									enemyList[j].Reset();

									//reset the enemy
									player1.bulletList[i].Reset();

									//give the player some points
									player1.playerScore += 50;
								}

							}
						}

					}


					//check to seeif the enemies hit the player
					for(int i = 0; i < enemyList.size(); i++){
						//if there is a collision between the two objects
						if(SDL_HasIntersection(&player1.posRect, &enemyList[i].posRect)){


							// play the explosion sound
							Mix_PlayChannel(-1, explosionSound, 0);

							//reset the enemy
							enemyList[i].Reset();

							//give the player some points
							player1.playerLives -= 1;

							//if game over
							if(player1.playerLives <= 0){
								players1 = false;
								gameState = LOSE;
								break;
							}
						}
					}
				}
				/// ********** player 1 active check ends ******************************

				//*********************************DRAW SECTION***************************************

				//clear sdl renderer
				SDL_RenderClear(renderer);

				//draw the bkgd image
				SDL_RenderCopy(renderer, bkgd1, NULL, &bkgd1Pos);

				//draw the bkgd2 image
				SDL_RenderCopy(renderer, bkgd2, NULL, &bkgd2Pos);

				//draw the enemies
				for(int i = 0; i < enemyList.size(); i++)
				{
					//draw enemies
					enemyList[i].Draw(renderer);
				}

				//draw the bkgd2 image
				//SDL_RenderCopy(renderer, oneN, NULL, &oneNPos);

				//draw the player
				player1.Draw(renderer);


				//sdl renderer present
				SDL_RenderPresent(renderer);



			}

			break;



		case PLAYERS2:

			enemyList.clear();

			//reset player 1 and 2
			player1.Reset();
			player2.Reset();

			players2 = true;

			//create the enemy pool
			for(int i = 0; i < 12; i++)
			{
				//create the enemy
				Enemy tmpEnemy(renderer, images_dir);

				//add to the enemy list
				enemyList.push_back(tmpEnemy);
			}


			while (players2)
			{

				//set up the frame rate for the section or case
				thisTime = SDL_GetTicks();
				deltaTime = (float)(thisTime - lastTime) / 1000;
				lastTime = thisTime;

				//check for input events
				if (SDL_PollEvent(&event))
				{
					//check to see if the sdl window is closed
					if (event.type == SDL_QUIT)
					{
						quit = true;
						players2 = false;
						break;
					}

					switch (event.type)
					{

					case SDL_CONTROLLERBUTTONDOWN:

						if (event.cdevice.which == 0 || event.cdevice.which == 1)
						{
							if (event.cbutton.button == SDL_CONTROLLER_BUTTON_X)
							{
								players2 = false;
								gameState = WIN;
							}
							if (event.cbutton.button == SDL_CONTROLLER_BUTTON_Y)
							{
								players2 = false;
								gameState = LOSE;
							}

						}

						//send the button press info for player 1

						if(player1.active){
						player1.OnControllerButton(event.cbutton);
						}

						//send the player 2 info
						if(player2.active){
						player2.OnControllerButton(event.cbutton);
						}

						break;

					case SDL_CONTROLLERAXISMOTION:
						//send axis info to player 1
						if(player1.active){
						player1.OnControllerAxis(event.caxis);
						}
						if(player2.active){
						player2.OnControllerAxis(event.caxis);
						}
						break;

					}
				}


				//****************************UPDATE SECTION*******************************
				UpdateBackground(deltaTime);

				if(player1.active){
				player1.Update(deltaTime, renderer);
				}
				if(player2.active){
				player2.Update(deltaTime, renderer);
				}

				//update the enemies
				for(int i = 0; i < enemyList.size(); i++)
				{
					//update enemy
					enemyList[i].Update(deltaTime);
				}


				//only check if the player is active
				if(player1.active){


					//use the plaer 1 bullet list to see if the active bullets hit any of the enemies
					for(int i = 0; i < player1.bulletList.size(); i++)
					{
						//check to see if the bullet is active onscreen
						if(player1.bulletList[i].active == true){

							//check all enemies against active bullet
							for(int j = 0; j < enemyList.size(); j++){

								//if there is a collision between the two objects
								if(SDL_HasIntersection(&player1.bulletList[i].posRect, &enemyList[j].posRect)){

									//play the explosion sound
									Mix_PlayChannel(-1, explosionSound, 0);

									//reset the enemy
									enemyList[j].Reset();

									//reset the enemy
									player1.bulletList[i].Reset();

									//give the player some points
									player1.playerScore += 50;
								}

							}
						}

					}


					//check to seeif the enemies hit the player
					for(int i = 0; i < enemyList.size(); i++){
						//if there is a collision between the two objects
						if(SDL_HasIntersection(&player1.posRect, &enemyList[i].posRect)){


							// play the explosion sound
							Mix_PlayChannel(-1, explosionSound, 0);

							//reset the enemy
							enemyList[i].Reset();

							//give the player some points
							player1.playerLives -= 1;

							//if game over
							if(player1.playerLives <= 0 && player2.playerLives <= 0){
								players2 = false;
								gameState = LOSE;
								break;
							}
						}
					}
				}
				/// ********** player 1 active check ends ******************************



				//only check if the player is active
				if(player2.active){


					//use the plaer 1 bullet list to see if the active bullets hit any of the enemies
					for(int i = 0; i < player2.bulletList.size(); i++)
					{
						//check to see if the bullet is active onscreen
						if(player2.bulletList[i].active == true){

							//check all enemies against active bullet
							for(int j = 0; j < enemyList.size(); j++){

								//if there is a collision between the two objects
								if(SDL_HasIntersection(&player2.bulletList[i].posRect, &enemyList[j].posRect)){

									//play the explosion sound
									Mix_PlayChannel(-1, explosionSound, 0);

									//reset the enemy
									enemyList[j].Reset();

									//reset the enemy
									player2.bulletList[i].Reset();

									//give the player some points
									player2.playerScore += 50;
								}

							}
						}

					}


					//check to seeif the enemies hit the player
					for(int i = 0; i < enemyList.size(); i++){
						//if there is a collision between the two objects
						if(SDL_HasIntersection(&player2.posRect, &enemyList[i].posRect)){


							// play the explosion sound
							Mix_PlayChannel(-1, explosionSound, 0);

							//reset the enemy
							enemyList[i].Reset();

							//give the player some points
							player2.playerLives -= 1;

							//if game over
							if(player1.playerLives <= 0 && player2.playerLives <= 0){
								players2 = false;
								gameState = LOSE;
								break;
							}
						}
					}
				}
				/// ********** player 2 active check ends ******************************

				//*********************************DRAW SECTION***************************************

				//clear sdl renderer
				SDL_RenderClear(renderer);

				//draw the bkgd image
				SDL_RenderCopy(renderer, bkgd1, NULL, &bkgd1Pos);

				//draw the bkgd2 image
				SDL_RenderCopy(renderer, bkgd2, NULL, &bkgd2Pos);

				//draw the enemies
				for(int i = 0; i < enemyList.size(); i++)
				{
					//draw enemies
					enemyList[i].Draw(renderer);
				}

				//draw the bkgd2 image
				//SDL_RenderCopy(renderer, twoN, NULL, &twoNPos);

				//draw the player 1
				player1.Draw(renderer);

				//draw the player 2
				player2.Draw(renderer);

				//sdl renderer present
				SDL_RenderPresent(renderer);
			}

			break;

		case WIN:
			alreadyOver = false;
			win = true;


			while (win)
			{

				//set up the frame rate for the section or case
				thisTime = SDL_GetTicks();
				deltaTime = (float)(thisTime - lastTime) / 1000;
				lastTime = thisTime;


				//check for input events
				if (SDL_PollEvent(&event))
				{
					//check to see if the sdl window is closed
					if (event.type == SDL_QUIT)
					{
						quit = true;
						win = false;
						break;
					}

					switch (event.type)
					{

					case SDL_CONTROLLERBUTTONDOWN:

						if (event.cdevice.which == 0)
						{
							if (event.cbutton.button == SDL_CONTROLLER_BUTTON_A)
							{
								//if player chooses main menu
								if(menuOver){
									Mix_PlayChannel(-1, pressedSound, 0);
									win = false;
									gameState = MENU;
									menuOver = false;
								}

								//if player chooses to play again
								if(playOver){
									Mix_PlayChannel(-1, pressedSound, 0);
									win = false;
									gameState = PLAYERS1;
									playOver = false;
								}
							}


						}
						break;
						///////*******************NEW***********************
					case SDL_CONTROLLERAXISMOTION:

						moveCursor(event.caxis);
						break;
						/////////////**************new**********************

					}
				}

				//****************************UPDATE SECTION*******************************
				UpdateBackground(deltaTime);

				//curosr
				UpdateCursor(deltaTime);

				menuOver = SDL_HasIntersection(&activePos, &menuPos);
				playOver = SDL_HasIntersection(&activePos, &playNPos);

				// **************************New audio code *******************************

				//if the cursor is over a button, play the over sound
				if(menuOver || playOver){
					if(alreadyOver == false){
						Mix_PlayChannel(-1, overSound, 0);
						alreadyOver = true;
					}
				}

				//if the cursor is not over any button reset the alreadyOver var
				if(!menuOver && !playOver){
					alreadyOver = false;
				}

				//*********************************DRAW SECTION***************************************

				//clear sdl renderer
				SDL_RenderClear(renderer);

				//draw the bkgd image
				SDL_RenderCopy(renderer, bkgd1, NULL, &bkgd1Pos);

				//draw the bkgd2 image
				SDL_RenderCopy(renderer, bkgd2, NULL, &bkgd2Pos);

				//draw the win text image
				SDL_RenderCopy(renderer, winText, NULL, &winPos);

				// ******************************* NEW ***********************************************
				if(menuOver){
					SDL_RenderCopy(renderer, menuO, NULL, &menuPos);
				}else{
					SDL_RenderCopy(renderer, playN, NULL, &playNPos);
				}
				// ******************************* NEW ***********************************************


				//draw the cursor  cursor
				SDL_RenderCopy(renderer, cursor, NULL, &cursorPos);

				//sdl renderer present
				SDL_RenderPresent(renderer);

			}

			break;



		case LOSE:
			alreadyOver = false;
			lose = true;


			while (lose)
			{

				//set up the frame rate for the section or case
				thisTime = SDL_GetTicks();
				deltaTime = (float)(thisTime - lastTime) / 1000;
				lastTime = thisTime;

				//check for input events
				if (SDL_PollEvent(&event))
				{
					//check to see if the sdl window is closed
					if (event.type == SDL_QUIT)
					{
						quit = true;
						lose = false;
						break;
					}

					switch (event.type)
					{

					case SDL_CONTROLLERBUTTONDOWN:

						if (event.cdevice.which == 0)
						{
							if (event.cbutton.button == SDL_CONTROLLER_BUTTON_A)
							{
								//if player chooses main menu
								if(menuOver){
									Mix_PlayChannel(-1, pressedSound, 0);
									win = false;
									gameState = MENU;
									menuOver = false;
								}

								//if player chooses to play again
								if(playOver){
									Mix_PlayChannel(-1, pressedSound, 0);
									win = false;
									gameState = PLAYERS1;
									playOver = false;
								}
							}


						}
						break;
						///////*******************NEW***********************
					case SDL_CONTROLLERAXISMOTION:

						moveCursor(event.caxis);
						break;
						/////////////**************new**********************

					}
				}

				//****************************UPDATE SECTION*******************************
				UpdateBackground(deltaTime);

				//curosr
				UpdateCursor(deltaTime);

				menuOver = SDL_HasIntersection(&activePos, &menuPos);
				playOver = SDL_HasIntersection(&activePos, &playNPos);

				// **************************New audio code *******************************

				//if the cursor is over a button, play the over sound
				if(menuOver || playOver){
					if(alreadyOver == false){
						Mix_PlayChannel(-1, overSound, 0);
						alreadyOver = true;
					}
				}

				//if the cursor is not over any button reset the alreadyOver var
				if(!menuOver && !playOver){
					alreadyOver = false;
				}
				//*********************************DRAW SECTION***************************************

				//clear sdl renderer
				SDL_RenderClear(renderer);

				//draw the bkgd image
				SDL_RenderCopy(renderer, bkgd1, NULL, &bkgd1Pos);

				//draw the bkgd2 image
				SDL_RenderCopy(renderer, bkgd2, NULL, &bkgd2Pos);

				//draw the win text image
				SDL_RenderCopy(renderer, loseText, NULL, &losePos);

				// ******************************* NEW ***********************************************
				if(menuOver){
					SDL_RenderCopy(renderer, menuO, NULL, &menuPos);
				}else{
					SDL_RenderCopy(renderer, playN, NULL, &playNPos);
				}
				// ******************************* NEW ***********************************************

				//draw the cursor  image
				SDL_RenderCopy(renderer, cursor, NULL, &cursorPos);

				//sdl renderer present
				SDL_RenderPresent(renderer);

			}

			break;


		}

	}



	//SDL_Delay(3000);  // Pause execution for 3000 milliseconds, for example

	 // Close and destroy the window
	SDL_DestroyWindow(window);

	// Clean up
	SDL_Quit();
	return 0;
}
