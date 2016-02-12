#include "explode.h"

//explode creation method
Explode::Explode(SDL_Renderer *renderer, string filePath, float x, float y)
{
	//set the explosion initial state
	active = false;

	//get the directory path the explosion graphic
	string explodePath = filePath + "explosion3.png";

	//init the frame counter
	frameCounter = 0.0f;

	//load th etexture into a surface
	SDL_Surface *surface = IMG_Load(explodePath.c_str());

	//create the texture from the [assed renderer and created surface
	texture = SDL_CreateTextureFromSurface(renderer, surface);

	//free the surface for later use
	SDL_FreeSurface(surface);

	//set the width and height of the bullets rectangle
	int w, h;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);

	//getting the width and height of the entire image
	textureWidth = w;
	textureHeight = h;

	//setting the individual image size
	posRect.w = 64;
	posRect.h = 64;

	//set the x and y positions of the explosion rectangle
	posRect.x = x;
	posRect.y = y;

	//frame width and height of each animation image
	frameWidth = 64;
	frameHeight = 64;

	//original draw rectangle used to draw one frame of the animation strip
	drawRect.x = 64;
	drawRect.y = 0;
	drawRect.w = frameWidth;
	drawRect.h = frameHeight;
}
