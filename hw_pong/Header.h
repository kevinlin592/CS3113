#pragma once
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <iostream>
#include <math.h>

class Paddle {
public:
	void Draw();
	void Reset(float pos){ x = pos; y = 0; };

	float x;
	float y;

	float h;
	float w;
	Paddle(float pos){ x = pos; y = 0; h = 0.15, w = 0.02; }
};

void Paddle::Draw(){
	glLoadIdentity();
	glTranslatef(x, y, 0);

	GLfloat rectangle[] = { -w, h, -w, -h, w, -h, w, h };
	glVertexPointer(2, GL_FLOAT, 0, rectangle);
	glEnableClientState(GL_VERTEX_ARRAY);

	glDrawArrays(GL_QUADS, 0, 4);
}

class Ball {
public:
	void Draw();
	void Reset(float angle){ x = 0; y = 0; d_x = cos(M_PI*angle / 180); d_y = sin(M_PI*angle / 180); };

	float x;
	float y;

	float size;

	float speed;
	float d_x;
	float d_y;
	Ball(float init_speed, float angle){ x = 0; y = 0; size = 0.04; speed = init_speed; d_x = cos(M_PI*angle / 180); d_y = sin(M_PI*angle / 180); }
};

void Ball::Draw(){
	glLoadIdentity();
	glTranslatef(x, y, 0);

	GLfloat square[] = { -size, size, -size, -size, size, -size, size, size };
	glVertexPointer(2, GL_FLOAT, 0, square);
	glEnableClientState(GL_VERTEX_ARRAY);

	glDrawArrays(GL_QUADS, 0, 4);
}

SDL_Window* displayWindow;