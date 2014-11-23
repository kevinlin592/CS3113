#include "include.h"

#define FIXED_TIMESTEP 0.0166666f
#define MAX_TIMESTEPS 6
#define TOTAL_ENEMIES 100
#define LEFT -0.75f
#define RIGHT 0.75f
#define TOP 1.0f
#define BOTTOM -1.0f

enum state {MAIN_MENU, GAME_LEVEL_1, GAME_LEVEL_2, GAME_LEVEL_3};

float timeLeftOver = 0.0f;

using namespace std;

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

class Bullet{
public:
	Matrix matrix;
	float x;
	float y;

	float scalex;
	float scaley;

	void setVector();

	Vector vector;
	float width;
	float height;

	void draw();
	void update();
	void genMatrix();
	GLuint textureID;

	float scalex2;
	float scaley2;

	float rotation;

	float u;
	float v;
	float speed;

	float left;
	float right;
	float top;
	float bottom;

	Vector topleft;
	Vector topright;
	Vector bottomleft;
	Vector bottomright;
	Matrix inverse;

	Bullet(){};
	Bullet(GLuint textureID, float u, float v, float width, float height, float scalex, float scaley)
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

class Entity{
public:
	void draw();
	void render();
	void shoot(GLuint textureID, float u, float v, float width, float height, float scalex, float scaley, float rot, float speed);
	void shoot(GLuint textureID, float u, float v, float width, float height, float scalex, float scaley, float rot, float speed, float x2);

	GLuint textureID;

	float u;
	float v;
	float scalex;
	float scaley;

	float scalex2;
	float scaley2;

	float start;
	float stop;
	float resume;

	bool alive;
	bool active;

	vector<Bullet> bullets;

	float rotation;

	float x;
	float y;
	float timeToShoot;
	float hp;
	bool powerup;
	float power;

	float left;
	float right;
	float top;
	float bottom;

	float speed;
	void updateVector();

	string pos;
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

	int type;

	Entity(){};
	Entity(GLuint textureID, float u, float v, float width, float height, float scalex, float scaley, int type)
		:textureID(textureID), u(u), v(v), width(width), height(height), scalex(scalex), scaley(scaley), scalex2(1.0f), scaley2(1.0f), rotation(0.0f), type(type){
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
	float lastshot;
	state level;
	const Uint8* keys;
	bool done;
	float lastFrameTicks;
	SDL_Window* displayWindow;

	Mix_Music* music;

	Entity enemy[TOTAL_ENEMIES];
	int enemysize;

	void reset();
	void resetGameLevel1();
	void resetGameLevel2();
	void resetGameLevel3();

	float gametime;

	GLuint BulletTexture;
	GLuint SheetSpriteTexture;

	void RenderMainMenu();
	void RenderGameLevel1();
	void RenderGameLevel2();
	void RenderGameLevel3();

	void UpdateMainMenu();
	void UpdateGameLevel1(float elapsed);
	void UpdateGameLevel2(float elapsed);
	void UpdateGameLevel3(float elapsed);

	void cover();

	bool bumprightwall();
	bool bumpleftwall();
	Entity user;

};