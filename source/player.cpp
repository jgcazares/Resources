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
		playerPath = filePath + "player 2.png";
	}

	//load the surface
	surface = IMG_Load(playerPath.c_str());

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

	//string to create the path to the bullet
	string bulletPath;

	//see if this is player 1 or player 2 to create path
	if (playerNum == 0)
	{
		//create the bullet texture
		bulletPath = filePath + "bullet.png";
	}
	else {
		//create the bullet 2 texture
		bulletPath = filePath + "bullet2.png";
	}

	//create the players bulet pool
	for (int i = 0; i < 10; i++)
	{
		//create the bullet and move offscreen
		Bullet tmpBullet(renderer, bulletPath, -1000, -1000);

		//add to the bullet list
		bulletList.push_back(tmpBullet);
	}

}

void Player::CreateBullet() {
	//see if there is a bullet active to fire
	for (int i = 0; i < bulletList.size(); i++)
	{
		//see if the bullet is not active
		if (bulletList[i].active == false)
		{
			//set the bullet to active
			bulletList[i].active == true;

			bulletList[i].posRect.x = (pos_X + (posRect.w / 2));

			//finishing aligning the bullets
			bulletList[i].posRect.x = (bulletList[i].posRect.x - (bulletList[i].posRect.w / 2));
			bulletList[i].posRect.y = posRect.y;

			//set the x and y position
			bulletList[i].pos_X = pos_X;
			bulletList[i].pos_Y = pos_Y;

			//one the bullet is found break out the loop
			break;
		}
	}
}


//player joystick method
void Player::OnControllerButton(const SDL_ControllerButtonEvent event)
{

	//if the players number is 0 and the joystick is 0
	if (event.which == 0 && playerNum == 0)
	{
		//if A button
		if (event.button == 0)
		{
			cout << "Player 1 - button A" << endl;

			//create a bullet
			CreateBullet();
		}

	}

	//if the players number is 1 and the joystick is 1
	if (event.which == 1 && playerNum == 1)
	{
		//if A button
		if(event.button == 0)
		{
			cout << "Player 2 - button A" << endl;

			//create a bullet
			CreateBullet();
		}
		
	}

}

//player joystick method
void Player::OnControllerAxis(const SDL_ContollerAxisEvent event)
{

	//axi movements and button presses both sent here as sdl axis structure
	
	//if the players number is 0 and jpystick is 0
	if (event.which == 0 && playerNum == 0)
	{
		//x axis
		if (event.axis == 0)
		{

			if (event.value < -JOYSTICK_DEAD_ZONE_)
			{
				xDir = -1.0f; //left
			}

			else if (event.value > JOYSTICK_DEAD_ZONE_)
			{
				xDir = 1.0f; //right
			}

			else
			{
				xDir = 0.0f; //none
			}
		}

		//Y axis
		if (event.axis == 1)
		{

			if (event.value < -JOYSTICK_DEAD_ZONE_)
			{
				yDir = -1.0f; //down
			}
			else if (event.value < JOYSTICK_DEAD_ZONE_)
			{
				yDir = 1.0f; //up
			}
			else
			{
				yDir = 0.0f; //none
			}
		}
	}



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

	//update for the players bullets
	for (int i = 0; i < bulletList.size(); i++)
	{
		//cheack to see if the bullet is active
		if (bulletList[i].active)
		{
			//update the bullet
			bulletList[i].Update(deltaTime);
		}
	}


}

//player draw method
void Player::Draw(SDL_Renderer *renderer)
{
	//draw the player texture using the vars texture ad posRec
	SDL_RenderCopy(renderer, texture, NULL, &posRect);

	//draws the players bullet
	for (int i = 0; i < bulletList.size(); i++) {

		//check to see if the bullet is active
		if (bulletList[i].active)
		{
			//draw the bullet
			bulletList[i].Draw(renderer);
		}
	}
}

//player destruction method
Player::~Player()
{
	SDL_DestroyTexture(texture);
}