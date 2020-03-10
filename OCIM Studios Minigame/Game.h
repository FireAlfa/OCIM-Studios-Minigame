#pragma once

#include "SDL/include/SDL.h"
#pragma comment( lib, "SDL/libx86/SDL2.lib" )
#pragma comment( lib, "SDL/libx86/SDL2main.lib" )
#include "SDL_Image/include/SDL_image.h"
#pragma comment( lib, "SDL_image/libx86/SDL2_image.lib" )
#include "SDL_Mixer/include/SDL_mixer.h"
#pragma comment( lib, "SDL_Mixer/libx86/SDL2_mixer.lib")

#include "Entity.h"
#include "Spike.h"

#define WINDOW_WIDTH	1024
#define WINDOW_HEIGHT	768
#define MAX_KEYS		256
#define PLAYER_WIDTH	64
#define PLAYER_HEIGHT	64


class Game
{
public:
	Game();
	~Game();

	bool Init();
	void Release();
	
	bool Input();
	bool Update();
	void Draw();

private:
	SDL_Window* Window;
	SDL_Renderer* Renderer;
	SDL_Surface* Surface;
	SDL_Texture* Texture_Player;
	SDL_Texture* Texture_Background;
	Mix_Music* Music_Background;

	Entity Player, Scene;
	Spike Spike[MAX_SPIKES];
	int png_flag = IMG_INIT_PNG;
	int ogg_flag = MIX_INIT_OGG;
	int mp3_flag = MIX_INIT_MP3;
	int contSong = 19800;
	bool flagCollision = false;
	

	enum KEY_STATE { KEY_IDLE, KEY_DOWN, KEY_REPEAT, KEY_UP	};
	KEY_STATE keys[MAX_KEYS]; 
};
