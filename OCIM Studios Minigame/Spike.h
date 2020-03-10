#include "Entity.h"

class Spike : public Entity {
public:
	Spike();
	~Spike();


	int GetY();
	void Move(int dx);
};
