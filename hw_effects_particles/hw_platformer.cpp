//Kevin Lin
//My simple platformer
//There is only a stage screen, a main menu screen, and a game over screen
//The instructions are shown on the screens when compiled

#include "hw_platformer.h"
#include "hw_platformer_classes.h"
#include "hw_platformer_read_map.h"

#define FIXED_TIMESTEP 0.0166666f
#define MAX_TIMESTEPS 6
#define TOTAL_ENEMIES 15
#define TOTAL_PRIZES 2
#define SPRITE_COUNT_X 13
#define SPRITE_COUNT_Y 8
#define TILE_WIDTH 0.3f
#define TILE_HEIGHT 0.3f
float timeLeftOver = 0.0f;


float lerp(float v0, float v1, float t) {
	return (1.0f - t)*v0 + t*v1;
}

Vector::Vector(){
	x = 1.0f;
	y = 1.0f;
	z = 1.0f;
	normalize();
}

Vector::Vector(float a, float b, float c){
	x = a;
	y = b;
	z = c;
}

float Vector::length(){
	return sqrtf(x*x + y*y + z*z);
}

void Vector::normalize(){
	float dist = length();
	x /= dist;
	y /= dist;
	z /= dist;
}

void ParticleEmitter::Render(){
	glPushMatrix();
	glLoadIdentity();
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	vector<float> particleVertices;
	
	for (unsigned int i = 0; i < particles.size(); i++) {
		particleVertices.push_back(particles[i].position.x);
		particleVertices.push_back(particles[i].position.y);
	}

	glVertexPointer(2, GL_FLOAT, 0, particleVertices.data());
	glEnableClientState(GL_VERTEX_ARRAY);
	
	vector<float> particleColors;
	for (unsigned int i = 0; i < particles.size(); i++) {
		float m = (particles[i].lifetime / maxLifetime);
		particleColors.push_back(lerp(1.0f, 1.0f, m));
		particleColors.push_back(lerp(1.0f, 1.0f, m));
		particleColors.push_back(lerp(1.0f, 1.0f, m));
		particleColors.push_back(lerp(1.0f, 0.0f, m));
	}
	glColorPointer(4, GL_FLOAT, 0, particleColors.data());
	glEnableClientState(GL_COLOR_ARRAY);
	
	glDrawArrays(GL_POINTS, 0, particleVertices.size() / 2);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glPopMatrix();
}

void ParticleEmitter::Update(float elapsed){
	for (unsigned int i = 0; i < particles.size(); i++){
		particles[i].lifetime += elapsed;
		particles[i].position.x += particles[i].velocity.x*elapsed;
		particles[i].position.y += particles[i].velocity.y*elapsed;
	}
}

float easeIn(float from, float to, float time) {
	float tVal = time*time*time*time*time;
	return (1.0f - tVal)*from + tVal*to;
}

float mapValue(float value, float srcMin, float srcMax, float dstMin, float dstMax) {
	float retVal = dstMin + ((value - srcMin) / (srcMax - srcMin) * (dstMax - dstMin));
	if (retVal < dstMin) {
		retVal = dstMin;
	}
	if (retVal > dstMax) {
		retVal = dstMax;
	}
	return retVal;
}

GLuint LoadTexture(const char *image_path, GLenum format) {
	SDL_Surface *surface = IMG_Load(image_path);

	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexImage2D(GL_TEXTURE_2D, 0, 4, surface->w, surface->h, 0, format, GL_UNSIGNED_BYTE, surface->pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	SDL_FreeSurface(surface);

	return textureID;
}

void drText(int fontTexture, string text, float size, float spacing, float r, float g, float b, float a, float x, float y) {
	glBindTexture(GL_TEXTURE_2D, fontTexture);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glLoadIdentity();
	glTranslatef(x, y, 0.0f);
	float texture_size = 1.0 / 16.0f;
	vector<float> vertexData;
	vector<float> texCoordData;
	vector<float> colorData;
	for (unsigned int i = 0; i < text.size(); i++) {
		float texture_x = (float)(((int)text[i]) % 16) / 16.0f;
		float texture_y = (float)(((int)text[i]) / 16) / 16.0f;

		colorData.insert(colorData.end(), { r, g, b, a, r, g, b, a, r, g, b, a, r, g, b, a });
		vertexData.insert(vertexData.end(), { ((size + spacing) * i) + (-0.5f * size), 0.5f * size, ((size + spacing) * i) +
			(-0.5f * size), -0.5f * size, ((size + spacing) * i) + (0.5f * size), -0.5f * size, ((size + spacing) * i) + (0.5f * size), 0.5f
			* size });
		texCoordData.insert(texCoordData.end(), { texture_x, texture_y, texture_x, texture_y + texture_size, texture_x +
			texture_size, texture_y + texture_size, texture_x + texture_size, texture_y });
	}
	glColorPointer(4, GL_FLOAT, 0, colorData.data());
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, vertexData.data());
	glEnableClientState(GL_VERTEX_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 0, texCoordData.data());
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glDrawArrays(GL_QUADS, 0, text.size() * 4);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

Entity::Entity(GLuint textureID, float u0, float v0, float width, float height, float scalex, float scaley, bool dynamic = false, bool alive = false) :
textureID(textureID), width(width), height(height), scalex(scalex), scaley(scaley), dynamic(dynamic), alive(alive), frame(0), coin(false), a_y(0.0f), collidedTop(false), collidedBottom(false), collidedRight(false), collidedLeft(false), active(false){
	u.push_back(u0);
	v.push_back(v0);
};

void Entity::resetcollision(){
	collidedBottom = false;
	collidedLeft = false;
	collidedRight = false;
	collidedTop = false;
}

bool Entity::collision(Entity entity){
	float widthhalf1 = width*scalex;
	float widthhalf2 = entity.width*entity.scalex;
	float heighthalf1 = height*scaley;
	float heighthalf2 = entity.height*entity.scaley;
	float left1 = x - widthhalf1;
	float right1 = x + widthhalf1;
	float top1 = y + heighthalf1;
	float bottom1 = y - heighthalf1;
	float left2 = entity.x - widthhalf2;
	float right2 = entity.x + widthhalf2;
	float top2 = entity.y + heighthalf2;
	float bottom2 = entity.y - heighthalf2;
	if ((right1<left2) || (left1>right2) ||
		(top1<bottom2) || (bottom1>top2)){
		return false;
	}
	return true;
}

bool App::collisionx(Entity &entity){
	float widthhalf = entity.width*entity.scalex;
	float heighthalf = entity.height*entity.scaley;
	float left1 = entity.x - widthhalf;
	float right1 = entity.x + widthhalf;

	worldtoTileCoordinates(left1, entity.y, entity.gridx, entity.gridy);
	if (levelData[entity.gridy][entity.gridx] != 0){
		tiletoWorldCoordinatesx(entity.x_pen, entity.gridx + 1);
		entity.x_pen -= left1;
		entity.x += entity.x_pen + 0.01f;
		entity.collidedLeft = true;
		return true;
	}
	worldtoTileCoordinates(right1, entity.y, entity.gridx, entity.gridy);
	if (levelData[entity.gridy][entity.gridx] != 0){
		tiletoWorldCoordinatesx(entity.x_pen, entity.gridx);
		entity.x_pen = right1 - entity.x_pen;
		entity.x -= (entity.x_pen + 0.01f);
		entity.collidedRight = true;
		return true;
	}
	return false;
}

bool App::collisiony(Entity &entity){
	worldtoTileCoordinates(entity.x, entity.y, entity.gridx, entity.gridy);
	float widthhalf = entity.width*entity.scalex;
	float heighthalf = entity.height*entity.scaley;
	float bottom1 = entity.y - heighthalf;
	float top1 = entity.y + heighthalf;

	worldtoTileCoordinates(entity.x, bottom1, entity.gridx, entity.gridy);
	if (levelData[entity.gridy][entity.gridx] != 0){
		tiletoWorldCoordinatesy(entity.y_pen, entity.gridy);
		entity.y_pen -= bottom1;
		entity.y += (entity.y_pen);
		entity.v_y = 0.0f;
		entity.collidedBottom = true;
		return true;
	}

	worldtoTileCoordinates(entity.x, top1, entity.gridx, entity.gridy);
	if (levelData[entity.gridy][entity.gridx] != 0){
		tiletoWorldCoordinatesy(entity.y_pen, entity.gridy + 1);
		entity.y_pen = top1 - entity.y_pen;
		entity.y -= (entity.y_pen + 0.01f);
		entity.v_y = 0.0f;
		entity.collidedTop = true;
		return true;
	}
	return false;
}

bool Entity::collisionx(Entity entity){
	float widthhalf1 = width*scalex;
	float widthhalf2 = entity.width*entity.scalex;
	float heighthalf1 = height*scaley;
	float heighthalf2 = entity.height*entity.scaley;
	float left1 = x - widthhalf1;
	float right1 = x + widthhalf1;
	float top1 = y + heighthalf1;
	float bottom1 = y - heighthalf1;
	float left2 = entity.x - widthhalf2;
	float right2 = entity.x + widthhalf2;
	float top2 = entity.y + heighthalf2;
	float bottom2 = entity.y - heighthalf2;
	if ((right1<left2) || (left1>right2) ||
		(top1<bottom2) || (bottom1>top2)){
		return false;
	}
	float xdist = fabs(x - entity.x);
	float x_pen = fabs(xdist - widthhalf1 - widthhalf2) + 0.0001f;
	if (right1 > right2) {
		collidedLeft = true;
		x += x_pen;
		return true;
	}
	else {
		x -= x_pen;
		collidedRight = true;
		return true;
	}
	return true;
}

bool Entity::collisiony(Entity entity){
	float widthhalf1 = width*scalex;
	float widthhalf2 = entity.width*entity.scalex;
	float heighthalf1 = height*scaley;
	float heighthalf2 = entity.height*entity.scaley;
	float left1 = x - widthhalf1;
	float right1 = x + widthhalf1;
	float top1 = y + heighthalf1;
	float bottom1 = y - heighthalf1;
	float left2 = entity.x - widthhalf2;
	float right2 = entity.x + widthhalf2;
	float top2 = entity.y + heighthalf2;
	float bottom2 = entity.y - heighthalf2;
	if ((right1<left2) || (left1>right2) ||
		(top1<bottom2) || (bottom1>top2)){
		return false;
	}
	float ydist = fabs(y - entity.y);
	y_pen = fabs(ydist - heighthalf1 - heighthalf2) + 0.0001f;
	if (bottom1 > bottom2) {
		collidedBottom = true;
		y += y_pen;
		return true;
	}
	else {
		collidedTop = true;
		y -= y_pen;
		return true;
	}
}

void Entity::draw(int frame) {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureID);

	//glLoadIdentity();

	glPushMatrix();
	glTranslatef(x, y, 0.0f);

	GLfloat quad[] = { -width * scalex, height * scaley, -width * scalex, -height * scaley,
		width * scalex, -height * scaley, width * scalex, height * scaley };

	glVertexPointer(2, GL_FLOAT, 0, quad);
	glEnableClientState(GL_VERTEX_ARRAY);

	float blackline = 0.0035f;
	GLfloat quadUVs[] = { u[frame] + blackline, v[frame] + blackline, 
		u[frame] + blackline, v[frame] + height - blackline,
		u[frame] + width - blackline, v[frame] + height - blackline,
		u[frame] + width - blackline, v[frame] + blackline };
	glTexCoordPointer(2, GL_FLOAT, 0, quadUVs);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glDrawArrays(GL_QUADS, 0, 4);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glPopMatrix();
}

void Entity::render(){
	if (alive == true){
		draw(frame);
	}
	else if (coin == true){
		draw(6);
	}
}

void App::reset(){
	score = 0;
	delay = 0.0f;
	enemyCount = 0;
	alpha = 1.0f;

	GLuint SheetSpriteTexture = LoadTexture("sprites.png", GL_RGBA);

	int width = 0;
	int height = 0;
	unsigned char ** map = NULL;
	mapRead(width, height, map);
	buildLevel(map, height, width);
	shakeStart = 0.0f;
	shakeEnd = 0.0f;

	genLevel();
	


	fill_n(enemy, TOTAL_ENEMIES, Entity(SheetSpriteTexture, 9.0f / 13.0f, 1.0f / 8.0f, 1.0f / 13.0f, 1.0f / 8.0f, 0.8f, true));
	fill_n(prize, TOTAL_PRIZES, Entity(SheetSpriteTexture, 12.0f / 13.0f, 2.0f / 8.0f, 1.0f / 13.0f, 1.0f / 8.0f, 0.7f, 0.7f, true, true));
	for (int i = 0; i < TOTAL_ENEMIES; i++){
		enemy[i].u.push_back(10.0f / 13.0f);
		enemy[i].v.push_back(1.0f / 8.0f);
		enemy[i].u.push_back(11.0f / 13.0f);
		enemy[i].v.push_back(1.0f / 8.0f);
		enemy[i].u.push_back(9.0f / 13.0f);
		enemy[i].v.push_back(2.0f / 8.0f);
		enemy[i].u.push_back(10.0f / 13.0f);
		enemy[i].v.push_back(2.0f / 8.0f);
		enemy[i].u.push_back(11.0f / 13.0f);
		enemy[i].v.push_back(2.0f / 8.0f);
		enemy[i].u.push_back(12.0f / 13.0f);
		enemy[i].v.push_back(2.0f / 8.0f);
	}

	enemy[0].x = 4.0f;
	enemy[0].y = -7.7f;
	enemy[1].x = 6.5f;
	enemy[1].y = -7.7f;
	enemy[2].x = 7.2f;
	enemy[2].y = -7.7f;
	enemy[3].x = 11.5f;
	enemy[3].y = -7.7f;
	enemy[4].x = 12.5f;
	enemy[4].y = -7.7f;
	enemy[5].x = 13.5f;
	enemy[5].y = -7.7f;
	enemy[6].x = 13.9f;
	enemy[6].y = -2.0f;
	enemy[7].x = 14.2f;
	enemy[7].y = -2.0f;
	enemy[8].x = 14.5f;
	enemy[8].y = -2.0f;
	enemy[9].x = 14.8f;
	enemy[9].y = -2.0f;
	enemy[10].x = 15.1f;
	enemy[10].y = -2.0f;
	enemy[11].x = 24.8f;
	enemy[11].y = -5.6f;
	enemy[12].x = 26.8f;
	enemy[12].y = -4.7f;
	enemy[13].x = 28.3f;
	enemy[13].y = -4.1f;
	enemy[14].x = 33.0f;
	enemy[14].y = -1.4f;

	createEnemy();

	prize[0].x = 8.76f;
	prize[0].y = -9.21f;
	prize[1].x = 12.96f;
	prize[1].y = -4.11f;


	user = Entity(SheetSpriteTexture, 6.0f / 13.0f, 1.0f / 8.0f, 1.0f / 13.0f, 1.0f / 8.0f, 0.8f, 0.8f, true, true);
	user.u.push_back(7.0f / 13.0f);
	user.v.push_back(1.0f / 8.0f);
	user.u.push_back(8.0f / 13.0f);
	user.v.push_back(1.0f / 8.0f);
	user.u.push_back(6.0f / 13.0f);
	user.v.push_back(2.0f / 8.0f);
	user.u.push_back(7.0f / 13.0f);
	user.v.push_back(2.0f / 8.0f);
	user.u.push_back(8.0f / 13.0f);
	user.v.push_back(2.0f / 8.0f);
	user.x = 1.8f;
	user.y = -7.5f;
	user.v_x = 0.0f;
	user.v_y = 0.0f;
	user.f_x = 7.0f;
	user.f_y = 1.0f;
	user.a_x = 0.0f;
	user.elapsed = 0.0f;
	user.faceleft = false;

}

App::App() {
	Init();

	keys = SDL_GetKeyboardState(NULL);

	glViewport(0, 0, 800, 600);
	glMatrixMode(GL_PROJECTION);
	glOrtho(-2.66, 2.66, -2.0, 2.0, -2.0, 2.0);

	state = STATE_MAIN_MENU;

	jumped = 0;
	gravity = -9.81f;
	done = false;
	lastFrameTicks = 0.0f;
	enemysize = 12;
	enemyCount = 0;
	animation = 0.0f;
	levelheight = 0;
	levelwidth = 0;
	screenShakeIntensity = 0.0f;
	screenShakeValue = 0.0f;
	screenShakeSpeed = 40.0f;

	sprites = LoadTexture("sprites.png", GL_RGBA);
	font = LoadTexture("font.png", GL_RGBA);

	glMatrixMode(GL_MODELVIEW);

}

void App::Init() {
	SDL_Init(SDL_INIT_VIDEO);
	displayWindow = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
	SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
	SDL_GL_MakeCurrent(displayWindow, context);

}

App::~App() {
	if (levelheight != 0 && levelwidth != 0){
		freeLevel();
	}
	SDL_Quit();
}

void App::Render() {
	switch (state) {
	case STATE_MAIN_MENU:
		RenderMainMenu();
		break;
	case STATE_GAME_LEVEL:
		RenderGameLevel();
		break;
	case STATE_GAME_OVER:
		RenderGameOver();
		break;
	}
	SDL_GL_SwapWindow(displayWindow);
}

void App::RenderMainMenu(){
	glClearColor(0.4f, 0.5f, 0.9f, 0.0f);

	glClear(GL_COLOR_BUFFER_BIT);
	
	drText(font, "Jumpin' Alice 2", 0.6f, -0.32f, 1.0f, 1.0f, 1.0f, 1.0f, -1.87f, 1.0f);
	drText(font, "Press SPACE to play!", 0.4f, -0.2f, 1.0f, 1.0f, 1.0f, 1.0f, -1.87f, -1.3f);
	drText(font, "Use the left and right arrow keys to move.", 0.2f, -0.1f, 1.0f, 1.0f, 1.0f, 1.0f, -1.8f, 0.4f);
	drText(font, "Use z to jump on the monsters for 100 points.", 0.2f, -0.1f, 1.0f, 1.0f, 1.0f, 1.0f, -1.8f, 0.2f);
	drText(font, "You can double-jump.", 0.2f, -0.1f, 1.0f, 1.0f, 1.0f, 1.0f, -1.8f, 0.0f);
	drText(font, "Collect the dropped coins before they", 0.2f, -0.1f, 1.0f, 1.0f, 1.0f, 1.0f, -1.8f, -0.2f);
	drText(font, "disappear for 200 points.", 0.2f, -0.1f, 1.0f, 1.0f, 1.0f, 1.0f, -1.8f, -0.4f);
	drText(font, "If you fall or touch the monsters you lose!", 0.2f, -0.1f, 1.0f, 1.0f, 1.0f, 1.0f, -1.8f, -0.6f);
	drText(font, "Reach the end to win!", 0.2f, -0.1f, 1.0f, 1.0f, 1.0f, 1.0f, -1.8f, -0.8f);
	
	
	/*
	//glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	GLfloat fade[] = { -10.0f, 10.0f, -10.0f, -10.0f, 10.0f, -10.0f, 10.0f, 10.0f };
	glVertexPointer(2, GL_FLOAT, 0, fade);
	glEnableClientState(GL_VERTEX_ARRAY);
	GLfloat fadecolors[] = { 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f };
	glColorPointer(4, GL_FLOAT, 0, fadecolors);
	glEnableClientState(GL_COLOR_ARRAY);
	glDrawArrays(GL_QUADS, 0, 4);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	*/
}

void App::createEnemy(){
	for (int i = 0; i < TOTAL_ENEMIES; i++){
		//enemy[i].width = 1.0f / 13.0f;
		//enemy[i].height = 1.0f / 8.0f;
		enemy[i].elapsed = 0.0f;
		enemy[i].alive = true;
		//enemy[i].y = 2.5f;
		//enemy[i].x = ((float)rand() / RAND_MAX - 0.5f) / 2.5f;

		
		enemy[i].a_x = -0.35f;
		enemy[i].v_x = -0.65f;
		enemy[i].f_x = 0.35f;
		enemy[i].f_y = 0.35f;
		enemy[i].v_y = 0.0f;
		
		enemy[i].coin = false;
		enemy[i].scalex = 0.8f;
		enemy[i].scaley = 0.8f;
	}
}

void App::RenderGameLevel(){

	glClearColor(0.4f, 0.5f, 0.9f, 0.0f);

	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();

	glTranslatef(0.0f, sinf(screenShakeValue * screenShakeSpeed) * screenShakeIntensity, 0.0f);
	if (user.x < 1.8f){
		glTranslatef(-1.8f, 0.0f, 0.0f);
	}
	else {
		glTranslatef(-user.x, 0.0f, 0.0f);
	}

	if (user.y < -8.5f){
		glTranslatef(0.0f, 8.5f, 0.0f);
	}
	else {
		glTranslatef(0.0f, -user.y, 0.0f);
	}
	user.render();

	p.Render();


	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, sprites);
	glEnable(GL_TEXTURE_2D);

	glVertexPointer(2, GL_FLOAT, 0, vertexData.data());
	glEnableClientState(GL_VERTEX_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 0, texCoordData.data());
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDrawArrays(GL_QUADS, 0, vertexData.size() / 2);

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glPopMatrix();

	worldtoTileCoordinates(user.x, user.y, user.gridx, user.gridy);






	for (int i = 0; i < TOTAL_ENEMIES; i++){
		if (enemy[i].active){
			enemy[i].render();
		}
	}

	for (int i = 0; i < TOTAL_PRIZES; i++){
		prize[i].render();
	}

	
	drText(font, "Score", 0.3f, -0.15f, 1.0f, 1.0f, 1.0f, 1.0f, 1.5f, 1.85f);

	drText(font, to_string(score), 0.3f, -0.15f, 1.0f, 1.0f, 1.0f, 1.0f, 1.5f, 1.6f);
	
	float val = mapValue(user.elapsed, 0.0f, 1.0f, 0.0f, 1.0f);
	alpha = lerp(1.0f, 0.0f, val);

	glDisable(GL_TEXTURE_2D);
	GLfloat fade[] = { -100.0f, 100.0f, -100.0f, -100.0f, 100.0f, -100.0f, 100.0f, 100.0f };
	glVertexPointer(2, GL_FLOAT, 0, fade);
	glEnableClientState(GL_VERTEX_ARRAY);
	GLfloat fadecolors[] = { 0.0f, 0.0f, 0.0f, alpha, 0.0f, 0.0f, 0.0f, alpha, 0.0f, 0.0f, 0.0f, alpha, 0.0f,0.0f,0.0f,alpha };
	glColorPointer(4, GL_FLOAT, 0, fadecolors);
	glEnableClientState(GL_COLOR_ARRAY);
	glDrawArrays(GL_QUADS, 0, 4);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

}

void App::RenderGameOver(){
	glClearColor(0.4f, 0.5f, 0.9f, 0.0f);

	glClear(GL_COLOR_BUFFER_BIT);

	drText(font, "Your final score:", 0.2f, -0.1f, 1.0f, 1.0f, 1.0f, 1.0f, -0.8f, 0.45f);
	drText(font, to_string(score), 0.2f, -0.1f, 1.0f, 1.0f, 1.0f, 1.0f, -0.1f, 0.2f);

	drText(font, "Press SPACE to play again!", 0.2f, -0.1f, 1.0f, 1.0f, 1.0f, 1.0f, -1.25f, -0.2f);
	drText(font, "Press ENTER to go to the", 0.2f, -0.1f, 1.0f, 1.0f, 1.0f, 1.0f, -1.15f, -0.4f);
	drText(font, "main menu!", 0.2f, -0.1f, 1.0f, 1.0f, 1.0f, 1.0f, -0.45f, -0.55f);
}


void App::Update() {

	if (state == STATE_GAME_LEVEL){
		UpdateGameLevel();
	}

	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
			done = true;
		}
		else if (event.type == SDL_KEYDOWN){
			if (state == STATE_GAME_LEVEL && event.key.keysym.scancode == SDL_SCANCODE_Z && !event.key.repeat){
				if (jumped == 0 && user.collidedBottom) {
					user.y += 0.05f;
					user.v_y = 3.85f;
					jumped = 1;
				}
				else if (jumped < 2) {
					user.v_y = 3.1f;
					jumped = 2;
				}
			}

			if (state == STATE_GAME_OVER){
				if (event.key.keysym.scancode == SDL_SCANCODE_RETURN){
					state = STATE_MAIN_MENU;
				}
				else if (event.key.keysym.scancode == SDL_SCANCODE_SPACE){
					state = STATE_GAME_LEVEL;
					reset();
				}
			}
			if (event.key.keysym.scancode == SDL_SCANCODE_SPACE && state == STATE_MAIN_MENU){
				state = STATE_GAME_LEVEL;
				reset();
			}


		}
	}
}

void App::worldtoTileCoordinates(float x, float y, int &gridx, int &gridy){
	gridx = (int)((x) / TILE_WIDTH);
	gridy = (int)((-y) / TILE_HEIGHT);
}

void App::tiletoWorldCoordinatesx(float &x, int gridx){
	x = ((float)gridx)*TILE_WIDTH;
}

void App::tiletoWorldCoordinatesy(float &y, int gridy){
	y = -((float)gridy)*TILE_HEIGHT;
}

void App::UpdateGameLevel(){
	if (user.y < -11.0f){
		state = STATE_GAME_OVER;
		p.particles.clear();
		freeLevel();
		return;
	}
	if (user.x > 35.5f){
		state = STATE_GAME_OVER;
		p.particles.clear();
		freeLevel();
		return;
	}

	p.Update(FIXED_TIMESTEP);

	float animation;

	screenShakeValue += FIXED_TIMESTEP;

	for (int i = 0; i < TOTAL_ENEMIES; i++){
		if (fabs(enemy[i].x - user.x) < 2.66f && fabs(enemy[i].y - user.y) < 2.0f){
			enemy[i].active = true;
		}
	}

	for (int i = 0; i < TOTAL_ENEMIES; i++){
		if (enemy[i].active){
			if (enemy[i].coin){
				enemy[i].resetcollision();

				enemy[i].v_y = lerp(enemy[i].v_y, 0.0f, FIXED_TIMESTEP * enemy[i].f_y);
				enemy[i].v_y += enemy[i].a_y * FIXED_TIMESTEP;
				enemy[i].v_y += gravity * FIXED_TIMESTEP;
				enemy[i].y += enemy[i].v_y * FIXED_TIMESTEP;
				collisiony(enemy[i]);

				enemy[i].elapsed += FIXED_TIMESTEP;

				if (enemy[i].y < -11.0f){
					enemy[i].active = false;
				}
			}

			else if (enemy[i].alive && enemy[i].y < -11.0f){
				enemy[i].alive = false;
			}

			enemy[i].elapsed += FIXED_TIMESTEP;

			animation = fmod(enemy[i].elapsed, FIXED_TIMESTEP*15.0f);
			enemy[i].faceleft = (enemy[i].v_x < 0);
			if (enemy[i].faceleft) {
				if (animation < FIXED_TIMESTEP*5.0f){
					enemy[i].frame = 0;
				}
				else if (animation < FIXED_TIMESTEP*10.0f){
					enemy[i].frame = 1;
				}
				else {
					enemy[i].frame = 2;
				}
			}
			else {
				if (animation < FIXED_TIMESTEP*5.0f){
					enemy[i].frame = 3;
				}
				else if (animation < FIXED_TIMESTEP*10.0f){
					enemy[i].frame = 4;
				}
				else {
					enemy[i].frame = 5;
				}
			}


			if (enemy[i].alive){
			enemy[i].resetcollision();
			
			
			enemy[i].v_y = lerp(enemy[i].v_y, 0.0f, FIXED_TIMESTEP * enemy[i].f_y);
			enemy[i].v_y += enemy[i].a_y * FIXED_TIMESTEP;
			enemy[i].v_y += gravity * FIXED_TIMESTEP;
			enemy[i].y += enemy[i].v_y * FIXED_TIMESTEP;
			collisiony(enemy[i]);

			enemy[i].v_x = lerp(enemy[i].v_x, 0.0f, FIXED_TIMESTEP * enemy[i].f_x);
			enemy[i].v_x += enemy[i].a_x * FIXED_TIMESTEP;
			enemy[i].x += enemy[i].v_x * FIXED_TIMESTEP;
				collisionx(enemy[i]);
				if (enemy[i].collidedLeft){
					enemy[i].v_x = fabs(enemy[i].v_x);
					enemy[i].a_x = fabs(enemy[i].a_x);
				}
				else if (enemy[i].collidedRight){
					enemy[i].v_x = -fabs(enemy[i].v_x);
					enemy[i].a_x = -fabs(enemy[i].a_x);
				}
			}
			

		}
	}

	user.elapsed += FIXED_TIMESTEP;

	animation = fmod(user.elapsed, FIXED_TIMESTEP*15.0f);

	if (user.faceleft) {
		if (fabs(user.v_x) < 0.2f){
			user.frame = 1;
		}
		else if (animation < FIXED_TIMESTEP*5.0f){
			user.frame = 0;
		}
		else if (animation < FIXED_TIMESTEP*10.0f){
			user.frame = 1;
		}
		else {
			user.frame = 2;
		}
	}
	else {
		if (fabs(user.v_x) < 0.2f){
			user.frame = 4;
		}
		else if (animation < FIXED_TIMESTEP*5.0f){
			user.frame = 3;
		}
		else if (animation < FIXED_TIMESTEP*10.0f){
			user.frame = 4;
		}
		else {
			user.frame = 5;
		}
	}

	float temp = -user.v_y;

	user.v_y = lerp(user.v_y, 0.0f, FIXED_TIMESTEP * user.f_y);
	user.v_y += user.a_y * FIXED_TIMESTEP;
	user.v_y += gravity * FIXED_TIMESTEP;
	user.y += user.v_y * FIXED_TIMESTEP;

	user.scaley = mapValue(fabs(user.v_y), 0.0f, 8.0f, 0.8f, 1.5f);
	user.scalex = mapValue(fabs(user.v_y), 5.0f, 0.0f, 0.8f, 1.0f);

	user.resetcollision();

	if (collisionx(user)){
		user.v_x = 0.0f;
	};
	collisiony(user);

	//float animationtime = mapValue(user.elapsed, user.elapsed, user.elapsed + 1.0f, 0.0f, 1.0f);
	//float animationtime = 1.0f;

	if (user.collidedBottom && jumped != 0){
		shakeStart = user.elapsed + 0.01f;
		shakeEnd = user.elapsed + 0.1f;
		if (temp < 2.8f){
			momentum = 0.0f;
		}
		else {
			momentum = temp * 0.04f;
		}
		
		for (int i = 0; i < TOTAL_ENEMIES; i++){
			if (enemy[i].active){
				enemy[i].v_y = momentum * 15.0f;
			}
		}
		
		//animationtime = mapValue(user.elapsed, user.elapsed, user.elapsed + 1.0f, 0.0f, 1.0f);
	}

	float animationtime = mapValue(user.elapsed, shakeStart, shakeEnd, 0.0f, 1.0f);

	if (user.collidedBottom){
		jumped = 0;
		//screenShakeIntensity = easeIn(0.0f, 1.0f, 0.5f);
	}
	else if (jumped == 0){
		jumped = 1;
	}

	screenShakeIntensity = easeIn(momentum, 0.0f, animationtime);

	for (int i = 0; i < TOTAL_ENEMIES; i++){
		if (enemy[i].alive && enemy[i].active) {
			if (user.collisiony(enemy[i])){
				if (user.collidedTop || user.v_y > 0.0f){
					state = STATE_GAME_OVER;
					p.particles.clear();
					freeLevel();
					return;
				}
				score += 100;
				p = ParticleEmitter(500);
				jumped = 1;
				user.v_y = 2.5f;
				enemy[i].alive = false;
				enemy[i].v_y += 3.0f;
				enemy[i].v_x = 0.0f;
				enemy[i].a_x = 0.0f;
				enemy[i].elapsed = 9999.0f;
				enemy[i].coin = true;
				//enemy[i].width = 40.0f / 256.0f;
				//enemy[i].height = 40.0f / 256.0f;
				enemy[i].scalex = 0.6f;
				enemy[i].scaley = 0.6f;
			}
		}

		if (enemy[i].coin){
			if (enemy[i].elapsed > 10000.0f && user.collision(enemy[i])){
				score += 200;
				p = ParticleEmitter(500);
				enemy[i].coin = false;
				enemyCount--;
			}
		}
	}
	
	for (int i = 0; i < TOTAL_PRIZES; i++){
		if (prize[i].alive){
			if (user.collision(prize[i])){
				score += 200;
				p = ParticleEmitter(500);
				prize[i].alive = false;
			}
		}
	}


	user.v_x = lerp(user.v_x, 0.0f, FIXED_TIMESTEP * user.f_x);
	user.v_x += user.a_x * FIXED_TIMESTEP;

	if (user.v_x > 1.5f){
		user.v_x = 1.5f;
	}
	else if (user.v_x < -1.5f){
		user.v_x = -1.5f;
	}

	user.x += user.v_x * FIXED_TIMESTEP;

	for (int i = 0; i < TOTAL_ENEMIES; i++){
		if (enemy[i].alive && enemy[i].active){
			if (user.collisionx(enemy[i])){
				state = STATE_GAME_OVER;
				p.particles.clear();
				freeLevel();
				return;
			}
		}
	}

	for (int i = 0; i < TOTAL_ENEMIES; i++){
		if (enemy[i].coin && enemy[i].active){
			if (enemy[i].elapsed > 10015.0f){
				enemy[i].coin = false;
			}
		}
	}


	if (keys[SDL_SCANCODE_LEFT]){
		user.v_x -= 18.0f * FIXED_TIMESTEP;
		user.faceleft = true;

	}
	if (keys[SDL_SCANCODE_RIGHT]){
		user.v_x += 18.0f * FIXED_TIMESTEP;
		user.faceleft = false;
	}
}

bool App::UpdateAndRender() {
	float ticks = (float)SDL_GetTicks() / 1000.0f;
	float elapsed = ticks - lastFrameTicks;
	lastFrameTicks = ticks;

	float fixedElapsed = elapsed + timeLeftOver;
	if (fixedElapsed > FIXED_TIMESTEP * MAX_TIMESTEPS){
		fixedElapsed = FIXED_TIMESTEP * MAX_TIMESTEPS;
	}

	while (fixedElapsed >= FIXED_TIMESTEP){
		fixedElapsed -= FIXED_TIMESTEP;
		Update();

		elapsed -= FIXED_TIMESTEP;
	}
	Render();
	timeLeftOver = fixedElapsed;

	return done;
}

void App::freeLevel(){
	for (int i = 0; i < levelheight; i++){
		delete[] levelData[i];
	}
	delete[] levelData;
	levelheight = 0;
	levelwidth = 0;
}

void App::buildLevel(unsigned char **newlevelData, int newlevelheight, int newlevelwidth) {
	levelheight = newlevelheight;
	levelwidth = newlevelwidth;
	levelData = new unsigned char *[newlevelheight];
	for (int i = 0; i < newlevelheight; ++i) {
		levelData[i] = new unsigned char[newlevelwidth];
		memcpy(levelData[i], newlevelData[i], newlevelwidth);
	}
	//memcpy(levelData, newlevelData, levelheight*levelwidth);
}

void App::genLevel(){

	for (int y = 0; y < levelheight; y++) {
		for (int x = 0; x < levelwidth; x++) {
			float blacklines = 0.003f;
			if (levelData[y][x] != 0){
				float u = (float)(((int)levelData[y][x]) % SPRITE_COUNT_X) / (float)SPRITE_COUNT_X;
				float v = (float)(((int)levelData[y][x]) / SPRITE_COUNT_X) / (float)SPRITE_COUNT_Y;
				float spriteWidth = 1.0f / (float)SPRITE_COUNT_X;
				float spriteHeight = 1.0f / (float)SPRITE_COUNT_Y;
				vertexData.insert(vertexData.end(), {
					TILE_WIDTH * x, -TILE_HEIGHT * y,
					TILE_WIDTH * x, (-TILE_HEIGHT * y) - TILE_HEIGHT,
					(TILE_WIDTH * x) + TILE_WIDTH, (-TILE_HEIGHT * y) - TILE_HEIGHT,
					(TILE_WIDTH * x) + TILE_WIDTH, -TILE_HEIGHT * y
				});
				texCoordData.insert(texCoordData.end(), { u + blacklines, v + blacklines,
					u + blacklines, v + spriteHeight - blacklines,
					u + spriteWidth - blacklines, v + spriteHeight - blacklines,
					u + spriteWidth - blacklines, v + blacklines
				});
			}
		}
	}

	world_offset_x = -TILE_WIDTH * levelwidth / 25.0f;
	world_offset_y = TILE_HEIGHT * levelheight / 1.5f;

	int test1;
	int test2;
	worldtoTileCoordinates(0.0f, 0.0f, test1, test2);

	worldtoTileCoordinates(0.3f, 0.3f, test1, test2);

}

int main(int argc, char *argv[])
{
	App app;
	/*
	int width = 0;
	int height = 0;
	unsigned char ** map = NULL;
	mapRead(width, height, map);
	app.buildLevel(map, height, width);

	app.sss();*/



	while (!app.UpdateAndRender()){
	}
	return 0;
}