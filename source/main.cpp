// Example program:
// Using SDL2 to create an application window

#if defined (_WIN32) || (_WIN64)

#include "SDL.h"
#include <stdio.h>

#endif


#if defined (__APPLE__)

#include SDL2/SDL2.h

#endif

#if defined (__linux__)

#include SDL2/SDL2.h

#endif

#include "SDL.h"
#include <stdio.h>
#include <iostream>

using namespace std;


int main(int argc, char* argv[]) {

#if defined (_WIN32) || (_WIN64)

	cout << "running on windows" << endl;
	cout << "Added on windows" << endl;

#endif


#if defined (__APPLE__)

	cout << "running on apple" << endl;

#endif

#if defined (__linux__)

	cout << "running on linux" << endl;

#endif

	SDL_Window *window;                    // Declare a pointer

	SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL2

										   // Create an application window with the following settings:
	window = SDL_CreateWindow(
		"An SDL2 window",                  // window title
		SDL_WINDOWPOS_UNDEFINED,           // initial x position
		SDL_WINDOWPOS_UNDEFINED,           // initial y position
		640,                               // width, in pixels
		480,                               // height, in pixels
		SDL_WINDOW_OPENGL                  // flags - see below
		);

	// Check that the window was successfully created
	if (window == NULL) {
		// In the case that the window could not be made...
		printf("Could not create window: %s\n", SDL_GetError());
		return 1;
	}

	// The window is open: could enter program loop here (see SDL_PollEvent())

	SDL_Delay(3000);  // Pause execution for 3000 milliseconds, for example

					  // Close and destroy the window
	SDL_DestroyWindow(window);

	// Clean up
	SDL_Quit();
	return 0;
}