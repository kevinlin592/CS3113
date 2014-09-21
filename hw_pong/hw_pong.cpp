//Simple 2 player pong imitation where the ball moves at a 45 degree angle
//Use w and s to control player 1
//Use up and down to control player 2
//A trophy will signify the winner of the game
//Press space whenever to reset the game

#include "Header.h"

GLuint LoadTexture(const char *image_path, GLenum format) {
	SDL_Surface *surface = IMG_Load(image_path);

	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexImage2D(GL_TEXTURE_2D, 0, 4, surface->w, surface->h, 0, format, GL_UNSIGNED_BYTE, surface->pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	SDL_FreeSurface(surface);

	return textureID;
}

void DrawSprite(GLint texture, float x, float y, float xscale, float yscale, float rotation) {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	glTranslatef(x, y, 0.0);
	glScalef(xscale, yscale, 1.0);
	glRotatef(rotation, 0.0, 0.0, 1.0);

	GLfloat quad[] = { -0.5f, 0.5f, -0.5f, -0.5f, 0.5f, -0.5f, 0.5f, 0.5f };
	glVertexPointer(2, GL_FLOAT, 0, quad);
	glEnableClientState(GL_VERTEX_ARRAY);

	GLfloat quadUVs[] = { 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0 };
	glTexCoordPointer(2, GL_FLOAT, 0, quadUVs);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glDrawArrays(GL_QUADS, 0, 4);
	glDisable(GL_TEXTURE_2D);
}

void Setup(){
	SDL_Init(SDL_INIT_VIDEO);
	displayWindow = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
	SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
	SDL_GL_MakeCurrent(displayWindow, context);
}

void PreProcesses(){
	glViewport(0, 0, 800, 600);
	glMatrixMode(GL_PROJECTION);
	glOrtho(-1.33, 1.33, -1.0, 1.0, -1.0, 1.0);
}

void Update(Ball& b){
	b.x += b.d_x*b.speed;
	b.y += b.d_y*b.speed;
}

bool CollisionX(Ball b){
	if (abs(b.y) + b.size > 1){
		return true;
	}
	else {
		return false;
	}
}

bool CollisionY(Ball b, Paddle p1, Paddle p2){
	if (((b.x + b.size<p1.x - p1.w) || (b.x - b.size>p1.x + p1.w) || (b.y + b.size<p1.y - p1.h) || (b.y - b.size>p1.y + p1.h)) && ((b.x + b.size<p2.x - p2.w) || (b.x - b.size>p2.x + p2.w) || (b.y + b.size<p2.y - p2.h) || (b.y - b.size>p2.y + p2.h))){
		return false;
	}
	else{
		return true;
	}
}

void Render(Paddle p1, Paddle p2, Ball b, GLuint wins){
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);


	p1.Draw();
	p2.Draw();
	b.Draw();

	if (b.x + b.size < p1.x - p1.w){
		DrawSprite(wins, 1.1, 0.8, 0.1, 0.08, 0);
	}
	else if (b.x - b.size > p2.x + p2.w){
		DrawSprite(wins, -1.1, 0.8, 0.1, 0.08, 0);
	}
}

void PaddleMovement(const Uint8* keys, float& pos1, float& pos2){
	if (keys[SDL_SCANCODE_W]){
		pos1 += 0.0005;
	}
	else if (keys[SDL_SCANCODE_S]){
		pos1 -= 0.0005;
	}
	if (keys[SDL_SCANCODE_UP]){
		pos2 += 0.0005;
	}
	else if (keys[SDL_SCANCODE_DOWN]){
		pos2 -= 0.0005;
	}
}


int main(int argc, char *argv[])
{
	Setup();

	bool done = false;

	SDL_Event event;

	PreProcesses();

	const Uint8* keys = SDL_GetKeyboardState(NULL);

	Paddle p1(-0.9);
	Paddle p2(0.9);
	float angle[] = { 45, 135, 225, 315 };
	int choice = floor(rand() % 4);
	Ball ball(0.0005, angle[choice]);

	GLuint wins = LoadTexture("wins.png", GL_RGBA);

	while (!done) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
				done = true;
			}
			else if (event.type == SDL_KEYDOWN){
				if (event.key.keysym.scancode == SDL_SCANCODE_SPACE){
					p1.Reset(-0.9);
					p2.Reset(0.9);
					choice = floor(rand() % 4);
					ball.Reset(angle[choice]);
				}
			}

		}

		if (CollisionX(ball)){
			ball.d_y = -ball.d_y;
		}

		if (CollisionY(ball, p1, p2)){
			if (ball.x > 0){
				ball.d_x = -abs(ball.d_x);
			}
			else {
				ball.d_x = abs(ball.d_x);
			}
		}

		PaddleMovement(keys, p1.y, p2.y);

		Update(ball);
		Render(p1, p2, ball, wins);

		SDL_GL_SwapWindow(displayWindow);
	}

	SDL_Quit();
	return 0;
}