#if defined(_WIN32) || (_WIN64)
#include <SDL.h>
#include <SDL_image.h>
#endif

#if defined (__APPLE__)
	#include <SDL2/SDL.h>
	#include <SDL2_image/SDL_image.h>
#endif

#if defined (__linux__)
	#include "SDL2/SDL.h"
	#include "SDL2/SDL_image.h"
#endif


#include <string>
#include <iostream>
using namespace std;

#include <stdlib.h>


class Enemy{

	//boolean for the state of the enemy
	bool active;

	//enemy texture
	SDL_Texture *textrue;

	//enemy rectangle for position
	SDL_Rect posRect;

	//movement direction values
	float xDir, yDir;

	//enemy speed
	float speed;

	//float positions to prevent precision loss
	float pos_X, pos_Y;

	//enemy angle
	float angle;

	//point for the center
	SDL_Point center;

	//enemy creation method
	Enemy(SDL_Renderer *renderer, string filePath);

	//enemy update
	void Update(float deltaTime);

	//enemy draw
	void Draw(SDL_Renderer *renderer);

	//enemy reset
	void Reset();

	//enemy destructuion
	~Enemy();

};
