#include "Entity.h"

class Spike : public Entity {
public:
	Spike();
	~Spike();


	int GetY();
	void Move(int dx);
	
private:
	int x, y;
	int width, height;
	int speed;
	bool is_alive;
};
