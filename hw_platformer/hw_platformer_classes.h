#include "hw_platformer.h"

enum GameState { STATE_MAIN_MENU, STATE_GAME_LEVEL, STATE_GAME_OVER };


class Entity{
public:
	void draw(int frame);
	void render();

	GLuint textureID;

	void resetcollision();

	bool collisionx(Entity entity);
	bool collisiony(Entity entity);
	bool collision(Entity entity);

	vector<float> u;
	vector<float> v;
	float scale;
	bool faceleft;

	float x;
	float y;

	float elapsed;
	int frame;

	float width;
	float height;

	float v_x;
	float v_y;

	float a_x;
	float a_y;

	float f_x;
	float f_y;

	bool alive;
	bool coin;
	bool dynamic;

	bool collidedTop;
	bool collidedBottom;
	bool collidedRight;
	bool collidedLeft;

	Entity(){};
	Entity(GLuint textureID0, float u0, float v0, float width, float height, float scale, bool dynamic, bool alive);
};

class App{
public:
	App();
	~App();

	void Init();
	bool UpdateAndRender();

	void Render();
	void Update();
private:
	int jumped;
	int enemyCount;
	void createEnemy();
	const Uint8* keys;
	bool done;
	float animation;
	GameState state;
	float lastFrameTicks;
	SDL_Window* displayWindow;
	GLuint font;

	Entity blocks[10];
	Entity enemy[25];
	int enemysize;
	float gravity;

	void reset();

	void RenderMainMenu();
	void RenderGameLevel();
	void RenderGameOver();

	void UpdateGameLevel();

	bool bumprightwall();
	bool bumpleftwall();
	float delay;
	Entity user;

	int score;
};