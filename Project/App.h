void App::reset(){
	srand((unsigned int)time(NULL));
	switch (level){
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

void App::resetGameLevel1(){
	Mix_PlayMusic(music, 0);

	user = Entity(SheetSpriteTexture, 777.0f / 1024.0f, 712.0f / 1024.0f, 32.0f / 1024.0f, 26.0 / 1024.0f, 2.0f, 2.0f, 0);

	user.x = 0.0f;
	user.y = -0.8f;
	user.power = 0.0f;
	gametime = 0.0f;

	ifstream input;
	input.open("Level1.csv");
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
			enemy[number].hp = 100.0f;
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
			enemy[number] = Entity(SheetSpriteTexture, 519.0f / 1024.0f, 325.0f / 1024.0f, 80.0f / 1024.0f, 84.0 / 1024.0f, 0.8f, 0.8f, stoi(ttemp));
			enemy[number].alive = false;
			enemy[number].active = false;
			enemy[number].powerup = false;
			enemy[number].hp = 1000.0f;

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
			enemy[number].hp = 10000.0f;

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
		}


		number++;

	}

	//float xtemp = 0.3325f - 1.33f;
	/*
	for (int i = 0; i < 1; i++){
	enemy[i] = Entity(SheetSpriteTexture, 120.0f / 1024.0f, 605.0f / 1024.0f, 104.0f / 1024.0f, 82.0 / 1024.0f, 1.0f, 1.0f, 1);
	//enemy[i].x = xtemp + i*0.665f;
	enemy[i].x = (float)rand() / (float)RAND_MAX*2.66f - 1.33f;
	//enemy[i].y = (float)rand() / (float)RAND_MAX*2.0f - 1.0f;
	//enemy[i].y = user.y + 0.15f;

	//enemy[i].randomize();
	}*/
}
void App::resetGameLevel2(){}
void App::resetGameLevel3(){}

App::App() {
	Init();

	keys = SDL_GetKeyboardState(NULL);

	SheetSpriteTexture = LoadTexture("sheet.png", GL_RGBA);
	BulletTexture = LoadTexture("CustomShots.png", GL_RGBA);

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

	done = false;
	lastFrameTicks = 0.0f;
	enemysize = 12;

	//Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2096);
	//music = Mix_LoadMUS("Level1.mp3");

	glMatrixMode(GL_MODELVIEW);
	Matrix initial;
	glLoadMatrixf(initial.ml);

	level = GAME_LEVEL_1;
	reset();

}

void App::Init() {
	SDL_Init(SDL_INIT_VIDEO);
	displayWindow = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
	SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
	SDL_GL_MakeCurrent(displayWindow, context);

}

App::~App() {
	//Mix_FreeMusic(music);
	SDL_Quit();
}

void App::cover(){
	//glDisable(GL_TEXTURE_2D);
	GLfloat rect[] = { -1.5f, 1.5f, -1.5f, -1.5f, LEFT, -1.5f, LEFT, 1.5f,
		1.5f, -1.5f, 1.5f, 1.5f, RIGHT, 1.5f, RIGHT, -1.5f };
	glVertexPointer(2, GL_FLOAT, 0, rect);
	//glEnableClientState(GL_VERTEX_ARRAY);
	GLfloat rectcolors[] = { 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f };
	glColorPointer(4, GL_FLOAT, 0, rectcolors);
	glEnableClientState(GL_COLOR_ARRAY);
	glDrawArrays(GL_QUADS, 0, 8);
	//glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
}

void App::Render() {
	switch (level) {
	case MAIN_MENU:
		RenderMainMenu();
		break;
	case GAME_LEVEL_1:
		RenderGameLevel1();
		break;
	case GAME_LEVEL_2:
		RenderGameLevel2();
		break;
	case GAME_LEVEL_3:
		RenderGameLevel3();
		break;
	}

	SDL_GL_SwapWindow(displayWindow);
}

void App::RenderMainMenu(){

}

void App::RenderGameLevel1(){
	glClearColor(0.2f, 0.3f, 0.5f, 0.0f);

	glClear(GL_COLOR_BUFFER_BIT);

	for (unsigned int i = 0; i < user.bullets.size(); i++){
		user.bullets[i].draw();
	}
	user.draw();

	for (int i = 0; i < TOTAL_ENEMIES; i++){
		enemy[i].render();
		for (unsigned int j = 0; j < enemy[i].bullets.size(); j++){
			enemy[i].bullets[j].draw();
		}
	}

	cover();

}

void App::RenderGameLevel2(){

}

void App::RenderGameLevel3(){

}

void App::Update(float elapsed) {
	switch (level) {
	case MAIN_MENU:
		UpdateMainMenu();
		break;
	case GAME_LEVEL_1:
		UpdateGameLevel1(elapsed);
		break;
	case GAME_LEVEL_2:
		UpdateGameLevel2(elapsed);
		break;
	case GAME_LEVEL_3:
		UpdateGameLevel3(elapsed);
		break;
	}

	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
			done = true;
		}
	}
}

void App::UpdateMainMenu(){

}

void App::UpdateGameLevel1(float elapsed){
	lastshot += elapsed;
	gametime += elapsed;

	for (int i = 0; i < TOTAL_ENEMIES; i++){
		if (enemy[i].alive){
			if (collision(enemy[i], user)){
				user.y = -0.5f;
				user.x = 0.0f;
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

	user.bullets.erase(remove_if(user.bullets.begin(), user.bullets.end(), removeBullet), user.bullets.end());

	for (unsigned int i = 0; i < user.bullets.size(); i++){
		user.bullets[i].x += user.bullets[i].vector.x * elapsed;
		user.bullets[i].y += user.bullets[i].vector.y * elapsed;
		user.bullets[i].genMatrix();


		for (int j = 0; j < TOTAL_ENEMIES; j++){
			if (enemy[j].alive){
				if (collision(user.bullets[i], enemy[j])){
					enemy[j].hp -= 50.0f;
					//enemy[j].x = 0.0f;
					//enemy[j].alive = false;
					//user.bullets.erase();
					user.bullets[i].y = 100.0f;
					//user.bullets.erase(remove_if(user.bullets.begin(), user.bullets.end(), removeBullet), user.bullets.end());
					break;
				}
			}
		}


		//user.bullets[i].x += user.bullets[i].vector.x * elapsed;
		//user.bullets[i].y += user.bullets[i].vector.y * elapsed;
		//user.bullets[i].genMatrix();
	}
	//user.setVector();


	for (int i = 0; i < TOTAL_ENEMIES; i++){
		enemy[i].bullets.erase(remove_if(enemy[i].bullets.begin(), enemy[i].bullets.end(), removeBullet), enemy[i].bullets.end());

		if (enemy[i].alive && enemy[i].hp <= 0.0f){
			enemy[i].alive = false;
			enemy[i].powerup = true;
			enemy[i].textureID = BulletTexture;

			//enemy[i].shoot(BulletTexture, 831.0f / 973.0f, 76.0f / 476.0f, 11.0f / 973.0f, 22.0f / 476.0f, 2.0f, 1.5f, M_PI, 1.0f);
			//Entity(SheetSpriteTexture, 519.0f / 1024.0f, 325.0f / 1024.0f, 80.0f / 1024.0f, 84.0 / 1024.0f, 0.8f, 0.8f, stoi(ttemp));
			enemy[i].u = 229.0f / 973.0f;
			enemy[i].v = 349.0f / 476.0f;
			enemy[i].width = 12.0f / 973.0f;
			enemy[i].height = 16.0f / 476.0f;
			enemy[i].scalex = 2.0f;
			enemy[i].scaley = 1.2f;
		}

		if (enemy[i].powerup) {
			if (enemy[i].y + enemy[i].height * enemy[i].scaley < BOTTOM - 0.25f){
				enemy[i].powerup = false;
			}
			else if (enemy[i].y - enemy[i].height * enemy[i].scaley > TOP + 0.25f){
				enemy[i].powerup = false;
			}
			else if (collision(enemy[i], user)){
				enemy[i].powerup = false;
				user.power += 10.0f;
			}
			else {
				enemy[i].y -= 0.5f * elapsed;
				enemy[i].genMatrix();
			}
		}

		for (unsigned int j = 0; j < enemy[i].bullets.size(); j++){
			enemy[i].bullets[j].x += enemy[i].bullets[j].vector.x * elapsed;
			enemy[i].bullets[j].y += enemy[i].bullets[j].vector.y * elapsed;
			enemy[i].bullets[j].genMatrix();

			if (collision(enemy[i].bullets[j], user)){
				user.y = -0.5f;
				user.x = 0.0f;
				enemy[i].bullets[j].y = 100.0f;
			}
		}

		if (!enemy[i].active && !enemy[i].alive){
			if (gametime > enemy[i].start){
				enemy[i].active = true;
				enemy[i].alive = true;
			}

		}

		if (enemy[i].alive) {
			if (enemy[i].x + enemy[i].width * enemy[i].scalex < LEFT - 0.25f){
				enemy[i].alive = false;
			}
			else if (enemy[i].x - enemy[i].width * enemy[i].scalex > RIGHT + 0.25f){
				enemy[i].alive = false;
			}
			if (enemy[i].y + enemy[i].height * enemy[i].scaley < BOTTOM - 0.25f){
				enemy[i].alive = false;
			}
			else if (enemy[i].y - enemy[i].height * enemy[i].scaley > TOP + 0.25f){
				enemy[i].alive = false;
			}

			enemy[i].timeToShoot -= elapsed;

			if (enemy[i].type == 1){
				if (gametime < enemy[i].stop){
					if (enemy[i].pos == "top"){
						enemy[i].y -= enemy[i].speed * elapsed;
					}
					else if (enemy[i].pos == "left"){
						enemy[i].x += enemy[i].speed * elapsed;
					}
					else {
						enemy[i].x -= enemy[i].speed * elapsed;
					}
				}
				else if (gametime > enemy[i].resume){
					if (enemy[i].pos == "top"){
						enemy[i].y += enemy[i].speed * elapsed;
					}
					else if (enemy[i].pos == "left"){
						enemy[i].x -= enemy[i].speed * elapsed;
					}
					else {
						enemy[i].x += enemy[i].speed * elapsed;
					}
				}

				if (enemy[i].timeToShoot < 0.0f){
					enemy[i].shoot(BulletTexture, 831.0f / 973.0f, 76.0f / 476.0f, 11.0f / 973.0f, 22.0f / 476.0f, 2.0f, 1.5f, (float)M_PI, 1.0f);
					enemy[i].timeToShoot = (float)rand() / (float)RAND_MAX * 1.5f + 0.75f;
				}
				//enemy[i].x += enemy[i].speed * elapsed;

			}
			else if (enemy[i].type == 2){
				if (gametime < enemy[i].stop){
					if (enemy[i].pos == "top"){
						enemy[i].y -= enemy[i].speed * elapsed;
					}
					else if (enemy[i].pos == "left"){
						enemy[i].x += enemy[i].speed * elapsed;
					}
					else {
						enemy[i].x -= enemy[i].speed * elapsed;
					}
				}
				else if (gametime > enemy[i].resume){
					if (enemy[i].pos == "top"){
						enemy[i].y += enemy[i].speed * elapsed;
					}
					else if (enemy[i].pos == "left"){
						enemy[i].x -= enemy[i].speed * elapsed;
					}
					else {
						enemy[i].x += enemy[i].speed * elapsed;
					}
				}

			}
			else {
				enemy[i].y -= enemy[i].speed*elapsed;
			}


			enemy[i].genMatrix();
		}
	}





	if (keys[SDL_SCANCODE_LEFT]){
		/*
		if (user.x - user.width*user.scalex > -1.33){
		user.x -= 0.75f * elapsed;
		}*/
		//user.rotation += 2.5f * elapsed;
		user.x -= 1.0f * elapsed;
	}
	else if (keys[SDL_SCANCODE_RIGHT]){
		/*
		if (user.x + user.width*user.scalex < 1.33){
		user.x += 0.75f * elapsed;
		}*/
		//user.rotation -= 2.5f * elapsed;
		user.x += 1.0f * elapsed;
	}

	if (keys[SDL_SCANCODE_UP]){
		//user.x += 0.75f * user.vector.x * elapsed;
		//user.y += 0.75f * user.vector.y * elapsed;
		user.y += 1.0f * elapsed;
	}
	else if (keys[SDL_SCANCODE_DOWN]){
		//user.x -= 0.5f * user.vector.x * elapsed;
		//user.y -= 0.5f * user.vector.y * elapsed;
		user.y -= 1.0f * elapsed;
	}

	if (keys[SDL_SCANCODE_Z] && lastshot > 0.1f){
		if (user.power <= 50.0f){
			user.shoot(BulletTexture, 784.0f / 973.0f, 294.0f / 476.0f, 4.0f / 973.0f, 16.0f / 476.0f, 2.5f, 1.5f, 0.0f, 3.0f);
		}
		else if (user.power <= 300.0f) {
			user.shoot(BulletTexture, 784.0f / 973.0f, 294.0f / 476.0f, 4.0f / 973.0f, 16.0f / 476.0f, 2.5f, 1.5f, 0.0f, 3.0f, user.x - 0.025f);
			user.shoot(BulletTexture, 784.0f / 973.0f, 294.0f / 476.0f, 4.0f / 973.0f, 16.0f / 476.0f, 2.5f, 1.5f, 0.0f, 3.0f, user.x + 0.025f);
		}
		else if (user.power <= 500.0f) {
			user.shoot(BulletTexture, 172.0f / 973.0f, 33.0f / 476.0f, 18.0f / 973.0f, 24.0f / 476.0f, 1.5f, 1.0f, (float)M_PI / 9.0f, 3.0f, user.x - 0.025f);
			user.shoot(BulletTexture, 784.0f / 973.0f, 294.0f / 476.0f, 4.0f / 973.0f, 16.0f / 476.0f, 2.5f, 1.5f, 0.0f, 3.0f, user.x - 0.025f);
			user.shoot(BulletTexture, 784.0f / 973.0f, 294.0f / 476.0f, 4.0f / 973.0f, 16.0f / 476.0f, 2.5f, 1.5f, 0.0f, 3.0f, user.x + 0.025f);
			user.shoot(BulletTexture, 172.0f / 973.0f, 33.0f / 476.0f, 18.0f / 973.0f, 24.0f / 476.0f, 1.5f, 1.0f, (float)-M_PI / 9.0f, 3.0f, user.x + 0.025f);
		}
		else {
			user.shoot(BulletTexture, 172.0f / 973.0f, 33.0f / 476.0f, 18.0f / 973.0f, 24.0f / 476.0f, 1.5f, 1.0f, (float)M_PI / 9.0f, 3.0f, user.x - 0.025f);
			user.shoot(BulletTexture, 172.0f / 973.0f, 14.0f / 476.0f, 18.0f / 973.0f, 18.0f / 476.0f, 1.5f, 1.0f, (float)M_PI / 18.0f, 3.0f, user.x);
			user.shoot(BulletTexture, 784.0f / 973.0f, 294.0f / 476.0f, 4.0f / 973.0f, 16.0f / 476.0f, 2.5f, 1.5f, 0.0f, 3.0f, user.x - 0.025f);
			user.shoot(BulletTexture, 784.0f / 973.0f, 294.0f / 476.0f, 4.0f / 973.0f, 16.0f / 476.0f, 2.5f, 1.5f, 0.0f, 3.0f, user.x + 0.025f);
			user.shoot(BulletTexture, 172.0f / 973.0f, 33.0f / 476.0f, 18.0f / 973.0f, 24.0f / 476.0f, 1.5f, 1.0f, (float)-M_PI / 9.0f, 3.0f, user.x + 0.025f);
			user.shoot(BulletTexture, 172.0f / 973.0f, 14.0f / 476.0f, 18.0f / 973.0f, 18.0f / 476.0f, 1.5f, 1.0f, (float)-M_PI / 18.0f, 3.0f, user.x);
		}
		lastshot = 0.0f;
	}

}

void App::UpdateGameLevel2(float elapsed){

}

void App::UpdateGameLevel3(float elapsed){

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