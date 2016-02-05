#include "player.h"

//analog joystick dead zone
const int JOYSTICK_DEAD_ZONE_ = 8000;

//player creation method
Player::Player(SDL_Renderer *renderer, int pNum, string filePath, float x, float y){

	//set the player number 0 or 1
	playerNum = pNum;

	//float for player speed
	speed = 500.0f;

	//see if the player 1, player 2, and create the correct file path
	if(playerNum = 0){
		//create player 1 texture
		playerPath = filePath + "player 1.png";
	}else{
		//create player 2 texture
		playerPath = filePath + "player 2.png"
	}

	//load the surface
	surface = IMG_LOAD(playerPath.c_str());

	//load the surface into the texture
	texture = SDL_CreateTextureFromSurface(renderer, surface);

	//free the surface
	SDL_FreeSurface(surface);

	//set the SDL rect
	posRect.x = x;
	posRect.y = y;

	//use the SDLQUerytexture to get the w and h of the players texture
	int w, h;

	SDL_QueryTexture(texture, NULL, NULL, &w, &h);

	posRect.w = w;
	posRect.h = h;

	//set the movenment of the players original x and y
	pos_X = x;
	pos_Y = y;

	//set the dir for the joystick
	xDir = 0;
	yDir = 0;

}

//player update method
void Player::Update(float deltaTime){

	//adjust position floats based on speed, directions of joystick axis and deltatime
	pos_X += (speed * xDir) * deltaTime;
	pos_Y += (speed * yDir) * deltaTime;

	//update the player position with code to account for precision loss
	posRect.x = (int)(pos_X + 0.5f);
	posRect.y = (int)(pos_Y + 0.5f);

	if(posRect.x < 0){
		posRect.x = 0;
		pos_X = posRect.x;
	}

	if(posRect.x > 1024 - posRect.w){
		posRect.x = 1024 - posRect.w;
		pos_X = posRect.x;
	}

	if(posRect.y < 0){
		posRect.y = 0;
		pos_Y = posRect.y;
	}

	if(posRect.y > 768 - posRect.h){
		posRect.y = 768 - posRect.h;
		pos_X = posRect.y;
	}

}

//player draw method
void Player::Draw(SDL_Renderer *renderer)
{
	//draw the player texture using the vars texture ad posRec
	SDL_RenderCopy(renderer, texture, NULL, &posRect);
}

