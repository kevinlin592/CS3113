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

		return true;
	}

	return false;
}