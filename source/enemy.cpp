#include "enemy.h"

//enemy creation method
Enemy::Enemy(SDL_Renderer *renderer, string filePath)
{
	//get the path to the enemy texture
	string enemyPath = filePath + "enemies.png";

	//load the texture into a surface
	SDL_Surface *surface = IMG_Load(enemyPath.c_str());

	//create the texture from the passed renderer and created surface
	texture = SDL_CreateTextureFromSurface(renderer, surface);

	//free the surface for later use
	SDL_FreeSurface(surface);

	//set the width and height of the enemies rectangle
	//by the querying the texture itself
	int w,h;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
	posRect.w = w;
	posRect.h = h;

	//reset the enemy
	Reset();

	//initialize the direction
	//no x movement, only y movement
	xDir = 0;
	yDir = 1;

	//start with a random angle
	angle = rand() % (360);

	//calculate the center of the object
	center.x = posRect.w /2;
	center.y = posRect.h /2;


}

//enemy reset
void Enemy::Reset(){

	//set a random enemy speed
	speed = rand() % (5) +1;
	speed *= 100;

	//generate random x position and set y back to the top of the screen
	posRect.x = rand() % (1024-posRect.w) +1;
	posRect.y = 0 - posRect.h;

	//set the float position values of the texture for presition loss
	pos_X = posRect.x;
	pos_Y = posRect.y;
}


//update method
void Enemy::Update(float deltaTime)
{
	//adjust the position float based on speed, direction and deltatime
	pos_Y += (speed * yDir) * deltaTime;

	//update the enemy position with code to account for precision loss
	posRect.y = (int)(pos_Y + 0.5f);

	//check to see if the enemy is off the bottom of the screen
	if(posRect.y > 768){

		//reset the enmy
		Reset();
	}

	//update the angle
	angle += .1;
}


//enemy draw method
void Enemy::Draw(SDL_Render *renderer)
{
	SDL_RenderCopyEx(renderer, texture, NULL, &posRect, angle, &center, SDL_FLIP_NONE);
}


//enemy destruction
Enemy::~Enemy()
{
	//SDL_DestroyTexture(texture);
}

