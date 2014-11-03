/*
void drText(int fontTexture, string text, float size, float spacing, float r, float g, float b, float a, float x, float y) {
	glBindTexture(GL_TEXTURE_2D, fontTexture);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPushMatrix();

	Matrix translate(1.0f, 0.0f, 0.0f, x,
		0.0f, 1.0f, 0.0f, y,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
	glMultMatrixf(translate.ml);

	//glTranslatef(x, y, 0.0f);
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
	glPopMatrix();
}*/

void App::reset(){
	Mix_PlayMusic(music, 0);

	GLuint SheetSpriteTexture = LoadTexture("sheet.png", GL_RGBA);

	user = Entity(SheetSpriteTexture, 777.0f / 1024.0f, 712.0f / 1024.0f, 32.0f / 1024.0f, 26.0 / 1024.0f, 2.0f, 2.0f);

	user.x = 0.0f;
	user.y = -0.8f;

	//float xtemp = 0.3325f - 1.33f;
	for (int i = 0; i < ASTEROIDS; i++){
		asteroid[i] = Entity(SheetSpriteTexture, 224.0f / 1024.0f, 748.0f / 1024.0f, 101.0f / 1024.0f, 84.0 / 1024.0f, 1.0f, 1.0f);
		//asteroid[i].x = xtemp + i*0.665f;
		asteroid[i].x = (float)rand() / (float)RAND_MAX*2.66f - 1.33f;
		asteroid[i].y = (float)rand() / (float)RAND_MAX*2.0f - 1.0f;
		//asteroid[i].y = user.y + 0.15f;

		asteroid[i].randomize();
	}
}

App::App() {
	Init();

	keys = SDL_GetKeyboardState(NULL);

	glViewport(0, 0, 800, 600);
	glMatrixMode(GL_PROJECTION);
	//glOrtho(-1.33, 1.33, -1.0, 1.0, -1.0, 1.0);
	Matrix start(0.752f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.5f, 0.5f,
		0.0f, 0.0f, 0.0f, 1.0f);
	glMultMatrixf(start.ml);
	//glPushMatrix();

	done = false;
	lastFrameTicks = 0.0f;
	enemysize = 12;

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2096);
	music = Mix_LoadMUS("spacemusic.mp3");

	glMatrixMode(GL_MODELVIEW);
	Matrix initial;
	glLoadMatrixf(initial.ml);
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
	Mix_FreeMusic(music);
	SDL_Quit();
}

void App::Render() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glClear(GL_COLOR_BUFFER_BIT);
	RenderGameLevel();
	SDL_GL_SwapWindow(displayWindow);
}

void App::RenderGameLevel(){

	user.draw();

	for (int i = 0; i < ASTEROIDS; i++){
		asteroid[i].draw();
	}

}


void App::Update(float elapsed) {
	for (int i = 0; i < ASTEROIDS; i++){
		collision(asteroid[i],user);
	}


	if (user.x < -1.53f){
		user.x = -user.x - 0.15f;
	}
	else if (user.x > 1.53f){
		user.x = -user.x + 0.15f;
	}
	if (user.y < -1.2f){
		user.y = -user.y - 0.15f;
	}
	else if (user.y > 1.2f){
		user.y = -user.y + 0.15f;
	}


	user.genMatrix();
	user.setVector();

	for (int i = 0; i < ASTEROIDS; i++){
		if (asteroid[i].x < -1.53f){
			asteroid[i].x = -asteroid[i].x - 0.15f;
		}
		else if (asteroid[i].x > 1.53f){
			asteroid[i].x = -asteroid[i].x + 0.15f;
		}

		if (asteroid[i].y < -1.2f){
			asteroid[i].y = -asteroid[i].y - 0.15f;
		}
		else if (asteroid[i].y > 1.2f){
			asteroid[i].y = -asteroid[i].y + 0.15f;
		}

		asteroid[i].x += asteroid[i].vector.x * elapsed;
		asteroid[i].y += asteroid[i].vector.y * elapsed;

		asteroid[i].genMatrix();
	}





	if (keys[SDL_SCANCODE_LEFT]){
		/*
		if (user.x - user.width*user.scalex > -1.33){
		user.x -= 0.75f * elapsed;
		}*/
		user.rotation += 2.5f * elapsed;
	}
	else if (keys[SDL_SCANCODE_RIGHT]){
		/*
		if (user.x + user.width*user.scalex < 1.33){
		user.x += 0.75f * elapsed;
		}*/
		user.rotation -= 2.5f * elapsed;
	}

	if (keys[SDL_SCANCODE_UP]){
		user.x += 0.75f * user.vector.x * elapsed;
		user.y += 0.75f * user.vector.y * elapsed;
	}
	else if (keys[SDL_SCANCODE_DOWN]){
		user.x -= 0.5f * user.vector.x * elapsed;
		user.y -= 0.5f * user.vector.y * elapsed;
	}

	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
			done = true;
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