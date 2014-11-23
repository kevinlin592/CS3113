bool removeBullet(Bullet b){
	if (fabs(b.y) > TOP + 0.1f || fabs(b.x) > RIGHT + 0.1f){
		return true;
	}
	return false;
}

void Bullet::draw() {
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

void Bullet::setVector(){
	vector = Vector(float(cos(rotation + M_PI / 2.0f)), float(sin(rotation + M_PI / 2.0f)), 0.0f);
}


void Bullet::genMatrix(){
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