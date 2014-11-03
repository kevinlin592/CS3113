//Kevin Lin
//"Asteroids" with only movement

//Uses non-axis-aligned collisions
//Use up, down, left, and right to move the ship
//Only the user ship can collide with the asteroids
//Asteroids will pass through other ones
//Asteroids can be pushed, but their direction cannot be changed

#include "hw_asteroids.h"
#include "Entity.h"
#include "Matrix.h"
#include "Vector.h"
#include "App.h"

SDL_Window* displayWindow;

int main(int argc, char *argv[])
{

	App app;

	while (!app.UpdateAndRender()){
	}
	return 0;
}