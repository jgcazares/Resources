// Example program:
// Using SDL2 to create an application window

#if defined (_WIN32) || (_WIN64)

#include "SDL.h"
#include <stdio.h>


#endif


#if defined (__APPLE__)

#include SDL2/SDL2.h
#include SDL2_image/SDL_image.h

#endif

#if defined (__linux__)

#include SDL2/SDL2.h

#endif

//#include "SDL.h"
#include <stdio.h>
#include <iostream>

using namespace std;

//code for framerate independence
float deltaTime = 0.0;
int thisTime = 0;
int lastTime = 0;





int main(int argc, char* argv[]) {

#if defined (_WIN32) || (_WIN64)

	cout << "running on windows" << endl;
	cout << "Added on windows" << endl;

#endif


#if defined (__APPLE__)

	cout << "running on apple" << endl;
	//get the current working directory
	string s_cwd(getcwd(NULL,0));

	//create a string linking to the mac images folder
	string s_cwd_images = s_cwd + "/Resources/images";

	//test
	cout << s_cwd_images << endl;

#endif

#if defined (__linux__)

	cout << "running on linux" << endl;

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
	renderer = SDL_CreateRenderer(window, -1,SDL_RENDERER_ACCELERATED);

	//***********CREATE BACKGROUND************
	string BKGDpath = s_cwd_images + "/BackGround.png";

	// create a SDL surface to hold the background image
	SDL_Surface *surface = IMG_Load(BKGDpath.c_str());

	//create an sdl texture
	SDL_Texture *bkgd1;

	//place the surface into the texture bkgd1
	bkgd1 = CreateTextureFromSurface(renderer, surface);

	//free the sdl surface
	SDL_FreeSurface(surface);

	//create the SDL_Rectangle for the textures position and size -x,y,z,h
	SDL_Rect bkgd1Pos;

	//set the X Y W H for the rectangle
	bkgd1Pos.x = 0;
	bkgd1Pos.y = 0;
	bkgd1Pos.w = 1024;
	bkgd1Pos.h = 768;


	//create the SDL_Rectangle for the textures position and size -x,y,z,h
	SDL_Rect bkgd2Pos;

	//create an sdl texture
	SDL_Texture *bkgd2;

	//place the surface into the texture bkgd1
	bkgd2 = CreateTextureFromSurface(renderer, surface);

	//set the X Y W H for the rectangle
	bkgd2Pos.x = 0;
	bkgd2Pos.y = -768;
	bkgd2Pos.w = 1024;
	bkgd2Pos.h = 768;

	//set the speed
	int bkgdSpeed = 100;


	//set temp variables to hold movement
	float BG1pos_X =0, BG1pos_Y=0;


	//set temp variables to hold movement
	float BG2pos_X =0, BG2pos_Y= -768;


	//create the cursor image
	string CURSORpath = s_cwd_images + "/jorgeCursor.png";

		// create a SDL surface to hold the background image
		SDL_Surface *surface = IMG_Load(CURSORpath.c_str());

		//create an sdl texture
		SDL_Texture *cursor;

		//place the surface into the texture bkgd1
		cursor = CreateTextureFromSurface(renderer, surface);

		//create the SDL_Rectangle for the textures position and size -x,y,z,h
			SDL_Rect cursorPos;

			//set the X Y W H for the rectangle
			cursorPos.x = 0;
			cursorPos.y = 0;
			cursorPos.w = 59;
			cursorPos.h = 62;


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
	//****set up the game controller*******
	SDL_GameController* gGameController = NULL;

	//*****open gam controller*****
	gGameController = SDL_GameControllerOpen(0);

	//******turn on events****
	SDL_GameControllerEventState(SDL_ENABLE);

	//*****sdl event to handle input
	SDL_Event event;

	//set up variables for the game states
	enum GameState { MENU, INSTRUCTIONS, PLAYERS1, PLAYERS2, WIN, LOSE };

	//Set up the initial state
	GameState gameState = MENU;

	//boolean values to control movement through the states
	bool menu, instructions, players1, players2, win, lose;
	bool quit = false;

	// The window is open: could enter program loop here (see SDL_PollEvent())
	while (!quit)
	{

		switch (gameState)
		{
		case MENU:
			menu = true;
			cout << "The Game State is Menu" << endl;
			cout << "Press the A Button for Instructions" << endl;
			cout << "Press the B Button for 1 Player Game" << endl;
			cout << "Press the X Button for 2 Player Game" << endl;
			cout << "Press the Y Button for Quit Game" << endl;
			cout << endl;

			while (menu)
			{

				//set up the frame rate for the section or case
				thisTime = SDL_GetTicks();
				deltaTime = (float)(thisTime - lastTime)/1000;




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
								menu = false;
								gameState = INSTRUCTIONS;
							}
							if (event.cbutton.button == SDL_CONTROLLER_BUTTON_B)
							{
								menu = false;
								gameState = PLAYERS1;
							}
							if (event.cbutton.button == SDL_CONTROLLER_BUTTON_X)
							{
								menu = false;
								gameState = PLAYERS2;
							}
							if (event.cbutton.button == SDL_CONTROLLER_BUTTON_Y)
							{
								menu = false;
								quit = true;
							}
						}
						break;

					}
				}

				//update

				//Update the bkgd 1
				BG1pos_Y +=(bkgdSpeed *1);

				//set the new bkgd10 poition
				bkgd1Pos.y = (int)(BG1pos_Y + 0.5f);

				//reset when off the bottom of the screen
				if(bkgd1Pos.y >= 768)
				{

					bkgd1Pos.y =-768;
					BG1pos_Y = bkgd1Pos.y;


				}


				//Update the bkgd 2
								BG2pos_Y +=(bkgdSpeed *1);

								//set the new bkgd10 poition
								bkgd2Pos.y = (int)(BG2pos_Y + 0.5f);

								//reset when off the bottom of the screen
								if(bkgd2Pos.y >= 768)
								{

									bkgd2Pos.y =-768;
									BG2pos_Y = bkgd2Pos.y;


								}

				//start drawing


				//clear sdl renderer
				SDL_RenderClear(renderer);

				//draw the bkgd image
				SDLRenderCopy(renderer, bkgd1, NULL, &bkgd1Pos);

				//draw the bkgd image
				SDLRenderCopy(renderer, bkgd1, NULL, &bkgd2Pos);

				//draw the cursor image
				SDLRenderCopy(renderer, bkgd1, NULL, &cursorPos);

				//sdl renderer present
				SDL_RendererPresent(renderer);



			}
			break;// end thre menu event



		case INSTRUCTIONS:
			instructions = true;
			cout << "The Game State is Instructions" << endl;
			cout << "Press the A Button for Main Menu" << endl;
			cout << endl;

			while (instructions)
			{
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
								instructions = false;
								gameState = MENU;
							}

						}
						break;

					}
				}
			}

			break;



		case PLAYERS1:
			players1 = true;
			cout << "The Game State is 1 Player Game" << endl;
			cout << "Press the A Button for Win Screen" << endl;
			cout << "Press the B Button for Lose Screen" << endl;
			cout << endl;

			while (players1)
			{
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
							if (event.cbutton.button == SDL_CONTROLLER_BUTTON_A)
							{
								players1 = false;
								gameState = WIN;
							}
							if (event.cbutton.button == SDL_CONTROLLER_BUTTON_B)
							{
								players1 = false;
								gameState = LOSE;
							}

						}
						break;

					}
				}
			}

			break;



		case PLAYERS2:
			players2 = true;
			cout << "The Game State is 2 Player Game" << endl;
			cout << "Press the A Button for Win Screen" << endl;
			cout << "Press the B Button for Lose Screen" << endl;
			cout << endl;

			while (players2)
			{
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

						if (event.cdevice.which == 0)
						{
							if (event.cbutton.button == SDL_CONTROLLER_BUTTON_A)
							{
								players2 = false;
								gameState = WIN;
							}
							if (event.cbutton.button == SDL_CONTROLLER_BUTTON_B)
							{
								players2 = false;
								gameState = LOSE;
							}

						}
						break;

					}
				}
			}

			break;

		case WIN:
			win = true;
			cout << "The Game State is Win State" << endl;
			cout << "Press the A Button for Main Menu" << endl;
			cout << "Press the B Button to Quit" << endl;
			cout << endl;

			while (win)
			{
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
								win = false;
								gameState = MENU;
							}
							if (event.cbutton.button == SDL_CONTROLLER_BUTTON_B)
							{
								win = false;
								quit = true;
							}

						}
						break;

					}
				}
			}

			break;



		case LOSE:
			lose = true;
			cout << "The Game State is Lose State" << endl;
			cout << "Press the A Button for Main Menu" << endl;
			cout << "Press the B Button to Quit" << endl;
			cout << endl;

			while (lose)
			{
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
								lose = false;
								gameState = MENU;
							}
							if (event.cbutton.button == SDL_CONTROLLER_BUTTON_B)
							{
								lose = false;
								quit = true;
							}

						}
						break;

					}
				}
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
