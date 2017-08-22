#include "LastMove.h"

LastMove::LastMove(){
	
	// -1 equates to no data
	// Initializes c,x,y,z to -1
	this->x = -1;
	this->y = -1;
	this->z = -1;
	this->color = -1;
}

LastMove::LastMove(int color, int x, int y, int z){
	
	// Initializes c,x,y,z to their respective inputs
	this->x = x;
	this->y = y;
	this->z = z;
	this->color = color;
}

void LastMove::recordColor(int color){
	
	// Records the input color
	this->color = color;
}

void LastMove::recordMove(int color, int x, int y, int z){
	
	// Records the input move
	this->x = x;
	this->y = y;
	this->z = z;
	this->color = color;
}

int LastMove::returnX(){
	
	// Recalls the input x position
	return this->x;
}

int LastMove::returnY(){
	
	// Recalls the input y position
	return this->y;
}

int LastMove::returnZ(){
	
	// Recalls the input z position
	return this->z;
}

int LastMove::returnColor(){
	
	// Recalls the input color
	return this->color;
}
	
void LastMove::dispMove(){
	
	// Displays the stored move
	printf("\nMove: %d, %d, %d\n", this->x, this->y, this->z);
	printf("Color: %d\n", this->color);
}
