bool collision(Entity &a, Entity b){
	//collision(enemy,user)
	if (a.type == 102){
		if (fabs(a.x - b.x) > 0.5f || fabs(a.y - b.y) > 0.3f){
			return false;
		}
	}
	else if (a.type == 100 || a.type == 101) {
		if (fabs(a.x - b.x) > 0.2f || fabs(a.y - b.y) > 0.2f){
			return false;
		}
	}
	else if (fabs(a.x - b.x) > 0.1f || fabs(a.y - b.y) > 0.1f){
		return false;
	}
	Vector a1 = a.matrix * a.topleft;
	a1 = b.inverse * a1;
	Vector b1 = a.matrix * a.topright;
	b1 = b.inverse * b1;
	Vector c1 = a.matrix * a.bottomleft;
	c1 = b.inverse * c1;
	Vector d1 = a.matrix * a.bottomright;
	d1 = b.inverse * d1;

	Vector a2 = b.matrix * b.topleft;
	a2 = a.inverse * a2;
	Vector b2 = b.matrix * b.topright;
	b2 = a.inverse * b2;
	Vector c2 = b.matrix * b.bottomleft;
	c2 = a.inverse * c2;
	Vector d2 = b.matrix * b.bottomright;
	d2 = a.inverse * d2;


	float smallx1 = min(min(a1.x, b1.x), min(c1.x, d1.x));
	float highx1 = max(max(a1.x, b1.x), max(c1.x, d1.x));
	float smally1 = min(min(a1.y, b1.y), min(c1.y, d1.y));
	float highy1 = max(max(a1.y, b1.y), max(c1.y, d1.y));

	float smallx2 = min(min(a2.x, b2.x), min(c2.x, d2.x));
	float highx2 = max(max(a2.x, b2.x), max(c2.x, d2.x));
	float smally2 = min(min(a2.y, b2.y), min(c2.y, d2.y));
	float highy2 = max(max(a2.y, b2.y), max(c2.y, d2.y));

	if (smallx1 <= b.right && highx1 >= b.left && smally1 <= b.top && highy1 >= b.bottom &&
		smallx2 <= a.right && highx2 >= a.left && smally2 <= a.top && highy2 >= a.bottom){
		/*
		float amount = 0.02f;
		if (a.x < b.x){
		a.x -= amount;
		if (a.y < b.y){
		a.y -= amount;
		}
		else if (a.y > b.y){
		a.y += amount;
		}
		}
		else if (a.x > b.x){
		a.x += amount;
		if (a.y < b.y){
		a.y -= amount;
		}
		else if (a.y > b.y){
		a.y += amount;
		}
		}
		else {
		if (a.y < b.y){
		a.y -= amount;
		}
		else if (a.y > b.y){
		a.y += amount;
		}
		}
		*/
		return true;
	}

	return false;
}

bool collision(Bullet &a, Entity b){
	if (b.type == 102){
		if (fabs(a.x - b.x) > 0.5f || fabs(a.y - b.y) > 0.3f){
			return false;
		}
	}
	else if (b.type == 100 || b.type == 101) {
		if (fabs(a.x - b.x) > 0.2f || fabs(a.y - b.y) > 0.2f){
			return false;
		}
	}
	else if (fabs(a.x - b.x) > 0.1f || fabs(a.y - b.y) > 0.1f){
		return false;
	} 
	Vector a1 = a.matrix * a.topleft;
	a1 = b.inverse * a1;
	Vector b1 = a.matrix * a.topright;
	b1 = b.inverse * b1;
	Vector c1 = a.matrix * a.bottomleft;
	c1 = b.inverse * c1;
	Vector d1 = a.matrix * a.bottomright;
	d1 = b.inverse * d1;

	Vector a2 = b.matrix * b.topleft;
	a2 = a.inverse * a2;
	Vector b2 = b.matrix * b.topright;
	b2 = a.inverse * b2;
	Vector c2 = b.matrix * b.bottomleft;
	c2 = a.inverse * c2;
	Vector d2 = b.matrix * b.bottomright;
	d2 = a.inverse * d2;


	float smallx1 = min(min(a1.x, b1.x), min(c1.x, d1.x));
	float highx1 = max(max(a1.x, b1.x), max(c1.x, d1.x));
	float smally1 = min(min(a1.y, b1.y), min(c1.y, d1.y));
	float highy1 = max(max(a1.y, b1.y), max(c1.y, d1.y));

	float smallx2 = min(min(a2.x, b2.x), min(c2.x, d2.x));
	float highx2 = max(max(a2.x, b2.x), max(c2.x, d2.x));
	float smally2 = min(min(a2.y, b2.y), min(c2.y, d2.y));
	float highy2 = max(max(a2.y, b2.y), max(c2.y, d2.y));

	if (smallx1 <= b.right && highx1 >= b.left && smally1 <= b.top && highy1 >= b.bottom &&
		smallx2 <= a.right && highx2 >= a.left && smally2 <= a.top && highy2 >= a.bottom){
		/*
		float amount = 0.02f;
		if (a.x < b.x){
		a.x -= amount;
		if (a.y < b.y){
		a.y -= amount;
		}
		else if (a.y > b.y){
		a.y += amount;
		}
		}
		else if (a.x > b.x){
		a.x += amount;
		if (a.y < b.y){
		a.y -= amount;
		}
		else if (a.y > b.y){
		a.y += amount;
		}
		}
		else {
		if (a.y < b.y){
		a.y -= amount;
		}
		else if (a.y > b.y){
		a.y += amount;
		}
		}
		*/
		return true;
	}

	return false;
}

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

GLuint LoadTexture2(const char *image_path, GLenum format) {
	SDL_Surface *surface = IMG_Load(image_path);

	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexImage2D(GL_TEXTURE_2D, 0, 3, surface->w, surface->h, 0, format, GL_UNSIGNED_BYTE, surface->pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	SDL_FreeSurface(surface);

	return textureID;
}

float lerp(float v0, float v1, float t) {
	return (1.0f - t)*v0 + t*v1;
}

float easeOutElastic(float from, float to, float time) {
	float p = 0.3f;
	float s = p / 4.0f;
	float diff = (to - from);
	return from + diff + (diff*pow(2.0f, -10.0f*time) * sinf((time - s)*(2.0f * (float)M_PI) / p));
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

void drText(int fontTexture, string text, float size, float spacing, float r, float g, float b, float a, float x, float y) {
	glBindTexture(GL_TEXTURE_2D, fontTexture);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPushMatrix();
	glTranslatef(x, y, 0.0f);
	float texture_size = 1.0 / 16.0f;
	vector<float> vertexData;
	vector<float> texCoordData;
	vector<float> colorData;
	float closegap = 0.0f;
	for (unsigned int i = 0; i < text.size(); i++) {
		float texture_x = (float)(((int)text[i]) % 16) / 16.0f;
		float texture_y = (float)(((int)text[i]) / 16) / 16.0f;

		colorData.insert(colorData.end(), { r, g, b, a, r, g, b, a, r, g, b, a, r, g, b, a });
		if (text[i] == 'j'){
			vertexData.insert(vertexData.end(), {
				((size + spacing) * i) + (-0.5f * size) - closegap,
				0.5f * size - 0.09375f * size,
				((size + spacing) * i) + (-0.5f * size) - closegap,
				-0.5f * size - 0.09375f * size,
				((size + spacing) * i) + (0.5f * size) - closegap,
				-0.5f * size - 0.09375f * size,
				((size + spacing) * i) + (0.5f * size) - closegap,
				0.5f * size - 0.09375f * size });
				closegap += size * 0.1f;
		}
		else if (text[i] == 'g' || text[i] == 'p' || text[i] == 'q'){
			vertexData.insert(vertexData.end(), {
				((size + spacing) * i) + (-0.5f * size) - closegap,
				0.5f * size - 0.09375f * size,
				((size + spacing) * i) + (-0.5f * size) - closegap,
				-0.5f * size - 0.09375f * size,
				((size + spacing) * i) + (0.5f * size) - closegap,
				-0.5f * size - 0.09375f * size,
				((size + spacing) * i) + (0.5f * size) - closegap,
				0.5f * size - 0.09375f * size });
		}
		else if (text[i] == 'y'){
			vertexData.insert(vertexData.end(), {
				((size + spacing) * i) + (-0.5f * size) - closegap,
				0.5f * size - 0.155f * size,
				((size + spacing) * i) + (-0.5f * size) - closegap,
				-0.5f * size - 0.155f * size,
				((size + spacing) * i) + (0.5f * size) - closegap,
				-0.5f * size - 0.155f * size,
				((size + spacing) * i) + (0.5f * size) - closegap,
				0.5f * size - 0.155f * size });
		}
		else if (text[i] == 'W'){
			closegap -= size * 0.1f;
			vertexData.insert(vertexData.end(), {
				((size + spacing) * i) + (-0.5f * size) - closegap,
				0.5f * size,
				((size + spacing) * i) + (-0.5f * size) - closegap,
				-0.5f * size,
				((size + spacing) * i) + (0.5f * size) - closegap,
				-0.5f * size,
				((size + spacing) * i) + (0.5f * size) - closegap,
				0.5f * size });
				closegap -= size * 0.03f;
		}
		else {
			vertexData.insert(vertexData.end(), {
				((size + spacing) * i) + (-0.5f * size) - closegap,
				0.5f * size,
				((size + spacing) * i) + (-0.5f * size) - closegap,
				-0.5f * size,
				((size + spacing) * i) + (0.5f * size) - closegap,
				-0.5f * size,
				((size + spacing) * i) + (0.5f * size) - closegap,
				0.5f * size });
		}
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
}