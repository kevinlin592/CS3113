#include "include.h"

#define FIXED_TIMESTEP 0.0166666f
#define MAX_TIMESTEPS 6
#define TOTAL_ENEMIES 500
#define LEFT -0.75f
#define RIGHT 0.75f
#define TOP 1.0f
#define BOTTOM -1.0f

#define POWER1 30
#define POWER2 100
#define POWER3 200
#define POWER4 400
#define POWER5 600

enum state {MAIN_MENU, INSTRUCTIONS, GAME_LEVEL_1, GAME_LEVEL_2, GAME_LEVEL_3};

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

	unsigned int type;

	Bullet(){};
	Bullet(unsigned int type, GLuint textureID, float u, float v, float width, float height, float scalex, float scaley)
		:type(type), textureID(textureID), u(u), v(v), width(width), height(height), scalex(scalex), scaley(scaley), scalex2(1.0f), scaley2(1.0f), rotation(0.0f){
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
	void draw(float posx, float posy, float newscalex, float newscaley);
	void render();
	void shoot(unsigned int type, GLuint textureID, float u, float v, float width, float height, float scalex, float scaley, float rot, float speed);
	void shoot(unsigned int type, GLuint textureID, float u, float v, float width, float height, float scalex, float scaley, float rot, float speed, float x2);
	void shoot(unsigned int type, GLuint textureID, float u, float v, float width, float height, float scalex, float scaley, float rot, float speed, float x2, float y2);
	unsigned int shotType;

	GLuint textureID;

	bool hit;
	void drawhit();
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
	unsigned int form;

	float x;
	float y;
	float timeToShoot;
	int hp;
	bool between;
	bool powerup;
	unsigned int power;

	float left;
	float right;
	float top;
	float bottom;

	float speed;
	float speed2;
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

	void resetXY();

	Entity(){};
	Entity(GLuint textureID, float u, float v, float width, float height, float scalex, float scaley, int type)
		:textureID(textureID), hit(false), u(u), v(v), width(width), height(height), scalex(scalex), scaley(scaley), scalex2(1.0f), scaley2(1.0f), rotation(0.0f), type(type){
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

class Particle {
public:
	Vector position;
	Vector velocity;
	float lifetime;
	float sizeDeviation;
	Particle() :lifetime(0.0f), sizeDeviation(0.2f){
		float temp = (float)rand() / (float)RAND_MAX - 0.5f;
		float temp2 = (float)rand() / (float)RAND_MAX - 0.5f;
		//float temp3 = (float)rand() / (float)RAND_MAX * 0.4f + 1.5f;
		velocity = Vector(temp * 0.8f, temp2 * 0.8f, 0.0f);
		//position = Vector(temp3, 1.6f, 0.0f);
		//position = Vector(0.0f, 0.0f, 0.0f);
	};
};

class ParticleEmitter {
public:
	//ParticleEmitter(unsigned int particleCount) :maxLifetime(2.5f), startSize(0.1f), endSize(0.0f), particles(vector<Particle>(particleCount)){};
	ParticleEmitter(unsigned int particleCount, float x, float y) :maxLifetime(2.5f), totalTime(0.0f),
		particles(vector<Particle>(particleCount)){
		for (unsigned int i = 0; i < particles.size(); i++){
			particles[i].position = Vector(x, y, 0.0f);
		}
	};
	ParticleEmitter(){};
	//~ParticleEmitter(){};
	void Update(float elapsed);
	void Render();
	Vector position;
	float maxLifetime;
	float totalTime;
	vector<Particle> particles;

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
	int shotChannel;

	float lastshot;
	float lastmissile;
	unsigned int lives;
	state level;
	Entity userbox;
	const Uint8* keys;
	float invincible;
	bool done;
	float lastFrameTicks;
	unsigned int kills;
	SDL_Window* displayWindow;

	Entity enemy[TOTAL_ENEMIES];
	bool dying;
	float deathTime;
	float killTime;
	unsigned int score;
	vector<unsigned int> powerups;
	vector<unsigned int> enemies;

	Mix_Music* levelSong;
	Mix_Chunk* userShoot;
	Mix_Chunk* explosion;
	Mix_Chunk* dangerSound;
	Mix_Chunk* userExplosion;
	Mix_Chunk* move;

	int bossAlive;

	void reset();
	void resetMainMenu();
	void resetInstructions();
	void resetGameLevel1();
	void resetGameLevel2();
	void resetGameLevel3();
	void loadLevel(ifstream& input);

	float changetime;
	float dangerTime;
	unsigned int change;

	vector<ParticleEmitter> p;

	float gametime;
	void fadeIn();
	void transition(int mode);
	bool pause;
	void pauseState();

	GLuint BulletTexture;
	GLuint SheetSpriteTexture;
	GLuint MapTexture;
	GLuint FontTexture;
	GLuint IconTexture;
	GLuint LevelTexture;
	GLuint DangerTexture;

	void drawDanger();
	void drawMap();
	void drawLevel();
	void drawIcon();
	void drawTitle();
	void drawLevelBar();
	void drawPowerBar(unsigned int power);
	void drawPoint(bool top);

	float ypos;

	float setTime;
	float prevPos;
	float newPos;

	float alpha;
	float xpos;
	float xpos2;

	float mapWidth;
	float mapHeight;
	float mapAway;

	bool pointTop;

	void RenderMainMenu();
	void RenderInstructions();
	void RenderGameLevel();

	void UpdateMainMenu(float elapsed);
	void UpdateInstructions(float elapsed);
	void UpdateGameLevel(float elapsed);

	void cover();

	bool bumprightwall();
	bool bumpleftwall();
	Entity user;

};

