//needed includes for cross platform developement
#if defined (_WIN32) || (WIN64)
#include "SDL.h"
#include  "SDL_image.h"
#endif

#if defined (__APPLE__)
#include SDL2/SDL2.h
#include SDL2_image/SDL_image.h
#endif

#if defined (__linux__)
#include SDL2/SDL2.h
#include SDL2/SDL_image.h
#endif

#include <string>
#include <iostream>
using namespace std;

class Bullet
{
public:
	//boolean for the state of the bullet
	bool active;

	//bullet texture
	SDL_Texture *texture;

	//bullet rectangle for positions
	SDL_Rect posRect;

	//movement direction values
	float xDir, yDir;

	//bullet speed
	float speed;

	//bullet float positions to prevent precision loss
	float pos_X, pos_Y;

	//bullet creation method
	Bullet(SDL_Renderer *renerer, string filePath, float x, float y);

	void Update(float deltaTime);

	//bullet draw
	void Draw(SDL_Renderer *renderer);

	void Reset();

	//bullet destruction method
	~Bullet();
};
