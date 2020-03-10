#include "Spike.h"

Spike::Spike() {
	is_alive = false;
}

Spike::~Spike() {

}

int Spike::GetY() {
	return y;
}

void Spike::Move(int dx){
	Spike::x *= dx * (-speed);
}