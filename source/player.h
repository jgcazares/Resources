//needed includes for cross platform developement
#if defined (_WIN32) || (WIN64)
	#include "SDL.h"
	#include  "SDL_image.h"
	#include  "SDL_mixer.h"
	#include  "SDL_ttf.h"
#endif

#if defined (__APPLE__)
	#include SDL2/SDL2.h
	#include SDL2_image/SDL_image.h
	#include SDL2_mixer/SDL_mixer.h
	#include SDL2_ttf/SDL_ttf.h
#endif

#if defined (__linux__)
	#include SDL2/SDL2.h
	#include SDL2image/SDL_image.h
	#include SDL2/SDL_mixer.h
	#include SDL2/SDL_ttf.h
#endif

///needed includes
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

#include <vector>
#include "bullet.h"

class Player{

public:

	//player score and lives
	int playerScore, oldScore, playerLives, oldLives;

	//varibel for what font to use
	TTF_Font *font;

	//font color
	SDL_Color colorP1 = {0, 255, 0, 255};

	//font color
	SDL_Color colorP2 = {0, 0, 255, 255};

	//surface for the player score and lives
	SDL_Surface *scoreSurface, *livesSurface;

	//textures for the player score and lives
	SDL_Texture * scoreTexture, * livesTexture;

	//sdl rects for the player
	SDL_Rect scorePos, livesPos;

	//strings to hold gthe temp values of the player lives and player score
	string tempScore, tempLives;


	//audio sound effect
	Mix_Chunk *laser;

	//variable to hold the bullet list
	vector<Bullet> bulletList;

	//string to hold the plath to the players texture
	string playerPath;

	//int for the players number
	int playerNum;

	//players sruface fot load png into
	SDL_Surface *surface;

	//players texture
	SDL_Surface *texture;

	//players rectangle
	SDL_Rect posRect;

	//floats to hold the joystick axis
	float xDir;
	float yDir;

	//float for player speed
	float speed;

	//float for the players position
	float pos_X, pos_Y;


	//players creation method using passed in values for renderer, player number, path to texture
	//starting position x staring position
	Player(SDL_Renderer *renderer, int pNum, string filePath, string audioPath, float x, float y);

	//method to allow the player the move via joystick axis
	void OnControllerAxis(const SDL_ControllerAxisEvent event);

	//method to allow the player interact with joystick buttons
	void OnControllerButton(const SDL_ControllerButtonEvent event);

	//update the player using the passed delta time
	void Update(float deltaTime, SDL_Renderer *renderer);

	//draw the players main
	void Draw(SDL_Renderer *renderer);

	//players destrucion method
	~Player();

	//update score
	void UpdateScore(SDL_Renderer *renderer);

	//update the score method
	void UpdateLives(SDL_Renderer *renderer);

private:
	void CreateBullet();
};
