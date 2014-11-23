bool collision(Entity &a, Entity b){
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

