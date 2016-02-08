#include "bullet.h"

//bullet creation method
Bullet::Bullet(SDL_Renderer *renderer, string filePath, float x, float y)
{
	//set bulet initial state
	active = false;

	//set the bullet speed
	speed = 800.0;

	//load the texture
	SDL_Surface *surface = IMG_Load(filePath.c_str());

	//create the texture
	texture = SDL_CreateTextureFromSurface(renderer, surface);

	//free the surface for later use
	SDL_FreeSurface(surface);

	//set the width
	int w, h;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
	posRect.w = w;
	posRect.h = h;

	//set the x and y position
	posRect.x = x - (posRect.w / 2);
	posRect.y = y;

	//set the position for precision loss
	pos_X = x;
	pos_Y = y;

	//intitialize the directions of vars
	//no x movement only y movement
	xDir = 0;
	yDir = -1;
}


//bullet update method
void Bullet::Update(float deltaTime)
{
	//check to see if the bullet is active
	if (active)
	{
		//adjust position to 
		pos_Y += (speed * yDir) * deltaTime;

		//update the bullet position
		posRect.y = (int)(pos_Y + 0.5f);

		//check to see if the bullet os off the top of the screen
		//and deactivate
		if (posRect.y < (0 - posRect.h))
		{
			posRect.x = -1000;
			pos_X = posRect.x;
			active = false;
		}
	}
}


//bullet draw method
void Bullet::Draw(SDL_Renderer *renderer)
{
	SDL_RenderCopy(renderer, texture, NULL, &posRect);
}

//bullet destruction
Bullet::~Bullet()
{
	SDL_DestroyTexture(texture);
}
