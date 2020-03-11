#include "Game.h"
#include <math.h>

Game::Game() {}
Game::~Game(){}


//INIT
bool Game::Init()
{
	//Initialize SDL with all subsystems
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	//Initialize IMG subsystems: image type flag
	IMG_Init(png_flag);

	//Create our window: title, x, y, w, h, flags
	Window = SDL_CreateWindow("Geometry Dash: space to jump", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	if (Window == NULL)
	{
		SDL_Log("Unable to create window: %s", SDL_GetError());
		return false;
	}

	//Create a 2D rendering context for a window: window, device index, flags
	Renderer = SDL_CreateRenderer(Window, -1, 0);
	if (Renderer == NULL)
	{
		SDL_Log("Unable to create rendering context: %s", SDL_GetError());
		return false;
	}

	//Initialize Surfaces
	Surface = IMG_Load("player.png");
	Texture_Player = SDL_CreateTextureFromSurface(Renderer, Surface);
	Surface = IMG_Load("background.png");
	Texture_Background = SDL_CreateTextureFromSurface(Renderer, Surface);
	Surface = IMG_Load("obstc.png");
	Texture_Obstc = SDL_CreateTextureFromSurface(Renderer, Surface);

	//Initialize Background music
	if (!Mix_Init(ogg_flag)) {
		SDL_Log("Unable to load OGG Flag: %s", Mix_GetError());
	}
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 1, 1024) == -1) {
		SDL_Log("Unable to Open Audio: %s", Mix_GetError());
	}

	Music_Background = Mix_LoadMUS("StereoMadness.ogg");
	if (!Music_Background) {
		SDL_Log("Unable to load Background Song: %s", Mix_GetError());
	}

	//Start song
	Mix_PlayMusic(Music_Background, 1);

	//Initialize keys array that has all key instructions
	for (int i = 0; i < MAX_KEYS; ++i) {
		keys[i] = KEY_IDLE;
	}

	//Initialize variables
	Player.Init(60, WINDOW_HEIGHT >> 1, PLAYER_WIDTH, PLAYER_HEIGHT, 5);
	Obstc[0].Init(500, 555, PLAYER_WIDTH, PLAYER_HEIGHT, -3);
	Obstc[1].Init(1000, 555, PLAYER_WIDTH, PLAYER_HEIGHT, -3);
	Obstc[2].Init(1200, 555, PLAYER_WIDTH, PLAYER_HEIGHT, -3);

	//Initialize background
	int bg_width;
	SDL_QueryTexture(Texture_Background, NULL, NULL, &bg_width, NULL);
	Scene.Init(0, 0, bg_width, WINDOW_HEIGHT, 4);


	return true;
}

//CLEANUP
void Game::Release()
{
	//Clean up all SDL initialized subsystems
	SDL_Quit();

	//Clear Textures
	SDL_DestroyTexture(Texture_Player);
	SDL_DestroyTexture(Texture_Background);
	SDL_DestroyTexture(Texture_Obstc);

	//Clear IMG subsystems
	IMG_Quit();

	//Clear Audio subsystems
	Mix_Quit();
}

//INPUT
bool Game::Input()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)	return false;
	}

	SDL_PumpEvents();
	const Uint8* keyboard = SDL_GetKeyboardState(NULL);
	for (int i = 0; i < MAX_KEYS; ++i)
	{
		if (keyboard[i])
			keys[i] = (keys[i] == KEY_IDLE) ? KEY_DOWN : KEY_REPEAT;
		else
			keys[i] = (keys[i] == KEY_REPEAT || keys[i] == KEY_DOWN) ? KEY_UP : KEY_IDLE;
	}


	return true;
}

//LOGIC (calls input)
bool Game::Update()
{
	//Read Input
	if (!Input()) {
		return true;
	}


	//LOGIC
	//Process Input
	 //Driection variables

	//Quit game
	if (keys[SDL_SCANCODE_ESCAPE] == KEY_DOWN) {
		return true;
	}

	//Move up
	if (keys[SDL_SCANCODE_SPACE] == KEY_REPEAT) {
		fy = -1;
		if (((Player.GetY() + PLAYER_HEIGHT) >= 600)) {
			jumpFlag = true;
		}
	}
	
	//Screen scroll
	Scene.Move(-1, 0);
	if (Scene.GetX() <= -Scene.GetWidth()) {
		Scene.SetX(0);
	}

	//Player update
	if (((Player.GetY() + PLAYER_HEIGHT) >= 600) || jumpFlag == true) {
		Player.Move(fx, fy);
		if ((Player.GetY() + PLAYER_HEIGHT) <= 400) {
			jumpFlag = false;
		}
	}
	else {
		Player.Move(0, 1);
	}
	//Obstacle update
	Obstc[0].Move(1, 0);
	Obstc[1].Move(1, 0);
	Obstc[2].Move(1, 0);

	//Collision 
	//if ((Player.GetX()+ Player.GetWidth()) == Obstc[0].GetX()) {
	//	Player.IsAlive = false;
	//}

	contSong--;
	if (contSong == 0) {
		Mix_FreeMusic(Music_Background);
		Music_Background = NULL;
		contSong = 19800;
	}
		

 	return false;
}

//DRAW	
void Game::Draw()
{
	//Crate auxiliar square to fill with object sizes
	SDL_Rect rc;

	//CLEAR rendering target
	SDL_RenderClear(Renderer);
	


	//DRAW
	//Draw scene
	Scene.GetRect(&rc.x, &rc.y, &rc.w, &rc.h);
	SDL_RenderCopy(Renderer, Texture_Background, NULL, &rc);
	rc.x += rc.w; //update x to draw the second background image
	SDL_RenderCopy(Renderer, Texture_Background, NULL, &rc);
	rc.x += rc.w; //update x to draw the second background image
	SDL_RenderCopy(Renderer, Texture_Background, NULL, &rc);

	//Draw player
	Player.GetRect(&rc.x, &rc.y, &rc.w, &rc.h);
	SDL_RenderCopy(Renderer, Texture_Player, NULL, &rc);

	//Draw obstacle
	Obstc[0].GetRect(&rc.x, &rc.y, &rc.w, &rc.h);
	SDL_RenderCopy(Renderer, Texture_Obstc, NULL, &rc);
	Obstc[1].GetRect(&rc.x, &rc.y, &rc.w, &rc.h);
	SDL_RenderCopy(Renderer, Texture_Obstc, NULL, &rc);
	Obstc[2].GetRect(&rc.x, &rc.y, &rc.w, &rc.h);
	SDL_RenderCopy(Renderer, Texture_Obstc, NULL, &rc);

	//UPDATE screen
	SDL_RenderPresent(Renderer);

	SDL_Delay(10);	// 1000/10 = 100 fps max
}