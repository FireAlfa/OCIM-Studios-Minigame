#pragma once

#include "Game.h"

class Entity
{
public:
	Entity();
	~Entity();

	void Init(int posx, int posy, int w, int h, int s);
	void GetRect(int* posx, int* posy, int* w, int* h);
	void SetX(int posx);
	int  GetX();
	int  GetWidth();
	void ShutDown();
	bool IsAlive();
	void Move(int dy);
	bool check_collision(SDL_Rect A, SDL_Rect B);

protected:
	int x, y;
	int width, height;
	int speed;
	bool is_alive;
};