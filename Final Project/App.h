void App::reset(){
	srand((unsigned int)time(NULL));
	p.clear();
	user.bullets.clear();
	powerups.clear();
	enemies.clear();
	for (unsigned int i = 0; i < TOTAL_ENEMIES; i++){
		enemy[i].bullets.clear();
	}

	dying = false;
	switch (level){
	case MAIN_MENU:
		resetMainMenu();
		break;
	case INSTRUCTIONS:
		resetInstructions();
		break;
	case GAME_LEVEL_1:
		resetGameLevel1();
		break;
	case GAME_LEVEL_2:
		resetGameLevel2();
		break;
	case GAME_LEVEL_3:
		resetGameLevel3();
		break;
	}
}

void App::resetMainMenu(){
	gametime = 0.0f;
	pointTop = true;
	user = Entity(SheetSpriteTexture, 777.0f / 1024.0f, 712.0f / 1024.0f, 32.0f / 1024.0f, 26.0 / 1024.0f, 2.0f, 2.0f, 0);
	user.rotation = (float)-M_PI / 2.0f;
	user.x = -0.5f;
	user.y = -0.2f;
	user.genMatrix();

	setTime = -10.0f;
	newPos = -0.2f;
	prevPos = -0.2f;
	change = 10;
	changetime = 999.0f;

	if (!Mix_PlayingMusic() || Mix_PausedMusic()){
		levelSong = Mix_LoadMUS("mainmenu.ogg");
		Mix_FadeInMusic(levelSong, 0, 10000);
	}
}

void App::resetInstructions(){

}

void App::resetGameLevel1(){

	LevelTexture = LoadTexture("level1icon.png", GL_RGBA);
	mapWidth = 1.0f;
	mapHeight = 0.6f;
	mapAway = 0.0f;
	kills = 0;
	lives = 3;
	score = 0;
	bossAlive = 1;

	user = Entity(SheetSpriteTexture, 777.0f / 1024.0f, 712.0f / 1024.0f, 32.0f / 1024.0f, 26.0 / 1024.0f, 2.0f, 2.0f, 0);
	//userbox = Entity(BulletTexture, 172.0f / 973.0f, 247.0f / 476.0f, 18.0f / 973.0f, 18.0f / 476.0f, 1.0f, 0.5f, 0);
	userbox = Entity(BulletTexture, 685.0f / 973.0f, 400.0f / 476.0f, 75.0f / 973.0f, 75.0f / 476.0f, 0.3f, 0.1468f, 0);

	user.x = 0.0f;
	user.y = -0.8f;
	userbox.x = user.x;
	userbox.y = user.y;
	user.power = 0;
	gametime = 0.0f;
	MapTexture = LoadTexture2("level1.png", GL_RGB);

	ifstream input;
	input.open("Level1.csv");
	loadLevel(input);
	input.close();

	levelSong = Mix_LoadMUS("level1.ogg");
	Mix_FadeInMusic(levelSong, 0, 10000);
}

void App::loadLevel(ifstream& input){
	string temp;
	string ttemp;
	int number = 0;
	input >> temp;
	while (input >> temp){
		istringstream t(temp);
		getline(t, ttemp, ',');
		if (ttemp == "1"){

			enemy[number] = Entity(SheetSpriteTexture, 120.0f / 1024.0f, 605.0f / 1024.0f, 104.0f / 1024.0f, 82.0 / 1024.0f, 0.7f, 0.7f, stoi(ttemp));
			enemy[number].timeToShoot = (float)rand() / (float)RAND_MAX * 1.5f + 0.75f;
			enemy[number].hp = 40;
			enemy[number].powerup = false;
			enemy[number].alive = false;
			enemy[number].active = false;

			getline(t, ttemp, ',');
			enemy[number].pos = ttemp;
			getline(t, ttemp, ',');

			if (enemy[number].pos == "top"){
				enemy[number].y = TOP + 0.1f;
				enemy[number].x = stof(ttemp);
			}
			else if (enemy[number].pos == "left"){
				enemy[number].x = LEFT - 0.1f;
				enemy[number].y = stof(ttemp);
			}
			else {
				enemy[number].x = RIGHT + 0.1f;
				enemy[number].y = stof(ttemp);
			}

			getline(t, ttemp, ',');
			enemy[number].start = stof(ttemp);

			getline(t, ttemp, ',');
			enemy[number].stop = stof(ttemp);

			getline(t, ttemp, ',');
			enemy[number].resume = stof(ttemp);

			getline(t, ttemp, ',');
			enemy[number].speed = stof(ttemp);
		}
		else if (ttemp == "2"){
			enemy[number] = Entity(SheetSpriteTexture, 519.0f / 1024.0f, 325.0f / 1024.0f, 80.0f / 1024.0f, 84.0 / 1024.0f, 1.1f, 1.1f, stoi(ttemp));
			enemy[number].alive = false;
			enemy[number].timeToShoot = 0.5f;
			enemy[number].active = false;
			enemy[number].powerup = false;
			enemy[number].hp = 1000;
			enemy[number].shotType = 1;

			getline(t, ttemp, ',');
			enemy[number].pos = ttemp;
			getline(t, ttemp, ',');

			if (enemy[number].pos == "top"){
				enemy[number].y = TOP + 0.1f;
				enemy[number].x = stof(ttemp);
			}
			else if (enemy[number].pos == "left"){
				enemy[number].x = LEFT - 0.1f;
				enemy[number].y = stof(ttemp);
			}
			else {
				enemy[number].x = RIGHT + 0.1f;
				enemy[number].y = stof(ttemp);
			}

			getline(t, ttemp, ',');
			enemy[number].start = stof(ttemp);

			getline(t, ttemp, ',');
			enemy[number].stop = stof(ttemp);

			getline(t, ttemp, ',');
			enemy[number].resume = stof(ttemp);

			getline(t, ttemp, ',');
			enemy[number].speed = stof(ttemp);
		}
		else if (ttemp == "3"){

			enemy[number] = Entity(SheetSpriteTexture, 421.0f / 1024.0f, 814.0f / 1024.0f, 97.0f / 1024.0f, 84.0 / 1024.0f, 0.7f, 0.7f, stoi(ttemp));
			enemy[number].timeToShoot = (float)rand() / (float)RAND_MAX * 1.5f + 0.75f;
			enemy[number].hp = 1;
			enemy[number].powerup = false;
			enemy[number].alive = false;
			enemy[number].active = false;

			getline(t, ttemp, ',');
			enemy[number].pos = ttemp;
			getline(t, ttemp, ',');

			if (enemy[number].pos == "top"){
				enemy[number].y = TOP + 0.1f;
				enemy[number].x = stof(ttemp);
			}
			else if (enemy[number].pos == "left"){
				enemy[number].x = LEFT - 0.1f;
				enemy[number].y = stof(ttemp);
			}
			else {
				enemy[number].x = RIGHT + 0.1f;
				enemy[number].y = stof(ttemp);
			}

			getline(t, ttemp, ',');
			enemy[number].start = stof(ttemp);

			getline(t, ttemp, ',');
			enemy[number].speed = stof(ttemp);

			getline(t, ttemp, ',');
			enemy[number].speed2 = stof(ttemp);
		}
		else if (ttemp == "4"){
			enemy[number] = Entity(SheetSpriteTexture, 637.0f / 1024.0f, 67.0f / 1024.0f, 47.0f / 1024.0f, 67.0 / 1024.0f, 1.0f, 1.0f, stoi(ttemp));
			enemy[number].timeToShoot = 0.0f;
			enemy[number].hp = 4000;
			enemy[number].powerup = false;
			enemy[number].alive = false;
			enemy[number].active = false;

			getline(t, ttemp, ',');
			enemy[number].pos = ttemp;
			getline(t, ttemp, ',');

			if (enemy[number].pos == "top"){
				enemy[number].y = TOP + 0.1f;
				enemy[number].x = stof(ttemp);
			}
			else if (enemy[number].pos == "left"){
				enemy[number].x = LEFT - 0.1f;
				enemy[number].y = stof(ttemp);
			}
			else {
				enemy[number].x = RIGHT + 0.1f;
				enemy[number].y = stof(ttemp);
			}

			getline(t, ttemp, ',');
			enemy[number].start = stof(ttemp);

			getline(t, ttemp, ',');
			enemy[number].stop = stof(ttemp);

			getline(t, ttemp, ',');
			enemy[number].resume = stof(ttemp);

			getline(t, ttemp, ',');
			enemy[number].speed = stof(ttemp);
		}
		else if (ttemp == "100"){
			enemy[number] = Entity(SheetSpriteTexture, 120.0f / 1024.0f, 605.0f / 1024.0f, 104.0f / 1024.0f, 82.0 / 1024.0f, 1.7f, 1.7f, stoi(ttemp));
			enemy[number].alive = false;
			enemy[number].active = false;
			enemy[number].powerup = false;
			enemy[number].hp = 30000;
			enemy[number].resume = 2.0f;
			enemy[number].timeToShoot = 1.5f;
			enemy[number].form = 1;

			getline(t, ttemp, ',');
			enemy[number].pos = ttemp;
			getline(t, ttemp, ',');

			if (enemy[number].pos == "top"){
				enemy[number].y = TOP + 0.1f;
				enemy[number].x = stof(ttemp);
			}
			else if (enemy[number].pos == "left"){
				enemy[number].x = LEFT - 0.1f;
				enemy[number].y = stof(ttemp);
			}
			else {
				enemy[number].x = RIGHT + 0.1f;
				enemy[number].y = stof(ttemp);
			}

			getline(t, ttemp, ',');
			dangerTime = stof(ttemp);
			enemy[number].start = stof(ttemp) + 4.0f;

			getline(t, ttemp, ',');
			enemy[number].stop = stof(ttemp) + 4.0f;

			getline(t, ttemp, ',');
			enemy[number].speed = stof(ttemp);
		}
		else if (ttemp == "101"){
			enemy[number] = Entity(SheetSpriteTexture, 120.0f / 1024.0f, 605.0f / 1024.0f, 104.0f / 1024.0f, 82.0 / 1024.0f, 1.7f, 1.7f, stoi(ttemp));
			enemy[number].alive = false;
			enemy[number].active = false;
			enemy[number].powerup = false;
			enemy[number].hp = 30000;
			enemy[number].resume = 2.0f;
			enemy[number].timeToShoot = 1.5f;
			enemy[number].form = 1;

			getline(t, ttemp, ',');
			enemy[number].pos = ttemp;
			getline(t, ttemp, ',');

			if (enemy[number].pos == "top"){
				enemy[number].y = TOP + 0.1f;
				enemy[number].x = stof(ttemp);
			}
			else if (enemy[number].pos == "left"){
				enemy[number].x = LEFT - 0.1f;
				enemy[number].y = stof(ttemp);
			}
			else {
				enemy[number].x = RIGHT + 0.1f;
				enemy[number].y = stof(ttemp);
			}

			getline(t, ttemp, ',');
			dangerTime = stof(ttemp);
			enemy[number].start = stof(ttemp) + 4.0f;

			getline(t, ttemp, ',');
			enemy[number].stop = stof(ttemp) + 4.0f;

			getline(t, ttemp, ',');
			enemy[number].speed = stof(ttemp);
		}
		else if (ttemp == "102"){
			enemy[number] = Entity(SheetSpriteTexture, 801.0f / 1024.0f, 16.0f / 1024.0f, 168.0f / 1024.0f, 83.0 / 1024.0f, 2.7f, 2.7f, stoi(ttemp));
			enemy[number].alive = false;
			enemy[number].active = false;
			enemy[number].powerup = false;
			enemy[number].hp = 75000;
			enemy[number].resume = 2.0f;
			enemy[number].timeToShoot = 1.5f;
			enemy[number].form = 1;

			getline(t, ttemp, ',');
			enemy[number].pos = ttemp;
			getline(t, ttemp, ',');

			if (enemy[number].pos == "top"){
				enemy[number].y = TOP + 0.1f;
				enemy[number].x = stof(ttemp);
			}
			else if (enemy[number].pos == "left"){
				enemy[number].x = LEFT - 0.1f;
				enemy[number].y = stof(ttemp);
			}
			else {
				enemy[number].x = RIGHT + 0.1f;
				enemy[number].y = stof(ttemp);
			}

			getline(t, ttemp, ',');
			dangerTime = stof(ttemp);
			enemy[number].start = stof(ttemp) + 4.0f;

			getline(t, ttemp, ',');
			enemy[number].stop = stof(ttemp) + 4.0f;

			getline(t, ttemp, ',');
			enemy[number].speed = stof(ttemp);
		}


		number++;

	}

	for (int i = number; i < TOTAL_ENEMIES; i++){
		enemy[i].start = 999.0f;
		enemy[i].y = -10.0f;
		enemy[i].powerup = false;
		enemy[i].alive = false;
	}
}

void App::resetGameLevel2(){

	LevelTexture = LoadTexture("level2icon.png", GL_RGBA);
	mapWidth = 1.0f;
	mapHeight = 0.6f;
	mapAway = 0.0f;

	//kills = 0;
	//lives = 3;
	bossAlive = 2;
	//score = 0;

	//user = Entity(SheetSpriteTexture, 777.0f / 1024.0f, 712.0f / 1024.0f, 32.0f / 1024.0f, 26.0 / 1024.0f, 2.0f, 2.0f, 0);
	//userbox = Entity(BulletTexture, 172.0f / 973.0f, 247.0f / 476.0f, 18.0f / 973.0f, 18.0f / 476.0f, 1.0f, 0.5f, 0);
	//userbox = Entity(BulletTexture, 685.0f / 973.0f, 400.0f / 476.0f, 75.0f / 973.0f, 75.0f / 476.0f, 0.3f, 0.1468f, 0);

	user.x = 0.0f;
	user.y = -0.8f;
	userbox.x = user.x;
	userbox.y = user.y;
	//user.power = 0;
	gametime = 0.0f;
	MapTexture = LoadTexture2("level2.png", GL_RGB);

	ifstream input;
	input.open("Level2.csv");
	loadLevel(input);
	input.close();

	levelSong = Mix_LoadMUS("level2.ogg");
	Mix_FadeInMusic(levelSong, 0, 10000);
}

void App::resetGameLevel3(){

	LevelTexture = LoadTexture("level3icon.png", GL_RGBA);
	mapWidth = 1.0f;
	mapHeight = 0.6f;
	mapAway = 0.0f;

	//kills = 0;
	//lives = 3;
	bossAlive = 1;
	//score = 0;

	//user = Entity(SheetSpriteTexture, 777.0f / 1024.0f, 712.0f / 1024.0f, 32.0f / 1024.0f, 26.0 / 1024.0f, 2.0f, 2.0f, 0);
	//userbox = Entity(BulletTexture, 172.0f / 973.0f, 247.0f / 476.0f, 18.0f / 973.0f, 18.0f / 476.0f, 1.0f, 0.5f, 0);
	//userbox = Entity(BulletTexture, 685.0f / 973.0f, 400.0f / 476.0f, 75.0f / 973.0f, 75.0f / 476.0f, 0.3f, 0.1468f, 0);

	user.x = 0.0f;
	user.y = -0.8f;
	userbox.x = user.x;
	userbox.y = user.y;
	//user.power = 0;
	gametime = 0.0f;
	MapTexture = LoadTexture2("level3.png", GL_RGB);

	ifstream input;
	input.open("Level3.csv");
	loadLevel(input);
	input.close();
	levelSong = Mix_LoadMUS("level3.ogg");
	Mix_FadeInMusic(levelSong, 0, 10000);
}

App::App() {
	Init();

	shotChannel = -1;

	keys = SDL_GetKeyboardState(NULL);

	DangerTexture = LoadTexture("danger.png", GL_RGBA);
	SheetSpriteTexture = LoadTexture("sheet.png", GL_RGBA);
	BulletTexture = LoadTexture("CustomShots.png", GL_RGBA);
	FontTexture = LoadTexture("font.png", GL_RGBA);
	IconTexture = LoadTexture("wavefire.png", GL_RGBA);

	glViewport(0, 0, 800, 600);
	glMatrixMode(GL_PROJECTION);

	//glOrtho(-1.33, 1.33, -1.0, 1.0, -1.0, 1.0);
	Matrix start(0.752f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.5f, 0.5f,
		0.0f, 0.0f, 0.0f, 1.0f);
	glMultMatrixf(start.ml);
	//glPushMatrix();
	lastshot = 999.0f;
	lastmissile = 999.0f;
	invincible = 0.0f;

	pause = false;
	done = false;
	lastFrameTicks = 0.0f;

	glMatrixMode(GL_MODELVIEW);
	Matrix initial;
	glLoadMatrixf(initial.ml);

	level = MAIN_MENU;

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
	Mix_AllocateChannels(32);
	move = Mix_LoadWAV("move.wav");
	userShoot = Mix_LoadWAV("sfx.wav");
	explosion = Mix_LoadWAV("aaa.wav");
	userExplosion = Mix_LoadWAV("userexplosion.wav");
	dangerSound = Mix_LoadWAV("bbb.wav");

	reset();

	//gametime = 40.0f;
	//user.power = 999;
}

void App::Init() {
	SDL_Init(SDL_INIT_VIDEO);
	displayWindow = SDL_CreateWindow("WaveFire", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
	SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
	SDL_GL_MakeCurrent(displayWindow, context);

}

App::~App() {
	Mix_FreeChunk(move);
	Mix_FreeChunk(explosion);
	Mix_FreeChunk(dangerSound);
	Mix_FreeChunk(userShoot);
	Mix_FreeChunk(userExplosion);
	Mix_FreeMusic(levelSong);
	SDL_Quit();
}

void App::cover(){
	//glDisable(GL_TEXTURE_2D);
	GLfloat rect[] = { -1.5f, 1.5f, -1.5f, -1.5f, LEFT, -1.5f, LEFT, 1.5f,
		1.5f, -1.5f, 1.5f, 1.5f, RIGHT, 1.5f, RIGHT, -1.5f };
	glVertexPointer(2, GL_FLOAT, 0, rect);
	glEnableClientState(GL_VERTEX_ARRAY);
	GLfloat rectcolors[] = { 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f };
	glColorPointer(4, GL_FLOAT, 0, rectcolors);
	glEnableClientState(GL_COLOR_ARRAY);
	glDrawArrays(GL_QUADS, 0, 8);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
}

void App::Render() {
	switch (level) {
	case MAIN_MENU:
		RenderMainMenu();
		break;
	case INSTRUCTIONS:
		RenderInstructions();
		break;
	case GAME_LEVEL_1: case GAME_LEVEL_2: case GAME_LEVEL_3:
		RenderGameLevel();
		break;
	}

	SDL_GL_SwapWindow(displayWindow);
}

void App::RenderMainMenu(){
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glClear(GL_COLOR_BUFFER_BIT);

	drawTitle();

	user.draw();
	for (unsigned int i = 0; i < user.bullets.size(); i++){
		user.bullets[i].draw();
	}


	drText(FontTexture, "Start", 0.15f, -0.075f, 1.0f, 1.0f, 1.0f, 1.0f, -0.0f, -0.2f);

	drText(FontTexture, "Instructions", 0.15f, -0.075f, 1.0f, 1.0f, 1.0f, 1.0f, -0.0f, -0.45f);

	drText(FontTexture, "Quit Game", 0.15f, -0.07f, 1.0f, 1.0f, 1.0f, 1.0f, -0.0f, -0.7f);
}

void App::drawMap(){
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, MapTexture);

	glPushMatrix();

	GLfloat quad[] = { LEFT, TOP, LEFT, BOTTOM, RIGHT, BOTTOM, RIGHT, TOP };
	glVertexPointer(2, GL_FLOAT, 0, quad);
	glEnableClientState(GL_VERTEX_ARRAY);

	GLfloat quadUVs[] = { 0.0f, 1.0f - mapAway - mapHeight,
		0.0f, 1.0f - mapAway,
		mapWidth, 1.0f - mapAway,
		mapWidth, 1.0f - mapAway - mapHeight };

	glTexCoordPointer(2, GL_FLOAT, 0, quadUVs);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glDrawArrays(GL_QUADS, 0, 4);
	glDisable(GL_TEXTURE_2D);
	//glDisableClientState(GL_COLOR_ARRAY);
	glPopMatrix();
}

void App::drawTitle(){
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, IconTexture);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPushMatrix();

	//GLfloat quad[] = { RIGHT, BOTTOM + 0.15f, RIGHT, BOTTOM - 0.05f, RIGHT + 0.48f, BOTTOM - 0.05f, RIGHT + 0.48f, BOTTOM + 0.15f };
	float scale = sinf(gametime);

	if (fmod(gametime, 2 * M_PI) > M_PI){
		glScalef(scale, 1.0f, 1.0f);
	}
	else {
		glScalef(1.0f, scale, 1.0f);
	}
	//float scale = sinf(gametime);
	glScalef(scale, 1.0f, 1.0f);
	float away = 0.3f;
	GLfloat quad[] = { LEFT + away, TOP - 0.2f, LEFT + away, TOP - 0.7f, RIGHT - away, TOP - 0.7f, RIGHT - away, TOP - 0.2f };

	glVertexPointer(2, GL_FLOAT, 0, quad);
	glEnableClientState(GL_VERTEX_ARRAY);

	GLfloat quadUVs[] = {
		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f
	};

	glTexCoordPointer(2, GL_FLOAT, 0, quadUVs);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glDrawArrays(GL_QUADS, 0, 4);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	//glDisableClientState(GL_COLOR_ARRAY);
	glPopMatrix();
}

void App::drawLevel(){
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, LevelTexture);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPushMatrix();

	GLfloat quad[] = { 0.2f, ypos, 0.2f, ypos - 0.1f, 0.6f, ypos - 0.1f, 0.6f, ypos };

	glVertexPointer(2, GL_FLOAT, 0, quad);
	glEnableClientState(GL_VERTEX_ARRAY);

	GLfloat quadUVs[] = {
		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f
	};

	glTexCoordPointer(2, GL_FLOAT, 0, quadUVs);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glDrawArrays(GL_QUADS, 0, 4);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	//glDisableClientState(GL_COLOR_ARRAY);
	glPopMatrix();
}

void App::drawLevelBar(){
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPushMatrix();

	GLfloat quad[] = { LEFT, -0.35f, LEFT, -0.55f, xpos, -0.55f, xpos, -0.35f };

	glVertexPointer(2, GL_FLOAT, 0, quad);
	glEnableClientState(GL_VERTEX_ARRAY);

	GLfloat quadcolors[] = { 0.5f, 0.7f, 0.2f, alpha,
		0.5f, 0.7f, 0.2f, alpha,
		0.5f, 0.7f, 0.2f, alpha,
		0.5f, 0.7f, 0.2f, alpha
	};

	glColorPointer(4, GL_FLOAT, 0, quadcolors);
	glEnableClientState(GL_COLOR_ARRAY);
	glDrawArrays(GL_QUADS, 0, 4);

	glDisable(GL_BLEND);
	glDisableClientState(GL_COLOR_ARRAY);
	glPopMatrix();
}

void App::drawDanger(){
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, DangerTexture);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPushMatrix();

	GLfloat quad[] = { xpos2, 0.0f,
		xpos2, -0.155f,
		xpos2 + 0.58f, -0.155f,
		xpos2 + 0.58f, 0.0f };

	glVertexPointer(2, GL_FLOAT, 0, quad);
	glEnableClientState(GL_VERTEX_ARRAY);

	float bottomDanger = gametime *10.0f;
	bottomDanger = (float)(int(floor(bottomDanger)) % 8)*1.0f / 8.0f;


	GLfloat quadUVs[] = { 0.0f, bottomDanger,
		0.0f, bottomDanger + 1.0f / 8.0f,
		1.0f, bottomDanger + 1.0f / 8.0f,
		1.0f, bottomDanger };

	glTexCoordPointer(2, GL_FLOAT, 0, quadUVs);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glDrawArrays(GL_QUADS, 0, 4);

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void App::drawPowerBar(unsigned int power){
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, SheetSpriteTexture);

	glPushMatrix();
	/*
	glTranslatef(x, y, 0.0f);
	glScalef(stretch, 1.0f, 1.0f);
	*/
	glTranslatef(-1.04f, 0.0f, 0.0f);
	glScalef(1.0f, 3.0f, 0.0f);
	glRotatef(90.0f, 0.0f, 0.0f, 1.0f);

	float u = 0.0f;
	float v = 0.0f;
	float width = 222.0f / 1024.0f;
	float height = 39.0f / 1024.0f;

	GLfloat quad[] = { -width, height, -width, -height,
		width, -height, width, height };
	glVertexPointer(2, GL_FLOAT, 0, quad);
	glEnableClientState(GL_VERTEX_ARRAY);

	GLfloat quadUVs[] = { u + 0.0001f, v + 0.0001f, u + 0.0001f, v + height - 0.0001f, u + width - 0.0001f, v + height - 0.0001f, u + width - 0.0001f, v + 0.0001f };
	//GLfloat quadUVs[] = { u + 0.0000000001f / width, v + 0.0000000001f / height, u + 0.0000000001f / width, v + height - 0.0000000001f / height,
	//	u + width - 0.0000000001f / width, v + height - 0.0000000001f / height, u + width - 0.0000000001f / width, v + 0.0000000001f / height };
	//GLfloat quadUVs[] = { u, v, u, v + height, u + width, v + height, u + width, v };

	glTexCoordPointer(2, GL_FLOAT, 0, quadUVs);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	/*
	GLfloat color[] = { 1.0f, 1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f, 1.0f };
	glColorPointer(4, GL_FLOAT, 0, color);
	glEnableClientState(GL_COLOR_ARRAY);
	*/
	glDrawArrays(GL_QUADS, 0, 4);
	glDisable(GL_TEXTURE_2D);
	//glDisable(GL_BLEND);
	//glDisableClientState(GL_COLOR_ARRAY);
	glPopMatrix();

	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPushMatrix();

	float value = (float)power;
	float alpha2;
	if (power <= POWER1){
		value = (value / POWER1) * 1.29f - 0.645f;
		alpha2 = 0.2f;
	}
	else if (power <= POWER2){
		value = (value - POWER1) / (POWER2 - POWER1) * 1.29f - 0.645f;
		alpha2 = 0.4f;
	}
	else if (power <= POWER3){
		value = (value - POWER2) / (POWER3 - POWER2) * 1.29f - 0.645f;
		alpha2 = 0.6f;
	}
	else if (power <= POWER4){
		value = (value - POWER3) / (POWER4 - POWER3) * 1.29f - 0.645f;
		alpha2 = 0.8f;
	}
	else if (power <= POWER5){
		value = (value - POWER4) / (POWER5 - POWER4) * 1.29f - 0.645f;
		alpha2 = 1.0f;
	}
	else{
		value = 0.645f;
		alpha2 = 1.0f;
	}

	//float x = 0.069f;
	float x = 0.037f;


	GLfloat quad2[] = { -1.04f - x, value,
		-1.04f - x, -0.645f,
		-1.04f + x, -0.645f,
		-1.04f + x, value
	};

	glVertexPointer(2, GL_FLOAT, 0, quad2);
	glEnableClientState(GL_VERTEX_ARRAY);

	float r = 222.0f / 256.0f;
	float g = 27.0f / 256.0f;
	float b = 40.0f / 256.0f;
	GLfloat quad2colors[] = { r, g, b, alpha2,
		r, g, b, alpha2,
		r, g, b, alpha2,
		r, g, b, alpha2
	};

	glColorPointer(4, GL_FLOAT, 0, quad2colors);
	glEnableClientState(GL_COLOR_ARRAY);
	glDrawArrays(GL_QUADS, 0, 4);

	glDisable(GL_BLEND);
	glDisableClientState(GL_COLOR_ARRAY);
	glPopMatrix();
}

void App::drawIcon(){
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, IconTexture);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPushMatrix();

	glRotatef(5.0f, 0.0f, 0.0f, 1.0f);
	GLfloat quad[] = { RIGHT, BOTTOM + 0.15f, RIGHT, BOTTOM - 0.05f, RIGHT + 0.48f, BOTTOM - 0.05f, RIGHT + 0.48f, BOTTOM + 0.15f };

	glVertexPointer(2, GL_FLOAT, 0, quad);
	glEnableClientState(GL_VERTEX_ARRAY);

	GLfloat quadUVs[] = {
		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f
	};

	glTexCoordPointer(2, GL_FLOAT, 0, quadUVs);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glDrawArrays(GL_QUADS, 0, 4);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	//glDisableClientState(GL_COLOR_ARRAY);
	glPopMatrix();
}

void App::RenderInstructions(){
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glClear(GL_COLOR_BUFFER_BIT);

	/*
	user.draw();
	for (unsigned int i = 0; i < user.bullets.size(); i++){
	user.bullets[i].draw();
	}*/

	drText(FontTexture, "Instructions:", 0.1f, -0.05f, 0.6f, 1.0f, 0.8f, 1.0f, -1.2f, 0.9f);
	drText(FontTexture, "Use the arrow keys to move.", 0.1f, -0.05f, 1.0f, 0.0f, 0.0f, 1.0f, -1.2f, 0.7f);
	drText(FontTexture, "If you get hit, you'll have a bad time.", 0.1f, -0.05f, 1.0f, 1.0f, 1.0f, 1.0f, -1.2f, 0.6f);
	drText(FontTexture, "Hold z to shoot down enemies.", 0.1f, -0.05f, 1.0f, 0.0f, 0.0f, 1.0f, -1.2f, 0.45f);
	drText(FontTexture, "If they get hit, you'll have a good time.", 0.1f, -0.05f, 1.0f, 1.0f, 1.0f, 1.0f, -1.2f, 0.35f);
	drText(FontTexture, "Hold the left shift key to \"focus\".", 0.1f, -0.05f, 1.0f, 0.0f, 0.0f, 1.0f, -1.2f, 0.2f);
	drText(FontTexture, "You'll see what it does.", 0.1f, -0.05f, 1.0f, 1.0f, 1.0f, 1.0f, -1.2f, 0.1f);
	drText(FontTexture, "Pick up enemy drops to POWERUPPP!!", 0.1f, -0.05f, 1.0f, 0.0f, 0.0f, 1.0f, -1.2f, -0.05f);
	drText(FontTexture, "This is a good thing.", 0.1f, -0.05f, 1.0f, 1.0f, 1.0f, 1.0f, -1.2f, -0.15f);
	drText(FontTexture, "Your hitbox is the small shiny pink orb.", 0.1f, -0.05f, 1.0f, 0.0f, 0.0f, 1.0f, -1.2f, -0.3f);
	drText(FontTexture, "So you die slower.", 0.1f, -0.05f, 1.0f, 1.0f, 1.0f, 1.0f, -1.2f, -0.4f);
	drText(FontTexture, "Press ESC to pause the game.", 0.1f, -0.05f, 1.0f, 0.0f, 0.0f, 1.0f, -1.2f, -0.55f);
	drText(FontTexture, "When you can't handle the greatness of this game.", 0.1f, -0.05f, 1.0f, 1.0f, 1.0f, 1.0f, -1.2f, -0.65f);
	drText(FontTexture, "Now go shoot some stuff.", 0.1f, -0.05f, 1.0f, 1.0f, 1.0f, 1.0f, -1.2f, -0.875f);



}

void App::RenderGameLevel(){
	//glClearColor(0.2f, 0.3f, 0.5f, 0.0f);

	//glClear(GL_COLOR_BUFFER_BIT);

	drawMap();

	for (unsigned int i = 0; i < user.bullets.size(); i++){
		user.bullets[i].draw();
	}

	for (unsigned int i = 0; i < enemies.size(); i++){
		enemy[enemies[i]].render();
	}

	for (unsigned int i = 0; i < powerups.size(); i++){
		enemy[powerups[i]].render();
	}

	for (int i = 0; i < TOTAL_ENEMIES; i++) {
		for (unsigned int j = 0; j < enemy[i].bullets.size(); j++){
			enemy[i].bullets[j].draw();
		}
	}

	for (unsigned int i = 0; i < p.size(); i++){
		p[i].Render();
	}

	cover();
	if (dangerTime < gametime){
		drawDanger();
	}
	drawLevelBar();
	drawIcon();

	drawLevel();

	drawPowerBar(user.power);
	drText(FontTexture, "SCORE", 0.08f, -0.04f, 0.6f, 0.8f, 1.0f, 1.0f, 0.95f, 0.9f);
	drText(FontTexture, to_string(score), 0.08f, -0.04f, 0.6f, 0.8f, 1.0f, 1.0f, 0.95f, 0.8f);

	drText(FontTexture, "LIVES", 0.08f, -0.04f, 0.6f, 0.8f, 1.0f, 1.0f, 0.95f, 0.6f);
	for (unsigned int i = 0; i < lives; i++){
		user.draw(0.95f + 0.1f * i, 0.5f, 0.6f, 0.5f);
	}
	drText(FontTexture, "KILLS", 0.08f, -0.04f, 0.6f, 0.8f, 1.0f, 1.0f, 0.95f, 0.3f);
	drText(FontTexture, to_string(kills), 0.08f, -0.04f, 0.6f, 0.8f, 1.0f, 1.0f, 0.95f, 0.2f);

	//drText(FontTexture, "POWER", 0.08f, -0.04f, 0.9f, 0.2f, 0.2f, 1.0f, -1.18, -0.72f);

	//drText(FontTexture, "Score", 0.1f, -0.05f, 0.8f, 0.6f, 1.0f, 1.0f, 0.95f, 0.94f);

	if (lives){
		user.draw();
		userbox.draw();
		if (!bossAlive){
			if (level == GAME_LEVEL_3){
				transition(2);
			}
			else {
				transition(1);
			}
		}
		else if (pause){
			transition(3);
		}
	}
	else {
		transition(0);
	}

	fadeIn();

}

void App::fadeIn(){
	glPushMatrix();

	float val = mapValue(gametime, 0.0f, 5.0f, 0.0f, 1.0f);
	float alpha2 = lerp(1.0f, 0.0f, val);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glDisable(GL_TEXTURE_2D);
	GLfloat fade[] = { -100.0f, 100.0f, -100.0f, -100.0f, 100.0f, -100.0f, 100.0f, 100.0f };
	glVertexPointer(2, GL_FLOAT, 0, fade);
	glEnableClientState(GL_VERTEX_ARRAY);
	GLfloat fadecolors[] = { 0.0f, 0.0f, 0.0f, alpha2, 0.0f, 0.0f, 0.0f, alpha2, 0.0f, 0.0f, 0.0f, alpha2, 0.0f, 0.0f, 0.0f, alpha2 };
	glColorPointer(4, GL_FLOAT, 0, fadecolors);
	glEnableClientState(GL_COLOR_ARRAY);
	glDrawArrays(GL_QUADS, 0, 4);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisable(GL_BLEND);

	glPopMatrix();
}

void App::transition(int mode){
	glPushMatrix();

	float val;
	if (mode == 0){
		val = mapValue(gametime, deathTime + 1.5f, deathTime + 5.0f, 0.0f, 1.0f);
	}
	else {
		val = mapValue(gametime, killTime + 1.5f, killTime + 5.0f, 0.0f, 1.0f);
	}
	
	float alpha2 = lerp(0.0f, 0.75f, val);
	if (mode == 3){
		alpha2 = 0.75f;
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glDisable(GL_TEXTURE_2D);
	GLfloat fade[] = { LEFT, TOP, LEFT, BOTTOM, RIGHT, BOTTOM, RIGHT, TOP };
	glVertexPointer(2, GL_FLOAT, 0, fade);
	glEnableClientState(GL_VERTEX_ARRAY);
	GLfloat fadecolors[] = { 0.0f, 0.0f, 0.0f, alpha2, 0.0f, 0.0f, 0.0f, alpha2, 0.0f, 0.0f, 0.0f, alpha2, 0.0f, 0.0f, 0.0f, alpha2 };
	glColorPointer(4, GL_FLOAT, 0, fadecolors);
	glEnableClientState(GL_COLOR_ARRAY);
	glDrawArrays(GL_QUADS, 0, 4);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisable(GL_BLEND);

	if (alpha2 > 0.5f){
		if (mode == 0){
			drText(FontTexture, "Game Over", 0.2f, -0.085f, 0.6f, 0.8f, 1.0f, 1.0f, -0.5f, 0.0f);
			drText(FontTexture, "Press Enter To Return To The Main Menu", 0.1f, -0.05f, 0.6f, 0.8f, 1.0f, 1.0f, -0.9f, -0.2f);
		}
		else if (mode == 1){
			drText(FontTexture, "Stage Cleared", 0.2f, -0.085f, 0.6f, 0.8f, 1.0f, 1.0f, -0.7f, 0.0f);
			drText(FontTexture, "Press Enter To Continue", 0.1f, -0.05f, 0.6f, 0.8f, 1.0f, 1.0f, -0.55f, -0.2f);
		}
		else if (mode == 2){
			drText(FontTexture, "Game Completed", 0.2f, -0.085f, 0.6f, 0.8f, 1.0f, 1.0f, -0.7f, 0.0f);
			drText(FontTexture, "Thank You For Playing!", 0.1f, -0.05f, 0.6f, 0.8f, 1.0f, 1.0f, -0.5f, -0.2f);
			drText(FontTexture, "Press Enter To Return To The Main Menu", 0.1f, -0.05f, 0.6f, 0.8f, 1.0f, 1.0f, -0.9f, -0.4f);
		}
		else if (mode == 3){
			drText(FontTexture, "Game Paused", 0.2f, -0.085f, 0.6f, 0.8f, 1.0f, 1.0f, -0.6f, 0.0f);
			drText(FontTexture, "Press ANY Other Key To Resume", 0.1f, -0.05f, 0.6f, 0.8f, 1.0f, 1.0f, -0.72f, -0.4f);
			drText(FontTexture, "Press Esc To Return To The Main Menu", 0.1f, -0.05f, 0.6f, 0.8f, 1.0f, 1.0f, -0.9f, -0.2f);
		}
	}



	glPopMatrix();
}

void App::Update(float elapsed) {
	switch (level) {
	case MAIN_MENU:
		UpdateMainMenu(elapsed);
		break;
	case INSTRUCTIONS:
		UpdateInstructions(elapsed);
		break;
	case GAME_LEVEL_1: case GAME_LEVEL_2: case GAME_LEVEL_3:
		UpdateGameLevel(elapsed);
		break;
	}
}

void App::UpdateMainMenu(float elapsed){
	gametime += elapsed;
	changetime -= elapsed;

	float animationAValue = mapValue(gametime, setTime, setTime + 0.3f, 0.0f, 1.0f);

	user.y = easeOutElastic(prevPos, newPos, animationAValue);
	user.genMatrix();

	for (unsigned int i = 0; i < user.bullets.size(); i++){
		user.bullets[i].x += user.bullets[i].vector.x * elapsed;
		user.bullets[i].genMatrix();
	}

	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
			done = true;
		}
		else if (event.type == SDL_KEYDOWN){
			if (event.key.keysym.scancode == SDL_SCANCODE_DOWN){
				if (roundf(user.y * 100) / 100 == -0.2f){
					Mix_PlayChannel(4, move, 0);
					setTime = gametime - elapsed;
					newPos = -0.45f;
					prevPos = -0.2f;
				}
				else if (roundf(user.y * 100) / 100 == -0.45f){
					Mix_PlayChannel(4, move, 0);
					setTime = gametime - elapsed;
					newPos = -0.7f;
					prevPos = -0.45f;
				}
			}
			else if (event.key.keysym.scancode == SDL_SCANCODE_UP){
				if (roundf(user.y * 100) / 100 == -0.45f){
					Mix_PlayChannel(4, move, 0);
					setTime = gametime - elapsed;
					newPos = -0.2f;
					prevPos = -0.45f;
				}
				else if (roundf(user.y * 100) / 100 == -0.7f){
					Mix_PlayChannel(4, move, 0);
					setTime = gametime - elapsed;
					newPos = -0.45f;
					prevPos = -0.75f;
				}
			}
			if ((event.key.keysym.scancode == SDL_SCANCODE_RETURN||event.key.keysym.scancode == SDL_SCANCODE_Z) && user.bullets.size() == 0){
				//Mix_HaltMusic();
				Mix_PlayChannel(0, userShoot, 0);
				Mix_PlayChannel(1, userShoot, 0);
				Mix_PlayChannel(2, userShoot, 0);
				Mix_PlayChannel(3, userShoot, 0);
				if (roundf(user.y * 100) / 100 == -0.7f){
					user.shoot(1, BulletTexture, 446.0f / 973.0f, 202.0f / 476.0f, 14.0f / 973.0f, 19.0f / 476.0f, 4.0f, 2.0f, (float)-M_PI / 2.0f, 2.0f);
					changetime = 1.0f;
					change = 2;
				}
				else if (roundf(user.y * 100) / 100 == -0.45f){
					user.shoot(1, BulletTexture, 446.0f / 973.0f, 202.0f / 476.0f, 14.0f / 973.0f, 19.0f / 476.0f, 4.0f, 2.0f, (float)-M_PI / 2.0f, 2.0f);
					changetime = 1.0f;
					change = 1;
				}
				else if (roundf(user.y * 100) / 100 == -0.2f){
					user.shoot(1, BulletTexture, 446.0f / 973.0f, 202.0f / 476.0f, 14.0f / 973.0f, 19.0f / 476.0f, 4.0f, 2.0f, (float)-M_PI / 2.0f, 2.0f);
					changetime = 1.0f;
					change = 0;
				}
			}
		}
	}

	if (changetime < 0.0f){
		if (change == 0){
			level = GAME_LEVEL_1;
			Mix_HaltMusic();
			//level = GAME_LEVEL_2;
			reset();
			//level = GAME_LEVEL_3;
			//reset();
			//user.power = 9999;
			//gametime = 70.0f;
			//userbox.scalex2 = 0;
			//userbox.scaley2 = 0;
			//lives = 3;
		}
		else if (change == 1){
			level = INSTRUCTIONS;
			reset();
		}
		else if (change == 2){
			done = true;
		}
	}
	
	//if ((roundf(user.y * 100)/100 == -0.2f)
}

void App::UpdateInstructions(float elapsed){

	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
			done = true;
		}
		else if (event.type == SDL_KEYDOWN){
			level = MAIN_MENU;
			reset();
			return;
		}
	}
}

void App::pauseState(){
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
			done = true;
		}
		else if (event.type == SDL_KEYDOWN){
			if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE){
				pause = false;
				level = MAIN_MENU;
				reset();
				return;
			}
			else {
				pause = false;
				Mix_ResumeMusic();
				return;
			}
		}
	}
}

void App::UpdateGameLevel(float elapsed){

	/*
	if (lives == 0){
		level = MAIN_MENU;
		reset();
		return;
	}
	
	if (!bossAlive){
	if (level == GAME_LEVEL_1){
	level = GAME_LEVEL_2;
	reset();
	return;
	}
	else if (level == GAME_LEVEL_2){
	level = GAME_LEVEL_3;
	reset();
	return;
	}
	}*/

	if (pause){
		pauseState();
		return;
	}

	if (!Mix_Playing(2)){
		if (fabs(dangerTime - gametime) < 1.0f){
			//Mix_FadeOutMusic(4000);
			//Mix_HaltMusic();
			Mix_PlayChannel(2, dangerSound, 0);
		}
	}

	enemies.clear();
	powerups.clear();

	for (unsigned int i = 0; i < TOTAL_ENEMIES; i++){
		if (enemy[i].alive){
			enemies.push_back(i);
		}
		else if (enemy[i].powerup){
			powerups.push_back(i);
		}
	}

	invincible -= elapsed;
	lastshot += elapsed;
	lastmissile += elapsed;
	gametime += elapsed;
	mapAway += elapsed * 0.005f;

	//float animationAValue = mapValue(gametime, 0.0f, 2.0f, 0.0f, 1.0f);
	float animationAValue;
	if (gametime > 4.0f){
		animationAValue = mapValue(gametime, 5.5f, 4.0f, 0.0f, 1.0f);
	}
	else {
		animationAValue = mapValue(gametime, 1.0f, 2.5f, 0.0f, 1.0f);
	}
	float animationBValue = mapValue(gametime, 3.0f, 6.0f, 0.0f, 1.0f);
	float animationCValue = mapValue(gametime, 0.0f, 2.0f, 0.0f, 1.0f);

	xpos = lerp(LEFT, RIGHT, animationCValue);

	alpha = lerp(0.5f, 0.0f, animationBValue);
	ypos = easeOutElastic(TOP + 0.2f, -0.4f, animationAValue);

	float animationDValue;
	if (dying){
		animationDValue = mapValue(gametime, deathTime, deathTime + 0.5f, 0.0f, 1.0f);
		user.scalex2 = lerp(1.0f, 0.0f, animationDValue);
		user.scaley2 = lerp(1.0f, 0.0f, animationDValue);
		userbox.scalex2 = lerp(1.0f, 0.0f, animationDValue);
		userbox.scaley2 = lerp(1.0f, 0.0f, animationDValue);
		if (gametime < deathTime + 0.5f){
			p.push_back(ParticleEmitter(10, user.x, user.y));
		}
		else if (gametime > deathTime + 1.5f){
			dying = false;
			user.scalex2 = 1.0f;
			user.scaley2 = 1.0f;
			userbox.scalex2 = 1.0f;
			userbox.scaley2 = 1.0f;
			user.x = 0.0f;
			user.y = -0.8f;
			lives--;
			invincible = 3.0f;
		}
	}

	float animationEValue = mapValue(gametime, dangerTime, dangerTime + 4.0f, 0.0f, 1.0f);
	xpos2 = lerp(LEFT, RIGHT, animationEValue);

	//user.y = easeOutElastic(prevPos, newPos, animationAValue);

	for (unsigned int i = 0; i < enemies.size(); i++){
		enemy[enemies[i]].hit = false;
	}

	if (!dying && invincible < 0.0f && lives && bossAlive){
		for (unsigned int i = 0; i < enemies.size(); i++){
			if (collision(enemy[enemies[i]], userbox)){
				dying = true;
				deathTime = gametime;
				Mix_PlayChannel(3, userExplosion, 0);
			}
		}
	}

	if (user.x - user.width * user.scalex < LEFT){
		user.x = LEFT + user.width * user.scalex;
	}
	else if (user.x + user.width * user.scalex > RIGHT){
		user.x = RIGHT - user.width * user.scalex;
	}
	if (user.y - user.height * user.scaley < BOTTOM){
		user.y = BOTTOM + user.height * user.scaley;
	}
	else if (user.y + user.height * user.scaley > TOP){
		user.y = TOP - user.height * user.scaley;
	}

	user.genMatrix();
	userbox.x = user.x;
	userbox.y = user.y - 0.01f;
	userbox.genMatrix();

	user.bullets.erase(remove_if(user.bullets.begin(), user.bullets.end(), removeBullet), user.bullets.end());


	for (unsigned int i = 0; i < user.bullets.size(); i++){
		user.bullets[i].x += user.bullets[i].vector.x * elapsed;
		user.bullets[i].y += user.bullets[i].vector.y * elapsed;
		user.bullets[i].genMatrix();

		for (unsigned int j = 0; j < enemies.size(); j++){
			if (collision(user.bullets[i], enemy[enemies[j]])){
				if (user.bullets[i].type == 1){
					enemy[enemies[j]].hp -= 10;
					enemy[enemies[j]].hit = true;
					//enemy[enemies[j]].x = 0.0f;
					//enemy[enemies[j]].alive = false;
					//user.bullets.erase();
					user.bullets[i].y = 100.0f;
					//user.bullets.erase(remove_if(user.bullets.begin(), user.bullets.end(), removeBullet), user.bullets.end());
					break;
				}
				else if (user.bullets[i].type == 2) {
					enemy[enemies[j]].hp -= 250;
					enemy[enemies[j]].hit = true;
					user.bullets[i].y = 100.0f;
					break;
				}
				else {
					enemy[enemies[j]].hp -= 20;
					enemy[enemies[j]].hit = true;
					user.bullets[i].y = 100.0f;
					break;
				}
			}
		}


		//user.bullets[i].x += user.bullets[i].vector.x * elapsed;
		//user.bullets[i].y += user.bullets[i].vector.y * elapsed;
		//user.bullets[i].genMatrix();
	}
	//user.setVector();

	p.erase(remove_if(p.begin(), p.end(), removeParticleEmitter), p.end());
	for (unsigned int i = 0; i < p.size(); i++){
		p[i].Update(elapsed);
	}

	for (int i = 0; i < TOTAL_ENEMIES; i++){
		enemy[i].bullets.erase(remove_if(enemy[i].bullets.begin(), enemy[i].bullets.end(), removeBullet), enemy[i].bullets.end());
	}

	for (unsigned int j = 0; j < enemies.size(); j++){
		int i = enemies[j];
		if (enemy[i].hp <= 0.0f){

			enemy[i].alive = false;
			enemy[i].powerup = true;
			enemy[i].hit = false;
			if (fabs(enemy[i].x) > RIGHT - 0.02f){
				if (enemy[i].x > 0.0f){
					enemy[i].x = RIGHT - 0.02f;
				}
				else {
					enemy[i].x = LEFT + 0.02f;
				}
			}

			kills++;
			Mix_PlayChannel(1, explosion, 0);
			enemy[i].vector.y = 1.0f;
			p.push_back(ParticleEmitter(25, enemy[i].x, enemy[i].y));
			enemy[i].textureID = BulletTexture;

			//enemy[i].shoot(BulletTexture, 831.0f / 973.0f, 76.0f / 476.0f, 11.0f / 973.0f, 22.0f / 476.0f, 2.0f, 1.5f, M_PI, 1.0f);
			//Entity(SheetSpriteTexture, 519.0f / 1024.0f, 325.0f / 1024.0f, 80.0f / 1024.0f, 84.0 / 1024.0f, 0.8f, 0.8f, stoi(ttemp));
			enemy[i].u = 229.0f / 973.0f;
			enemy[i].v = 349.0f / 476.0f;
			enemy[i].width = 12.0f / 973.0f;
			enemy[i].height = 16.0f / 476.0f;
			enemy[i].scalex = 2.0f;
			enemy[i].scaley = 1.2f;
			enemy[i].resetXY();

			if (enemy[i].type == 1){
				score += 10000;
			}
			else if (enemy[i].type == 2){
				score += 50000;
			}
			else if (enemy[i].type == 3){
				score += 7500;
			}
			else if (enemy[i].type == 4){
				score += 75000;
			}
			else if (enemy[i].type == 100){
				score += 1000000;
				bossAlive--;
				killTime = gametime;
				//level = GAME_LEVEL_2;
				//reset();
				//return;
			}
			else if (enemy[i].type == 101){
				score += 750000;
				bossAlive--;
				killTime = gametime;
				//level = GAME_LEVEL_3;
				//reset();
				//return;
			}
			else if (enemy[i].type == 102){
				score += 2500000;
				bossAlive--;
				killTime = gametime;
				//reset();
				return;
			}
		}
	}

	for (unsigned int i = 0; i < powerups.size(); i++){
		if (enemy[powerups[i]].y + enemy[powerups[i]].height * enemy[powerups[i]].scaley < BOTTOM - 0.25f){
			enemy[powerups[i]].powerup = false;
		}
		else if (lives && collision(enemy[powerups[i]], user)){
			enemy[powerups[i]].powerup = false;
			if (user.power >= POWER5){
				score += 5000;
			}
			else {
				score += 500;
				user.power += 10;
			}
		}
		else {
			if (enemy[powerups[i]].vector.y > -0.65f){
				enemy[powerups[i]].vector.y -= 2.0f * elapsed;
			}
			enemy[powerups[i]].y += enemy[powerups[i]].vector.y * elapsed;
			enemy[powerups[i]].genMatrix();
		}
	}

	for (int i = 0; i < TOTAL_ENEMIES; i++){
		for (unsigned int j = 0; j < enemy[i].bullets.size(); j++){
			enemy[i].bullets[j].x += enemy[i].bullets[j].vector.x * elapsed;
			enemy[i].bullets[j].y += enemy[i].bullets[j].vector.y * elapsed;
			enemy[i].bullets[j].genMatrix();

			if (!dying && invincible < 0.0f && lives && bossAlive){
				if (collision(enemy[i].bullets[j], userbox)){
					//lives--;
					dying = true;
					deathTime = gametime;
					enemy[i].bullets[j].y = 100.0f;
					Mix_PlayChannel(3, userExplosion, 0);
				}
			}
		}


		if (!enemy[i].active && !enemy[i].alive){
			if (gametime > enemy[i].start){
				enemy[i].active = true;
				enemy[i].alive = true;
			}

		}
	}

	for (unsigned int i = 0; i < enemies.size(); i++){
		int j = enemies[i];
		if (enemy[j].x + enemy[j].width * enemy[j].scalex < LEFT - 0.25f){
			enemy[j].alive = false;
		}
		else if (enemy[j].x - enemy[j].width * enemy[j].scalex > RIGHT + 0.25f){
			enemy[j].alive = false;
		}
		if (enemy[j].y + enemy[j].height * enemy[j].scaley < BOTTOM - 0.25f){
			enemy[j].alive = false;
		}
		else if (enemy[j].y - enemy[j].height * enemy[j].scaley > TOP + 0.25f){
			enemy[j].alive = false;
		}

		enemy[j].timeToShoot -= elapsed;

		if (enemy[j].type == 1){
			if (gametime < enemy[j].stop){
				if (enemy[j].pos == "top"){
					enemy[j].y -= enemy[j].speed * elapsed;
				}
				else if (enemy[j].pos == "left"){
					enemy[j].x += enemy[j].speed * elapsed;
				}
				else {
					enemy[j].x -= enemy[j].speed * elapsed;
				}
			}
			else if (gametime > enemy[j].resume){
				if (enemy[j].pos == "top"){
					enemy[j].y += enemy[j].speed * elapsed;
				}
				else if (enemy[j].pos == "left"){
					enemy[j].x -= enemy[j].speed * elapsed;
				}
				else {
					enemy[j].x += enemy[j].speed * elapsed;
				}
			}

			if (enemy[j].timeToShoot < 0.0f){
				enemy[j].shoot(1, BulletTexture, 831.0f / 973.0f, 76.0f / 476.0f, 11.0f / 973.0f, 22.0f / 476.0f, 2.0f, 1.0f, (float)M_PI, 1.0f);
				enemy[j].timeToShoot = (float)rand() / (float)RAND_MAX * 1.5f + 0.75f;
			}
			//enemy[j].x += enemy[j].speed * elapsed;

		}
		else if (enemy[j].type == 2){
			if (gametime < enemy[j].stop){
				if (enemy[j].pos == "top"){
					enemy[j].y -= enemy[j].speed * elapsed;
				}
				else if (enemy[j].pos == "left"){
					enemy[j].x += enemy[j].speed * elapsed;
				}
				else {
					enemy[j].x -= enemy[j].speed * elapsed;
				}
			}
			else if (gametime > enemy[j].resume){
				if (enemy[j].pos == "top"){
					enemy[j].y += enemy[j].speed * elapsed;
				}
				else if (enemy[j].pos == "left"){
					enemy[j].x -= enemy[j].speed * elapsed;
				}
				else {
					enemy[j].x += enemy[j].speed * elapsed;
				}
			}

			if (enemy[j].timeToShoot < 0.0f){
				if (enemy[j].shotType == 1){
					enemy[j].shoot(1, BulletTexture, 223.0f / 973.0f, 64.0f / 476.0f, 17.0f / 973.0f, 12.0f / 476.0f, 2.0f, 1.0f, (float)M_PI * 11.0f / 12.0f, 0.6f);
					enemy[j].shoot(1, BulletTexture, 313.0f / 973.0f, 64.0f / 476.0f, 17.0f / 973.0f, 12.0f / 476.0f, 2.0f, 1.0f, (float)M_PI *5.0f / 6.0f, 0.6f);
					//enemy[j].shoot(1, BulletTexture, 223.0f / 973.0f, 64.0f / 476.0f, 17.0f / 973.0f, 12.0f / 476.0f, 2.0f, 1.0f, (float)M_PI, 1.0f);
					enemy[j].shoot(1, BulletTexture, 313.0f / 973.0f, 64.0f / 476.0f, 17.0f / 973.0f, 12.0f / 476.0f, 2.0f, 1.0f, (float)-M_PI * 5.0f / 6.0f, 0.6f);
					enemy[j].shoot(1, BulletTexture, 223.0f / 973.0f, 64.0f / 476.0f, 17.0f / 973.0f, 12.0f / 476.0f, 2.0f, 1.0f, (float)-M_PI * 11.0f / 12.0f, 0.6f);
					enemy[j].timeToShoot = 0.5f;
					enemy[j].shotType = 2;
				}
				else {
					enemy[j].shoot(1, BulletTexture, 313.0f / 973.0f, 64.0f / 476.0f, 17.0f / 973.0f, 12.0f / 476.0f, 2.0f, 1.0f, (float)M_PI * 11.0f / 12.0f, 0.6f);
					enemy[j].shoot(1, BulletTexture, 223.0f / 973.0f, 64.0f / 476.0f, 17.0f / 973.0f, 12.0f / 476.0f, 2.0f, 1.0f, (float)M_PI *5.0f / 6.0f, 0.6f);
					//enemy[j].shoot(1, BulletTexture, 313.0f / 973.0f, 64.0f / 476.0f, 17.0f / 973.0f, 12.0f / 476.0f, 2.0f, 1.0f, (float)M_PI, 1.0f);
					enemy[j].shoot(1, BulletTexture, 223.0f / 973.0f, 64.0f / 476.0f, 17.0f / 973.0f, 12.0f / 476.0f, 2.0f, 1.0f, (float)-M_PI * 5.0f / 6.0f, 0.6f);
					enemy[j].shoot(1, BulletTexture, 313.0f / 973.0f, 64.0f / 476.0f, 17.0f / 973.0f, 12.0f / 476.0f, 2.0f, 1.0f, (float)-M_PI * 11.0f / 12.0f, 0.6f);
					enemy[j].timeToShoot = 0.5f;
					enemy[j].shotType = 1;
				}
			}

		}
		else if (enemy[j].type == 3){
			enemy[j].y -= enemy[j].speed * elapsed;
			enemy[j].x += enemy[j].speed2 * elapsed;
		}
		else if (enemy[j].type == 4){
			if (gametime < enemy[j].stop){
				if (enemy[j].pos == "top"){
					enemy[j].y -= enemy[j].speed * elapsed;
				}
				else if (enemy[j].pos == "left"){
					enemy[j].x += enemy[j].speed * elapsed;
				}
				else {
					enemy[j].x -= enemy[j].speed * elapsed;
				}
			}
			else if (gametime > enemy[j].resume){
				if (enemy[j].pos == "top"){
					enemy[j].y += enemy[j].speed * elapsed;
				}
				else if (enemy[j].pos == "left"){
					enemy[j].x -= enemy[j].speed * elapsed;
				}
				else {
					enemy[j].x += enemy[j].speed * elapsed;
				}
			}

			if (enemy[j].timeToShoot < 0.0f){
				enemy[j].shoot(1, BulletTexture, 43.0f / 973.0f, 120.0f / 476.0f, 20.0f / 973.0f, 20.0f / 476.0f, 2.0f, 1.0f, (float)M_PI, 0.3f);
				enemy[j].timeToShoot = 0.6f;
			}
			//enemy[j].x += enemy[j].speed * elapsed;

		}
		else if (enemy[j].type == 100){
			if (gametime < enemy[j].stop){
				enemy[j].y -= enemy[j].speed * elapsed;
			}

			if (enemy[j].form == 1 && enemy[j].hp < 15000){
				enemy[j].form = 2;
			}

			else if (enemy[j].resume < 0.0f){
				if (enemy[j].pos == "left"){
					enemy[j].pos = "right";
				}
				else {
					enemy[j].pos = "left";
				}
				enemy[j].resume = 4.5f;
			}
			else {
				if (enemy[j].pos == "left"){
					enemy[j].x += enemy[j].speed * 0.2f * elapsed;
				}
				else {
					enemy[j].x -= enemy[j].speed * 0.2f * elapsed;
				}
				enemy[j].resume -= elapsed;

			}
			if (enemy[j].form == 1){
				if (enemy[j].timeToShoot < 0.0f){
					enemy[j].shoot(1, BulletTexture, 421.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, 0.0f, 0.4f);
					enemy[j].shoot(1, BulletTexture, 421.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 1.0f / 6.0f, 0.4f);
					enemy[j].shoot(1, BulletTexture, 421.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 2.0f / 6.0f, 0.4f);
					enemy[j].shoot(1, BulletTexture, 421.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 3.0f / 6.0f, 0.4f);
					enemy[j].shoot(1, BulletTexture, 421.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 4.0f / 6.0f, 0.4f);
					enemy[j].shoot(1, BulletTexture, 421.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 5.0f / 6.0f, 0.4f);
					enemy[j].shoot(1, BulletTexture, 421.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 6.0f / 6.0f, 0.4f);
					enemy[j].shoot(1, BulletTexture, 421.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 7.0f / 6.0f, 0.4f);
					enemy[j].shoot(1, BulletTexture, 421.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 8.0f / 6.0f, 0.4f);
					enemy[j].shoot(1, BulletTexture, 421.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 9.0f / 6.0f, 0.4f);
					enemy[j].shoot(1, BulletTexture, 421.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 10.0f / 6.0f, 0.4f);
					enemy[j].shoot(1, BulletTexture, 421.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 11.0f / 6.0f, 0.4f);
					enemy[j].timeToShoot = 0.5f;
				}
			}
			else if (enemy[j].form == 2){
				if (enemy[j].timeToShoot < 0.0f){
					if (enemy[j].shotType == 1){
						enemy[j].shoot(1, BulletTexture, 421.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, 0.0f, 0.5f);
						enemy[j].shoot(1, BulletTexture, 421.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 1.0f / 6.0f, 0.5f);
						enemy[j].shoot(1, BulletTexture, 421.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 2.0f / 6.0f, 0.5f);
						enemy[j].shoot(1, BulletTexture, 421.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 3.0f / 6.0f, 0.5f);
						enemy[j].shoot(1, BulletTexture, 421.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 4.0f / 6.0f, 0.5f);
						enemy[j].shoot(1, BulletTexture, 421.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 5.0f / 6.0f, 0.5f);
						enemy[j].shoot(1, BulletTexture, 421.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 6.0f / 6.0f, 0.5f);
						enemy[j].shoot(1, BulletTexture, 421.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 7.0f / 6.0f, 0.5f);
						enemy[j].shoot(1, BulletTexture, 421.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 8.0f / 6.0f, 0.5f);
						enemy[j].shoot(1, BulletTexture, 421.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 9.0f / 6.0f, 0.5f);
						enemy[j].shoot(1, BulletTexture, 421.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 10.0f / 6.0f, 0.5f);
						enemy[j].shoot(1, BulletTexture, 421.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 11.0f / 6.0f, 0.5f);
						enemy[j].timeToShoot = 0.25f;
						enemy[j].shotType = 2;
					}
					else {
						enemy[j].shoot(1, BulletTexture, 463.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 0.5f / 6.0f, 0.5f);
						enemy[j].shoot(1, BulletTexture, 463.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 1.5f / 6.0f, 0.5f);
						enemy[j].shoot(1, BulletTexture, 463.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 2.5f / 6.0f, 0.5f);
						enemy[j].shoot(1, BulletTexture, 463.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 3.5f / 6.0f, 0.5f);
						enemy[j].shoot(1, BulletTexture, 463.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 4.5f / 6.0f, 0.5f);
						enemy[j].shoot(1, BulletTexture, 463.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 5.5f / 6.0f, 0.5f);
						enemy[j].shoot(1, BulletTexture, 463.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 6.5f / 6.0f, 0.5f);
						enemy[j].shoot(1, BulletTexture, 463.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 7.5f / 6.0f, 0.5f);
						enemy[j].shoot(1, BulletTexture, 463.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 8.5f / 6.0f, 0.5f);
						enemy[j].shoot(1, BulletTexture, 463.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 9.5f / 6.0f, 0.5f);
						enemy[j].shoot(1, BulletTexture, 463.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 10.5f / 6.0f, 0.5f);
						enemy[j].shoot(1, BulletTexture, 463.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 11.5f / 6.0f, 0.5f);
						enemy[j].timeToShoot = 0.25f;
						enemy[j].shotType = 1;
					}
				}
			}
		}
		else if (enemy[j].type == 101){
			if (gametime < enemy[j].stop){
				enemy[j].y -= enemy[j].speed * elapsed;
			}

			if (enemy[j].form == 1 && enemy[j].hp < 25000){
				enemy[j].form = 2;
			}

			else if (enemy[j].resume < 0.0f){
				if (enemy[j].pos == "left"){
					enemy[j].pos = "right";
				}
				else {
					enemy[j].pos = "left";
				}
				enemy[j].resume = 4.5f;
			}
			else {
				if (enemy[j].pos == "left"){
					enemy[j].x += enemy[j].speed * 0.2f * elapsed;
				}
				else {
					enemy[j].x -= enemy[j].speed * 0.2f * elapsed;
				}
				enemy[j].resume -= elapsed;

			}
			if (enemy[j].form == 1){
				if (enemy[j].timeToShoot < 0.0f){
					enemy[j].shoot(1, BulletTexture, 421.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, 0.0f, 0.4f);
					enemy[j].shoot(1, BulletTexture, 421.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 1.0f / 6.0f, 0.4f);
					enemy[j].shoot(1, BulletTexture, 421.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 2.0f / 6.0f, 0.4f);
					enemy[j].shoot(1, BulletTexture, 421.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 3.0f / 6.0f, 0.4f);
					enemy[j].shoot(1, BulletTexture, 421.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 4.0f / 6.0f, 0.4f);
					enemy[j].shoot(1, BulletTexture, 421.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 5.0f / 6.0f, 0.4f);
					enemy[j].shoot(1, BulletTexture, 421.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 6.0f / 6.0f, 0.4f);
					enemy[j].shoot(1, BulletTexture, 421.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 7.0f / 6.0f, 0.4f);
					enemy[j].shoot(1, BulletTexture, 421.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 8.0f / 6.0f, 0.4f);
					enemy[j].shoot(1, BulletTexture, 421.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 9.0f / 6.0f, 0.4f);
					enemy[j].shoot(1, BulletTexture, 421.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 10.0f / 6.0f, 0.4f);
					enemy[j].shoot(1, BulletTexture, 421.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 11.0f / 6.0f, 0.4f);
					enemy[j].timeToShoot = 0.75f;
				}
			}
			else if (enemy[j].form == 2){
				if (enemy[j].timeToShoot < 0.0f){
					if (enemy[j].shotType == 1){
						enemy[j].shoot(1, BulletTexture, 421.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, 0.0f, 0.5f);
						enemy[j].shoot(1, BulletTexture, 421.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 1.0f / 6.0f, 0.5f);
						enemy[j].shoot(1, BulletTexture, 421.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 2.0f / 6.0f, 0.5f);
						enemy[j].shoot(1, BulletTexture, 421.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 3.0f / 6.0f, 0.5f);
						enemy[j].shoot(1, BulletTexture, 421.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 4.0f / 6.0f, 0.5f);
						enemy[j].shoot(1, BulletTexture, 421.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 5.0f / 6.0f, 0.5f);
						enemy[j].shoot(1, BulletTexture, 421.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 6.0f / 6.0f, 0.5f);
						enemy[j].shoot(1, BulletTexture, 421.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 7.0f / 6.0f, 0.5f);
						enemy[j].shoot(1, BulletTexture, 421.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 8.0f / 6.0f, 0.5f);
						enemy[j].shoot(1, BulletTexture, 421.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 9.0f / 6.0f, 0.5f);
						enemy[j].shoot(1, BulletTexture, 421.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 10.0f / 6.0f, 0.5f);
						enemy[j].shoot(1, BulletTexture, 421.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 11.0f / 6.0f, 0.5f);
						enemy[j].timeToShoot = 0.5f;
						enemy[j].shotType = 2;
					}
					else {
						enemy[j].shoot(1, BulletTexture, 463.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 0.5f / 6.0f, 0.5f);
						enemy[j].shoot(1, BulletTexture, 463.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 1.5f / 6.0f, 0.5f);
						enemy[j].shoot(1, BulletTexture, 463.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 2.5f / 6.0f, 0.5f);
						enemy[j].shoot(1, BulletTexture, 463.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 3.5f / 6.0f, 0.5f);
						enemy[j].shoot(1, BulletTexture, 463.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 4.5f / 6.0f, 0.5f);
						enemy[j].shoot(1, BulletTexture, 463.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 5.5f / 6.0f, 0.5f);
						enemy[j].shoot(1, BulletTexture, 463.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 6.5f / 6.0f, 0.5f);
						enemy[j].shoot(1, BulletTexture, 463.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 7.5f / 6.0f, 0.5f);
						enemy[j].shoot(1, BulletTexture, 463.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 8.5f / 6.0f, 0.5f);
						enemy[j].shoot(1, BulletTexture, 463.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 9.5f / 6.0f, 0.5f);
						enemy[j].shoot(1, BulletTexture, 463.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 10.5f / 6.0f, 0.5f);
						enemy[j].shoot(1, BulletTexture, 463.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 11.5f / 6.0f, 0.5f);
						enemy[j].timeToShoot = 0.5f;
						enemy[j].shotType = 1;
					}
				}
			}
		}
		else if (enemy[j].type == 102){
			if (enemy[j].x - enemy[j].width * enemy[j].scalex < LEFT){
				enemy[j].x = LEFT + enemy[j].width * enemy[j].scalex;
				enemy[j].speed *= -1.0f;
			}
			else if (enemy[j].x + enemy[j].width * enemy[j].scalex > RIGHT){
				enemy[j].x = RIGHT - enemy[j].width * enemy[j].scalex;
				enemy[j].speed *= -1.0f;
			}/*
			if (enemy[j].y - enemy[j].height * enemy[j].scaley < BOTTOM){
			enemy[j].y = BOTTOM + enemy[j].height * enemy[j].scaley;
			}
			else if (enemy[j].y + enemy[j].height * enemy[j].scaley > TOP){
			enemy[j].y = TOP - enemy[j].height * enemy[j].scaley;
			}*/

			if (gametime < enemy[j].stop){
				enemy[j].y -= enemy[j].speed * elapsed;
			}


			if (enemy[j].form == 1 && enemy[j].hp < 50000){
				enemy[j].form = 2;
			}
			else if (enemy[j].form == 2 && enemy[j].hp < 25000){
				enemy[j].form = 3;
			}
			/*
			else if (enemy[j].resume < 0.0f){
			if (enemy[j].pos == "left"){
			enemy[j].pos = "right";
			}
			else {
			enemy[j].pos = "left";
			}
			enemy[j].resume = 4.5f;
			}
			else {
			if (enemy[j].pos == "left"){
			enemy[j].x += enemy[j].speed * 0.2f * elapsed;
			}
			else {
			enemy[j].x -= enemy[j].speed * 0.2f * elapsed;
			}
			enemy[j].resume -= elapsed;

			}*/

			if (enemy[j].form == 1){
				/*
				if (enemy[j].x-enemy[j].width*enemy[j].scalex2*enemy[j].scalex < LEFT){
				enemy[j].speed *= -1.0f;
				}
				enemy[j].x += enemy[j].speed * 0.2f * elapsed;*/

				if (enemy[j].resume < 0.0f){
					if (enemy[j].pos == "left"){
						enemy[j].pos = "right";
					}
					else {
						enemy[j].pos = "left";
					}
					enemy[j].resume = (float)rand() / (float)RAND_MAX * 3.0f + 1.0f;
					enemy[j].speed = (float)rand() / (float)RAND_MAX * 2.0f + 1.0f;
				}
				else {
					if (enemy[j].pos == "left"){
						enemy[j].x += enemy[j].speed * 0.2f * elapsed;
					}
					else {
						enemy[j].x -= enemy[j].speed * 0.2f * elapsed;
					}
					enemy[j].resume -= elapsed;

				}
				if (enemy[j].timeToShoot < 0.0f){
					enemy[j].shoot(1, BulletTexture, 554.0f / 973.0f, 17.0f / 476.0f, 18.0f / 973.0f, 24.0f / 476.0f, 1.5f, 1.0f, (float)M_PI, 1.0f, enemy[j].x - 0.35f);
					enemy[j].shoot(1, BulletTexture, 554.0f / 973.0f, 17.0f / 476.0f, 18.0f / 973.0f, 24.0f / 476.0f, 1.5f, 1.0f, (float)M_PI, 1.0f, enemy[j].x + 0.35f);

					enemy[j].shoot(1, BulletTexture, 554.0f / 973.0f, 17.0f / 476.0f, 18.0f / 973.0f, 24.0f / 476.0f, 1.5f, 1.0f, (float)M_PI, 1.0f, enemy[j].x - 0.25f);
					enemy[j].shoot(1, BulletTexture, 554.0f / 973.0f, 17.0f / 476.0f, 18.0f / 973.0f, 24.0f / 476.0f, 1.5f, 1.0f, (float)M_PI, 1.0f, enemy[j].x + 0.25f);
					//enemy[j].shoot(1, BulletTexture, 421.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 1.0f / 6.0f, 0.4f);
					//enemy[j].shoot(1, BulletTexture, 421.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 2.0f / 6.0f, 0.4f);
					//enemy[j].shoot(1, BulletTexture, 421.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 3.0f / 6.0f, 0.4f);
					//enemy[j].shoot(1, BulletTexture, 421.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 4.0f / 6.0f, 0.4f);
					//enemy[j].shoot(1, BulletTexture, 421.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 5.0f / 6.0f, 0.4f);
					//enemy[j].shoot(1, BulletTexture, 421.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 6.0f / 6.0f, 0.4f);
					//enemy[j].shoot(1, BulletTexture, 421.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 7.0f / 6.0f, 0.4f);
					//enemy[j].shoot(1, BulletTexture, 421.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 8.0f / 6.0f, 0.4f);
					//enemy[j].shoot(1, BulletTexture, 421.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 9.0f / 6.0f, 0.4f);
					//enemy[j].shoot(1, BulletTexture, 421.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 10.0f / 6.0f, 0.4f);
					//enemy[j].shoot(1, BulletTexture, 421.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 11.0f / 6.0f, 0.4f);
					enemy[j].timeToShoot = 0.1f;
				}


			}
			else if (enemy[j].form == 2){
				if (enemy[j].x - user.x > 0.01f){
					enemy[j].x = enemy[j].x - 0.5f*pow((enemy[j].x - user.x), 2.0f);
				}
				else if (enemy[j].x - user.x < -0.01f){
					enemy[j].x = enemy[j].x + 0.5f*pow((enemy[j].x - user.x), 2.0f);
				}

				if (enemy[j].timeToShoot < 0.0f){
					enemy[j].shoot(1, BulletTexture, 554.0f / 973.0f, 17.0f / 476.0f, 18.0f / 973.0f, 24.0f / 476.0f, 1.5f, 1.0f, (float)M_PI, 1.0f, enemy[j].x - 0.35f);
					enemy[j].shoot(1, BulletTexture, 554.0f / 973.0f, 17.0f / 476.0f, 18.0f / 973.0f, 24.0f / 476.0f, 1.5f, 1.0f, (float)M_PI, 1.0f, enemy[j].x + 0.35f);

					enemy[j].shoot(1, BulletTexture, 554.0f / 973.0f, 17.0f / 476.0f, 18.0f / 973.0f, 24.0f / 476.0f, 1.5f, 1.0f, (float)M_PI, 1.0f, enemy[j].x - 0.25f);
					enemy[j].shoot(1, BulletTexture, 554.0f / 973.0f, 17.0f / 476.0f, 18.0f / 973.0f, 24.0f / 476.0f, 1.5f, 1.0f, (float)M_PI, 1.0f, enemy[j].x + 0.25f);
					//enemy[j].shoot(1, BulletTexture, 421.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 1.0f / 6.0f, 0.4f);
					//enemy[j].shoot(1, BulletTexture, 421.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 2.0f / 6.0f, 0.4f);
					//enemy[j].shoot(1, BulletTexture, 421.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 3.0f / 6.0f, 0.4f);
					//enemy[j].shoot(1, BulletTexture, 421.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 4.0f / 6.0f, 0.4f);
					//enemy[j].shoot(1, BulletTexture, 421.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 5.0f / 6.0f, 0.4f);
					//enemy[j].shoot(1, BulletTexture, 421.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 6.0f / 6.0f, 0.4f);
					//enemy[j].shoot(1, BulletTexture, 421.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 7.0f / 6.0f, 0.4f);
					//enemy[j].shoot(1, BulletTexture, 421.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 8.0f / 6.0f, 0.4f);
					//enemy[j].shoot(1, BulletTexture, 421.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 9.0f / 6.0f, 0.4f);
					//enemy[j].shoot(1, BulletTexture, 421.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 10.0f / 6.0f, 0.4f);
					//enemy[j].shoot(1, BulletTexture, 421.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 11.0f / 6.0f, 0.4f);
					enemy[j].timeToShoot = 0.1f;
				}
				if (enemy[j].between){
					float p = (float)floor((float)rand() / (float)RAND_MAX * 12.0f);
					float xTemp = 253.0f + (float)p*33.0f;
					float dir = (float)rand() / (float)RAND_MAX * 2.0f * (float)M_PI;
					enemy[j].shoot(1, BulletTexture, xTemp / 973.0f, 109.0f / 476.0f, 32.0f / 973.0f, 32.0f / 476.0f, 2.0f, 1.0f, dir, 0.75f);
					enemy[j].between = false;
				}
				else {
					if ((float)rand() / (float)RAND_MAX < 0.5f){
						enemy[j].between = true;
					}
				}

			}
			else if (enemy[j].form == 3){
				if (enemy[j].x - user.x > 0.01f){
					enemy[j].x = enemy[j].x - 0.15f*pow((enemy[j].x - user.x), 2.0f);
				}
				else if (enemy[j].x - user.x < -0.01f){
					enemy[j].x = enemy[j].x + 0.15f*pow((enemy[j].x - user.x), 2.0f);
				}

				if (enemy[j].timeToShoot < 0.0f){
					enemy[j].shoot(1, BulletTexture, 554.0f / 973.0f, 17.0f / 476.0f, 18.0f / 973.0f, 24.0f / 476.0f, 1.5f, 1.0f, (float)M_PI, 1.0f, enemy[j].x - 0.35f);
					enemy[j].shoot(1, BulletTexture, 554.0f / 973.0f, 17.0f / 476.0f, 18.0f / 973.0f, 24.0f / 476.0f, 1.5f, 1.0f, (float)M_PI, 1.0f, enemy[j].x + 0.35f);

					enemy[j].shoot(1, BulletTexture, 554.0f / 973.0f, 17.0f / 476.0f, 18.0f / 973.0f, 24.0f / 476.0f, 1.5f, 1.0f, (float)M_PI, 1.0f, enemy[j].x - 0.25f);
					enemy[j].shoot(1, BulletTexture, 554.0f / 973.0f, 17.0f / 476.0f, 18.0f / 973.0f, 24.0f / 476.0f, 1.5f, 1.0f, (float)M_PI, 1.0f, enemy[j].x + 0.25f);
					//enemy[j].shoot(1, BulletTexture, 421.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 1.0f / 6.0f, 0.4f);
					//enemy[j].shoot(1, BulletTexture, 421.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 2.0f / 6.0f, 0.4f);
					//enemy[j].shoot(1, BulletTexture, 421.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 3.0f / 6.0f, 0.4f);
					//enemy[j].shoot(1, BulletTexture, 421.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 4.0f / 6.0f, 0.4f);
					//enemy[j].shoot(1, BulletTexture, 421.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 5.0f / 6.0f, 0.4f);
					//enemy[j].shoot(1, BulletTexture, 421.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 6.0f / 6.0f, 0.4f);
					//enemy[j].shoot(1, BulletTexture, 421.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 7.0f / 6.0f, 0.4f);
					//enemy[j].shoot(1, BulletTexture, 421.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 8.0f / 6.0f, 0.4f);
					//enemy[j].shoot(1, BulletTexture, 421.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 9.0f / 6.0f, 0.4f);
					//enemy[j].shoot(1, BulletTexture, 421.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 10.0f / 6.0f, 0.4f);
					//enemy[j].shoot(1, BulletTexture, 421.0f / 973.0f, 67.0f / 476.0f, 5.0f / 973.0f, 9.0f / 476.0f, 4.0f, 2.0f, (float)M_PI * 11.0f / 6.0f, 0.4f);
					enemy[j].timeToShoot = 0.1f;
				}
				if (enemy[j].between){
					float p = (float)floor((float)rand() / (float)RAND_MAX * 12.0f);
					float xTemp = 253.0f + (float)p*33.0f;
					float dir = (float)rand() / (float)RAND_MAX * 2.0f * (float)M_PI;
					enemy[j].shoot(1, BulletTexture, xTemp / 973.0f, 109.0f / 476.0f, 32.0f / 973.0f, 32.0f / 476.0f, 2.0f, 1.0f, dir, 0.75f);
					enemy[j].between = false;
				}
				else {
					enemy[j].between = true;
				}
			}
		}


		/*
		else {
		enemy[j].y -= enemy[j].speed*elapsed;
		}*/


		enemy[j].genMatrix();
	}

	if (!dying && lives){
		if (keys[SDL_SCANCODE_LSHIFT]){
			if (keys[SDL_SCANCODE_LEFT]){
				user.x -= 0.5f * elapsed;
			}
			else if (keys[SDL_SCANCODE_RIGHT]){
				user.x += 0.5f * elapsed;
			}

			if (keys[SDL_SCANCODE_UP]){
				user.y += 0.5f * elapsed;
			}
			else if (keys[SDL_SCANCODE_DOWN]){
				user.y -= 0.5f * elapsed;
			}


			if (keys[SDL_SCANCODE_Z] && lastshot > 0.05f){
				Mix_PlayChannel(0, userShoot, 0);
				if (user.power < POWER1){
					user.shoot(1, BulletTexture, 890.0f / 973.0f, 20.0f / 476.0f, 11.0f / 973.0f, 18.0f / 476.0f, 2.0f, 1.0f, 0.0f, 3.0f, user.x - 0.035f);
					user.shoot(1, BulletTexture, 890.0f / 973.0f, 20.0f / 476.0f, 11.0f / 973.0f, 18.0f / 476.0f, 2.0f, 1.0f, 0.0f, 3.0f, user.x + 0.035f);
				}
				else if (user.power < POWER2) {
					user.shoot(1, BulletTexture, 890.0f / 973.0f, 20.0f / 476.0f, 11.0f / 973.0f, 18.0f / 476.0f, 2.0f, 1.0f, 0.0f, 3.0f, user.x - 0.05f);
					user.shoot(1, BulletTexture, 784.0f / 973.0f, 294.0f / 476.0f, 4.0f / 973.0f, 16.0f / 476.0f, 2.5f, 1.5f, 0.0f, 3.0f, user.x - 0.01f);
					user.shoot(1, BulletTexture, 784.0f / 973.0f, 294.0f / 476.0f, 4.0f / 973.0f, 16.0f / 476.0f, 2.5f, 1.5f, 0.0f, 3.0f, user.x + 0.01f);
					user.shoot(1, BulletTexture, 890.0f / 973.0f, 20.0f / 476.0f, 11.0f / 973.0f, 18.0f / 476.0f, 2.0f, 1.0f, 0.0f, 3.0f, user.x + 0.05f);
				}
				else if (user.power < POWER3) {
					user.shoot(3, BulletTexture, 172.0f / 973.0f, 33.0f / 476.0f, 18.0f / 973.0f, 24.0f / 476.0f, 1.5f, 1.0f, (float)M_PI / 9.0f / 2.0f, 3.0f, user.x - 0.025f);
					user.shoot(1, BulletTexture, 890.0f / 973.0f, 20.0f / 476.0f, 11.0f / 973.0f, 18.0f / 476.0f, 2.0f, 1.0f, 0.0f, 3.0f, user.x - 0.05f);
					user.shoot(1, BulletTexture, 784.0f / 973.0f, 294.0f / 476.0f, 4.0f / 973.0f, 16.0f / 476.0f, 2.5f, 1.5f, 0.0f, 3.0f, user.x - 0.01f);
					user.shoot(1, BulletTexture, 784.0f / 973.0f, 294.0f / 476.0f, 4.0f / 973.0f, 16.0f / 476.0f, 2.5f, 1.5f, 0.0f, 3.0f, user.x + 0.01f);
					user.shoot(1, BulletTexture, 890.0f / 973.0f, 20.0f / 476.0f, 11.0f / 973.0f, 18.0f / 476.0f, 2.0f, 1.0f, 0.0f, 3.0f, user.x + 0.05f);
					user.shoot(3, BulletTexture, 172.0f / 973.0f, 33.0f / 476.0f, 18.0f / 973.0f, 24.0f / 476.0f, 1.5f, 1.0f, (float)-M_PI / 9.0f / 2.0f, 3.0f, user.x + 0.025f);
				}
				else if (user.power < POWER4) {
					user.shoot(1, BulletTexture, 890.0f / 973.0f, 20.0f / 476.0f, 11.0f / 973.0f, 18.0f / 476.0f, 2.0f, 1.0f, 0.0f, 3.0f, user.x - 0.05f);
					user.shoot(1, BulletTexture, 784.0f / 973.0f, 294.0f / 476.0f, 4.0f / 973.0f, 16.0f / 476.0f, 2.5f, 1.5f, 0.0f, 3.0f, user.x - 0.01f);
					user.shoot(1, BulletTexture, 784.0f / 973.0f, 294.0f / 476.0f, 4.0f / 973.0f, 16.0f / 476.0f, 2.5f, 1.5f, 0.0f, 3.0f, user.x + 0.01f);
					user.shoot(1, BulletTexture, 890.0f / 973.0f, 20.0f / 476.0f, 11.0f / 973.0f, 18.0f / 476.0f, 2.0f, 1.0f, 0.0f, 3.0f, user.x + 0.05f);
					user.shoot(3, BulletTexture, 172.0f / 973.0f, 33.0f / 476.0f, 18.0f / 973.0f, 24.0f / 476.0f, 1.5f, 1.0f, (float)M_PI / 9.0f / 2.0f, 3.0f, user.x - 0.025f);
					user.shoot(3, BulletTexture, 172.0f / 973.0f, 33.0f / 476.0f, 18.0f / 973.0f, 24.0f / 476.0f, 1.5f, 1.0f, (float)-M_PI / 9.0f / 2.0f, 3.0f, user.x + 0.025f);
					user.shoot(3, BulletTexture, 172.0f / 973.0f, 14.0f / 476.0f, 18.0f / 973.0f, 18.0f / 476.0f, 1.5f, 1.0f, (float)M_PI / 18.0f / 2.0f, 3.0f, user.x);
					user.shoot(3, BulletTexture, 172.0f / 973.0f, 14.0f / 476.0f, 18.0f / 973.0f, 18.0f / 476.0f, 1.5f, 1.0f, (float)-M_PI / 18.0f / 2.0f, 3.0f, user.x);
				}
				else if (user.power < POWER5){
					user.shoot(1, BulletTexture, 890.0f / 973.0f, 20.0f / 476.0f, 11.0f / 973.0f, 18.0f / 476.0f, 2.0f, 1.0f, 0.0f, 3.0f, user.x - 0.05f);
					user.shoot(1, BulletTexture, 784.0f / 973.0f, 294.0f / 476.0f, 4.0f / 973.0f, 16.0f / 476.0f, 2.5f, 1.5f, 0.0f, 3.0f, user.x - 0.01f);
					user.shoot(1, BulletTexture, 784.0f / 973.0f, 294.0f / 476.0f, 4.0f / 973.0f, 16.0f / 476.0f, 2.5f, 1.5f, 0.0f, 3.0f, user.x + 0.01f);
					user.shoot(1, BulletTexture, 890.0f / 973.0f, 20.0f / 476.0f, 11.0f / 973.0f, 18.0f / 476.0f, 2.0f, 1.0f, 0.0f, 3.0f, user.x + 0.05f);
					user.shoot(3, BulletTexture, 172.0f / 973.0f, 33.0f / 476.0f, 18.0f / 973.0f, 24.0f / 476.0f, 1.5f, 1.0f, (float)M_PI / 9.0f / 2.0f, 3.0f, user.x - 0.025f);
					user.shoot(3, BulletTexture, 172.0f / 973.0f, 33.0f / 476.0f, 18.0f / 973.0f, 24.0f / 476.0f, 1.5f, 1.0f, (float)-M_PI / 9.0f / 2.0f, 3.0f, user.x + 0.025f);
					user.shoot(3, BulletTexture, 172.0f / 973.0f, 14.0f / 476.0f, 18.0f / 973.0f, 18.0f / 476.0f, 1.5f, 1.0f, (float)M_PI / 18.0f / 2.0f, 3.0f, user.x);
					user.shoot(3, BulletTexture, 172.0f / 973.0f, 14.0f / 476.0f, 18.0f / 973.0f, 18.0f / 476.0f, 1.5f, 1.0f, (float)-M_PI / 18.0f / 2.0f, 3.0f, user.x);
					if (lastmissile > 0.8f){
						lastmissile = 0.0f;
						user.shoot(2, BulletTexture, 769.0f / 973.0f, 179.0f / 476.0f, 14.0f / 973.0f, 41.0f / 476.0f, 2.0f, 1.0f, 0.0f, 1.2f, user.x - 0.05f, user.y - 0.1f);
						user.shoot(2, BulletTexture, 769.0f / 973.0f, 179.0f / 476.0f, 14.0f / 973.0f, 41.0f / 476.0f, 2.0f, 1.0f, 0.0f, 1.2f, user.x + 0.05f, user.y - 0.1f);
					}
				}
				else {
					user.shoot(1, BulletTexture, 890.0f / 973.0f, 20.0f / 476.0f, 11.0f / 973.0f, 18.0f / 476.0f, 2.0f, 1.0f, 0.0f, 3.0f, user.x - 0.05f);
					user.shoot(1, BulletTexture, 784.0f / 973.0f, 294.0f / 476.0f, 4.0f / 973.0f, 16.0f / 476.0f, 2.5f, 1.5f, 0.0f, 3.0f, user.x - 0.01f);
					user.shoot(1, BulletTexture, 784.0f / 973.0f, 294.0f / 476.0f, 4.0f / 973.0f, 16.0f / 476.0f, 2.5f, 1.5f, 0.0f, 3.0f, user.x + 0.01f);
					user.shoot(1, BulletTexture, 890.0f / 973.0f, 20.0f / 476.0f, 11.0f / 973.0f, 18.0f / 476.0f, 2.0f, 1.0f, 0.0f, 3.0f, user.x + 0.05f);
					user.shoot(3, BulletTexture, 172.0f / 973.0f, 33.0f / 476.0f, 18.0f / 973.0f, 24.0f / 476.0f, 1.5f, 1.0f, (float)M_PI / 9.0f / 2.0f, 3.0f, user.x - 0.025f);
					user.shoot(3, BulletTexture, 172.0f / 973.0f, 33.0f / 476.0f, 18.0f / 973.0f, 24.0f / 476.0f, 1.5f, 1.0f, (float)-M_PI / 9.0f / 2.0f, 3.0f, user.x + 0.025f);
					user.shoot(3, BulletTexture, 172.0f / 973.0f, 14.0f / 476.0f, 18.0f / 973.0f, 18.0f / 476.0f, 1.5f, 1.0f, (float)M_PI / 18.0f / 2.0f, 3.0f, user.x);
					user.shoot(3, BulletTexture, 172.0f / 973.0f, 14.0f / 476.0f, 18.0f / 973.0f, 18.0f / 476.0f, 1.5f, 1.0f, (float)-M_PI / 18.0f / 2.0f, 3.0f, user.x);
					if (lastmissile > 0.8f){
						lastmissile = 0.0f;
						user.shoot(2, BulletTexture, 799.0f / 973.0f, 179.0f / 476.0f, 14.0f / 973.0f, 41.0f / 476.0f, 2.0f, 1.0f, 0.0f, 0.8f, user.x - 0.1f, user.y - 0.2f);
						user.shoot(2, BulletTexture, 784.0f / 973.0f, 179.0f / 476.0f, 14.0f / 973.0f, 41.0f / 476.0f, 2.0f, 1.0f, 0.0f, 1.0f, user.x - 0.075f, user.y - 0.15f);
						user.shoot(2, BulletTexture, 769.0f / 973.0f, 179.0f / 476.0f, 14.0f / 973.0f, 41.0f / 476.0f, 2.0f, 1.0f, 0.0f, 1.2f, user.x - 0.05f, user.y - 0.1f);
						user.shoot(2, BulletTexture, 769.0f / 973.0f, 179.0f / 476.0f, 14.0f / 973.0f, 41.0f / 476.0f, 2.0f, 1.0f, 0.0f, 1.2f, user.x + 0.05f, user.y - 0.1f);
						user.shoot(2, BulletTexture, 784.0f / 973.0f, 179.0f / 476.0f, 14.0f / 973.0f, 41.0f / 476.0f, 2.0f, 1.0f, 0.0f, 1.0f, user.x + 0.075f, user.y - 0.15f);
						user.shoot(2, BulletTexture, 799.0f / 973.0f, 179.0f / 476.0f, 14.0f / 973.0f, 41.0f / 476.0f, 2.0f, 1.0f, 0.0f, 0.8f, user.x + 0.1f, user.y - 0.2f);
					}
				}
				lastshot = 0.0f;
			}




		}
		else{

			if (keys[SDL_SCANCODE_LEFT]){
				user.x -= 1.0f * elapsed;
			}
			else if (keys[SDL_SCANCODE_RIGHT]){
				user.x += 1.0f * elapsed;
			}

			if (keys[SDL_SCANCODE_UP]){
				user.y += 1.0f * elapsed;
			}
			else if (keys[SDL_SCANCODE_DOWN]){
				user.y -= 1.0f * elapsed;
			}


			if (keys[SDL_SCANCODE_Z] && lastshot > 0.05f){
				Mix_PlayChannel(0, userShoot, 0);
				if (user.power < POWER1){
					user.shoot(1, BulletTexture, 890.0f / 973.0f, 20.0f / 476.0f, 11.0f / 973.0f, 18.0f / 476.0f, 2.0f, 1.0f, 0.0f, 3.0f, user.x - 0.035f);
					user.shoot(1, BulletTexture, 890.0f / 973.0f, 20.0f / 476.0f, 11.0f / 973.0f, 18.0f / 476.0f, 2.0f, 1.0f, 0.0f, 3.0f, user.x + 0.035f);
				}
				else if (user.power < POWER2) {
					user.shoot(1, BulletTexture, 890.0f / 973.0f, 20.0f / 476.0f, 11.0f / 973.0f, 18.0f / 476.0f, 2.0f, 1.0f, 0.0f, 3.0f, user.x - 0.05f);
					user.shoot(1, BulletTexture, 784.0f / 973.0f, 294.0f / 476.0f, 4.0f / 973.0f, 16.0f / 476.0f, 2.5f, 1.5f, 0.0f, 3.0f, user.x - 0.01f);
					user.shoot(1, BulletTexture, 784.0f / 973.0f, 294.0f / 476.0f, 4.0f / 973.0f, 16.0f / 476.0f, 2.5f, 1.5f, 0.0f, 3.0f, user.x + 0.01f);
					user.shoot(1, BulletTexture, 890.0f / 973.0f, 20.0f / 476.0f, 11.0f / 973.0f, 18.0f / 476.0f, 2.0f, 1.0f, 0.0f, 3.0f, user.x + 0.05f);
				}
				else if (user.power < POWER3) {
					user.shoot(3, BulletTexture, 172.0f / 973.0f, 33.0f / 476.0f, 18.0f / 973.0f, 24.0f / 476.0f, 1.5f, 1.0f, (float)M_PI / 9.0f, 3.0f, user.x - 0.025f);
					user.shoot(1, BulletTexture, 890.0f / 973.0f, 20.0f / 476.0f, 11.0f / 973.0f, 18.0f / 476.0f, 2.0f, 1.0f, 0.0f, 3.0f, user.x - 0.05f);
					user.shoot(1, BulletTexture, 784.0f / 973.0f, 294.0f / 476.0f, 4.0f / 973.0f, 16.0f / 476.0f, 2.5f, 1.5f, 0.0f, 3.0f, user.x - 0.01f);
					user.shoot(1, BulletTexture, 784.0f / 973.0f, 294.0f / 476.0f, 4.0f / 973.0f, 16.0f / 476.0f, 2.5f, 1.5f, 0.0f, 3.0f, user.x + 0.01f);
					user.shoot(1, BulletTexture, 890.0f / 973.0f, 20.0f / 476.0f, 11.0f / 973.0f, 18.0f / 476.0f, 2.0f, 1.0f, 0.0f, 3.0f, user.x + 0.05f);
					user.shoot(3, BulletTexture, 172.0f / 973.0f, 33.0f / 476.0f, 18.0f / 973.0f, 24.0f / 476.0f, 1.5f, 1.0f, (float)-M_PI / 9.0f, 3.0f, user.x + 0.025f);
				}
				else if (user.power < POWER4) {
					user.shoot(1, BulletTexture, 890.0f / 973.0f, 20.0f / 476.0f, 11.0f / 973.0f, 18.0f / 476.0f, 2.0f, 1.0f, 0.0f, 3.0f, user.x - 0.05f);
					user.shoot(1, BulletTexture, 784.0f / 973.0f, 294.0f / 476.0f, 4.0f / 973.0f, 16.0f / 476.0f, 2.5f, 1.5f, 0.0f, 3.0f, user.x - 0.01f);
					user.shoot(1, BulletTexture, 784.0f / 973.0f, 294.0f / 476.0f, 4.0f / 973.0f, 16.0f / 476.0f, 2.5f, 1.5f, 0.0f, 3.0f, user.x + 0.01f);
					user.shoot(1, BulletTexture, 890.0f / 973.0f, 20.0f / 476.0f, 11.0f / 973.0f, 18.0f / 476.0f, 2.0f, 1.0f, 0.0f, 3.0f, user.x + 0.05f);
					user.shoot(3, BulletTexture, 172.0f / 973.0f, 33.0f / 476.0f, 18.0f / 973.0f, 24.0f / 476.0f, 1.5f, 1.0f, (float)M_PI / 9.0f, 3.0f, user.x - 0.025f);
					user.shoot(3, BulletTexture, 172.0f / 973.0f, 33.0f / 476.0f, 18.0f / 973.0f, 24.0f / 476.0f, 1.5f, 1.0f, (float)-M_PI / 9.0f, 3.0f, user.x + 0.025f);
					user.shoot(3, BulletTexture, 172.0f / 973.0f, 14.0f / 476.0f, 18.0f / 973.0f, 18.0f / 476.0f, 1.5f, 1.0f, (float)M_PI / 18.0f, 3.0f, user.x);
					user.shoot(3, BulletTexture, 172.0f / 973.0f, 14.0f / 476.0f, 18.0f / 973.0f, 18.0f / 476.0f, 1.5f, 1.0f, (float)-M_PI / 18.0f, 3.0f, user.x);
				}
				else if (user.power < POWER5){
					user.shoot(1, BulletTexture, 890.0f / 973.0f, 20.0f / 476.0f, 11.0f / 973.0f, 18.0f / 476.0f, 2.0f, 1.0f, 0.0f, 3.0f, user.x - 0.05f);
					user.shoot(1, BulletTexture, 784.0f / 973.0f, 294.0f / 476.0f, 4.0f / 973.0f, 16.0f / 476.0f, 2.5f, 1.5f, 0.0f, 3.0f, user.x - 0.01f);
					user.shoot(1, BulletTexture, 784.0f / 973.0f, 294.0f / 476.0f, 4.0f / 973.0f, 16.0f / 476.0f, 2.5f, 1.5f, 0.0f, 3.0f, user.x + 0.01f);
					user.shoot(1, BulletTexture, 890.0f / 973.0f, 20.0f / 476.0f, 11.0f / 973.0f, 18.0f / 476.0f, 2.0f, 1.0f, 0.0f, 3.0f, user.x + 0.05f);
					user.shoot(3, BulletTexture, 172.0f / 973.0f, 33.0f / 476.0f, 18.0f / 973.0f, 24.0f / 476.0f, 1.5f, 1.0f, (float)M_PI / 9.0f, 3.0f, user.x - 0.025f);
					user.shoot(3, BulletTexture, 172.0f / 973.0f, 33.0f / 476.0f, 18.0f / 973.0f, 24.0f / 476.0f, 1.5f, 1.0f, (float)-M_PI / 9.0f, 3.0f, user.x + 0.025f);
					user.shoot(3, BulletTexture, 172.0f / 973.0f, 14.0f / 476.0f, 18.0f / 973.0f, 18.0f / 476.0f, 1.5f, 1.0f, (float)M_PI / 18.0f, 3.0f, user.x);
					user.shoot(3, BulletTexture, 172.0f / 973.0f, 14.0f / 476.0f, 18.0f / 973.0f, 18.0f / 476.0f, 1.5f, 1.0f, (float)-M_PI / 18.0f, 3.0f, user.x);
					if (lastmissile > 0.8f){
						lastmissile = 0.0f;
						user.shoot(2, BulletTexture, 769.0f / 973.0f, 179.0f / 476.0f, 14.0f / 973.0f, 41.0f / 476.0f, 2.0f, 1.0f, 0.0f, 1.0f, user.x - 0.2f, user.y - 0.1f);
						user.shoot(2, BulletTexture, 769.0f / 973.0f, 179.0f / 476.0f, 14.0f / 973.0f, 41.0f / 476.0f, 2.0f, 1.0f, 0.0f, 1.0f, user.x + 0.2f, user.y - 0.1f);
					}
				}
				else {
					user.shoot(1, BulletTexture, 890.0f / 973.0f, 20.0f / 476.0f, 11.0f / 973.0f, 18.0f / 476.0f, 2.0f, 1.0f, 0.0f, 3.0f, user.x - 0.05f);
					user.shoot(1, BulletTexture, 784.0f / 973.0f, 294.0f / 476.0f, 4.0f / 973.0f, 16.0f / 476.0f, 2.5f, 1.5f, 0.0f, 3.0f, user.x - 0.01f);
					user.shoot(1, BulletTexture, 784.0f / 973.0f, 294.0f / 476.0f, 4.0f / 973.0f, 16.0f / 476.0f, 2.5f, 1.5f, 0.0f, 3.0f, user.x + 0.01f);
					user.shoot(1, BulletTexture, 890.0f / 973.0f, 20.0f / 476.0f, 11.0f / 973.0f, 18.0f / 476.0f, 2.0f, 1.0f, 0.0f, 3.0f, user.x + 0.05f);
					user.shoot(3, BulletTexture, 172.0f / 973.0f, 33.0f / 476.0f, 18.0f / 973.0f, 24.0f / 476.0f, 1.5f, 1.0f, (float)M_PI / 9.0f, 3.0f, user.x - 0.025f);
					user.shoot(3, BulletTexture, 172.0f / 973.0f, 33.0f / 476.0f, 18.0f / 973.0f, 24.0f / 476.0f, 1.5f, 1.0f, (float)-M_PI / 9.0f, 3.0f, user.x + 0.025f);
					user.shoot(3, BulletTexture, 172.0f / 973.0f, 14.0f / 476.0f, 18.0f / 973.0f, 18.0f / 476.0f, 1.5f, 1.0f, (float)M_PI / 18.0f, 3.0f, user.x);
					user.shoot(3, BulletTexture, 172.0f / 973.0f, 14.0f / 476.0f, 18.0f / 973.0f, 18.0f / 476.0f, 1.5f, 1.0f, (float)-M_PI / 18.0f, 3.0f, user.x);
					if (lastmissile > 0.8f){
						lastmissile = 0.0f;
						user.shoot(2, BulletTexture, 799.0f / 973.0f, 179.0f / 476.0f, 14.0f / 973.0f, 41.0f / 476.0f, 2.0f, 1.0f, 0.0f, 0.8f, user.x - 0.5f, user.y - 0.2f);
						user.shoot(2, BulletTexture, 784.0f / 973.0f, 179.0f / 476.0f, 14.0f / 973.0f, 41.0f / 476.0f, 2.0f, 1.0f, 0.0f, 1.0f, user.x - 0.35f, user.y - 0.15f);
						user.shoot(2, BulletTexture, 769.0f / 973.0f, 179.0f / 476.0f, 14.0f / 973.0f, 41.0f / 476.0f, 2.0f, 1.0f, 0.0f, 1.2f, user.x - 0.2f, user.y - 0.1f);
						user.shoot(2, BulletTexture, 769.0f / 973.0f, 179.0f / 476.0f, 14.0f / 973.0f, 41.0f / 476.0f, 2.0f, 1.0f, 0.0f, 1.2f, user.x + 0.2f, user.y - 0.1f);
						user.shoot(2, BulletTexture, 784.0f / 973.0f, 179.0f / 476.0f, 14.0f / 973.0f, 41.0f / 476.0f, 2.0f, 1.0f, 0.0f, 1.0f, user.x + 0.35f, user.y - 0.15f);
						user.shoot(2, BulletTexture, 799.0f / 973.0f, 179.0f / 476.0f, 14.0f / 973.0f, 41.0f / 476.0f, 2.0f, 1.0f, 0.0f, 0.8f, user.x + 0.5f, user.y - 0.2f);
					}
				}
				lastshot = 0.0f;
			}
		}
	}

	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
			done = true;
		}
		else if (event.type == SDL_KEYDOWN){
			if (event.key.keysym.scancode == SDL_SCANCODE_RETURN){
				if (!bossAlive){
					if (level == GAME_LEVEL_1){
						level = GAME_LEVEL_2;
						Mix_HaltMusic();
						reset();
						return;
					}
					else if (level == GAME_LEVEL_2){
						level = GAME_LEVEL_3;
						Mix_HaltMusic();
						reset();
						return;
					}
					else if (level == GAME_LEVEL_3){
						level = MAIN_MENU;
						Mix_HaltMusic();
						reset();
						return;
					}
				}
				else if (!lives){
					level = MAIN_MENU;
					Mix_HaltMusic();
					reset();
					return;
				}
			}
			else if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE){
				if (level == GAME_LEVEL_1 || level == GAME_LEVEL_2 || level == GAME_LEVEL_3){
					pause = true;
					Mix_PauseMusic();
					return;
				}
			}
		}
	}
}

bool App::UpdateAndRender() {
	//float ticks = (float)SDL_GetTicks() / 1000.0f;
	//float elapsed = ticks - lastFrameTicks;
	//lastFrameTicks = ticks;
	//Update(elapsed);
	//Render();

	float ticks = (float)SDL_GetTicks() / 1000.0f;
	float elapsed = ticks - lastFrameTicks;
	lastFrameTicks = ticks;

	float fixedElapsed = elapsed + timeLeftOver;
	if (fixedElapsed > FIXED_TIMESTEP * MAX_TIMESTEPS){
		fixedElapsed = FIXED_TIMESTEP * MAX_TIMESTEPS;
	}

	while (fixedElapsed >= FIXED_TIMESTEP){
		fixedElapsed -= FIXED_TIMESTEP;
		Update(FIXED_TIMESTEP);
		elapsed -= FIXED_TIMESTEP;
	}
	timeLeftOver = fixedElapsed;
	Render();

	return done;
}