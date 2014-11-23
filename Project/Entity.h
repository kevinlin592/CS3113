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

	GLfloat quadUVs[] = { u + 0.001f, v + 0.001f, u + 0.001f, v + height - 0.001f, u + width - 0.001f, v + height - 0.001f, u + width - 0.001f, v + 0.001f };
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
	if (alive || powerup){
		draw();
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

void Entity::shoot(GLuint textureID, float u, float v, float width, float height, float scalex, float scaley, float rot, float speed){
	Bullet newBullet(textureID, u, v, width, height, scalex, scaley);
	newBullet.x = x;
	newBullet.y = y;
	newBullet.rotation = rot;
	newBullet.setVector();
	newBullet.genMatrix();
	newBullet.vector.x *= speed;
	newBullet.vector.y *= speed;
	
	bullets.push_back(newBullet);
}

void Entity::shoot(GLuint textureID, float u, float v, float width, float height, float scalex, float scaley, float rot, float speed, float x2){
	Bullet newBullet(textureID, u, v, width, height, scalex, scaley);
	newBullet.x = x2;
	newBullet.y = y;
	newBullet.rotation = rot;
	newBullet.setVector();
	newBullet.genMatrix();
	newBullet.vector.x *= speed;
	newBullet.vector.y *= speed;

	bullets.push_back(newBullet);
}