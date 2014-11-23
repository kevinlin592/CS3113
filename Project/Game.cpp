//Kevin Lin

#include "Game.h"
#include "Bullet.h"
#include "Entity.h"
#include "Matrix.h"
#include "Vector.h"
#include "MiscFunctions.h"
#include "App.h"

SDL_Window* displayWindow;

int main(int argc, char *argv[])
{

	App app;

	while (!app.UpdateAndRender()){
	}
	return 0;
}