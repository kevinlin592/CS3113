//Kevin Lin
//My version of Space Invaders
//There is only a stage screen, a main menu screen, and a game over screen
//The instructions are shown on the screens when compiled

#include "hw_space_invaders.h"

int main(int argc, char *argv[])
{
	App app;

	while (!app.UpdateAndRender()){
	}
	return 0;
}