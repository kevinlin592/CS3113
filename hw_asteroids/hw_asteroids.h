#include "include.h"

#define FIXED_TIMESTEP 0.0166666f
#define MAX_TIMESTEPS 6
#define ASTEROIDS 5
float timeLeftOver = 0.0f;

using namespace std;


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

class Vector {
public:
	Vector();
	Vector(float a, float b, float c);
	float length();
	void normalize();
	float x;
	float y;
	float z;
};

class Matrix {
public:
	Matrix();
	Matrix(float a, float b, float c, float d, float e, float f, float g, float h, float i, float j, float k, float l, float n, float o, float p, float q);
	union {
		float m[4][4];
		float ml[16];
	};

	union {
		float m2[4][4];
		float ml2[16];
	};

	void identity();
	Matrix inverse();
	Matrix operator * (const Matrix &m2);
	Vector operator * (const Vector &v2);
};

class Entity{
public:
	void draw();
	void render();

	GLuint textureID;

	float u;
	float v;
	float scalex;
	float scaley;

	float scalex2;
	float scaley2;

	float rotation;

	float x;
	float y;

	float left;
	float right;
	float top;
	float bottom;

	float speed;
	void updateVector();

	Vector topleft;
	Vector topright;
	Vector bottomleft;
	Vector bottomright;

	float width;
	float height;

	Matrix matrix;
	Matrix inverse;
	void genMatrix();

	void setVector();
	void randomize();
	bool collision(Entity a);

	Vector vector;

	Entity(){};
	Entity(GLuint textureID, float u, float v, float width, float height, float scalex, float scaley)
		:textureID(textureID), u(u), v(v), width(width), height(height), scalex(scalex), scaley(scaley), scalex2(1.0f), scaley2(1.0f), rotation(0.0f){
		left = -width * scalex;
		right = width * scalex;
		top = height * scaley;
		bottom = -height * scaley;
		topleft = Vector(left, top, 1.0f);
		topright = Vector(right, top, 1.0f);
		bottomleft = Vector(left, bottom, 1.0f);
		bottomright = Vector(right, bottom, 1.0f);
	};
};

class App{
public:
	App();
	~App();

	void Init();
	bool UpdateAndRender();

	void Render();
	void Update(float elapsed);
private:
	const Uint8* keys;
	bool done;
	float lastFrameTicks;
	SDL_Window* displayWindow;

	Mix_Music* music;

	Entity asteroid[ASTEROIDS];
	int enemysize;

	void reset();

	void RenderGameLevel();

	bool bumprightwall();
	bool bumpleftwall();
	Entity user;

};