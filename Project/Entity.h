void Entity::draw() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glPushMatrix();
	/*
	glTranslatef(x, y, 0.0f);
	glScalef(stretch, 1.0f, 1.0f);
	*/
	glMultMatrixf(matrix.ml);

	GLfloat quad[] = { -width * scalex, height * scaley, -width * scalex, -height * scaley,
		width * scalex, -height * scaley, width * scalex, height * scaley};
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
	glDisable(GL_BLEND);
	//glDisableClientState(GL_COLOR_ARRAY);
	glPopMatrix();
}

void Entity::draw(float posx, float posy, float newscalex, float newscaley) {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glPushMatrix();
	
	glTranslatef(posx, posy, 0.0f);
	glScalef(newscalex, newscaley, 1.0f);
	
	//glMultMatrixf(matrix.ml);

	GLfloat quad[] = { -width * scalex, height * scaley, -width * scalex, -height * scaley,
		width * scalex, -height * scaley, width * scalex, height * scaley };
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
	glDisable(GL_BLEND);
	//glDisableClientState(GL_COLOR_ARRAY);
	glPopMatrix();
}

void Entity::drawhit() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glPushMatrix();
	/*
	glTranslatef(x, y, 0.0f);
	glScalef(stretch, 1.0f, 1.0f);
	*/
	glMultMatrixf(matrix.ml);

	GLfloat quad[] = { -width * scalex, height * scaley, -width * scalex, -height * scaley,
		width * scalex, -height * scaley, width * scalex, height * scaley };
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
	
	GLfloat color[] = { 0.2f, 0.2f, 0.2f, 1.0f,
	0.2f, 0.2f, 0.2f, 1.0f,
	0.2f, 0.2f, 0.2f, 1.0f,
	0.2f, 0.2f, 0.2f, 1.0f };
	glColorPointer(4, GL_FLOAT, 0, color);
	glEnableClientState(GL_COLOR_ARRAY);
	
	glDrawArrays(GL_QUADS, 0, 4);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glDisableClientState(GL_COLOR_ARRAY);
	glPopMatrix();
}

void Entity::render(){
	if (alive || powerup){
		if (hit){
			drawhit();
		} 
		else {
			draw();
		}
	}
}

void Entity::genMatrix(){
	matrix = Matrix(scalex2, 0.0f, 0.0f, 0.0f,
		0.0f, scaley2, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);

	matrix = matrix * Matrix(cos(rotation), -sin(rotation), 0.0f, 0.0f,
		sin(rotation), cos(rotation), 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);

	matrix = matrix * Matrix(1.0f, 0.0f, 0.0f, x,
		0.0f, 1.0f, 0.0f, y,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);

	inverse = matrix.inverse();
}

void Entity::setVector(){
	vector = Vector(float(cos(rotation+ M_PI/2.0f)), float(sin(rotation + M_PI/2.0f)), 0.0f);
}

void Entity::resetXY(){
	left = -width * scalex;
	right = width * scalex;
	top = height * scaley;
	bottom = -height * scaley;
	topleft = Vector(left, top, 1.0f);
	topright = Vector(right, top, 1.0f);
	bottomleft = Vector(left, bottom, 1.0f);
	bottomright = Vector(right, bottom, 1.0f);
}

void Entity::updateVector(){
	setVector();
	vector.x *= speed;
	vector.y *= speed;
	genMatrix();
}

void Entity::randomize(){
	float size = (float)rand() / (float)RAND_MAX * 3.0f + 0.5f;
	scalex2 = size;
	scaley2 = size;
	rotation = (float)rand() / (float)RAND_MAX * 2.0f * (float)M_PI;
	setVector();
	genMatrix();

	speed = (float)rand() / (float)RAND_MAX * 0.5f + 0.25f;
	//speed = 0.0f;
	vector.x *= speed;
	vector.y *= speed;
}

void Entity::shoot(unsigned int type, GLuint textureID, float u, float v, float width, float height, float scalex, float scaley, float rot, float speed){
	Bullet newBullet(type, textureID, u, v, width, height, scalex, scaley);
	newBullet.x = x;
	newBullet.y = y;
	newBullet.rotation = rot;
	newBullet.setVector();
	newBullet.genMatrix();
	newBullet.vector.x *= speed;
	newBullet.vector.y *= speed;
	
	bullets.push_back(newBullet);
}

void Entity::shoot(unsigned int type, GLuint textureID, float u, float v, float width, float height, float scalex, float scaley, float rot, float speed, float x2){
	Bullet newBullet(type, textureID, u, v, width, height, scalex, scaley);
	newBullet.x = x2;
	newBullet.y = y;
	newBullet.rotation = rot;
	newBullet.setVector();
	newBullet.genMatrix();
	newBullet.vector.x *= speed;
	newBullet.vector.y *= speed;

	bullets.push_back(newBullet);
}

void Entity::shoot(unsigned int type, GLuint textureID, float u, float v, float width, float height, float scalex, float scaley, float rot, float speed, float x2, float y2){
	Bullet newBullet(type, textureID, u, v, width, height, scalex, scaley);
	newBullet.x = x2;
	newBullet.y = y2;
	newBullet.rotation = rot;
	newBullet.setVector();
	newBullet.genMatrix();
	newBullet.vector.x *= speed;
	newBullet.vector.y *= speed;

	bullets.push_back(newBullet);
}