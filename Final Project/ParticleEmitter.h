bool removeParticleEmitter(ParticleEmitter p){
	if (p.totalTime > p.maxLifetime){
		return true;
	}
	return false;
}
/*
bool removeParticle(Particle p){
	if (p.lifetime >){
		return true;
	}
	return false;
}
*/

void ParticleEmitter::Render(){
	glPushMatrix();
	glLoadIdentity();
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	vector<float> particleVertices;
	
	for (unsigned int i = 0; i < particles.size(); i++) {
		//particleVertices.push_back(particles[i].position.x);
		//particleVertices.push_back(particles[i].position.y);
		particleVertices.insert(particleVertices.end(), {particles[i].position.x, particles[i].position.y});
	}

	glVertexPointer(2, GL_FLOAT, 0, particleVertices.data());
	glEnableClientState(GL_VERTEX_ARRAY);

	vector<float> particleColors;
	for (unsigned int i = 0; i < particles.size(); i++) {
		float m = (particles[i].lifetime / maxLifetime);
		particleColors.insert(particleColors.end(), { 1.0f, 1.0f, 1.0f, lerp(1.0f, 0.0f, m) });
	}
	glColorPointer(4, GL_FLOAT, 0, particleColors.data());
	glEnableClientState(GL_COLOR_ARRAY);

	glDrawArrays(GL_POINTS, 0, particleVertices.size() / 2);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisable(GL_BLEND);
	glPopMatrix();
}
/*
void ParticleEmitter::Render(){
	glPushMatrix();
	glLoadIdentity();
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	vector<float> particleVertices;

	for (unsigned int i = 0; i < particles.size(); i++) {
		particleVertices.push_back(particles[i].position.x - sizeDeviation);
		particleVertices.push_back(particles[i].position.y + sizeDeviation);
		particleVertices.push_back(particles[i].position.x - sizeDeviation);
		particleVertices.push_back(particles[i].position.y - sizeDeviation);
		particleVertices.push_back(particles[i].position.x + sizeDeviation);
		particleVertices.push_back(particles[i].position.y - sizeDeviation);
		particleVertices.push_back(particles[i].position.x + sizeDeviation);
		particleVertices.push_back(particles[i].position.y + sizeDeviation);
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
		particleColors.push_back(lerp(1.0f, 1.0f, m));
		particleColors.push_back(lerp(1.0f, 1.0f, m));
		particleColors.push_back(lerp(1.0f, 1.0f, m));
		particleColors.push_back(lerp(1.0f, 0.0f, m));
		particleColors.push_back(lerp(1.0f, 1.0f, m));
		particleColors.push_back(lerp(1.0f, 1.0f, m));
		particleColors.push_back(lerp(1.0f, 1.0f, m));
		particleColors.push_back(lerp(1.0f, 0.0f, m));
		particleColors.push_back(lerp(1.0f, 1.0f, m));
		particleColors.push_back(lerp(1.0f, 1.0f, m));
		particleColors.push_back(lerp(1.0f, 1.0f, m));
		particleColors.push_back(lerp(1.0f, 0.0f, m));
	}
	glColorPointer(4, GL_FLOAT, 0, particleColors.data());
	glEnableClientState(GL_COLOR_ARRAY);

	//glDrawArrays(GL_POINTS, 0, particleVertices.size() / 2);
	glDrawArrays(GL_QUADS, 0, particleVertices.size() / 2);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisable(GL_BLEND);
	glPopMatrix();
}*/

void ParticleEmitter::Update(float elapsed){
	for (unsigned int i = 0; i < particles.size(); i++){
		particles[i].position.x += particles[i].velocity.x*elapsed;
		particles[i].position.y += particles[i].velocity.y*elapsed;
	}
	totalTime += elapsed;
}