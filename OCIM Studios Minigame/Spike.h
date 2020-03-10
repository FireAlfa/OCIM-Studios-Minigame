#pragma once

#include "Entity.h"

#define MAX_SPIKES 20

class Spike : public Entity {
public:
	Spike();
	~Spike();

	int GetY();
	void Move(int dx);
};
